#include "sdl_ohos.h"
#include <cstring>
#include <queue>
#include <hilog/log.h>

#undef LOG_DOMAIN
#undef LOG_TAG
#define LOG_DOMAIN 0x0000
#define LOG_TAG "SDL_OHOS"

static std::queue<SDL_Event> g_event_queue;
static SDL_mutex *g_event_mutex = nullptr;
static uint32_t g_next_user_event = SDL_USEREVENT;
static SDL_Keymod g_mod_state = KMOD_NONE;
static int g_mouse_x = 0, g_mouse_y = 0;
static uint8_t g_mouse_buttons = 0;

static void ensure_event_mutex()
{
    if (!g_event_mutex) {
        g_event_mutex = SDL_CreateMutex();
    }
}

extern "C" void OHOS_PushSDLKeyEvent(SDL_Scancode scancode, SDL_Keycode keycode, uint16_t mod, uint8_t down)
{
    ensure_event_mutex();
    SDL_Event event;
    memset(&event, 0, sizeof(event));
    event.type = down ? SDL_KEYDOWN : SDL_KEYUP;
    event.key.keysym.scancode = scancode;
    event.key.keysym.sym = keycode;
    event.key.keysym.mod = mod;
    event.key.state = down ? SDL_PRESSED : SDL_RELEASED;
    event.key.repeat = 0;
    SDL_LockMutex(g_event_mutex);
    g_event_queue.push(event);
    SDL_UnlockMutex(g_event_mutex);
}

extern "C" void OHOS_PushSDLMouseEvent(int x, int y, uint8_t button, uint8_t down)
{
    ensure_event_mutex();
    SDL_Event event;
    memset(&event, 0, sizeof(event));
    g_mouse_x = x;
    g_mouse_y = y;
    if (down) {
        event.type = SDL_MOUSEBUTTONDOWN;
        event.button.button = button;
        event.button.state = SDL_PRESSED;
    } else {
        event.type = SDL_MOUSEBUTTONUP;
        event.button.button = button;
        event.button.state = SDL_RELEASED;
    }
    event.button.x = x;
    event.button.y = y;
    event.button.clicks = 1;
    SDL_LockMutex(g_event_mutex);
    g_event_queue.push(event);
    SDL_UnlockMutex(g_event_mutex);
}

extern "C" void OHOS_PushSDLMotionEvent(int x, int y, int xrel, int yrel)
{
    ensure_event_mutex();
    SDL_Event event;
    memset(&event, 0, sizeof(event));
    event.type = SDL_MOUSEMOTION;
    event.motion.x = x;
    event.motion.y = y;
    event.motion.xrel = xrel;
    event.motion.yrel = yrel;
    event.motion.state = g_mouse_buttons;
    g_mouse_x = x;
    g_mouse_y = y;
    SDL_LockMutex(g_event_mutex);
    g_event_queue.push(event);
    SDL_UnlockMutex(g_event_mutex);
}

extern "C" void OHOS_PushSDLQuitEvent()
{
    ensure_event_mutex();
    SDL_Event event;
    memset(&event, 0, sizeof(event));
    event.type = SDL_QUIT;
    SDL_LockMutex(g_event_mutex);
    g_event_queue.push(event);
    SDL_UnlockMutex(g_event_mutex);
}

int SDL_PollEvent(SDL_Event *event)
{
    if (!event) return 0;
    ensure_event_mutex();
    SDL_LockMutex(g_event_mutex);
    if (g_event_queue.empty()) {
        SDL_UnlockMutex(g_event_mutex);
        return 0;
    }
    *event = g_event_queue.front();
    g_event_queue.pop();
    SDL_UnlockMutex(g_event_mutex);
    return 1;
}

int SDL_WaitEvent(SDL_Event *event)
{
    if (!event) return 0;
    while (1) {
        if (SDL_PollEvent(event)) return 1;
        SDL_Delay(10);
    }
}

void SDL_PumpEvents()
{
}

int SDL_PushEvent(SDL_Event *event)
{
    if (!event) return -1;
    ensure_event_mutex();
    SDL_LockMutex(g_event_mutex);
    g_event_queue.push(*event);
    SDL_UnlockMutex(g_event_mutex);
    return 1;
}

uint32_t SDL_RegisterEvents(int numevents)
{
    uint32_t base = g_next_user_event;
    g_next_user_event += numevents;
    return base;
}

void SDL_SetEventFilter(SDL_EventFilter filter, void *userdata)
{
}

uint8_t SDL_GetMouseState(int *x, int *y)
{
    if (x) *x = g_mouse_x;
    if (y) *y = g_mouse_y;
    return g_mouse_buttons;
}

int SDL_SetRelativeMouseMode(int enabled)
{
    return 0;
}

int SDL_ShowCursor(int toggle)
{
    return 0;
}

SDL_Keymod SDL_GetModState()
{
    return g_mod_state;
}

const char *SDL_GetScancodeName(SDL_Scancode scancode)
{
    return "Unknown";
}

void SDL_StartTextInput()
{
}

void SDL_StopTextInput()
{
}

typedef struct SDL_Joystick {
    int index;
} SDL_Joystick;

SDL_Joystick *SDL_JoystickOpen(int device_index)
{
    return nullptr;
}

void SDL_JoystickClose(SDL_Joystick *joystick)
{
}

void SDL_JoystickUpdate()
{
}

int SDL_JoystickInstanceID(SDL_Joystick *joystick)
{
    return -1;
}

int SDL_JoystickNumAxes(SDL_Joystick *joystick)
{
    return 0;
}

int SDL_JoystickNumHats(SDL_Joystick *joystick)
{
    return 0;
}

int SDL_JoystickNumButtons(SDL_Joystick *joystick)
{
    return 0;
}

uint8_t SDL_JoystickGetButton(SDL_Joystick *joystick, int button)
{
    return 0;
}

int16_t SDL_JoystickGetAxis(SDL_Joystick *joystick, int axis)
{
    return 0;
}

uint8_t SDL_JoystickGetHat(SDL_Joystick *joystick, int hat)
{
    return SDL_HAT_CENTERED;
}

const char *SDL_JoystickNameForIndex(int device_index)
{
    return nullptr;
}

SDL_bool SDL_JoystickHasLED(SDL_Joystick *joystick)
{
    return SDL_FALSE;
}

int SDL_JoystickSetLED(SDL_Joystick *joystick, uint8_t red, uint8_t green, uint8_t blue)
{
    return -1;
}

SDL_AudioDeviceID SDL_OpenAudioDevice(const char *device, int iscapture, const SDL_AudioSpec *desired, SDL_AudioSpec *obtained, int allowed_changes)
{
    if (obtained && desired) {
        *obtained = *desired;
    }
    return 1;
}

void SDL_CloseAudioDevice(SDL_AudioDeviceID dev)
{
}

void SDL_PauseAudioDevice(SDL_AudioDeviceID dev, int pause_on)
{
}

const char *SDL_GetCurrentAudioDriver()
{
    return "ohaudio";
}

SDL_RWops *SDL_AllocRW()
{
    SDL_RWops *rw = (SDL_RWops *)calloc(1, sizeof(SDL_RWops));
    return rw;
}

void SDL_FreeRW(SDL_RWops *area)
{
    free(area);
}

size_t SDL_RWread(SDL_RWops *ctx, void *ptr, size_t size, size_t maxnum)
{
    if (!ctx || !ctx->read) return 0;
    return ctx->read(ctx, ptr, size, maxnum);
}

int64_t SDL_RWseek(SDL_RWops *ctx, int64_t offset, int whence)
{
    if (!ctx || !ctx->seek) return -1;
    return ctx->seek(ctx, offset, whence);
}

int64_t SDL_RWtell(SDL_RWops *ctx)
{
    return SDL_RWseek(ctx, 0, RW_SEEK_CUR);
}

int SDL_RWclose(SDL_RWops *ctx)
{
    if (!ctx) return -1;
    if (ctx->close) return ctx->close(ctx);
    SDL_FreeRW(ctx);
    return 0;
}

int SDL_GL_SetAttribute(SDL_GLattr attr, int value)
{
    return 0;
}

void SDL_GL_ResetAttributes()
{
}

void *SDL_GL_CreateContext(SDL_Window *window)
{
    return (void *)1;
}

void SDL_GL_DeleteContext(void *context)
{
}

void *SDL_GL_GetProcAddress(const char *proc)
{
    return nullptr;
}

void SDL_GL_GetDrawableSize(SDL_Window *window, int *w, int *h)
{
    SDL_GetWindowSize(window, w, h);
}

int SDL_GL_SwapWindow(SDL_Window *window)
{
    return 0;
}

int SDL_GL_SetSwapInterval(int interval)
{
    return 0;
}
