#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "bmp.h"
#include "../logger/logger.h"

#define HEADER_SIZE 54
#define BMP 0x4d42
#define PIXEL_SIZE 3


typedef struct __attribute__((packed)) bmp_header_struct  {             // Total: 54 bytes
  uint16_t  type;             // Magic identifier: 0x4d42
  uint32_t  size;             // File size in bytes
  uint16_t  reserved1;        // Not used
  uint16_t  reserved2;        // Not used
  uint32_t  offset;           // Offset to image data in bytes from beginning of file (54 bytes)
  uint32_t  dib_header_size;  // DIB Header size in bytes (40 bytes)
  int32_t   width_px;         // Width of the image
  int32_t   height_px;        // Height of image
  uint16_t  num_planes;       // Number of color planes
  uint16_t  bits_per_pixel;   // Bits per pixel
  uint32_t  compression;      // Compression type
  uint32_t  image_size_bytes; // Image size in bytes
  int32_t   x_resolution_ppm; // Pixels per meter
  int32_t   y_resolution_ppm; // Pixels per meter
  uint32_t  num_colors;       // Number of colors  
  uint32_t  important_colors; // Important colors 
} bmp_header_struct;

/*
typedef struct __attribute__((packed)) Pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alpha;
} Pixel;
*/ 

typedef struct bmp_image_struct {
    bmp_header_struct header;
    uint8_t * data;
} bmp_image_struct;


static void read_header(FILE * fp, bmp_image image);
static void read_image_data(FILE * fp, bmp_image image);
//static void check_bmp_header(bmp_image image);


/**
    Assume that the file is already open.
    Do not close the file.
*/
bmp_image read_image(FILE * fp) {
    log(INFO, "Reading bmp image");
    bmp_image image = calloc(1, sizeof(bmp_image_struct));

    if(NULL == image) {
        //TODO handle error
    }

    read_header(fp, image);
    read_image_data(fp, image);

    return image;
}

void free_image(bmp_image image) {
    free(image->data);
    free(image);
}

/*void write_image(bmp_image image, FILE * fp) {

}*/

static void read_header(FILE * fp, bmp_image image) {
    uint8_t raw_header[HEADER_SIZE];
    fread(&raw_header, 1, HEADER_SIZE, fp);

    //image->header = (bmp_header_struct) raw_header; //Not works :(
    memcpy(&image->header, raw_header, HEADER_SIZE); //It works
}

/**
    Read data from a bmp_image with a valid header
*/
static void read_image_data(FILE * fp, bmp_image image) {
    int data_size = PIXEL_SIZE * image->header.width_px * image->header.height_px;
    image->data = malloc(data_size);
    fread(image->data, 1, data_size, fp);
}


/**
    Check:
        type == 0x4d42
        
*/
/*
static void check_bmp_header(bmp_image image) {
    
}
*/