#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <endian.h>
#include <errno.h>

#include "embed.h"
#include "../files/bmp.h"
#include "../files/file.h"
#include "../logger/logger.h"


static uint8_t * get_data_to_embed(uint8_t * file_data, uint32_t file_data_size, char * file_extension, uint32_t * embed_size);

void embed(files f, stego_strategy stego_strategy_fn, crypto_cfg crypto_cfg_ptr) {
    log(INFO, "Embeding file, please wait...");

    bmp_image image = read_carrier_file(f);
    file input_file = read_input_file(f);

    uint8_t * image_data = get_image_data(image);
    uint32_t image_data_size = get_image_size(image);

    uint8_t * file_data = get_file_data(input_file);
    uint32_t file_data_size = get_file_data_size(input_file);
    char * file_extension = get_file_extension(input_file);

    uint32_t to_hide_size = 0;
    uint8_t * to_hide_data = get_data_to_embed(file_data, file_data_size, file_extension, &to_hide_size);

    if(NULL != crypto_cfg_ptr) {
        uint32_t ciphertext_size;

        uint8_t * ciphertext = run_crypto_config(crypto_cfg_ptr, to_hide_data, to_hide_size, &ciphertext_size);
        free(to_hide_data);

        to_hide_size = sizeof(uint32_t) + ciphertext_size;
        to_hide_data = calloc(1, to_hide_size);
        
        ((uint32_t *) to_hide_data)[0] = htobe32(ciphertext_size);
        memcpy(to_hide_data + sizeof(uint32_t), ciphertext, ciphertext_size);

        free(ciphertext);    
    }
    
    stego_strategy_fn(image_data, image_data_size, &to_hide_data, &to_hide_size);

    free(to_hide_data);

    write_output_image(f, image);

    free_carrier_file(image);
    free_file(input_file);

    log(INFO, "File embed correctly");
}

static uint8_t * get_data_to_embed(uint8_t * file_data, uint32_t file_data_size, char * file_extension, uint32_t * embed_size) {
    *embed_size = sizeof(uint32_t) + file_data_size + strlen(file_extension) + 1;
    uint8_t * to_hide_data = calloc(1, *embed_size);
    if(NULL == to_hide_data) log(FATAL, "%s", strerror(errno));

    uint32_t data_offset = sizeof(uint32_t);
    uint32_t extension_offset = data_offset + file_data_size;
    
    uint32_t be_data_size = htobe32(file_data_size);

    memcpy(to_hide_data, &be_data_size, sizeof(uint32_t));
    memcpy(to_hide_data + data_offset, file_data, file_data_size);
    memcpy(to_hide_data + extension_offset, file_extension, strlen(file_extension));

    return to_hide_data;
}
