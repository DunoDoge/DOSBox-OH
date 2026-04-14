#ifndef ZLIB_H_STUB
#define ZLIB_H_STUB

/*
 * Stub zlib.h for OHOS platform where zlib is not directly available.
 * Provides minimal type definitions and stub functions needed by zmbv and png_writer.
 */

#include <cstdint>
#include <cstddef>

/* z_stream structure */
typedef struct z_stream_s {
    const uint8_t *next_in;
    uint32_t avail_in;
    uint32_t total_in;

    uint8_t *next_out;
    uint32_t avail_out;
    uint32_t total_out;

    const char *msg;
    void *state;
    void *zalloc;
    void *zfree;
    void *opaque;

    int data_type;
    uint32_t adler;
    uint32_t reserved;
} z_stream;

typedef z_stream *z_streamp;

/* zlib constants */
#define Z_OK            0
#define Z_STREAM_END    1
#define Z_NEED_DICT     2
#define Z_ERRNO        (-1)
#define Z_STREAM_ERROR (-2)
#define Z_DATA_ERROR   (-3)
#define Z_MEM_ERROR    (-4)
#define Z_BUF_ERROR    (-5)
#define Z_VERSION_ERROR (-6)

#define Z_NO_COMPRESSION         0
#define Z_BEST_SPEED             1
#define Z_BEST_COMPRESSION       9
#define Z_DEFAULT_COMPRESSION   (-1)

#define Z_DEFAULT_STRATEGY       0
#define Z_FILTERED               1
#define Z_HUFFMAN_ONLY           2
#define Z_RLE                    3
#define Z_FIXED                  4

#define Z_DEFLATED               8

/* Flush constants */
#define Z_NO_FLUSH      0
#define Z_PARTIAL_FLUSH 1
#define Z_SYNC_FLUSH    2
#define Z_FULL_FLUSH    3
#define Z_FINISH        4
#define Z_BLOCK         5
#define Z_TREES         6

/* Stub functions */
inline int deflateInit2(z_stream *strm, int level, int method, int windowBits,
                        int memLevel, int strategy) { return Z_OK; }
inline int deflateReset(z_stream *strm) { return Z_OK; }
inline int deflate(z_stream *strm, int flush) { return Z_STREAM_END; }
inline int deflateEnd(z_stream *strm) { return Z_OK; }
inline int inflateInit(z_stream *strm) { return Z_OK; }
inline int inflateInit2(z_stream *strm, int windowBits) { return Z_OK; }
inline int inflateReset(z_stream *strm) { return Z_OK; }
inline int inflate(z_stream *strm, int flush) { return Z_STREAM_END; }
inline int inflateEnd(z_stream *strm) { return Z_OK; }

/* zlib-ng compatibility: also provide zng_ prefixed names */
#define zng_deflateInit2 deflateInit2
#define zng_deflateReset deflateReset
#define zng_deflate deflate
#define zng_deflateEnd deflateEnd
#define zng_inflateInit inflateInit
#define zng_inflateReset inflateReset
#define zng_inflate inflate
#define zng_stream z_stream

#endif
