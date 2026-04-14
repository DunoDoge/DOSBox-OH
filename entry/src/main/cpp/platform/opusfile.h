#ifndef OPUSFILE_H_STUB
#define OPUSFILE_H_STUB

/*
 * Stub opusfile.h for OHOS platform where libopusfile is not available.
 * Provides type definitions and stub functions needed by opus.cpp.
 */

#include <cstdint>
#include <cstdlib>

/* opus integer types */
typedef int16_t opus_int16;
typedef int64_t opus_int64;

/* ogg integer types */
typedef int64_t ogg_int64_t;

/* OpusFileCallbacks structure - IO callback functions */
typedef struct OpusFileCallbacks {
    int (*read)(void*, unsigned char*, int);
    int (*seek)(void*, opus_int64, int);
    opus_int64 (*tell)(void*);
    int (*close)(void*);
} OpusFileCallbacks;

/* OggOpusFile - opaque handle */
struct OggOpusFile;
typedef struct OggOpusFile OggOpusFile;

/* OpusHead - stream header info */
typedef struct OpusHead {
    int version;
    int channel_count;
    unsigned int pre_skip;
    unsigned int input_sample_rate;
    int stream_count;
} OpusHead;

/* OpusTags - comment metadata */
typedef struct OpusTags {
    char *vendor;
    int comments;
    char **user_comments;
} OpusTags;

/* Error codes */
#define OP_FALSE        (-1)
#define OP_EOF          (-2)
#define OP_HOLE         (-3)
#define OP_EREAD        (-4)
#define OP_EFAULT       (-5)
#define OP_EIMPL        (-6)
#define OP_EINVAL       (-7)
#define OP_ENOTFORMAT   (-8)
#define OP_EBADHEADER   (-9)
#define OP_EVERSION     (-10)
#define OP_ENOTAUDIO    (-11)
#define OP_EBADPACKET   (-12)
#define OP_EBADLINK     (-13)
#define OP_ENOSEEK      (-14)
#define OP_EBADTIMESTAMP (-15)

/* Stub functions - these are no-ops on OHOS */
inline OggOpusFile *op_open_callbacks(void*, const OpusFileCallbacks*,
                                       const unsigned char*, size_t, int*) { return nullptr; }
inline void op_free(OggOpusFile*) {}
inline const OpusHead *op_head(const OggOpusFile*, int) { return nullptr; }
inline const OpusTags *op_tags(const OggOpusFile*, int) { return nullptr; }
inline int op_seekable(const OggOpusFile*) { return 0; }
inline int op_serialno(const OggOpusFile*, int) { return 0; }
inline ogg_int64_t op_pcm_total(const OggOpusFile*, int) { return 0; }
inline int op_pcm_seek(const OggOpusFile*, ogg_int64_t) { return -1; }
inline int op_read(const OggOpusFile*, opus_int16*, int, int*) { return 0; }

#endif
