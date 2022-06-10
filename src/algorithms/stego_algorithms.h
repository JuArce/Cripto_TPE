#ifndef STEGO_ALGORITHMS_H
#define STEGO_ALGORITHMS_H

#include <stdint.h>


void lsb1_embed(uint8_t * carrier, uint32_t * carrier_size, uint8_t * hide, uint32_t * hide_size);

void lsb1_extract();

void lsb4_embed();

void lsb4_extract();

void lsbi_embed();

void lsbi_extract();

#endif