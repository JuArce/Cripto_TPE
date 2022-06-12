#ifndef ENCRYPT_H
#define ENCRYPT_H
#include <stdint.h>

#include "../strategy/crypto_algo_strategy.h"


unsigned char * encrypt(unsigned char * plaintext, uint32_t plaintext_len, char * password, uint32_t * output_len, crypto_algo_strategy crypto_algo_fn, uint32_t key_size);

#endif