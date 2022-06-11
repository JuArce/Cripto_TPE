#ifndef ENCRYPT_H
#define ENCRYPT_H

#include "../strategy/crypto_algo_strategy.h"

void encrypt(unsigned char * plaintext, int plaintext_len, unsigned char * cyphertext, char * password, crypto_algo_strategy crypto_algo_fn);

#endif