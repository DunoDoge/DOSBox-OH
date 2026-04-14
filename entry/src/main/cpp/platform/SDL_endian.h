#ifndef SDL_ENDIAN_H
#define SDL_ENDIAN_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#define SDL_LIL_ENDIAN 1234
#define SDL_BIG_ENDIAN 4321

#ifdef __BYTE_ORDER__
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define SDL_BYTEORDER SDL_LIL_ENDIAN
#else
#define SDL_BYTEORDER SDL_BIG_ENDIAN
#endif
#else
#define SDL_BYTEORDER SDL_LIL_ENDIAN
#endif

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
static inline uint16_t SDL_Swap16(uint16_t x) { return __builtin_bswap16(x); }
static inline uint32_t SDL_Swap32(uint32_t x) { return __builtin_bswap32(x); }
static inline uint64_t SDL_Swap64(uint64_t x) { return __builtin_bswap64(x); }
#else
static inline uint16_t SDL_Swap16(uint16_t x) { return x; }
static inline uint32_t SDL_Swap32(uint32_t x) { return x; }
static inline uint64_t SDL_Swap64(uint64_t x) { return x; }
#endif

#define SDL_SwapLE16(x) (SDL_BYTEORDER == SDL_LIL_ENDIAN ? (x) : SDL_Swap16(x))
#define SDL_SwapLE32(x) (SDL_BYTEORDER == SDL_LIL_ENDIAN ? (x) : SDL_Swap32(x))
#define SDL_SwapLE64(x) (SDL_BYTEORDER == SDL_LIL_ENDIAN ? (x) : SDL_Swap64(x))
#define SDL_SwapBE16(x) (SDL_BYTEORDER == SDL_BIG_ENDIAN ? (x) : SDL_Swap16(x))
#define SDL_SwapBE32(x) (SDL_BYTEORDER == SDL_BIG_ENDIAN ? (x) : SDL_Swap32(x))
#define SDL_SwapBE64(x) (SDL_BYTEORDER == SDL_BIG_ENDIAN ? (x) : SDL_Swap64(x))

#endif
