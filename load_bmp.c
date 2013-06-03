#include <stdio.h>
#include <stdlib.h>
#include "loadBMP.h"
static BMP_HDR *bmp_hdr;
static DIB_HDR *dib_hdr;
static char *extra;
static uint32_t dib_size;

int load_BMP(const char *filepath, ColorRGBA **img_data)
{
    FILE *fh;
    if (!(fh = fopen(filepath,"rb"))) {
        printf("Error occured while opening file\n");
        return -1;
    }

    // Load Headers
    bmp_hdr = malloc(sizeof(BMP_HDR));

    if (!fread((void *)bmp_hdr, 14, 1, fh)) {
        printf("Failed to read BMP header data\n");
        return -1;
    }
    fread(&dib_size, sizeof(uint32_t), 1, fh); 

    dib_hdr = (DIB_HDR*)malloc(dib_size);
    if (!fread((void *)dib_hdr, dib_size, 1, fh)) {
    }

    printf("sizes: %u %u\n", sizeof(BMP_HDR), dib_hdr->bit_depth);
    printf("size colorRGBA: %u \n", sizeof(ColorRGBA));
    // Read if pixel_data is less than 2MB
    if (dib_size < 2097152) {
        printf("reading pixel data\n");
        fseek(fh, bmp_hdr->px_offset, SEEK_SET);

        *img_data = (ColorRGBA*)malloc(dib_hdr->data_size);

        printf("size of image_data %d\n", dib_hdr->data_size);
        if (!fread((void *)*img_data, dib_hdr->data_size, 1, fh)) {
            printf("Failed to read BMP pixel data\n");
            return -1;
        }
    }
    return 0;
}

void print_headers()
{
    printf("BMP width %d\n", dib_hdr->width);
    printf("BMP height %d\n", dib_hdr->height);
}
int write_BMP(const char *filename, ColorRGBA *img_data)
{
    printf("Writing bitmap\n");
    FILE *fh = fopen(filename, "wb");
    fwrite((void*)bmp_hdr, 14, 1, fh);
    fwrite((void*)&dib_size, 4, 1, fh);
    fwrite((void*)dib_hdr, dib_size, 1, fh);
    fwrite((void*)img_data, dib_hdr->width*dib_hdr->height, 1, fh);
    fclose(fh);
    return 0;
}
int bmp_free(ColorRGBA *img_data)
{
    free(bmp_hdr);
    free(dib_hdr);
}
void average_grayscale(ColorRGBA *img_data)
{
    printf("converting to grayscale\n");
    int i;
    for (i = 0; i < dib_hdr->width*dib_hdr->height; i++) {
        uint8_t avg = (img_data[i].r + img_data[i].g + img_data[i].b)/3;
        img_data[i].r = avg;
        img_data[i].g = avg;
        img_data[i].b = avg;
    }
}
int main() 
{
    ColorRGBA *img_data;
    load_BMP("lena.bmp", &img_data);
    printf("first pixel:%d\n",img_data[0].b);
    print_headers();
    average_grayscale(img_data);
    write_BMP("test2.bmp", img_data);
    bmp_free(img_data);
    return 0;
}
