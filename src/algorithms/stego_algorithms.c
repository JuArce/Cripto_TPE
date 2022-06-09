#include <stdio.h>
#include <stdint.h>

#include "./stego_algorithms.h"
#include "../logger/logger.h"


#define LSB1_MASK 0xFE


void lsb1_embed(uint8_t * carrier, size_t * carrier_size, uint8_t * hide, size_t * hide_size) {
    if(*hide_size * 8 > *carrier_size) {
    	log(FATAL, "File to hide can not fit into carrier");
    }

	for(size_t i = 0; i < *hide_size; i++) {
		carrier[i] = hide[i];
	}
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
