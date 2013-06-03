#include <stdint.h>

#pragma pack(push, 1)
typedef struct BMP_HDR {
    uint16_t magic;
    uint32_t size;
    uint32_t unused;
    uint32_t px_offset;
} BMP_HDR;
#pragma(pop)

#pragma pack(push, 1)
typedef struct DIB_HDR {
    uint32_t width;
    uint32_t height;
    uint16_t n_color_planes;
    uint16_t bit_depth;
    uint32_t compression;
    uint32_t data_size;
    uint32_t h_res;
    uint32_t v_res;
    uint32_t palette_size;
    uint32_t n_imp_colors;
    uint32_t R_MASK;
    uint32_t G_MASK;
    uint32_t B_MASK;
    uint32_t A_MASK;
    uint32_t color_space;
    // ignore rest
} DIB_HDR;
#pragma(pop)

typedef struct ColorRGBA {
    uint8_t b;
    uint8_t g;
    uint8_t r;
//    uint8_t a;
} ColorRGBA;
