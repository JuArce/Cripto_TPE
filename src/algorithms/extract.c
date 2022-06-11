#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <endian.h>
#include <errno.h>

#include "extract.h"
#include "../files/bmp.h"
#include "../files/file.h"
#include "../logger/logger.h"


void extract(files f, stego_strategy stego_strategy_fn) {
    log(INFO, "Extracting file, please wait...");
    
    bmp_image image = read_carrier_file(f);

    uint8_t * image_data = get_image_data(image);
    uint32_t image_data_size = get_image_size(image);

    uint8_t * hidden_data = NULL;
    uint32_t hidden_data_size = 0;

    stego_strategy_fn(image_data, image_data_size, &hidden_data, &hidden_data_size);

    uint32_t data_size; 
    memcpy(&data_size, hidden_data, sizeof(uint32_t));
    data_size = be32toh(data_size);

    uint32_t data_offset = sizeof(uint32_t);
    uint32_t extension_offset = data_offset + data_size;

    uint8_t * data = calloc(1, data_size);
    if(NULL == data) log(FATAL, "%s", strerror(errno));
    memcpy(data, hidden_data + data_offset, data_size);

    char * extension = (char *)hidden_data + extension_offset;
    
    write_output_file(f, data, data_size, extension);

    free(hidden_data);
    free(data);
    free_carrier_file(image);

    log(INFO, "File extracted correctly");
}
