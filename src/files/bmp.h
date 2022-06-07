#ifndef BMP_H
#define BMP_H

typedef struct bmp_image_struct * bmp_image;


bmp_image read_image(FILE * fp);

void free_image(bmp_image image);

void write_image(bmp_image image, FILE * fp);

#endif