#ifndef STEGO_ALGORITHMS_H
#define STEGO_ALGORITHMS_H

void lsb1_embed(uint8_t * carrier, size_t * carrier_size, uint8_t * hide, size_t * hide_size);

void lsb1_extract();

void lsb4_embed();

void lsb4_extract();

void lsbi_embed();

void lsbi_extract();

#endif