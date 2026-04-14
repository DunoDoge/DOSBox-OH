#include "dosbox_bridge.h"
#include "platform/sdl_ohos.h"
#include <hilog/log.h>
#include <unistd.h>
#include <cstring>
#include <sys/mman.h>

#undef LOG_DOMAIN
#undef LOG_TAG
#define LOG_DOMAIN 0x0000
#define LOG_TAG "DosBoxBridge"

extern int dosbox_main(int argc, char *argv[]);

DosBoxBridge &DosBoxBridge::Instance()
{
    static DosBoxBridge instance;
    return instance;
}

void DosBoxBridge::SetNativeWindow(OHNativeWindow *window)
{
    nativeWindow_ = window;
    nativeWindowReady_.store(window != nullptr);
    OH_LOG_INFO(LOG_APP, "SetNativeWindow: %{public}s", window ? "set" : "null");
}

bool DosBoxBridge::StartEmulator()
{
    if (running_.load()) {
        OH_LOG_WARN(LOG_APP, "Emulator already running");
        return false;
    }

    running_.store(true);
    int ret = pthread_create(&emulatorThread_, nullptr, EmulatorThreadEntry, this);
    if (ret != 0) {
        running_.store(false);
        OH_LOG_ERROR(LOG_APP, "Failed to create emulator thread: %{public}d", ret);
        return false;
    }

    OH_LOG_INFO(LOG_APP, "Emulator thread started");
    return true;
}

void DosBoxBridge::StopEmulator()
{
    if (!running_.load()) return;

    OH_LOG_INFO(LOG_APP, "Stopping emulator...");
    running_.store(false);
    OHOS_PushSDLQuitEvent();
    pthread_join(emulatorThread_, nullptr);
    OH_LOG_INFO(LOG_APP, "Emulator thread stopped");
}

void *DosBoxBridge::EmulatorThreadEntry(void *arg)
{
    DosBoxBridge *bridge = static_cast<DosBoxBridge *>(arg);
    bridge->EmulatorLoop();
    return nullptr;
}

void DosBoxBridge::EmulatorLoop()
{
    OH_LOG_INFO(LOG_APP, "DosBox main loop starting...");

    char arg0[] = "dosbox";
    char arg1[] = "-noprimaryconf";
    char *argv[] = {arg0, arg1, nullptr};
    int argc = 2;

    int ret = dosbox_main(argc, argv);

    running_.store(false);
    OH_LOG_INFO(LOG_APP, "DosBox main loop exited with code %{public}d", ret);
}

void DosBoxBridge::PushKeyEvent(int scancode, int keycode, bool down)
{
    OHOS_PushSDLKeyEvent(static_cast<SDL_Scancode>(scancode), static_cast<SDL_Keycode>(keycode), 0, down ? 1 : 0);
}

void DosBoxBridge::PushQuitEvent()
{
    OHOS_PushSDLQuitEvent();
}

void DosBoxBridge::RenderFrame(const uint8_t *pixels, int width, int height, int pitch)
{
    if (!nativeWindowReady_.load() || !nativeWindow_ || !pixels) return;

    OHNativeWindowBuffer *buffer = nullptr;
    int fenceFd = -1;
    int32_t ret = OH_NativeWindow_NativeWindowRequestBuffer(nativeWindow_, &buffer, &fenceFd);
    if (ret != 0 || !buffer) return;

    BufferHandle *bufferHandle = OH_NativeWindow_GetBufferHandleFromNative(buffer);
    if (!bufferHandle) return;

    if (bufferHandle->virAddr != nullptr) {
        uint8_t *dst = static_cast<uint8_t *>(bufferHandle->virAddr);
        int dstStride = bufferHandle->stride;
        int copyWidth = width * 4;
        if (copyWidth > dstStride) copyWidth = dstStride;

        for (int y = 0; y < height && y < bufferHandle->height; y++) {
            memcpy(dst + y * dstStride, pixels + y * pitch, copyWidth);
        }
    } else if (bufferHandle->fd >= 0) {
        void *mapped = mmap(nullptr, bufferHandle->size, PROT_READ | PROT_WRITE, MAP_SHARED, bufferHandle->fd, 0);
        if (mapped != MAP_FAILED) {
            uint8_t *dst = static_cast<uint8_t *>(mapped);
            int dstStride = bufferHandle->stride;
            int copyWidth = width * 4;
            if (copyWidth > dstStride) copyWidth = dstStride;

            for (int y = 0; y < height && y < bufferHandle->height; y++) {
                memcpy(dst + y * dstStride, pixels + y * pitch, copyWidth);
            }
            munmap(mapped, bufferHandle->size);
        }
    }

    Region region;
    Region::Rect rect = {0, 0, static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
    region.rects = &rect;
    region.rectNumber = 1;
    OH_NativeWindow_NativeWindowFlushBuffer(nativeWindow_, buffer, fenceFd, region);
}
