#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "./stego_algorithms.h"
#include "../logger/logger.h"


#define LSB1_MASK 0xFE
#define LSB1_SIZE_FACTOR 8
#define LSB1_OPERATIONS 8

#define LSB4_MASK 0xF0
#define LSB4_SIZE_FACTOR 2
#define LSB4_OPERATIONS 2

#define LSBI_MASK LSB1_MASK
#define LSBI_PATTERN_MASK 0x03 /* 0000 0011 */ 
#define LSBI_SIZE_FACTOR 8
#define LSBI_OPERATIONS 8
#define LSBI_PATTERN_SIZE 4


typedef struct patterns_changes_struct {
    uint32_t changes;
    uint32_t no_changes;
} patterns_changes_struct;

static uint8_t get_i_bit(uint8_t byte, uint8_t i);
static void set_ls_bit(uint8_t * byte, uint8_t value);
static uint8_t get_i_nibble(uint8_t byte, uint8_t i);
static void set_ls_nibble(uint8_t * byte, uint8_t value);
static uint8_t get_pattern_index(uint8_t byte);


void lsb1_embed(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hide, uint32_t * hide_size) {
    if(*hide_size * LSB1_SIZE_FACTOR > carrier_size) log(FATAL, "File to hide can not fit into carrier");

    uint32_t i = 0;
    for(uint32_t j = 0; j < *hide_size; j++) {
        for(int k = LSB1_OPERATIONS; k > 0; k--) {
            uint8_t bit = get_i_bit((*hide)[j], k);
            set_ls_bit(carrier + i++, bit);
        }
    }
}

void lsb1_extract(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hidden, uint32_t * hidden_size) {
    *hidden_size = carrier_size / LSB1_SIZE_FACTOR;

    *hidden = calloc(1, *hidden_size);
    if(NULL == *hidden) log(FATAL, "%s", strerror(errno));

    uint8_t byte = 0;
    uint32_t hidden_iter = 0;
    for(uint32_t i = 0, j = 0; i < carrier_size; i++) {
        uint8_t bit = get_i_bit(carrier[i], 1);
        byte <<= 1;
        byte |= bit;
        j++;
        if(j % LSB1_OPERATIONS == 0) {
            (*hidden)[hidden_iter++] = byte;
            byte = 0;
            j = 0;
        }   
    }
}

void lsb4_embed(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hide, uint32_t * hide_size) {
    if(*hide_size * LSB4_SIZE_FACTOR > carrier_size) log(FATAL, "File to hide can not fit into carrier");

    uint32_t i = 0;
    for(uint32_t j = 0; j < *hide_size; j++) {
        for(int k = LSB4_OPERATIONS; k > 0; k--) {
            uint8_t nibble = get_i_nibble((*hide)[j], k);
            set_ls_nibble(carrier + i++, nibble);
        }
    }
}

void lsb4_extract(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hidden, uint32_t * hidden_size) {
    *hidden_size = carrier_size / LSB4_SIZE_FACTOR;

    *hidden = calloc(1, *hidden_size);
    if(NULL == *hidden) log(FATAL, "%s", strerror(errno));

    uint8_t byte = 0;
    uint32_t hidden_iter = 0;
    for(uint32_t i = 0, j = 0; i < carrier_size; i++) {
        uint8_t nibble = get_i_nibble(carrier[i], 1);
        byte <<= 4;
        byte |= nibble;
        if(++j % LSB4_OPERATIONS == 0) {
            (*hidden)[hidden_iter++] = byte;
            byte = 0;
            j = 0;
        }
    }
}

void lsbi_embed() {
    printf("lsb i embed\n");
    /*patterns_changes_struct pattern_changes[LSBI_PATTERN_SIZE];
    memset(&pattern_changes, 0, sizeof(pattern_changes));*/
}

void lsbi_extract(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hidden, uint32_t * hidden_size) {
    *hidden_size = carrier_size / LSBI_SIZE_FACTOR;

    *hidden = calloc(1, *hidden_size);
    if(NULL == *hidden) log(FATAL, "%s", strerror(errno));

    uint8_t byte = 0;
    uint32_t hidden_iter = 0;

    uint8_t * aux_carrier = carrier;

    uint8_t patterns[LSBI_PATTERN_SIZE] = {0};
    /* Extract 4 bits patterns */ 
    for(uint32_t i = 0; i < LSBI_PATTERN_SIZE; i++) {
        uint8_t bit = get_i_bit(aux_carrier[i], 1);
        patterns[i] = bit;
    }

    aux_carrier += LSBI_PATTERN_SIZE;
    /* Extract all the data */
    for(uint32_t i = 0, j = 0; i < carrier_size - LSBI_PATTERN_SIZE; i++) {
        uint8_t pattern_index = get_pattern_index(aux_carrier[i]);
        uint8_t bit = get_i_bit(aux_carrier[i], 1);
        if(patterns[pattern_index] == 1) {
            bit = bit == 1 ? 0 : 1;
        }
        byte <<= 1;
        byte |= bit;
        j++;
        if(j % LSBI_OPERATIONS == 0) {
            (*hidden)[hidden_iter++] = byte;
            byte = 0;
            j = 0;
        }   
    }
}


/**
    Return the i_th bit from byte
    i in range (1, ..., 8)
    1 is the less significative bit
    |____|____|
    |8   |   1|
*/
static uint8_t get_i_bit(uint8_t byte, uint8_t i) {
    return (byte >> (i - 1)) & 1;
}

/**
    Set the Less Significative bit (ls)
    |____|___*|
    |    |ls b|
*/
static void set_ls_bit(uint8_t * byte, uint8_t value) {
    //log(DEBUG, "%d", value);
    if(value > 1) {
        log(FATAL, "Invalid bit value");
    }

    *byte = (*byte & LSB1_MASK) | value;
}

/**
    Return the i_th nibble from byte
    i in range (1, 2)
    1 is the less significative nibble
    |____|____|
    |2nd |1st |
*/
static uint8_t get_i_nibble(uint8_t byte, uint8_t i) {
    return (byte >> ((i - 1) * 4)) & 0xF;
}

/**
    Set the Less Significative nibble (ls)
    |____|____|
    |    |ls n|
*/
static void set_ls_nibble(uint8_t * byte, uint8_t value) {
    //log(DEBUG, "%d", value);
    if(value > 0xF) {
        log(FATAL, "Invalid nibble value");
    }

    *byte = (*byte & LSB4_MASK) | value;
}

/**
    Return 
    |____|____|
    |____|_ba_|

    Output: ab in range (0, ..., 3)
*/
static uint8_t get_pattern_index(uint8_t byte) {
    return (get_i_bit(byte, 2) << 1) | get_i_bit(byte, 3);
}
