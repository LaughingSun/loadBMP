#include <stdint.h>

#define BITMAPCOREHEADER    12
#define BITMAPCOREHEADER2   64
#define BITMAPINFOHEADER    40
#define BITMAPV2INFOHEADER  52
#define BITMAPV3INFOHEADER  56
#define BITMAPV4INFOHEADER  108
#define BITMAPV5INFOHEADER  124

#pragma pack(push, 1)
typedef struct {
    uint16_t magic;
    uint32_t size;
    uint32_t unused;
    uint32_t px_offset;
} BMP_HDR;
#pragma(pop)

#pragma pack(push, 1)
typedef struct {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t n_color_planes;
    uint16_t bit_depth;
    uint32_t compression;
    uint32_t data_size;
    int32_t h_res;
    int32_t v_res;
    uint32_t palette_size;
    uint32_t n_imp_colors;
} DIB_HDR;
#pragma(pop)

typedef struct {
    uint32_t R_MASK;
    uint32_t G_MASK;
    uint32_t B_MASK;
    uint32_t A_MASK;
    uint32_t color_space;
} COLOR_TABLE;

typedef struct {
    uint8_t b;
    uint8_t g;
    uint8_t r;
} ColorRGB;

typedef struct {
    int32_t width;
    int32_t height;
    ColorRGB *data;
} IMAGE;

int writeBMP(const char *filename, IMAGE *img);
int loadBMP(const char *filepath, IMAGE **image);
int freeBMP(IMAGE *img_data);
