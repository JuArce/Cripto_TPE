#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "./stego_algorithms.h"
#include "../logger/logger.h"


#define LSB1_MASK 0xFE
#define LSB4_MASK 0xF0


static uint8_t get_i_bit(uint8_t byte, uint8_t i);
static void set_ls_bit(uint8_t * byte, uint8_t value);


void lsb1_embed(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hide, uint32_t * hide_size) {
    if(*hide_size * 8 > carrier_size) log(FATAL, "File to hide can not fit into carrier");

    uint32_t i = 0;
    for(uint32_t j = 0; j < *hide_size; j++) {
        for(int k = 8; k > 0; k--) {
            uint8_t bit = get_i_bit((*hide)[j], k);
            set_ls_bit(carrier + i++, bit);
        }
    }
}

void lsb1_extract(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hidden, uint32_t * hidden_size) {
    *hidden_size = carrier_size / 8;

    *hidden = calloc(1, *hidden_size);
    if(NULL == *hidden) log(FATAL, "%s", strerror(errno));

    uint8_t byte = 0;
    uint32_t hidden_iter = 0;
    for(uint32_t i = 0, j = 0; i < carrier_size; i++) {
        uint8_t bit = get_i_bit(carrier[i], 1);
        byte <<= 1;
        byte |= bit;
        j++;
        if(j % 8 == 0) {
            j = 0;
            (*hidden)[hidden_iter++] = byte;
            byte = 0;
        }   
    }
}

void lsb4_embed() {
    printf("lsb 4 embed\n");
}

void lsb4_extract() {
    printf("lsb4 extract\n");
}

void lsbi_embed() {
    printf("lsb i embed\n");
}

void lsbi_extract() {
    printf("lsbi extract\n");
}


/**
    Return the i_th bit from byte
    i in range (1, ..., 8)
    1 is the less significative bit
*/
static uint8_t get_i_bit(uint8_t byte, uint8_t i) {
    return (byte >> (i - 1)) & 1;
}

/**
    Set the Less Significative bit (ls)
*/
static void set_ls_bit(uint8_t * byte, uint8_t value) {
    //log(DEBUG, "%d", value);
    if(value != 0 && value != 1) {
        log(FATAL, "Invalid bit value");
    }

    *byte = (*byte & LSB1_MASK) | value;
}
