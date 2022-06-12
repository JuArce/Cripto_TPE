#ifndef DECRYPT_H
#define DECRYPT_H
#include <stdint.h>

#include "../strategy/crypto_algo_strategy.h"


unsigned char * decrypt(unsigned char * ciphertext , uint32_t ciphertext_len, char * password, uint32_t * output_len, crypto_algo_strategy crypto_algo_fn, uint32_t key_size);

#endif