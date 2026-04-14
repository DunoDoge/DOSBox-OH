#include "dosbox_bridge.h"
#include "platform/sdl_ohos.h"
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <native_window/external_window.h>
#include <napi/native_api.h>
#include <hilog/log.h>

#undef LOG_DOMAIN
#undef LOG_TAG
#define LOG_DOMAIN 0x0000
#define LOG_TAG "NAPI_Entry"

static bool g_callback_registered = false;
static bool g_napi_initialized = false;

static napi_value StartEmulator(napi_env env, napi_callback_info info)
{
    OH_LOG_INFO(LOG_APP, "StartEmulator called");
    bool ok = DosBoxBridge::Instance().StartEmulator();
    napi_value result;
    napi_get_boolean(env, ok, &result);
    return result;
}

static napi_value StopEmulator(napi_env env, napi_callback_info info)
{
    OH_LOG_INFO(LOG_APP, "StopEmulator called");
    DosBoxBridge::Instance().StopEmulator();
    return nullptr;
}

// Map HarmonyOS keyCode to SDL scancode.
// HarmonyOS keyCodes: A=2017..Z=2042, 0=2000..9=2009, etc.
// SDL scancodes: A=4..Z=29, 1=30..9=38, 0=39, etc.
static SDL_Scancode OHOSKeyCodeToSDLScancode(int32_t keyCode)
{
    // Letters A-Z: HarmonyOS 2017-2042 -> SDL 4-29
    if (keyCode >= 2017 && keyCode <= 2042) {
        return static_cast<SDL_Scancode>(SDL_SCANCODE_A + (keyCode - 2017));
    }
    // Digits 0-9: HarmonyOS 2000-2009 -> SDL 39,30-38
    if (keyCode == 2000) return SDL_SCANCODE_0;
    if (keyCode >= 2001 && keyCode <= 2009) {
        return static_cast<SDL_Scancode>(SDL_SCANCODE_1 + (keyCode - 2001));
    }
    // Navigation keys
    if (keyCode == 2012) return SDL_SCANCODE_UP;
    if (keyCode == 2013) return SDL_SCANCODE_DOWN;
    if (keyCode == 2014) return SDL_SCANCODE_LEFT;
    if (keyCode == 2015) return SDL_SCANCODE_RIGHT;
    // Enter, Backspace, Tab, Space, Escape
    if (keyCode == 2054) return SDL_SCANCODE_RETURN;
    if (keyCode == 2055) return SDL_SCANCODE_BACKSPACE;
    if (keyCode == 2049) return SDL_SCANCODE_TAB;
    if (keyCode == 2050) return SDL_SCANCODE_SPACE;
    if (keyCode == 2070) return SDL_SCANCODE_ESCAPE;
    // Punctuation
    if (keyCode == 2043) return SDL_SCANCODE_COMMA;
    if (keyCode == 2044) return SDL_SCANCODE_PERIOD;
    if (keyCode == 2056) return SDL_SCANCODE_GRAVE;
    if (keyCode == 2057) return SDL_SCANCODE_MINUS;
    if (keyCode == 2058) return SDL_SCANCODE_EQUALS;
    if (keyCode == 2059) return SDL_SCANCODE_LEFTBRACKET;
    if (keyCode == 2060) return SDL_SCANCODE_RIGHTBRACKET;
    if (keyCode == 2061) return SDL_SCANCODE_BACKSLASH;
    if (keyCode == 2062) return SDL_SCANCODE_SEMICOLON;
    if (keyCode == 2063) return SDL_SCANCODE_APOSTROPHE;
    if (keyCode == 2064) return SDL_SCANCODE_SLASH;
    // Modifiers
    if (keyCode == 2045) return SDL_SCANCODE_LALT;
    if (keyCode == 2046) return SDL_SCANCODE_RALT;
    if (keyCode == 2047) return SDL_SCANCODE_LSHIFT;
    if (keyCode == 2048) return SDL_SCANCODE_RSHIFT;
    if (keyCode == 2072) return SDL_SCANCODE_LCTRL;
    if (keyCode == 2073) return SDL_SCANCODE_RCTRL;
    if (keyCode == 2074) return SDL_SCANCODE_CAPSLOCK;
    // Function keys F1-F12: HarmonyOS 2090-2101 -> SDL 58-69
    if (keyCode >= 2090 && keyCode <= 2101) {
        return static_cast<SDL_Scancode>(SDL_SCANCODE_F1 + (keyCode - 2090));
    }
    // Other keys
    if (keyCode == 2068) return SDL_SCANCODE_PAGEUP;
    if (keyCode == 2069) return SDL_SCANCODE_PAGEDOWN;
    if (keyCode == 2071) return SDL_SCANCODE_DELETE;
    if (keyCode == 2083) return SDL_SCANCODE_INSERT;
    if (keyCode == 2075) return SDL_SCANCODE_SCROLLLOCK;

    OH_LOG_WARN(LOG_APP, "OHOSKeyCodeToSDLScancode: unmapped keyCode=%{public}d", keyCode);
    return SDL_SCANCODE_UNKNOWN;
}

static napi_value SendKeyEvent(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    int32_t keyCode = 0;
    int32_t down = 0;
    napi_get_value_int32(env, args[0], &keyCode);
    napi_get_value_int32(env, args[1], &down);

    SDL_Scancode scancode = OHOSKeyCodeToSDLScancode(keyCode);
    if (scancode == SDL_SCANCODE_UNKNOWN) {
        return nullptr;
    }

    OH_LOG_INFO(LOG_APP, "SendKeyEvent: keyCode=%{public}d -> scancode=%{public}d down=%{public}d", keyCode, scancode, down);
    DosBoxBridge::Instance().PushKeyEvent(scancode, scancode, down != 0);
    return nullptr;
}

// Set NativeWindow from surface ID obtained from ETS XComponent context.
// This avoids depending on OnSurfaceCreated callback which may not fire
// if callbacks are registered after the surface is already created.
static napi_value SetSurfaceId(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    // Get string surface ID from ETS
    size_t strSize = 0;
    napi_get_value_string_utf8(env, args[0], nullptr, 0, &strSize);
    if (strSize == 0) {
        OH_LOG_ERROR(LOG_APP, "SetSurfaceId: empty surface ID string");
        return nullptr;
    }
    std::string surfaceIdStr(strSize, '\0');
    napi_get_value_string_utf8(env, args[0], &surfaceIdStr[0], strSize + 1, &strSize);

    OH_LOG_INFO(LOG_APP, "SetSurfaceId: surfaceId=%{public}s", surfaceIdStr.c_str());

    // Parse surface ID string to uint64_t
    uint64_t surfaceId = 0;
    try {
        surfaceId = std::stoull(surfaceIdStr);
    } catch (...) {
        OH_LOG_ERROR(LOG_APP, "SetSurfaceId: failed to parse surface ID");
        return nullptr;
    }

    // Create NativeWindow from surface ID
    OHNativeWindow *nativeWindow = nullptr;
    int32_t ret = OH_NativeWindow_CreateNativeWindowFromSurfaceId(surfaceId, &nativeWindow);
    if (ret != 0 || !nativeWindow) {
        OH_LOG_ERROR(LOG_APP, "SetSurfaceId: CreateNativeWindowFromSurfaceId failed (ret=%{public}d)", ret);
        return nullptr;
    }

    OH_LOG_INFO(LOG_APP, "SetSurfaceId: NativeWindow created at %{public}p", nativeWindow);
    DosBoxBridge::Instance().SetNativeWindow(nativeWindow);

    return nullptr;
}

static void OnSurfaceCreatedCB(OH_NativeXComponent *component, void *window)
{
    OH_LOG_INFO(LOG_APP, "XComponent OnSurfaceCreated");
    // Only set if NativeWindow not already set via SetSurfaceId
    if (!DosBoxBridge::Instance().GetNativeWindow()) {
        OHNativeWindow *nativeWindow = static_cast<OHNativeWindow *>(window);
        DosBoxBridge::Instance().SetNativeWindow(nativeWindow);
    }
}

static void OnSurfaceChangedCB(OH_NativeXComponent *component, void *window)
{
    OH_LOG_INFO(LOG_APP, "XComponent OnSurfaceChanged");
    if (!DosBoxBridge::Instance().GetNativeWindow()) {
        OHNativeWindow *nativeWindow = static_cast<OHNativeWindow *>(window);
        DosBoxBridge::Instance().SetNativeWindow(nativeWindow);
    }
}

static void OnSurfaceDestroyedCB(OH_NativeXComponent *component, void *window)
{
    OH_LOG_INFO(LOG_APP, "XComponent OnSurfaceDestroyed");
    DosBoxBridge::Instance().SetNativeWindow(nullptr);
}

static void DispatchTouchEventCB(OH_NativeXComponent *component, void *window)
{
    OH_NativeXComponent_TouchEvent touchEvent;
    OH_NativeXComponent_GetTouchEvent(component, window, &touchEvent);

    if (touchEvent.type == OH_NATIVEXCOMPONENT_DOWN) {
        OHOS_PushSDLMouseEvent(static_cast<int>(touchEvent.x), static_cast<int>(touchEvent.y), SDL_BUTTON_LEFT, 1);
    } else if (touchEvent.type == OH_NATIVEXCOMPONENT_UP) {
        OHOS_PushSDLMouseEvent(static_cast<int>(touchEvent.x), static_cast<int>(touchEvent.y), SDL_BUTTON_LEFT, 0);
    } else if (touchEvent.type == OH_NATIVEXCOMPONENT_MOVE) {
        OHOS_PushSDLMotionEvent(static_cast<int>(touchEvent.x), static_cast<int>(touchEvent.y), 0, 0);
    }
}

static void DoRegisterXComponentCallback(OH_NativeXComponent *nativeXComponent)
{
    if (g_callback_registered) {
        OH_LOG_INFO(LOG_APP, "XComponent callback already registered, skipping");
        return;
    }

    OH_LOG_INFO(LOG_APP, "Registering XComponent callbacks...");

    OH_NativeXComponent_Callback callback = {
        .OnSurfaceCreated = OnSurfaceCreatedCB,
        .OnSurfaceChanged = OnSurfaceChangedCB,
        .OnSurfaceDestroyed = OnSurfaceDestroyedCB,
        .DispatchTouchEvent = DispatchTouchEventCB,
    };

    int32_t ret = OH_NativeXComponent_RegisterCallback(nativeXComponent, &callback);
    if (ret != 0) {
        OH_LOG_ERROR(LOG_APP, "Failed to register XComponent callback: %{public}d", ret);
        return;
    }

    g_callback_registered = true;
    OH_LOG_INFO(LOG_APP, "XComponent callback registered (ret=%{public}d)", ret);
}

// Called from ETS onLoad with the XComponent context object.
static napi_value RegisterCallback(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    OH_LOG_INFO(LOG_APP, "RegisterCallback called");

    napi_value xcomponentObj = nullptr;
    napi_status status = napi_get_named_property(env, args[0], OH_NATIVE_XCOMPONENT_OBJ, &xcomponentObj);
    if (status != napi_ok || !xcomponentObj) {
        OH_LOG_ERROR(LOG_APP, "RegisterCallback: No XComponent property (status=%{public}d)", status);
        napi_value result;
        napi_get_boolean(env, false, &result);
        return result;
    }

    OH_NativeXComponent *nativeXComponent = nullptr;
    status = napi_unwrap(env, xcomponentObj, reinterpret_cast<void **>(&nativeXComponent));
    if (status != napi_ok || !nativeXComponent) {
        OH_LOG_ERROR(LOG_APP, "RegisterCallback: unwrap failed (status=%{public}d, comp=%{public}p)",
                     status, nativeXComponent);
        napi_value result;
        napi_get_boolean(env, false, &result);
        return result;
    }

    OH_LOG_INFO(LOG_APP, "RegisterCallback: got XComponent at %{public}p", nativeXComponent);
    DoRegisterXComponentCallback(nativeXComponent);

    napi_value result;
    napi_get_boolean(env, true, &result);
    return result;
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    OH_LOG_INFO(LOG_APP, "Init called");

    if (!g_napi_initialized) {
        napi_property_descriptor desc[] = {
            {"startEmulator", nullptr, StartEmulator, nullptr, nullptr, nullptr, napi_default, nullptr},
            {"stopEmulator", nullptr, StopEmulator, nullptr, nullptr, nullptr, napi_default, nullptr},
            {"sendKeyEvent", nullptr, SendKeyEvent, nullptr, nullptr, nullptr, napi_default, nullptr},
            {"registerCallback", nullptr, RegisterCallback, nullptr, nullptr, nullptr, napi_default, nullptr},
            {"setSurfaceId", nullptr, SetSurfaceId, nullptr, nullptr, nullptr, napi_default, nullptr},
        };
        napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
        DosBoxBridge::Instance().SetEnv(env);
        g_napi_initialized = true;
        OH_LOG_INFO(LOG_APP, "NAPI properties defined");
    }

    // Do NOT register XComponent callbacks in Init.
    // Registering in Init causes crashes in libace_compatible.z.so.
    // Callbacks are registered via registerCallback() from ETS onLoad instead.

    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void *)0),
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void)
{
    napi_module_register(&demoModule);
}
