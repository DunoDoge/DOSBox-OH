#include "dosbox_bridge.h"
#include "platform/sdl_ohos.h"
#include <hilog/log.h>
#include <unistd.h>
#include <cstring>
#include <sys/mman.h>
#include <sys/stat.h>

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

    // Build command line arguments
    // Use -c "MOUNT D <path>" to pass MOUNT command directly to DOSBox.
    // The -c flag is processed by DOSBox's AUTOEXEC mechanism and is not
    // affected by -noprimaryconf, making it more reliable than config file injection.
    std::string mountCmd;
    char *argv[5] = {nullptr};
    int argc = 0;

    char arg0[] = "dosbox";
    char arg1[] = "-noprimaryconf";
    argv[argc++] = arg0;
    argv[argc++] = arg1;

    if (!sharedFolderPath_.empty()) {
        // Validate the shared folder path is accessible from C++ layer
        struct stat st;
        if (stat(sharedFolderPath_.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
            mountCmd = "MOUNT D " + std::string("\"") + sharedFolderPath_ + std::string("\"");
            OH_LOG_INFO(LOG_APP, "Mounting shared folder: '%{public}s'", mountCmd.c_str());
            static char argC1[] = "-c";
            argv[argc++] = argC1;
            argv[argc++] = const_cast<char *>(mountCmd.c_str());
        } else {
            OH_LOG_WARN(LOG_APP, "Shared folder path not accessible, skipping mount: '%{public}s'",
                        sharedFolderPath_.c_str());
        }
    } else {
        OH_LOG_INFO(LOG_APP, "No shared folder path set, skipping mount");
    }

    // Log the full command line for debugging
    OH_LOG_INFO(LOG_APP, "DOSBox args: argc=%{public}d", argc);
    for (int i = 0; i < argc; i++) {
        OH_LOG_INFO(LOG_APP, "  argv[%{public}d] = '%{public}s'", i, argv[i] ? argv[i] : "(null)");
    }

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

void DosBoxBridge::SetSharedFolderPath(const std::string &path)
{
    sharedFolderPath_ = path;
    OH_LOG_INFO(LOG_APP, "SetSharedFolderPath: '%{public}s'", path.c_str());
}

// Scale and center the source frame into the destination buffer.
// src: source pixels (ARGB8888, width*height, srcPitch stride)
// dst: destination buffer (dstWidth*dstHeight, dstStride stride)
// The source is scaled to fit the destination while maintaining aspect ratio,
// then centered with black letterboxing/pillarboxing.
static void ScaleAndCenterFrame(const uint8_t *src, int srcW, int srcH, int srcPitch,
                                uint8_t *dst, int dstW, int dstH, int dstStride)
{
    if (srcW <= 0 || srcH <= 0 || dstW <= 0 || dstH <= 0) return;

    // Calculate scaled size maintaining aspect ratio
    float scaleX = static_cast<float>(dstW) / srcW;
    float scaleY = static_cast<float>(dstH) / srcH;
    float scale = (scaleX < scaleY) ? scaleX : scaleY;

    int outW = static_cast<int>(srcW * scale);
    int outH = static_cast<int>(srcH * scale);
    if (outW <= 0) outW = 1;
    if (outH <= 0) outH = 1;

    // Center offset
    int offX = (dstW - outW) / 2;
    int offY = (dstH - outH) / 2;

    // Clear entire destination to black
    for (int y = 0; y < dstH; y++) {
        memset(dst + y * dstStride, 0, dstW * 4);
    }

    // Nearest-neighbor scaling with centering
    for (int dy = 0; dy < outH; dy++) {
        int sy = dy * srcH / outH;
        if (sy >= srcH) sy = srcH - 1;

        const uint32_t *srcRow = reinterpret_cast<const uint32_t *>(src + sy * srcPitch);
        uint32_t *dstRow = reinterpret_cast<uint32_t *>(dst + (offY + dy) * dstStride);

        for (int dx = 0; dx < outW; dx++) {
            int sx = dx * srcW / outW;
            if (sx >= srcW) sx = srcW - 1;
            dstRow[offX + dx] = srcRow[sx];
        }
    }
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

    int dstW = bufferHandle->width;
    int dstH = bufferHandle->height;
    int dstStride = bufferHandle->stride;

    // If source matches destination exactly, skip scaling for performance
    bool needsScaling = (width != dstW || height != dstH);

    if (bufferHandle->virAddr != nullptr) {
        uint8_t *dst = static_cast<uint8_t *>(bufferHandle->virAddr);
        if (needsScaling) {
            ScaleAndCenterFrame(pixels, width, height, pitch, dst, dstW, dstH, dstStride);
        } else {
            int copyWidth = width * 4;
            if (copyWidth > dstStride) copyWidth = dstStride;
            for (int y = 0; y < height; y++) {
                memcpy(dst + y * dstStride, pixels + y * pitch, copyWidth);
            }
        }
    } else if (bufferHandle->fd >= 0) {
        void *mapped = mmap(nullptr, bufferHandle->size, PROT_READ | PROT_WRITE, MAP_SHARED, bufferHandle->fd, 0);
        if (mapped != MAP_FAILED) {
            uint8_t *dst = static_cast<uint8_t *>(mapped);
            if (needsScaling) {
                ScaleAndCenterFrame(pixels, width, height, pitch, dst, dstW, dstH, dstStride);
            } else {
                int copyWidth = width * 4;
                if (copyWidth > dstStride) copyWidth = dstStride;
                for (int y = 0; y < height; y++) {
                    memcpy(dst + y * dstStride, pixels + y * pitch, copyWidth);
                }
            }
            munmap(mapped, bufferHandle->size);
        }
    }

    Region region;
    Region::Rect rect = {0, 0, static_cast<uint32_t>(dstW), static_cast<uint32_t>(dstH)};
    region.rects = &rect;
    region.rectNumber = 1;
    OH_NativeWindow_NativeWindowFlushBuffer(nativeWindow_, buffer, fenceFd, region);
}
