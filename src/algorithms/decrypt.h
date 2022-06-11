#ifndef DECRYPT_H
#define DECRYPT_H

#include "../strategy/crypto_algo_strategy.h"

void decrypt(unsigned char * cyphertext , int cyphertext_len, unsigned char * plaintext, char * password, crypto_algo_strategy crypto_algo_fn);

#endif