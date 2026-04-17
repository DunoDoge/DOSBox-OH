#include "sdl_ohos.h"
#include "dosbox_bridge.h"
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <hilog/log.h>

#undef LOG_DOMAIN
#undef LOG_TAG
#define LOG_DOMAIN 0x0000
#define LOG_TAG "SDL_OHOS"

static SDL_Window *g_window = nullptr;
static SDL_Renderer *g_renderer = nullptr;
static SDL_Surface *g_screen_surface = nullptr;
static char g_error_msg[256] = {0};
static std::mutex g_window_mutex;

struct SDL_Window {
    int x, y, w, h;
    uint32_t flags;
    char title[256];
    uint32_t id;
    float opacity;
};

struct SDL_Renderer {
    SDL_Window *window;
    uint32_t flags;
    SDL_Texture *target;
    SDL_Rect viewport;
    uint8_t draw_r, draw_g, draw_b, draw_a;
};

struct SDL_Texture {
    uint32_t format;
    int access;
    int w, h;
    uint8_t *pixels;
    int pitch;
    SDL_ScaleMode scaleMode;
};

static uint32_t g_next_window_id = 1;

int SDL_Init(uint32_t flags)
{
    OH_LOG_INFO(LOG_APP, "SDL_Init flags=0x%{public}x", flags);
    return 0;
}

int SDL_InitSubSystem(uint32_t flags)
{
    OH_LOG_INFO(LOG_APP, "SDL_InitSubSystem flags=0x%{public}x", flags);
    return 0;
}

void SDL_QuitSubSystem(uint32_t flags)
{
}

uint32_t SDL_WasInit(uint32_t flags)
{
    return flags;
}

void SDL_Quit()
{
    if (g_screen_surface) {
        SDL_FreeSurface(g_screen_surface);
        g_screen_surface = nullptr;
    }
    if (g_renderer) {
        SDL_DestroyRenderer(g_renderer);
        g_renderer = nullptr;
    }
    if (g_window) {
        SDL_DestroyWindow(g_window);
        g_window = nullptr;
    }
    OH_LOG_INFO(LOG_APP, "SDL_Quit");
}

SDL_Window *SDL_CreateWindow(const char *title, int x, int y, int w, int h, uint32_t flags)
{
    OH_LOG_INFO(LOG_APP, "SDL_CreateWindow title=%{public}s size=%{public}dx%{public}d flags=0x%{public}x", title, w, h, flags);
    SDL_Window *win = new SDL_Window();
    win->x = x;
    win->y = y;
    win->w = w;
    win->h = h;
    win->flags = flags;
    if (title) {
        strncpy(win->title, title, sizeof(win->title) - 1);
    }
    win->id = g_next_window_id++;
    win->opacity = 1.0f;
    
    {
        std::lock_guard<std::mutex> lock(g_window_mutex);
        g_window = win;
    }
    
    OH_LOG_INFO(LOG_APP, "SDL_CreateWindow: window created successfully, id=%{public}d", win->id);
    return win;
}

void SDL_DestroyWindow(SDL_Window *window)
{
    OH_LOG_INFO(LOG_APP, "SDL_DestroyWindow: destroying window id=%{public}d", window ? window->id : 0);
    if (window == g_window) {
        std::lock_guard<std::mutex> lock(g_window_mutex);
        g_window = nullptr;
    }
    delete window;
}

uint32_t SDL_GetWindowID(SDL_Window *window)
{
    return window ? window->id : 0;
}

SDL_Window *SDL_GetWindowFromID(uint32_t id)
{
    std::lock_guard<std::mutex> lock(g_window_mutex);
    if (g_window && g_window->id == id) return g_window;
    return nullptr;
}

SDL_Window* SDL_OHOS_GetWindow(void)
{
    std::lock_guard<std::mutex> lock(g_window_mutex);
    return g_window;
}

void SDL_GetWindowSize(SDL_Window *window, int *w, int *h)
{
    if (window) {
        if (w) *w = window->w;
        if (h) *h = window->h;
    }
}

void SDL_GetWindowSizeInPixels(SDL_Window *window, int *w, int *h)
{
    SDL_GetWindowSize(window, w, h);
}

void SDL_SetWindowSize(SDL_Window *window, int w, int h)
{
    if (window) {
        window->w = w;
        window->h = h;
    }
}

int SDL_GetWindowDisplayIndex(SDL_Window *window)
{
    return 0;
}

void SDL_SetWindowPosition(SDL_Window *window, int x, int y)
{
    if (window) { window->x = x; window->y = y; }
}

void SDL_GetWindowPosition(SDL_Window *window, int *x, int *y)
{
    if (window) {
        if (x) *x = window->x;
        if (y) *y = window->y;
    }
}

uint32_t SDL_GetWindowFlags(SDL_Window *window)
{
    return window ? window->flags : 0;
}

void SDL_RaiseWindow(SDL_Window *window)
{
}

int SDL_SetWindowInputFocus(SDL_Window *window)
{
    return 0;
}

void SDL_SetWindowFullscreen(SDL_Window *window, uint32_t flags)
{
    if (window) window->flags = (window->flags & ~SDL_WINDOW_FULLSCREEN_DESKTOP) | flags;
}

void SDL_SetWindowBordered(SDL_Window *window, int bordered)
{
}

void SDL_SetWindowResizable(SDL_Window *window, int resizable)
{
}

int SDL_SetWindowOpacity(SDL_Window *window, float opacity)
{
    if (window) window->opacity = opacity;
    return 0;
}

void SDL_SetWindowKeyboardGrab(SDL_Window *window, int grabbed)
{
}

int SDL_SetWindowMinimumSize(SDL_Window *window, int min_w, int min_h)
{
    return 0;
}

int SDL_GetWindowBordersSize(SDL_Window *window, int *top, int *left, int *bottom, int *right)
{
    if (top) *top = 0;
    if (left) *left = 0;
    if (bottom) *bottom = 0;
    if (right) *right = 0;
    return 0;
}

void SDL_WarpMouseInWindow(SDL_Window *window, int x, int y)
{
}

void SDL_SetWindowTitle(SDL_Window *window, const char *title)
{
    if (window && title) {
        strncpy(window->title, title, sizeof(window->title) - 1);
    }
}

SDL_Renderer *SDL_CreateRenderer(SDL_Window *window, int index, uint32_t flags)
{
    OH_LOG_INFO(LOG_APP, "SDL_CreateRenderer");
    SDL_Renderer *ren = new SDL_Renderer();
    ren->window = window;
    ren->flags = flags;
    ren->target = nullptr;
    ren->draw_r = ren->draw_g = ren->draw_b = ren->draw_a = 0;
    ren->viewport.x = ren->viewport.y = 0;
    if (window) {
        ren->viewport.w = window->w;
        ren->viewport.h = window->h;
    }
    g_renderer = ren;
    return ren;
}

void SDL_DestroyRenderer(SDL_Renderer *renderer)
{
    if (renderer == g_renderer) g_renderer = nullptr;
    delete renderer;
}

int SDL_GetRendererInfo(SDL_Renderer *renderer, SDL_RendererInfo *info)
{
    if (!info) return -1;
    memset(info, 0, sizeof(SDL_RendererInfo));
    info->name = "ohos";
    info->flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE;
    info->max_texture_width = 4096;
    info->max_texture_height = 4096;
    return 0;
}

int SDL_GetNumRenderDrivers()
{
    return 1;
}

int SDL_GetRenderDriverInfo(int index, SDL_RendererInfo *info)
{
    return SDL_GetRendererInfo(nullptr, info);
}

int SDL_GetRendererOutputSize(SDL_Renderer *renderer, int *w, int *h)
{
    if (renderer && renderer->window) {
        if (w) *w = renderer->window->w;
        if (h) *h = renderer->window->h;
        return 0;
    }
    return -1;
}

int SDL_RenderSetViewport(SDL_Renderer *renderer, const SDL_Rect *rect)
{
    if (renderer) {
        if (rect) renderer->viewport = *rect;
        else if (renderer->window) {
            renderer->viewport.x = renderer->viewport.y = 0;
            renderer->viewport.w = renderer->window->w;
            renderer->viewport.h = renderer->window->h;
        }
    }
    return 0;
}

int SDL_SetRenderDrawColor(SDL_Renderer *renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    if (renderer) {
        renderer->draw_r = r;
        renderer->draw_g = g;
        renderer->draw_b = b;
        renderer->draw_a = a;
    }
    return 0;
}

int SDL_RenderClear(SDL_Renderer *renderer)
{
    return 0;
}

int SDL_RenderCopy(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect)
{
    if (renderer && texture) {
        renderer->target = texture;
    }
    return 0;
}

void SDL_RenderPresent(SDL_Renderer *renderer)
{
    if (!renderer || !renderer->target) return;

    SDL_Texture *tex = renderer->target;
    if (!tex->pixels || tex->w <= 0 || tex->h <= 0) return;

    DosBoxBridge::Instance().RenderFrame(tex->pixels, tex->w, tex->h, tex->pitch);
}

int SDL_RenderReadPixels(SDL_Renderer *renderer, const SDL_Rect *rect, uint32_t format, void *pixels, int pitch)
{
    return -1;
}

int SDL_RenderSetVSync(SDL_Renderer *renderer, int vsync)
{
    return 0;
}

SDL_Texture *SDL_CreateTexture(SDL_Renderer *renderer, uint32_t format, int access, int w, int h)
{
    SDL_Texture *tex = new SDL_Texture();
    tex->format = format;
    tex->access = access;
    tex->w = w;
    tex->h = h;
    tex->pitch = w * 4;
    tex->pixels = (uint8_t *)calloc(w * h, 4);
    tex->scaleMode = SDL_SCALEMODE_NEAREST;
    return tex;
}

void SDL_DestroyTexture(SDL_Texture *texture)
{
    if (texture) {
        free(texture->pixels);
        delete texture;
    }
}

int SDL_UpdateTexture(SDL_Texture *texture, const SDL_Rect *rect, const void *pixels, int pitch)
{
    if (!texture || !pixels) return -1;
    int x = 0, y = 0, w = texture->w, h = texture->h;
    if (rect) { x = rect->x; y = rect->y; w = rect->w; h = rect->h; }
    for (int row = 0; row < h; row++) {
        memcpy(texture->pixels + (y + row) * texture->pitch + x * 4,
               (const uint8_t *)pixels + row * pitch, w * 4);
    }
    return 0;
}

int SDL_SetTextureScaleMode(SDL_Texture *texture, SDL_ScaleMode scaleMode)
{
    if (texture) texture->scaleMode = scaleMode;
    return 0;
}

SDL_Surface *SDL_CreateRGBSurfaceWithFormat(uint32_t flags, int width, int height, int depth, uint32_t format)
{
    SDL_Surface *surface = new SDL_Surface();
    memset(surface, 0, sizeof(SDL_Surface));
    surface->w = width;
    surface->h = height;
    surface->format = new SDL_PixelFormat();
    memset(surface->format, 0, sizeof(SDL_PixelFormat));
    surface->format->format = format;
    surface->format->BitsPerPixel = depth;
    surface->format->BytesPerPixel = depth / 8;
    if (format == SDL_PIXELFORMAT_ARGB8888) {
        surface->format->Rmask = 0x00FF0000;
        surface->format->Gmask = 0x0000FF00;
        surface->format->Bmask = 0x000000FF;
        surface->format->Amask = 0xFF000000;
        surface->format->Rshift = 16;
        surface->format->Gshift = 8;
        surface->format->Bshift = 0;
        surface->format->Ashift = 24;
    }
    surface->pitch = width * surface->format->BytesPerPixel;
    surface->pixels = calloc(width * height, surface->format->BytesPerPixel);
    surface->refcount = 1;
    return surface;
}

void SDL_FreeSurface(SDL_Surface *surface)
{
    if (surface) {
        if (surface->format) delete surface->format;
        free(surface->pixels);
        delete surface;
    }
}

int SDL_LockSurface(SDL_Surface *surface)
{
    return 0;
}

void SDL_UnlockSurface(SDL_Surface *surface)
{
}

int SDL_MUSTLOCK(const SDL_Surface *surface)
{
    return 0;
}

int SDL_SetSurfaceBlendMode(SDL_Surface *surface, SDL_BlendMode blendMode)
{
    return 0;
}

int SDL_GetNumVideoDisplays()
{
    return 1;
}

int SDL_GetDisplayBounds(int displayIndex, SDL_Rect *rect)
{
    int w = DosBoxBridge::Instance().GetScreenWidth();
    int h = DosBoxBridge::Instance().GetScreenHeight();
    if (w <= 0 || h <= 0) { w = 1080; h = 1920; } // fallback
    if (rect) { rect->x = 0; rect->y = 0; rect->w = w; rect->h = h; }
    return 0;
}

int SDL_GetCurrentDisplayMode(int displayIndex, SDL_DisplayMode *mode)
{
    int w = DosBoxBridge::Instance().GetScreenWidth();
    int h = DosBoxBridge::Instance().GetScreenHeight();
    if (w <= 0 || h <= 0) { w = 1080; h = 1920; } // fallback
    if (mode) { mode->w = w; mode->h = h; mode->refresh_rate = 60; mode->format = SDL_PIXELFORMAT_ARGB8888; }
    return 0;
}

const char *SDL_GetCurrentVideoDriver()
{
    return "ohos";
}

const char *SDL_GetError()
{
    return g_error_msg;
}

void SDL_SetError(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(g_error_msg, sizeof(g_error_msg), fmt, ap);
    va_end(ap);
}

int SDL_SetHint(const char *name, const char *value)
{
    return SDL_TRUE;
}

int SDL_SetHintWithPriority(const char *name, const char *value, SDL_HintPriority priority)
{
    return SDL_TRUE;
}

void SDL_EnableScreenSaver()
{
}

void SDL_DisableScreenSaver()
{
}

void SDL_GetVersion(SDL_version *ver)
{
    if (ver) {
        ver->major = SDL_MAJOR_VERSION;
        ver->minor = SDL_MINOR_VERSION;
        ver->patch = SDL_PATCHLEVEL;
    }
}
