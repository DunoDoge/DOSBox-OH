#ifndef PNG_H_STUB
#define PNG_H_STUB

/*
 * Stub png.h for OHOS platform where libpng is not available.
 * Provides type definitions and stub functions needed by png_writer.h/cpp.
 */

#include <cstdio>
#include <cstdint>
#include <csetjmp>
#include <string>

/* Basic libpng type stubs */
typedef void* png_voidp;
typedef void* png_structp;
typedef void (*png_error_ptr)(png_structp, const char*);
typedef void* png_infop;
typedef png_infop* png_infopp;
typedef uint8_t png_byte;
typedef png_byte* png_bytep;
typedef const png_byte* png_const_bytep;
typedef char* png_charp;
typedef int png_int_32;
typedef unsigned int png_uint_32;
typedef uint16_t png_uint_16;

/* png_color structure for palette */
typedef struct png_color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} png_color;

typedef png_color* png_colorp;

/* png_text structure */
typedef struct png_text {
    int compression;
    char* key;
    char* text;
    size_t text_length;
} png_text;

/* Version string */
#define PNG_LIBPNG_VER_STRING "1.6.0"

/* Stub functions - these are no-ops on OHOS */
inline png_structp png_create_write_struct(const char*, png_voidp, png_error_ptr, png_error_ptr) { return nullptr; }
inline png_infop png_create_info_struct(png_structp) { return nullptr; }
inline void png_destroy_write_struct(png_structp*, png_infopp) {}
inline void png_init_io(png_structp, FILE*) {}
inline void png_set_IHDR(png_structp, png_infop, uint32_t, uint32_t, int, int, int, int, int) {}
inline void png_set_pHYs(png_structp, png_infop, uint32_t, uint32_t, int) {}
inline void png_write_info(png_structp, png_infop) {}
inline void png_set_compression_level(png_structp, int) {}
inline void png_set_compression_mem_level(png_structp, int) {}
inline void png_set_compression_strategy(png_structp, int) {}
inline void png_set_compression_window_bits(png_structp, int) {}
inline void png_set_compression_method(png_structp, int) {}
inline void png_set_compression_buffer_size(png_structp, int) {}
inline void png_set_filter(png_structp, int, int) {}
inline void png_write_row(png_structp, png_bytep) {}
inline void png_write_end(png_structp, png_infop) {}
inline void png_set_PLTE(png_structp, png_infop, png_colorp, int) {}
inline void png_set_tRNS(png_structp, png_infop, void*, int, void*) {}
inline void png_set_gAMA(png_structp, png_infop, double) {}
inline void png_set_text(png_structp, png_infop, png_text*, int) {}
inline int png_setjmp(png_structp) { return 0; }

/* PNG constants */
#define PNG_COLOR_TYPE_PALETTE 3
#define PNG_COLOR_TYPE_RGB 2
#define PNG_COLOR_TYPE_RGB_ALPHA 6
#define PNG_INTERLACE_NONE 0
#define PNG_COMPRESSION_TYPE_DEFAULT 0
#define PNG_FILTER_TYPE_DEFAULT 0
#define PNG_RESOLUTION_METER 1
#define PNG_ALL_FILTERS 0xFF
#define PNG_TEXT_COMPRESSION_NONE 0

/* Feature macros - enable all for stub */
#define PNG_gAMA_SUPPORTED
#define PNG_pHYs_SUPPORTED
#define PNG_TEXT_SUPPORTED

#endif
