#include <stdio.h>
#include <stdlib.h>
#include "loadBMP.h"

static BMP_HDR *bmp_hdr;
static DIB_HDR *dib_hdr;
static char *extra;
static uint32_t dib_size;
char *compression[] = {"BI_RGB","BI_RLE8","BI_RLE4", "BI_BITFIELDS",
                     "BI_JPEG","BI_PNG","BI_ALPHABITFIELDS"};

int loadBMP(const char *filepath, IMAGE **image)
{
    FILE *fh;
    ColorRGB *img_data;
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

    //Load DIB Header
    fread(&dib_size, sizeof(uint32_t), 1, fh); 

    if (dib_size != BITMAPINFOHEADER) {
        printf("Unsupported DIB Header of size %u", dib_size);
        return -1;
    }

    fseek(fh, -sizeof(uint32_t), SEEK_CUR);
    dib_hdr = (DIB_HDR*)malloc(dib_size);

    if (!fread((void *)dib_hdr, dib_size, 1, fh)) {
        printf("Failed to read DIB header data\n");
        return -1;
    }

    #ifdef DEBUG
        printf("sizes: %u %u\n", sizeof(BMP_HDR), dib_hdr->bit_depth);
        printf("size colorRGBA: %u \n", sizeof(ColorRGB));
    #endif

    // Read if pixel_data is less than 2MB
    if (dib_size < 2097152) {
        fseek(fh, bmp_hdr->px_offset, SEEK_SET);

        img_data = (ColorRGB*)malloc(dib_hdr->data_size);

        #ifdef DEBUG
            printf("reading pixel data\n");
            printf("size of image_data %d\n", dib_hdr->data_size);
        #endif

        if (!fread((void *)img_data, sizeof(ColorRGB),
                    dib_hdr->data_size/sizeof(ColorRGB), fh)) {
            printf("Failed to read BMP pixel data\n");
            return -1;
        }
    }
    #ifdef DEBUG
        uint32_t beg = ftell(fh);
        fseek(fh, 0, SEEK_END);
        uint32_t end = ftell(fh);
        
        printf("Finished: %u/%u\n", beg, end);
    #endif
    *image = malloc(sizeof(IMAGE));
    (*image)->data = img_data;
    (*image)->width = dib_hdr->width;
    (*image)->height = dib_hdr->height;
    return 0;
}

void print_headers()
{
    printf("BMP width %d\n", dib_hdr->width);
    printf("BMP height %d\n", dib_hdr->height);
}

int writeBMP(const char *filename, IMAGE *img)
{
    #ifdef DEBUG
        printf("\nWriting bitmap\n");
        printf("sizes %u %u",sizeof(BMP_HDR),sizeof(DIB_HDR));
    #endif
    FILE *fh = fopen(filename, "wb");
    fwrite((void*)bmp_hdr, 14, 1, fh);
    fwrite((void*)dib_hdr, 40, 1, fh);
    fwrite((void*)img->data, sizeof(ColorRGB),
            dib_hdr->width*dib_hdr->height, fh);
    fclose(fh);
    return 0;
}

int freeBMP(IMAGE *img_data)
{
    free(bmp_hdr);
    free(dib_hdr);
}
