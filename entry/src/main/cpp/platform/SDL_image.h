#ifndef SDL_IMAGE_H
#define SDL_IMAGE_H

#include "SDL.h"

/* Stub SDL_image functions for OHOS platform where SDL_image is not available */

#ifdef __cplusplus
extern "C" {
#endif

/* IMG_Load_RW loads an image from an SDL_RWops stream.
 * Stub: returns nullptr (image loading not supported on OHOS) */
SDL_Surface *IMG_Load_RW(SDL_RWops *src, int freesrc);

#ifdef __cplusplus
}
#endif

#endif
