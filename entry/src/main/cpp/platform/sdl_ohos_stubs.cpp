#include "SDL.h"

/* Undef macro versions so we can provide real function implementations */
#undef SDL_malloc
#undef SDL_realloc
#undef SDL_free
#undef SDL_memcpy
#undef SDL_memset
#undef SDL_memcmp
#undef SDL_qsort
#undef SDL_calloc

extern "C" {

int SDL_SetTextureColorMod(SDL_Texture *texture, uint8_t r, uint8_t g, uint8_t b) {
    return 0; // stub
}

int SDL_RenderDrawRect(SDL_Renderer *renderer, const SDL_Rect *rect) {
    return 0; // stub
}

int SDL_RenderFillRect(SDL_Renderer *renderer, const SDL_Rect *rect) {
    return 0; // stub
}

SDL_Renderer *SDL_GetRenderer(SDL_Window *window) {
    return nullptr; // stub
}

int SDL_NumJoysticks(void) {
    return 0; // stub
}

char *SDL_GameControllerMappingForDeviceIndex(int joystick_index) {
    return nullptr; // stub
}

SDL_bool SDL_HasClipboardText(void) {
    return SDL_FALSE; // stub
}

char *SDL_GetClipboardText(void) {
    return nullptr; // stub
}

int SDL_SetClipboardText(const char *text) {
    return 0; // stub
}

SDL_TimerID SDL_AddTimer(uint32_t interval, SDL_TimerCallback callback, void *param) {
    return 0; // stub
}

SDL_bool SDL_RemoveTimer(SDL_TimerID id) {
    return SDL_FALSE; // stub
}

SDL_threadID SDL_GetThreadID(SDL_Thread *thread) {
    return 0; // stub
}

SDL_threadID SDL_ThreadID(void) {
    return 0; // stub
}

SDL_Surface *SDL_CreateRGBSurfaceFrom(void *pixels, int width, int height, int depth, int pitch, uint32_t Rmask, uint32_t Gmask, uint32_t Bmask, uint32_t Amask) {
    // Stub: return a minimal surface structure
    SDL_Surface *s = (SDL_Surface *)calloc(1, sizeof(SDL_Surface));
    if (s) {
        s->w = width;
        s->h = height;
        s->pitch = pitch;
        s->pixels = pixels;
    }
    return s;
}

SDL_Texture *SDL_CreateTextureFromSurface(SDL_Renderer *renderer, SDL_Surface *surface) {
    return nullptr; // stub
}

SDL_Joystick *SDL_JoystickFromInstanceID(int32_t instance_id) {
    return nullptr; // stub
}

const char *SDL_JoystickName(SDL_Joystick *joystick) {
    return "Stub Joystick"; // stub
}

int SDL_RenderSetLogicalSize(SDL_Renderer *renderer, int w, int h) {
    return 0; // stub
}

int SDL_SetPaletteColors(SDL_Palette *palette, const SDL_Color *colors, int firstcolor, int ncolors) {
    return 0; // stub
}

/* SDL_image stub */
SDL_Surface *IMG_Load_RW(SDL_RWops *src, int freesrc) {
    return nullptr; // stub: image loading not supported
}

/* SDL RWops stubs */
SDL_RWops *SDL_RWFromFile(const char *file, const char *mode) {
    return nullptr; // stub: file RWops not supported
}

int64_t SDL_RWsize(SDL_RWops *ctx) {
    if (ctx && ctx->size) return ctx->size(ctx);
    return -1;
}

/* SDL memory function stubs (C libraries call these directly) */
void *SDL_malloc(size_t size) { return malloc(size); }
void *SDL_realloc(void *ptr, size_t size) { return realloc(ptr, size); }
void SDL_free(void *ptr) { free(ptr); }
void *SDL_memcpy(void *dst, const void *src, size_t len) { return memcpy(dst, src, len); }
void *SDL_memset(void *dst, int val, size_t len) { return memset(dst, val, len); }
int SDL_memcmp(const void *p1, const void *p2, size_t len) { return memcmp(p1, p2, len); }
void SDL_qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
    qsort(base, nmemb, size, compar);
}

} // extern "C"
