#include <stdio.h>

#include "./stego_algorithms.h"
#include "../logger/logger.h"


#define LSB1_MASK 0xFE
#define LSB4_MASK 0xF0


static uint8_t get_i_bit(uint8_t byte, uint8_t i);
static void set_last_bit(uint8_t * byte, uint8_t value);


void lsb1_embed(uint8_t * carrier, uint32_t * carrier_size, uint8_t * hide, uint32_t * hide_size) {
    if(*hide_size * 8 > *carrier_size) {
        log(FATAL, "File to hide can not fit into carrier");
    }

    uint32_t i = 0;
    for(uint32_t j = 0; j < *hide_size; j++) {
        for(int k = 1; k <= 8; k++) {
            uint8_t bit = get_i_bit(hide[j], k);
            set_last_bit(carrier + i++, bit);
        }
    }
}

/**
    Return the i_th bit from byte
    i in range (1, ..., 8)
*/
static uint8_t get_i_bit(uint8_t byte, uint8_t i) {
    return (byte >> (i - 1)) & 1;
}

/**
    
*/
static void set_last_bit(uint8_t * byte, uint8_t value) {
    //log(DEBUG, "%d", value);
    if(value != 0 && value != 1) {
        log(FATAL, "Invalid bit value");
    }

    *byte = (*byte & LSB1_MASK) | value;
}

void lsb1_extract() {
    printf("lsb1 extract\n");
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
