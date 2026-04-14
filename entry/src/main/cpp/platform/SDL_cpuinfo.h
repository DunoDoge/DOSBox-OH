#ifndef SDL_CPUINFO_H
#define SDL_CPUINFO_H

#define SDL_CACHELINE_SIZE 128

static inline int SDL_GetCPUCount() { return 4; }
static inline int SDL_GetCPUCacheLineSize() { return SDL_CACHELINE_SIZE; }
static inline SDL_bool SDL_HasRDTSC() { return SDL_TRUE; }
static inline SDL_bool SDL_HasAltiVec() { return SDL_FALSE; }
static inline SDL_bool SDL_HasMMX() { return SDL_FALSE; }
static inline SDL_bool SDL_Has3DNow() { return SDL_FALSE; }
static inline SDL_bool SDL_HasSSE() { return SDL_TRUE; }
static inline SDL_bool SDL_HasSSE2() { return SDL_TRUE; }
static inline SDL_bool SDL_HasSSE3() { return SDL_TRUE; }
static inline SDL_bool SDL_HasSSE41() { return SDL_TRUE; }
static inline SDL_bool SDL_HasSSE42() { return SDL_TRUE; }
static inline SDL_bool SDL_HasAVX() { return SDL_FALSE; }
static inline SDL_bool SDL_HasAVX2() { return SDL_FALSE; }
static inline SDL_bool SDL_HasAVX512F() { return SDL_FALSE; }
static inline SDL_bool SDL_HasNEON() { return SDL_TRUE; }
static inline int SDL_GetSystemRAM() { return 4096; }

#endif
