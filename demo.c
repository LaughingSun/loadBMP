// Example BMP color-to-greyscale program
#include <stdio.h>
#include "loadBMP.h"

void average_greyscale(IMAGE *img)
{
    printf("Converting to greyscale\n");
    int i;
    for (i = 0; i < img->width*img->height; i++) {
        uint8_t avg = (img->data[i].r + img->data[i].g + img->data[i].b)/3;
        img->data[i].r = avg;
        img->data[i].g = avg;
        img->data[i].b = avg;
    }
}

int main() 
{
    IMAGE *img;
    loadBMP("lena.bmp", &img);

    average_greyscale(img);

    writeBMP("demo.bmp", img);
    freeBMP(img);
    return 0;
}
