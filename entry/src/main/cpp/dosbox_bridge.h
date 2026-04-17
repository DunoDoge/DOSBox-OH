#ifndef DOSBOX_BRIDGE_H
#define DOSBOX_BRIDGE_H

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <native_window/external_window.h>
#include <napi/native_api.h>
#include <pthread.h>
#include <atomic>
#include <mutex>
#include <queue>
#include <cstdint>
#include <string>

class DosBoxBridge {
public:
    static DosBoxBridge &Instance();

    void SetNativeWindow(OHNativeWindow *window);
    OHNativeWindow *GetNativeWindow() const { return nativeWindow_; }

    void SetEnv(napi_env env) { env_ = env; }

    bool StartEmulator();
    void StopEmulator();
    bool IsRunning() const { return running_.load(); }

    void PushKeyEvent(int scancode, int keycode, bool down);
    void PushQuitEvent();

    void RenderFrame(const uint8_t *pixels, int width, int height, int pitch);

    void SetScreenSize(int w, int h) { screenWidth_ = w; screenHeight_ = h; }
    int GetScreenWidth() const { return screenWidth_; }
    int GetScreenHeight() const { return screenHeight_; }

    void SetSharedFolderPath(const std::string &path);
    std::string GetSharedFolderPath() const { return sharedFolderPath_; }

    void RegisterExitCallback(napi_env env, napi_value callback);
    void NotifyExit();

    void RegisterShowKeyboardCallback(napi_env env, napi_value callback);
    void NotifyShowKeyboard();

private:
    DosBoxBridge() = default;
    ~DosBoxBridge() = default;
    DosBoxBridge(const DosBoxBridge &) = delete;
    DosBoxBridge &operator=(const DosBoxBridge &) = delete;

    static void *EmulatorThreadEntry(void *arg);
    void EmulatorLoop();

    OHNativeWindow *nativeWindow_ = nullptr;
    napi_env env_ = nullptr;
    pthread_t emulatorThread_;
    std::atomic<bool> running_{false};
    std::atomic<bool> nativeWindowReady_{false};
    int screenWidth_ = 0;
    int screenHeight_ = 0;
    std::string sharedFolderPath_;
    napi_threadsafe_function exitTsfn_ = nullptr;
    napi_threadsafe_function showKeyboardTsfn_ = nullptr;
};

#endif
