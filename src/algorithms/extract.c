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


void extract(files f, stego_strategy stego_strategy_fn, crypto_cfg crypto_cfg_ptr) {
    log(INFO, "Extracting file, please wait...");
    
    bmp_image image = read_carrier_file(f);

    uint8_t * image_data = get_image_data(image);
    uint32_t image_data_size = get_image_size(image);

    uint8_t * hidden_data = NULL;
    uint32_t hidden_data_size = 0;

    stego_strategy_fn(image_data, image_data_size, &hidden_data, &hidden_data_size);

    if(NULL != crypto_cfg_ptr) {
        uint32_t plaintext_size;

        uint32_t cipher_size = be32toh(((uint32_t *)hidden_data)[0]);

        uint8_t * plaintext = run_crypto_config(crypto_cfg_ptr, hidden_data + sizeof(uint32_t), cipher_size, &plaintext_size);
        free(hidden_data);
        
        hidden_data = plaintext;
        hidden_data_size = plaintext_size;
    }

    uint32_t data_size = be32toh(((uint32_t *)hidden_data)[0]);
    uint8_t * data = hidden_data + sizeof(uint32_t);
    char * extension = (char *)hidden_data + sizeof(uint32_t) + data_size;

    if(data_size > hidden_data_size) log(FATAL, "Invalid data size");

    write_output_file(f, data, data_size, extension);

    free(hidden_data);
    free_carrier_file(image);

    log(INFO, "File extracted correctly");
}
