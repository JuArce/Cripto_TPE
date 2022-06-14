#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "./stego_algorithms.h"
#include "../logger/logger.h"


#define LSB1_MASK 0xFE /* 1111 1110 */
#define LSB1_SIZE_FACTOR 8
#define LSB1_OPERATIONS 8

#define LSB4_MASK 0xF0 /* 1111 0000 */
#define LSB4_SIZE_FACTOR 2
#define LSB4_OPERATIONS 2

#define LSBI_MASK LSB1_MASK /* 1111 1110 */
#define LSBI_PATTERN_MASK 0x03 /* 0000 0011 */ 
#define LSBI_SIZE_FACTOR 8
#define LSBI_OPERATIONS 8
#define LSBI_PATTERN_SIZE 4 /* 00 | 01 | 11 | 10 */ 


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
    log(DEBUG, "Using LSB1 embed");

    if(*hide_size * LSB1_SIZE_FACTOR > carrier_size) log(FATAL, "File to hide can not fit into carrier. "
        "Max size is %.2f KB (%u bytes)", (float)carrier_size / LSB1_SIZE_FACTOR / 1024, carrier_size / LSB1_SIZE_FACTOR);

    uint32_t i = 0;
    for(uint32_t j = 0; j < *hide_size; j++) {
        for(int k = LSB1_OPERATIONS; k > 0; k--) {
            uint8_t bit = get_i_bit((*hide)[j], k);
            set_ls_bit(carrier + i++, bit);
        }
    }
}

void lsb1_extract(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hidden, uint32_t * hidden_size) {
    log(DEBUG, "Using LSB1 extract");

    *hidden_size = carrier_size / LSB1_SIZE_FACTOR;

    *hidden = calloc(1, *hidden_size);
    if(NULL == *hidden) log(FATAL, "%s", strerror(errno));

    uint8_t byte = 0;
    uint32_t hidden_iter = 0;
    for(uint32_t i = 0, j = 0; i < carrier_size; i++) {
        uint8_t bit = get_i_bit(carrier[i], 1);
        byte <<= 1;
        byte |= bit;
        if(++j % LSB1_OPERATIONS == 0) {
            (*hidden)[hidden_iter++] = byte;
            byte = 0;
            j = 0;
        }   
    }
}

void lsb4_embed(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hide, uint32_t * hide_size) {
    log(DEBUG, "Using LSB4 embed");
    
    if(*hide_size * LSB4_SIZE_FACTOR > carrier_size) log(FATAL, "File to hide can not fit into carrier. "
        "Max size is %.2f KB (%u bytes)", (float)carrier_size / LSB4_SIZE_FACTOR / 1024, carrier_size / LSB4_SIZE_FACTOR);

    uint32_t i = 0;
    for(uint32_t j = 0; j < *hide_size; j++) {
        for(int k = LSB4_OPERATIONS; k > 0; k--) {
            uint8_t nibble = get_i_nibble((*hide)[j], k);
            set_ls_nibble(carrier + i++, nibble);
        }
    }
}

void lsb4_extract(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hidden, uint32_t * hidden_size) {
    log(DEBUG, "Using LSB4 extract");
    
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

void lsbi_embed(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hide, uint32_t * hide_size) {
    log(DEBUG, "Using LSBI embed");
    
    if(*hide_size * LSBI_SIZE_FACTOR + LSBI_PATTERN_SIZE > carrier_size) log(FATAL, "File to hide can not fit into carrier. "
        "Max size is %.2f KB (%u bytes)", ((float)carrier_size / LSBI_SIZE_FACTOR - LSBI_PATTERN_SIZE) / 1024, carrier_size / LSBI_SIZE_FACTOR - LSBI_PATTERN_SIZE);

    patterns_changes_struct pattern_changes[LSBI_PATTERN_SIZE] = {0};

    /* Count quantity of bit changes and no changes */
    uint32_t carrier_index = 0;
    for(uint32_t j = 0; j < *hide_size; j++) {
        for(int k = LSBI_OPERATIONS; k > 0; k--) {
            uint8_t hide_bit = get_i_bit((*hide)[j], k);
            uint8_t carrier_bit = get_i_bit(carrier[carrier_index], 1);
            uint8_t pattern_index = get_pattern_index(carrier[carrier_index++]);
            hide_bit == carrier_bit ? 
                pattern_changes[pattern_index].no_changes++ : pattern_changes[pattern_index].changes++; 
        }
    }

    
    uint8_t patterns[LSBI_PATTERN_SIZE] = {0};
    /** Set 4 bits patterns 
     *  If no changes is greater or equals than changes then set pattern value to 0
     *  Else set value to 1
     *  0 -> No invert 
     *  1 -> Invert  
     */ 
    for(uint32_t i = 0; i < LSBI_PATTERN_SIZE; i++) {
        patterns[i] = pattern_changes[i].no_changes < pattern_changes[i].changes ? 1 : 0;
    }

    /** Embed the 4 bits patterns at begin
     *  Carrier     |____|___a| |____|___b| |____|___c| |____|___d|
     *  Patterns    |abcd|
     */
    uint32_t i = 0;
    for(uint32_t j = 0; j < LSBI_PATTERN_SIZE; j++) {
        set_ls_bit(carrier + i++, patterns[j]);
    }

    /** Embed all the data after the 4 bits patterns
     *  Carrier     |____|___a| |____|___b| |____|___c| |____|___d|...
     *  Patterns    |abcd|
     *
     *  Carrier + 4 ...|____|___a|...
     *  To hide     |a___|____|...
     */
    for(uint32_t j = 0; j < *hide_size; j++) {
        for(int k = LSBI_OPERATIONS; k > 0; k--) {
            uint8_t bit = get_i_bit((*hide)[j], k);
            uint8_t pattern_index = get_pattern_index(carrier[i]);
            set_ls_bit(carrier + i++, patterns[pattern_index] == 1 ? !bit : bit);
        }
    }
}

void lsbi_extract(uint8_t * carrier, uint32_t carrier_size, uint8_t ** hidden, uint32_t * hidden_size) {
    log(DEBUG, "Using LSBI extract");
    
    *hidden_size = carrier_size / LSBI_SIZE_FACTOR;

    *hidden = calloc(1, *hidden_size);
    if(NULL == *hidden) log(FATAL, "%s", strerror(errno));

    uint8_t byte = 0;
    uint32_t hidden_iter = 0;
    uint32_t carrier_iter = 0;
    uint8_t patterns[LSBI_PATTERN_SIZE] = {0};

    /** Extract 4 bits patterns 
     *  Carrier     |____|___a| |____|___b| |____|___c| |____|___d|...
     *  Patterns    [a, b, c, d]
     */ 
    for(carrier_iter = 0; carrier_iter < LSBI_PATTERN_SIZE; carrier_iter++) {
        uint8_t bit = get_i_bit(carrier[carrier_iter], 1);
        patterns[carrier_iter] = bit;
    }

    /** Extract all the data after the 4 bits patterns
     *  Carrier     |____|___a| |____|___b| |____|___c| |____|___d|...
     *  Patterns    |abcd|
     *
     *  Carrier + 4 ...|____|___a|...
     *  Hidden      |a___|____|...
     */
    for(uint32_t j = 0; carrier_iter < carrier_size; carrier_iter++) {
        uint8_t pattern_index = get_pattern_index(carrier[carrier_iter]);
        uint8_t bit = get_i_bit(carrier[carrier_iter], 1);
        if(patterns[pattern_index] == 1) {
            bit = bit == 1 ? 0 : 1;
        }
        byte <<= 1;
        byte |= bit;
        if(++j % LSBI_OPERATIONS == 0) {
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
    if(value > 0xF) {
        log(FATAL, "Invalid nibble value");
    }

    *byte = (*byte & LSB4_MASK) | value;
}

/**
    |____|____|
    |____|_ba_|

    Output: ab in range (0, ..., 3)
*/
static uint8_t get_pattern_index(uint8_t byte) {
    return (get_i_bit(byte, 2) << 1) | get_i_bit(byte, 3);
}
