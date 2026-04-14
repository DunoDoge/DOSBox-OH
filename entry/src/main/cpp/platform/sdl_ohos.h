#ifndef SDL_OHOS_H
#define SDL_OHOS_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef uint8_t Uint8;
typedef int8_t Sint8;
typedef uint16_t Uint16;
typedef int16_t Sint16;
typedef uint32_t Uint32;
typedef int32_t Sint32;
typedef uint64_t Uint64;
typedef int64_t Sint64;

#define SDL_MAJOR_VERSION 2
#define SDL_MINOR_VERSION 0
#define SDL_PATCHLEVEL 26

typedef uint32_t SDL_InitFlags;
#define SDL_INIT_TIMER      0x00000001
#define SDL_INIT_AUDIO      0x00000010
#define SDL_INIT_VIDEO      0x00000020
#define SDL_INIT_JOYSTICK   0x00000200
#define SDL_INIT_HAPTIC     0x00001000
#define SDL_INIT_GAMECONTROLLER 0x00002000
#define SDL_INIT_EVENTS     0x00004000
#define SDL_INIT_NOPARACHUTE 0x00100000
#define SDL_INIT_EVERYTHING (SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_HAPTIC|SDL_INIT_GAMECONTROLLER|SDL_INIT_EVENTS)

typedef int32_t SDL_bool;
#define SDL_TRUE  1
#define SDL_FALSE 0

typedef enum {
    SDL_FIRSTEVENT = 0,
    SDL_QUIT = 0x100,
    SDL_WINDOWEVENT = 0x200,
    SDL_SYSWMEVENT,
    SDL_KEYDOWN = 0x300,
    SDL_KEYUP,
    SDL_TEXTEDITING,
    SDL_TEXTINPUT,
    SDL_MOUSEMOTION = 0x400,
    SDL_MOUSEBUTTONDOWN,
    SDL_MOUSEBUTTONUP,
    SDL_MOUSEWHEEL,
    SDL_JOYAXISMOTION = 0x600,
    SDL_JOYBALLMOTION,
    SDL_JOYHATMOTION,
    SDL_JOYBUTTONDOWN,
    SDL_JOYBUTTONUP,
    SDL_JOYDEVICEADDED,
    SDL_JOYDEVICEREMOVED,
    SDL_CONTROLLERAXISMOTION = 0x650,
    SDL_CONTROLLERBUTTONDOWN,
    SDL_CONTROLLERBUTTONUP,
    SDL_CONTROLLERDEVICEADDED,
    SDL_CONTROLLERDEVICEREMOVED,
    SDL_CONTROLLERDEVICEREMAPPED,
    SDL_FINGERDOWN = 0x700,
    SDL_FINGERUP,
    SDL_FINGERMOTION,
    SDL_DOLLARGESTROKE = 0x800,
    SDL_DOLLARGESTART,
    SDL_DOLLARRECORD,
    SDL_MULTIGESTURE,
    SDL_CLIPBOARDUPDATE = 0x900,
    SDL_DROPFILE = 0x1000,
    SDL_DISPLAYEVENT = 0x150,
    SDL_USEREVENT = 0x8000,
    SDL_LASTEVENT = 0xFFFF
} SDL_EventType;

typedef enum {
    SDL_WINDOWEVENT_NONE,
    SDL_WINDOWEVENT_SHOWN,
    SDL_WINDOWEVENT_HIDDEN,
    SDL_WINDOWEVENT_EXPOSED,
    SDL_WINDOWEVENT_MOVED,
    SDL_WINDOWEVENT_RESIZED,
    SDL_WINDOWEVENT_SIZE_CHANGED,
    SDL_WINDOWEVENT_MINIMIZED,
    SDL_WINDOWEVENT_MAXIMIZED,
    SDL_WINDOWEVENT_RESTORED,
    SDL_WINDOWEVENT_ENTER,
    SDL_WINDOWEVENT_LEAVE,
    SDL_WINDOWEVENT_FOCUS_GAINED,
    SDL_WINDOWEVENT_FOCUS_LOST,
    SDL_WINDOWEVENT_CLOSE,
    SDL_WINDOWEVENT_TAKE_FOCUS,
    SDL_WINDOWEVENT_HIT_TEST,
    SDL_WINDOWEVENT_ICCPROF_CHANGED,
    SDL_WINDOWEVENT_DISPLAY_CHANGED
} SDL_WindowEventID;

typedef enum {
    SDL_SCANCODE_UNKNOWN = 0,
    SDL_SCANCODE_A = 4,
    SDL_SCANCODE_B = 5,
    SDL_SCANCODE_C = 6,
    SDL_SCANCODE_D = 7,
    SDL_SCANCODE_E = 8,
    SDL_SCANCODE_F = 9,
    SDL_SCANCODE_G = 10,
    SDL_SCANCODE_H = 11,
    SDL_SCANCODE_I = 12,
    SDL_SCANCODE_J = 13,
    SDL_SCANCODE_K = 14,
    SDL_SCANCODE_L = 15,
    SDL_SCANCODE_M = 16,
    SDL_SCANCODE_N = 17,
    SDL_SCANCODE_O = 18,
    SDL_SCANCODE_P = 19,
    SDL_SCANCODE_Q = 20,
    SDL_SCANCODE_R = 21,
    SDL_SCANCODE_S = 22,
    SDL_SCANCODE_T = 23,
    SDL_SCANCODE_U = 24,
    SDL_SCANCODE_V = 25,
    SDL_SCANCODE_W = 26,
    SDL_SCANCODE_X = 27,
    SDL_SCANCODE_Y = 28,
    SDL_SCANCODE_Z = 29,
    SDL_SCANCODE_1 = 30,
    SDL_SCANCODE_2 = 31,
    SDL_SCANCODE_3 = 32,
    SDL_SCANCODE_4 = 33,
    SDL_SCANCODE_5 = 34,
    SDL_SCANCODE_6 = 35,
    SDL_SCANCODE_7 = 36,
    SDL_SCANCODE_8 = 37,
    SDL_SCANCODE_9 = 38,
    SDL_SCANCODE_0 = 39,
    SDL_SCANCODE_RETURN = 40,
    SDL_SCANCODE_ESCAPE = 41,
    SDL_SCANCODE_BACKSPACE = 42,
    SDL_SCANCODE_TAB = 43,
    SDL_SCANCODE_SPACE = 44,
    SDL_SCANCODE_MINUS = 45,
    SDL_SCANCODE_EQUALS = 46,
    SDL_SCANCODE_LEFTBRACKET = 47,
    SDL_SCANCODE_RIGHTBRACKET = 48,
    SDL_SCANCODE_BACKSLASH = 49,
    SDL_SCANCODE_NONUSHASH = 50,
    SDL_SCANCODE_SEMICOLON = 51,
    SDL_SCANCODE_APOSTROPHE = 52,
    SDL_SCANCODE_GRAVE = 53,
    SDL_SCANCODE_COMMA = 54,
    SDL_SCANCODE_PERIOD = 55,
    SDL_SCANCODE_SLASH = 56,
    SDL_SCANCODE_CAPSLOCK = 57,
    SDL_SCANCODE_F1 = 58,
    SDL_SCANCODE_F2 = 59,
    SDL_SCANCODE_F3 = 60,
    SDL_SCANCODE_F4 = 61,
    SDL_SCANCODE_F5 = 62,
    SDL_SCANCODE_F6 = 63,
    SDL_SCANCODE_F7 = 64,
    SDL_SCANCODE_F8 = 65,
    SDL_SCANCODE_F9 = 66,
    SDL_SCANCODE_F10 = 67,
    SDL_SCANCODE_F11 = 68,
    SDL_SCANCODE_F12 = 69,
    SDL_SCANCODE_PRINTSCREEN = 70,
    SDL_SCANCODE_SCROLLLOCK = 71,
    SDL_SCANCODE_PAUSE = 72,
    SDL_SCANCODE_INSERT = 73,
    SDL_SCANCODE_HOME = 74,
    SDL_SCANCODE_PAGEUP = 75,
    SDL_SCANCODE_DELETE = 76,
    SDL_SCANCODE_END = 77,
    SDL_SCANCODE_PAGEDOWN = 78,
    SDL_SCANCODE_RIGHT = 79,
    SDL_SCANCODE_LEFT = 80,
    SDL_SCANCODE_DOWN = 81,
    SDL_SCANCODE_UP = 82,
    SDL_SCANCODE_NUMLOCKCLEAR = 83,
    SDL_SCANCODE_KP_DIVIDE = 84,
    SDL_SCANCODE_KP_MULTIPLY = 85,
    SDL_SCANCODE_KP_MINUS = 86,
    SDL_SCANCODE_KP_PLUS = 87,
    SDL_SCANCODE_KP_ENTER = 88,
    SDL_SCANCODE_KP_1 = 89,
    SDL_SCANCODE_KP_2 = 90,
    SDL_SCANCODE_KP_3 = 91,
    SDL_SCANCODE_KP_4 = 92,
    SDL_SCANCODE_KP_5 = 93,
    SDL_SCANCODE_KP_6 = 94,
    SDL_SCANCODE_KP_7 = 95,
    SDL_SCANCODE_KP_8 = 96,
    SDL_SCANCODE_KP_9 = 97,
    SDL_SCANCODE_KP_0 = 98,
    SDL_SCANCODE_KP_PERIOD = 99,
    SDL_SCANCODE_LCTRL = 224,
    SDL_SCANCODE_LSHIFT = 225,
    SDL_SCANCODE_LALT = 226,
    SDL_SCANCODE_LGUI = 227,
    SDL_SCANCODE_RCTRL = 228,
    SDL_SCANCODE_RSHIFT = 229,
    SDL_SCANCODE_RALT = 230,
    SDL_SCANCODE_RGUI = 231,
    SDL_SCANCODE_NONUSBACKSLASH = 100,
    SDL_SCANCODE_INTERNATIONAL1 = 135,
    SDL_NUM_SCANCODES = 512
} SDL_Scancode;

typedef enum {
    SDLK_UNKNOWN = 0,
    SDLK_RETURN = '\r',
    SDLK_ESCAPE = '\033',
    SDLK_BACKSPACE = '\b',
    SDLK_TAB = '\t',
    SDLK_SPACE = ' ',
    SDLK_EXCLAIM = '!',
    SDLK_QUOTEDBL = '"',
    SDLK_HASH = '#',
    SDLK_DOLLAR = '$',
    SDLK_PERCENT = '%',
    SDLK_AMPERSAND = '&',
    SDLK_APOSTROPHE = '\'',
    SDLK_LEFTPAREN = '(',
    SDLK_RIGHTPAREN = ')',
    SDLK_ASTERISK = '*',
    SDLK_PLUS = '+',
    SDLK_COMMA = ',',
    SDLK_MINUS = '-',
    SDLK_PERIOD = '.',
    SDLK_SLASH = '/',
    SDLK_0 = '0',
    SDLK_1 = '1',
    SDLK_2 = '2',
    SDLK_3 = '3',
    SDLK_4 = '4',
    SDLK_5 = '5',
    SDLK_6 = '6',
    SDLK_7 = '7',
    SDLK_8 = '8',
    SDLK_9 = '9',
    SDLK_COLON = ':',
    SDLK_SEMICOLON = ';',
    SDLK_LESS = '<',
    SDLK_EQUALS = '=',
    SDLK_GREATER = '>',
    SDLK_QUESTION = '?',
    SDLK_AT = '@',
    SDLK_LEFTBRACKET = '[',
    SDLK_BACKSLASH = '\\',
    SDLK_RIGHTBRACKET = ']',
    SDLK_CARET = '^',
    SDLK_UNDERSCORE = '_',
    SDLK_BACKQUOTE = '`',
    SDLK_a = 'a',
    SDLK_b = 'b',
    SDLK_c = 'c',
    SDLK_d = 'd',
    SDLK_e = 'e',
    SDLK_f = 'f',
    SDLK_g = 'g',
    SDLK_h = 'h',
    SDLK_i = 'i',
    SDLK_j = 'j',
    SDLK_k = 'k',
    SDLK_l = 'l',
    SDLK_m = 'm',
    SDLK_n = 'n',
    SDLK_o = 'o',
    SDLK_p = 'p',
    SDLK_q = 'q',
    SDLK_r = 'r',
    SDLK_s = 's',
    SDLK_t = 't',
    SDLK_u = 'u',
    SDLK_v = 'v',
    SDLK_w = 'w',
    SDLK_x = 'x',
    SDLK_y = 'y',
    SDLK_z = 'z',
    SDLK_F1 = (1 << 30) | 58,
    SDLK_F2 = (1 << 30) | 59,
    SDLK_F3 = (1 << 30) | 60,
    SDLK_F4 = (1 << 30) | 61,
    SDLK_F5 = (1 << 30) | 62,
    SDLK_F6 = (1 << 30) | 63,
    SDLK_F7 = (1 << 30) | 64,
    SDLK_F8 = (1 << 30) | 65,
    SDLK_F9 = (1 << 30) | 66,
    SDLK_F10 = (1 << 30) | 67,
    SDLK_F11 = (1 << 30) | 68,
    SDLK_F12 = (1 << 30) | 69,
    SDLK_INSERT = (1 << 30) | 73,
    SDLK_HOME = (1 << 30) | 74,
    SDLK_PAGEUP = (1 << 30) | 75,
    SDLK_DELETE = '\177',
    SDLK_END = (1 << 30) | 77,
    SDLK_PAGEDOWN = (1 << 30) | 78,
    SDLK_RIGHT = (1 << 30) | 79,
    SDLK_LEFT = (1 << 30) | 80,
    SDLK_DOWN = (1 << 30) | 81,
    SDLK_UP = (1 << 30) | 82,
    SDLK_KP_ENTER = (1 << 30) | 88,
    SDLK_LCTRL = (1 << 30) | 224,
    SDLK_LSHIFT = (1 << 30) | 225,
    SDLK_LALT = (1 << 30) | 226,
    SDLK_RCTRL = (1 << 30) | 228,
    SDLK_RSHIFT = (1 << 30) | 229,
    SDLK_RALT = (1 << 30) | 230,
    SDLK_CAPSLOCK = (1 << 30) | 57,
    SDLK_NUMLOCKCLEAR = (1 << 30) | 83,
    SDLK_SCROLLLOCK = (1 << 30) | 71,
    SDLK_PAUSE = (1 << 30) | 72,
    SDLK_PRINTSCREEN = (1 << 30) | 70
} SDL_Keycode;

typedef enum {
    KMOD_NONE = 0x0000,
    KMOD_LSHIFT = 0x0001,
    KMOD_RSHIFT = 0x0002,
    KMOD_LCTRL = 0x0040,
    KMOD_RCTRL = 0x0080,
    KMOD_LALT = 0x0100,
    KMOD_RALT = 0x0200,
    KMOD_LGUI = 0x0400,
    KMOD_RGUI = 0x0800,
    KMOD_NUM = 0x1000,
    KMOD_CAPS = 0x2000,
    KMOD_MODE = 0x4000,
    KMOD_CTRL = KMOD_LCTRL | KMOD_RCTRL,
    KMOD_SHIFT = KMOD_LSHIFT | KMOD_RSHIFT,
    KMOD_ALT = KMOD_LALT | KMOD_RALT,
    KMOD_GUI = KMOD_LGUI | KMOD_RGUI
} SDL_Keymod;

typedef enum {
    SDL_PIXELFORMAT_UNKNOWN = 0,
    SDL_PIXELFORMAT_INDEX8 = 0x20000000,
    SDL_PIXELFORMAT_RGB332 = 0x14110801,
    SDL_PIXELFORMAT_RGB444 = 0x12100c02,
    SDL_PIXELFORMAT_RGB555 = 0x15130f02,
    SDL_PIXELFORMAT_BGR555 = 0x15550f02,
    SDL_PIXELFORMAT_ARGB4444 = 0x15321002,
    SDL_PIXELFORMAT_RGBA4444 = 0x15421002,
    SDL_PIXELFORMAT_ABGR4444 = 0x21321002,
    SDL_PIXELFORMAT_BGRA4444 = 0x21421002,
    SDL_PIXELFORMAT_RGB565 = 0x15151002,
    SDL_PIXELFORMAT_BGR565 = 0x15551002,
    SDL_PIXELFORMAT_RGB24 = 0x17101803,
    SDL_PIXELFORMAT_BGR24 = 0x17401803,
    SDL_PIXELFORMAT_RGB888 = 0x16161804,
    SDL_PIXELFORMAT_BGRX8888 = 0x16661804,
    SDL_PIXELFORMAT_ARGB8888 = 0x16362004,
    SDL_PIXELFORMAT_RGBA8888 = 0x16462004,
    SDL_PIXELFORMAT_ABGR8888 = 0x20772004,
    SDL_PIXELFORMAT_BGRA8888 = 0x20872004
} SDL_PixelFormatEnum;

typedef enum {
    SDL_BLENDMODE_NONE = 0,
    SDL_BLENDMODE_BLEND = 1,
    SDL_BLENDMODE_ADD = 2,
    SDL_BLENDMODE_MOD = 4,
    SDL_BLENDMODE_MUL = 8
} SDL_BlendMode;

typedef enum {
    SDL_TEXTUREACCESS_STATIC,
    SDL_TEXTUREACCESS_STREAMING,
    SDL_TEXTUREACCESS_TARGET
} SDL_TextureAccess;

typedef enum {
    SDL_SCALEMODE_NEAREST = 0,
    SDL_SCALEMODE_LINEAR = 1,
    SDL_SCALEMODE_BEST = 2
} SDL_ScaleMode;

typedef enum {
    SDL_RENDERER_SOFTWARE = 0x00000001,
    SDL_RENDERER_ACCELERATED = 0x00000002,
    SDL_RENDERER_PRESENTVSYNC = 0x00000004,
    SDL_RENDERER_TARGETTEXTURE = 0x00000008
} SDL_RendererFlags;

typedef enum {
    SDL_WINDOW_FULLSCREEN = 0x00000001,
    SDL_WINDOW_OPENGL = 0x00000002,
    SDL_WINDOW_SHOWN = 0x00000004,
    SDL_WINDOW_HIDDEN = 0x00000008,
    SDL_WINDOW_BORDERLESS = 0x00000010,
    SDL_WINDOW_RESIZABLE = 0x00000020,
    SDL_WINDOW_MINIMIZED = 0x00000040,
    SDL_WINDOW_MAXIMIZED = 0x00000080,
    SDL_WINDOW_INPUT_GRABBED = 0x00000100,
    SDL_WINDOW_INPUT_FOCUS = 0x00000200,
    SDL_WINDOW_MOUSE_FOCUS = 0x00000400,
    SDL_WINDOW_FULLSCREEN_DESKTOP = 0x00001001,
    SDL_WINDOW_FOREIGN = 0x00000800,
    SDL_WINDOW_ALLOW_HIGHDPI = 0x00002000,
    SDL_WINDOW_MOUSE_CAPTURE = 0x00004000,
    SDL_WINDOW_ALWAYS_ON_TOP = 0x00008000,
    SDL_WINDOW_SKIP_TASKBAR = 0x00010000,
    SDL_WINDOW_UTILITY = 0x00020000,
    SDL_WINDOW_TOOLTIP = 0x00040000,
    SDL_WINDOW_POPUP_MENU = 0x00080000,
    SDL_WINDOW_KEYBOARD_GRABBED = 0x00100000,
    SDL_WINDOW_VULKAN = 0x10000000,
    SDL_WINDOW_METAL = 0x20000000
} SDL_WindowFlags;

typedef enum {
    SDL_GL_RED_SIZE,
    SDL_GL_GREEN_SIZE,
    SDL_GL_BLUE_SIZE,
    SDL_GL_ALPHA_SIZE,
    SDL_GL_BUFFER_SIZE,
    SDL_GL_DOUBLEBUFFER,
    SDL_GL_DEPTH_SIZE,
    SDL_GL_STENCIL_SIZE,
    SDL_GL_ACCUM_RED_SIZE,
    SDL_GL_ACCUM_GREEN_SIZE,
    SDL_GL_ACCUM_BLUE_SIZE,
    SDL_GL_ACCUM_ALPHA_SIZE,
    SDL_GL_STEREO,
    SDL_GL_MULTISAMPLEBUFFERS,
    SDL_GL_MULTISAMPLESAMPLES,
    SDL_GL_ACCELERATED_VISUAL,
    SDL_GL_RETAINED_BACKING,
    SDL_GL_CONTEXT_MAJOR_VERSION,
    SDL_GL_CONTEXT_MINOR_VERSION,
    SDL_GL_CONTEXT_EGL,
    SDL_GL_CONTEXT_FLAGS,
    SDL_GL_CONTEXT_PROFILE_MASK,
    SDL_GL_SHARE_WITH_CURRENT_CONTEXT,
    SDL_GL_FRAMEBUFFER_SRGB_CAPABLE,
    SDL_GL_CONTEXT_RELEASE_BEHAVIOR,
    SDL_GL_CONTEXT_RESET_NOTIFICATION,
    SDL_GL_CONTEXT_NO_ERROR,
    SDL_GL_FLOATBUFFERS
} SDL_GLattr;

#define SDL_HINT_RENDER_VSYNC "SDL_RENDER_VSYNC"
#define SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS "SDL_VIDEO_MINIMIZE_ON_FOCUS_LOSS"
#define SDL_HINT_MOUSE_RELATIVE_MODE_WARP "SDL_MOUSE_RELATIVE_MODE_WARP"
#define SDL_HINT_VIDEO_ALLOW_SCREENSAVER "SDL_VIDEO_ALLOW_SCREENSAVER"
#define SDL_HINT_RENDER_SCALE_QUALITY "SDL_RENDER_SCALE_QUALITY"
#define SDL_HINT_VIDEO_X11_NET_WM_BYPALL_COMPOSITOR "SDL_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR"
#define SDL_HINT_ORIENTATIONS "SDL_IOS_ORIENTATIONS"
#define SDL_HINT_APP_NAME "SDL_APP_NAME"
#define SDL_HINT_AUDIO_RESAMPLING_MODE "SDL_AUDIO_RESAMPLING_MODE"
#define SDL_HINT_AUDIO_CATEGORY "SDL_AUDIO_CATEGORY"
#define SDL_HINT_RENDER_DRIVER "SDL_RENDER_DRIVER"
#define SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH "SDL_MOUSE_FOCUS_CLICKTHROUGH"
#define SDL_HINT_ALLOW_ALT_TAB_WHILE_GRABBED "SDL_ALLOW_ALT_TAB_WHILE_GRABBED"
#define SDL_HINT_APP_ID "SDL_APP_ID"
#define SDL_HINT_WINDOWS_DPI_AWARENESS "SDL_WINDOWS_DPI_AWARENESS"
#define SDL_HINT_WINDOWS_DPI_SCALING "SDL_WINDOWS_DPI_SCALING"
#define SDL_HINT_MAC_COLOR_SPACE "SDL_MAC_COLOR_SPACE"
#define SDL_HINT_AUDIO_DEVICE_STREAM_NAME "SDL_AUDIO_DEVICE_STREAM_NAME"

/* SDL_HintPriority for SDL_SetHintWithPriority */
typedef enum {
    SDL_HINT_DEFAULT = 0,
    SDL_HINT_NORMAL,
    SDL_HINT_OVERRIDE
} SDL_HintPriority;

typedef struct SDL_Rect {
    int x, y;
    int w, h;
} SDL_Rect;

typedef struct SDL_Point {
    int x, y;
} SDL_Point;

typedef struct SDL_Color {
    uint8_t r, g, b, a;
} SDL_Color;

typedef struct SDL_Palette {
    int ncolors;
    SDL_Color *colors;
    uint32_t version;
    int refcount;
} SDL_Palette;

typedef struct SDL_PixelFormat {
    uint32_t format;
    SDL_Palette *palette;
    uint8_t BitsPerPixel;
    uint8_t BytesPerPixel;
    uint8_t padding[2];
    uint32_t Rmask;
    uint32_t Gmask;
    uint32_t Bmask;
    uint32_t Amask;
    uint8_t Rloss;
    uint8_t Gloss;
    uint8_t Bloss;
    uint8_t Aloss;
    uint8_t Rshift;
    uint8_t Gshift;
    uint8_t Bshift;
    uint8_t Ashift;
    int refcount;
    struct SDL_PixelFormat *next;
} SDL_PixelFormat;

typedef struct SDL_Surface {
    uint32_t flags;
    SDL_PixelFormat *format;
    int w, h;
    int pitch;
    void *pixels;
    void *userdata;
    int locked;
    void *lock_data;
    SDL_Rect clip_rect;
    void *map;
    int refcount;
} SDL_Surface;

typedef uint16_t SDL_AudioFormat;

#define SDL_AUDIO_MASK_BITSIZE       (0xFF)
#define SDL_AUDIO_MASK_DATATYPE      (1<<8)
#define SDL_AUDIO_MASK_ENDIAN        (1<<12)
#define SDL_AUDIO_MASK_SIGNED        (1<<15)
#define SDL_AUDIO_BITSIZE(x)         (x & SDL_AUDIO_MASK_BITSIZE)
#define SDL_AUDIO_ISFLOAT(x)         (x & SDL_AUDIO_MASK_DATATYPE)
#define SDL_AUDIO_ISBIGENDIAN(x)     (x & SDL_AUDIO_MASK_ENDIAN)
#define SDL_AUDIO_ISSIGNED(x)        (x & SDL_AUDIO_MASK_SIGNED)
#define SDL_AUDIO_ISINT(x)           (!SDL_AUDIO_ISFLOAT(x))
#define SDL_AUDIO_ISLITTLEENDIAN(x)  (!SDL_AUDIO_ISBIGENDIAN(x))
#define SDL_AUDIO_ISUNSIGNED(x)      (!SDL_AUDIO_ISSIGNED(x))

#define AUDIO_U8        0x0008
#define AUDIO_S8        0x8008
#define AUDIO_U16LSB    0x0010
#define AUDIO_S16LSB    0x8010
#define AUDIO_U16MSB    0x1010
#define AUDIO_S16MSB    0x9010
#define AUDIO_U16       AUDIO_U16LSB
#define AUDIO_S16       AUDIO_S16LSB
#define AUDIO_S32LSB    0x8020
#define AUDIO_S32MSB    0x9020
#define AUDIO_S32       AUDIO_S32LSB
#define AUDIO_F32LSB    0x8120
#define AUDIO_F32MSB    0x9120
#define AUDIO_F32       AUDIO_F32LSB

typedef struct SDL_Joystick SDL_Joystick;
typedef int32_t SDL_JoystickID;

typedef struct SDL_Window SDL_Window;

typedef struct SDL_Renderer SDL_Renderer;

typedef struct SDL_Texture SDL_Texture;

typedef struct SDL_DisplayMode {
    uint32_t format;
    int w;
    int h;
    int refresh_rate;
    void *driverdata;
} SDL_DisplayMode;

typedef struct SDL_RendererInfo {
    const char *name;
    uint32_t flags;
    uint32_t num_texture_formats;
    uint32_t texture_formats[16];
    int max_texture_width;
    int max_texture_height;
} SDL_RendererInfo;

typedef int (*SDL_ThreadFunction)(void *data);

typedef enum {
    SDL_THREAD_PRIORITY_LOW,
    SDL_THREAD_PRIORITY_NORMAL,
    SDL_THREAD_PRIORITY_HIGH,
    SDL_THREAD_PRIORITY_TIME_CRITICAL
} SDL_ThreadPriority;

typedef struct SDL_Thread SDL_Thread;

typedef struct SDL_mutex SDL_mutex;
typedef struct SDL_cond SDL_cond;
typedef struct SDL_sem SDL_sem;

typedef struct SDL_Keysym {
    SDL_Scancode scancode;
    SDL_Keycode sym;
    uint16_t mod;
    uint32_t unused;
} SDL_Keysym;

typedef struct SDL_KeyboardEvent {
    uint32_t type;
    uint32_t timestamp;
    uint32_t windowID;
    uint8_t state;
    uint8_t repeat;
    uint8_t padding2;
    uint8_t padding3;
    SDL_Keysym keysym;
} SDL_KeyboardEvent;

typedef struct SDL_MouseMotionEvent {
    uint32_t type;
    uint32_t timestamp;
    uint32_t windowID;
    uint32_t which;
    uint32_t state;
    int32_t x;
    int32_t y;
    int32_t xrel;
    int32_t yrel;
} SDL_MouseMotionEvent;

typedef struct SDL_MouseButtonEvent {
    uint32_t type;
    uint32_t timestamp;
    uint32_t windowID;
    uint32_t which;
    uint8_t button;
    uint8_t state;
    uint8_t clicks;
    uint8_t padding1;
    int32_t x;
    int32_t y;
} SDL_MouseButtonEvent;

typedef struct SDL_MouseWheelEvent {
    uint32_t type;
    uint32_t timestamp;
    uint32_t windowID;
    uint32_t which;
    int32_t x;
    int32_t y;
    uint32_t direction;
} SDL_MouseWheelEvent;

typedef struct SDL_WindowEvent {
    uint32_t type;
    uint32_t timestamp;
    uint32_t windowID;
    uint8_t event;
    uint8_t padding1;
    uint8_t padding2;
    uint8_t padding3;
    int32_t data1;
    int32_t data2;
} SDL_WindowEvent;

typedef struct SDL_JoyAxisEvent {
    uint32_t type;
    uint32_t timestamp;
    int32_t which;
    uint8_t axis;
    uint8_t padding1;
    uint8_t padding2;
    uint8_t padding3;
    int16_t value;
    uint16_t padding4;
} SDL_JoyAxisEvent;

typedef struct SDL_JoyButtonEvent {
    uint32_t type;
    uint32_t timestamp;
    int32_t which;
    uint8_t button;
    uint8_t state;
    uint8_t padding1;
    uint8_t padding2;
} SDL_JoyButtonEvent;

typedef struct SDL_JoyHatEvent {
    uint32_t type;
    uint32_t timestamp;
    int32_t which;
    uint8_t hat;
    uint8_t value;
    uint8_t padding1;
    uint8_t padding2;
} SDL_JoyHatEvent;

typedef struct SDL_JoyDeviceEvent {
    uint32_t type;
    uint32_t timestamp;
    int32_t which;
} SDL_JoyDeviceEvent;

typedef struct SDL_UserEvent {
    uint32_t type;
    uint32_t timestamp;
    uint32_t windowID;
    int32_t code;
    void *data1;
    void *data2;
} SDL_UserEvent;

typedef struct SDL_QuitEvent {
    uint32_t type;
    uint32_t timestamp;
} SDL_QuitEvent;

typedef struct SDL_CommonEvent {
    uint32_t type;
    uint32_t timestamp;
} SDL_CommonEvent;

typedef enum {
    SDL_DISPLAYEVENT_ORIENTATION,
    SDL_DISPLAYEVENT_CONNECTED,
    SDL_DISPLAYEVENT_DISCONNECTED
} SDL_DisplayEventID;

typedef struct SDL_DisplayEvent {
    uint32_t type;
    uint32_t timestamp;
    uint32_t display;
    uint8_t event;
    uint8_t padding1;
    uint8_t padding2;
    uint8_t padding3;
    int32_t data1;
} SDL_DisplayEvent;

typedef union SDL_Event {
    uint32_t type;
    SDL_CommonEvent common;
    SDL_KeyboardEvent key;
    SDL_MouseMotionEvent motion;
    SDL_MouseButtonEvent button;
    SDL_MouseWheelEvent wheel;
    SDL_WindowEvent window;
    SDL_JoyAxisEvent jaxis;
    SDL_JoyButtonEvent jbutton;
    SDL_JoyHatEvent jhat;
    SDL_JoyDeviceEvent jdevice;
    SDL_UserEvent user;
    SDL_QuitEvent quit;
    SDL_DisplayEvent display;
} SDL_Event;

typedef struct SDL_version {
    uint8_t major;
    uint8_t minor;
    uint8_t patch;
} SDL_version;

#define SDL_BUTTON_LEFT     1
#define SDL_BUTTON_MIDDLE   2
#define SDL_BUTTON_RIGHT    3
#define SDL_BUTTON_X1       4
#define SDL_BUTTON_X2       5
#define SDL_BUTTON_LMASK    (1 << (SDL_BUTTON_LEFT - 1))
#define SDL_BUTTON_MMASK    (1 << (SDL_BUTTON_MIDDLE - 1))
#define SDL_BUTTON_RMASK    (1 << (SDL_BUTTON_RIGHT - 1))
#define SDL_BUTTON_X1MASK   (1 << (SDL_BUTTON_X1 - 1))
#define SDL_BUTTON_X2MASK   (1 << (SDL_BUTTON_X2 - 1))

#define SDL_HAT_CENTERED    0x00
#define SDL_HAT_UP          0x01
#define SDL_HAT_RIGHT       0x02
#define SDL_HAT_DOWN        0x04
#define SDL_HAT_LEFT        0x08
#define SDL_HAT_RIGHTUP     (SDL_HAT_RIGHT|SDL_HAT_UP)
#define SDL_HAT_RIGHTDOWN   (SDL_HAT_RIGHT|SDL_HAT_DOWN)
#define SDL_HAT_LEFTUP      (SDL_HAT_LEFT|SDL_HAT_UP)
#define SDL_HAT_LEFTDOWN    (SDL_HAT_LEFT|SDL_HAT_DOWN)

#define SDL_RELEASED 0
#define SDL_PRESSED  1

#define SDL_IGNORE   0
#define SDL_DISABLE  0
#define SDL_ENABLE   1

/* Window position constants */
#define SDL_WINDOWPOS_UNDEFINED  0x1FFF0000
#define SDL_WINDOWPOS_CENTERED  0x2FFF0000
#define SDL_WINDOWPOS_UNDEFINED_DISPLAY(X) (0x1FFF0000 | ((X) & 0xFFFF))
#define SDL_WINDOWPOS_CENTERED_DISPLAY(X)  (0x2FFF0000 | ((X) & 0xFFFF))
#define SDL_WINDOWPOS_ISUNDEFINED(X)  (((X) & 0xFFFF0000) == 0x1FFF0000)
#define SDL_WINDOWPOS_ISCENTERED(X)   (((X) & 0xFFFF0000) == 0x2FFF0000)

/* Alpha constants */
#define SDL_ALPHA_OPAQUE      255
#define SDL_ALPHA_TRANSPARENT 0

/* ScaleMode compatibility names (SDL2 style) */
#define SDL_ScaleModeNearest SDL_SCALEMODE_NEAREST
#define SDL_ScaleModeLinear  SDL_SCALEMODE_LINEAR
#define SDL_ScaleModeBest    SDL_SCALEMODE_BEST

/* Mouse wheel direction */
#define SDL_MOUSEWHEEL_NORMAL  0
#define SDL_MOUSEWHEEL_FLIPPED 1

/* Version macros */
#define SDL_VERSION_ATLEAST(X, Y, Z) \
    ((SDL_MAJOR_VERSION >= X) && \
     (SDL_MAJOR_VERSION > X || SDL_MINOR_VERSION >= Y) && \
     (SDL_MAJOR_VERSION > X || SDL_MINOR_VERSION > Y || SDL_PATCHLEVEL >= Z))

#define SDL_TICKS_PASSED(A, B) ((Sint32)((B) - (A)) <= 0)

/* Byte order */
#define SDL_LIL_ENDIAN  1234
#define SDL_BIG_ENDIAN  4321
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define SDL_BYTEORDER SDL_BIG_ENDIAN
#else
#define SDL_BYTEORDER SDL_LIL_ENDIAN
#endif

/* Audio format system-endian aliases */
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
#define AUDIO_S16SYS AUDIO_S16LSB
#define AUDIO_U16SYS AUDIO_U16LSB
#define AUDIO_S32SYS AUDIO_S32LSB
#define AUDIO_F32SYS AUDIO_F32LSB
#else
#define AUDIO_S16SYS AUDIO_S16MSB
#define AUDIO_U16SYS AUDIO_U16MSB
#define AUDIO_S32SYS AUDIO_S32MSB
#define AUDIO_F32SYS AUDIO_F32MSB
#endif

#define SDL_AUDIO_ALLOW_FREQUENCY_CHANGE    0x00000001
#define SDL_AUDIO_ALLOW_FORMAT_CHANGE       0x00000002
#define SDL_AUDIO_ALLOW_CHANNELS_CHANGE     0x00000004
#define SDL_AUDIO_ALLOW_SAMPLES_CHANGE      0x00000008
#define SDL_AUDIO_ALLOW_ANY_CHANGE          (SDL_AUDIO_ALLOW_FREQUENCY_CHANGE|SDL_AUDIO_ALLOW_FORMAT_CHANGE|SDL_AUDIO_ALLOW_CHANNELS_CHANGE|SDL_AUDIO_ALLOW_SAMPLES_CHANGE)

typedef void (*SDL_AudioCallback)(void *userdata, uint8_t *stream, int len);

typedef struct SDL_AudioSpec {
    int freq;
    SDL_AudioFormat format;
    uint8_t channels;
    uint8_t silence;
    uint16_t samples;
    uint16_t padding;
    uint32_t size;
    SDL_AudioCallback callback;
    void *userdata;
} SDL_AudioSpec;

typedef uint32_t SDL_AudioDeviceID;

typedef struct SDL_RWops {
    int64_t (*size)(struct SDL_RWops *context);
    int64_t (*seek)(struct SDL_RWops *context, int64_t offset, int whence);
    size_t (*read)(struct SDL_RWops *context, void *ptr, size_t size, size_t maxnum);
    size_t (*write)(struct SDL_RWops *context, const void *ptr, size_t size, size_t maxnum);
    int (*close)(struct SDL_RWops *context);
    uint32_t type;
    union {
        struct {
            void *data;
            int64_t size;
            int64_t pos;
        } mem;
        struct {
            void *data1;
            void *data2;
        } unknown;
    } hidden;
} SDL_RWops;

#define RW_SEEK_SET 0
#define RW_SEEK_CUR 1
#define RW_SEEK_END 2

typedef int (*SDL_EventFilter)(void *userdata, SDL_Event *event);

#ifdef __cplusplus
extern "C" {
#endif

int SDL_Init(uint32_t flags);
int SDL_InitSubSystem(uint32_t flags);
void SDL_QuitSubSystem(uint32_t flags);
uint32_t SDL_WasInit(uint32_t flags);
void SDL_Quit(void);

SDL_Window *SDL_CreateWindow(const char *title, int x, int y, int w, int h, uint32_t flags);
void SDL_DestroyWindow(SDL_Window *window);
uint32_t SDL_GetWindowID(SDL_Window *window);
SDL_Window *SDL_GetWindowFromID(uint32_t id);
void SDL_GetWindowSize(SDL_Window *window, int *w, int *h);
void SDL_GetWindowSizeInPixels(SDL_Window *window, int *w, int *h);
void SDL_SetWindowSize(SDL_Window *window, int w, int h);
int SDL_GetWindowDisplayIndex(SDL_Window *window);
void SDL_SetWindowPosition(SDL_Window *window, int x, int y);
void SDL_GetWindowPosition(SDL_Window *window, int *x, int *y);
uint32_t SDL_GetWindowFlags(SDL_Window *window);
void SDL_RaiseWindow(SDL_Window *window);
int SDL_SetWindowInputFocus(SDL_Window *window);
void SDL_SetWindowFullscreen(SDL_Window *window, uint32_t flags);
void SDL_SetWindowBordered(SDL_Window *window, int bordered);
void SDL_SetWindowResizable(SDL_Window *window, int resizable);
int SDL_SetWindowOpacity(SDL_Window *window, float opacity);
void SDL_SetWindowKeyboardGrab(SDL_Window *window, int grabbed);
int SDL_SetWindowMinimumSize(SDL_Window *window, int min_w, int min_h);
int SDL_GetWindowBordersSize(SDL_Window *window, int *top, int *left, int *bottom, int *right);
void SDL_WarpMouseInWindow(SDL_Window *window, int x, int y);
void SDL_SetWindowTitle(SDL_Window *window, const char *title);

SDL_Renderer *SDL_CreateRenderer(SDL_Window *window, int index, uint32_t flags);
void SDL_DestroyRenderer(SDL_Renderer *renderer);
int SDL_GetRendererInfo(SDL_Renderer *renderer, SDL_RendererInfo *info);
int SDL_GetNumRenderDrivers(void);
int SDL_GetRenderDriverInfo(int index, SDL_RendererInfo *info);
int SDL_GetRendererOutputSize(SDL_Renderer *renderer, int *w, int *h);
int SDL_RenderSetViewport(SDL_Renderer *renderer, const SDL_Rect *rect);
int SDL_SetRenderDrawColor(SDL_Renderer *renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
int SDL_RenderClear(SDL_Renderer *renderer);
int SDL_RenderCopy(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect);
void SDL_RenderPresent(SDL_Renderer *renderer);
int SDL_RenderReadPixels(SDL_Renderer *renderer, const SDL_Rect *rect, uint32_t format, void *pixels, int pitch);
int SDL_RenderSetVSync(SDL_Renderer *renderer, int vsync);

SDL_Texture *SDL_CreateTexture(SDL_Renderer *renderer, uint32_t format, int access, int w, int h);
void SDL_DestroyTexture(SDL_Texture *texture);
int SDL_UpdateTexture(SDL_Texture *texture, const SDL_Rect *rect, const void *pixels, int pitch);
int SDL_SetTextureScaleMode(SDL_Texture *texture, SDL_ScaleMode scaleMode);
int SDL_SetTextureColorMod(SDL_Texture *texture, uint8_t r, uint8_t g, uint8_t b);
int SDL_RenderDrawRect(SDL_Renderer *renderer, const SDL_Rect *rect);
int SDL_RenderFillRect(SDL_Renderer *renderer, const SDL_Rect *rect);
SDL_Renderer *SDL_GetRenderer(SDL_Window *window);

SDL_Surface *SDL_CreateRGBSurfaceWithFormat(uint32_t flags, int width, int height, int depth, uint32_t format);
void SDL_FreeSurface(SDL_Surface *surface);
int SDL_LockSurface(SDL_Surface *surface);
void SDL_UnlockSurface(SDL_Surface *surface);
int SDL_MUSTLOCK(const SDL_Surface *surface);
int SDL_SetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode blendMode);

int SDL_PollEvent(SDL_Event *event);
int SDL_WaitEvent(SDL_Event *event);
void SDL_PumpEvents(void);
int SDL_PushEvent(SDL_Event *event);
uint32_t SDL_RegisterEvents(int numevents);
void SDL_SetEventFilter(SDL_EventFilter filter, void *userdata);

uint8_t SDL_GetMouseState(int *x, int *y);
int SDL_SetRelativeMouseMode(int enabled);
int SDL_ShowCursor(int toggle);

SDL_Keymod SDL_GetModState(void);
const char *SDL_GetScancodeName(SDL_Scancode scancode);
void SDL_StartTextInput(void);
void SDL_StopTextInput(void);

int SDL_GetNumVideoDisplays(void);
int SDL_GetDisplayBounds(int displayIndex, SDL_Rect *rect);
int SDL_GetCurrentDisplayMode(int displayIndex, SDL_DisplayMode *mode);
const char *SDL_GetCurrentVideoDriver(void);

SDL_Joystick *SDL_JoystickOpen(int device_index);
void SDL_JoystickClose(SDL_Joystick *joystick);
void SDL_JoystickUpdate(void);
int SDL_JoystickInstanceID(SDL_Joystick *joystick);
int SDL_JoystickNumAxes(SDL_Joystick *joystick);
int SDL_JoystickNumHats(SDL_Joystick *joystick);
int SDL_JoystickNumButtons(SDL_Joystick *joystick);
uint8_t SDL_JoystickGetButton(SDL_Joystick *joystick, int button);
int16_t SDL_JoystickGetAxis(SDL_Joystick *joystick, int axis);
uint8_t SDL_JoystickGetHat(SDL_Joystick *joystick, int hat);
const char *SDL_JoystickNameForIndex(int device_index);
SDL_bool SDL_JoystickHasLED(SDL_Joystick *joystick);
int SDL_JoystickSetLED(SDL_Joystick *joystick, uint8_t red, uint8_t green, uint8_t blue);
int SDL_NumJoysticks(void);
char *SDL_GameControllerMappingForDeviceIndex(int joystick_index);

uint32_t SDL_GetTicks(void);
uint64_t SDL_GetPerformanceCounter(void);
uint64_t SDL_GetPerformanceFrequency(void);
void SDL_Delay(uint32_t ms);

/* Timer types and functions */
typedef uint32_t SDL_TimerID;
typedef uint32_t (*SDL_TimerCallback)(uint32_t interval, void *param);
SDL_TimerID SDL_AddTimer(uint32_t interval, SDL_TimerCallback callback, void *param);
SDL_bool SDL_RemoveTimer(SDL_TimerID id);

SDL_Thread *SDL_CreateThread(SDL_ThreadFunction fn, const char *name, void *data);
void SDL_WaitThread(SDL_Thread *thread, int *status);
int SDL_SetThreadPriority(SDL_ThreadPriority priority);

/* Thread ID */
typedef uint32_t SDL_threadID;
SDL_threadID SDL_GetThreadID(SDL_Thread *thread);
SDL_threadID SDL_ThreadID(void);

/* Clipboard functions */
SDL_bool SDL_HasClipboardText(void);
char *SDL_GetClipboardText(void);
int SDL_SetClipboardText(const char *text);

SDL_mutex *SDL_CreateMutex(void);
void SDL_DestroyMutex(SDL_mutex *mutex);
int SDL_LockMutex(SDL_mutex *mutex);
int SDL_TryLockMutex(SDL_mutex *mutex);
int SDL_UnlockMutex(SDL_mutex *mutex);

SDL_cond *SDL_CreateCond(void);
void SDL_DestroyCond(SDL_cond *cond);
int SDL_CondSignal(SDL_cond *cond);
int SDL_CondBroadcast(SDL_cond *cond);
int SDL_CondWait(SDL_cond *cond, SDL_mutex *mutex);
int SDL_CondWaitTimeout(SDL_cond *cond, SDL_mutex *mutex, uint32_t ms);

SDL_sem *SDL_CreateSemaphore(uint32_t initial_value);
void SDL_DestroySemaphore(SDL_sem *sem);
int SDL_SemWait(SDL_sem *sem);
int SDL_SemTryWait(SDL_sem *sem);
int SDL_SemPost(SDL_sem *sem);
uint32_t SDL_SemValue(SDL_sem *sem);

SDL_AudioDeviceID SDL_OpenAudioDevice(const char *device, int iscapture, const SDL_AudioSpec *desired, SDL_AudioSpec *obtained, int allowed_changes);
void SDL_CloseAudioDevice(SDL_AudioDeviceID dev);
void SDL_PauseAudioDevice(SDL_AudioDeviceID dev, int pause_on);
const char *SDL_GetCurrentAudioDriver(void);

SDL_RWops *SDL_AllocRW(void);
void SDL_FreeRW(SDL_RWops *area);
size_t SDL_RWread(SDL_RWops *ctx, void *ptr, size_t size, size_t maxnum);
int64_t SDL_RWseek(SDL_RWops *ctx, int64_t offset, int whence);
int64_t SDL_RWtell(SDL_RWops *ctx);
int SDL_RWclose(SDL_RWops *ctx);
SDL_RWops *SDL_RWFromFile(const char *file, const char *mode);
int64_t SDL_RWsize(SDL_RWops *ctx);

/* SDL memory functions - map to standard C library */
#define SDL_memcpy(dst, src, len) memcpy(dst, src, len)
#define SDL_memset(dst, val, len) memset(dst, val, len)
#define SDL_memcmp(p1, p2, len) memcmp(p1, p2, len)
#define SDL_malloc(size) malloc(size)
#define SDL_realloc(ptr, size) realloc(ptr, size)
#define SDL_free(ptr) free(ptr)
#define SDL_qsort(base, nmemb, size, compar) qsort(base, nmemb, size, compar)
#define SDL_calloc(nmemb, size) calloc(nmemb, size)

int SDL_SetHint(const char *name, const char *value);
int SDL_SetHintWithPriority(const char *name, const char *value, SDL_HintPriority priority);
void SDL_EnableScreenSaver(void);
void SDL_DisableScreenSaver(void);
void SDL_GetVersion(SDL_version *ver);
const char *SDL_GetError(void);
void SDL_SetError(const char *fmt, ...);
void SDL_free(void *ptr);

int SDL_GL_SetAttribute(SDL_GLattr attr, int value);
void SDL_GL_ResetAttributes(void);
void *SDL_GL_CreateContext(SDL_Window *window);
void SDL_GL_DeleteContext(void *context);
void *SDL_GL_GetProcAddress(const char *proc);
void SDL_GL_GetDrawableSize(SDL_Window *window, int *w, int *h);
int SDL_GL_SwapWindow(SDL_Window *window);
int SDL_GL_SetSwapInterval(int interval);

void OHOS_PushSDLKeyEvent(SDL_Scancode scancode, SDL_Keycode keycode, uint16_t mod, uint8_t down);
void OHOS_PushSDLMouseEvent(int x, int y, uint8_t button, uint8_t down);
void OHOS_PushSDLMotionEvent(int x, int y, int xrel, int yrel);
void OHOS_PushSDLQuitEvent();

/* Additional SDL2 functions needed by dosbox */
SDL_Surface *SDL_CreateRGBSurfaceFrom(void *pixels, int width, int height, int depth, int pitch, uint32_t Rmask, uint32_t Gmask, uint32_t Bmask, uint32_t Amask);
SDL_Texture *SDL_CreateTextureFromSurface(SDL_Renderer *renderer, SDL_Surface *surface);
SDL_Joystick *SDL_JoystickFromInstanceID(int32_t instance_id);
const char *SDL_JoystickName(SDL_Joystick *joystick);
int SDL_RenderSetLogicalSize(SDL_Renderer *renderer, int w, int h);
int SDL_SetPaletteColors(SDL_Palette *palette, const SDL_Color *colors, int firstcolor, int ncolors);

/* SDLCALL calling convention (no-op on most platforms) */
#ifndef SDLCALL
#define SDLCALL
#endif

#ifdef __cplusplus
}
#endif

#endif
