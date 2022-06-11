#ifndef CRYPTO_ALGO_STRATEGY_H
#define CRYPTO_ALGO_STRATEGY_H

#include <openssl/evp.h>

typedef const EVP_CIPHER * (* crypto_algo_strategy) ();

#endif