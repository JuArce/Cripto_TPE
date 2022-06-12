#ifndef CRYPTO_MODE_STRATEGY_H
#define CRYPTO_MODE_STRATEGY_H
#include <stdint.h>

#include "crypto_algo_strategy.h"

typedef unsigned char * (* crypto_mode_strategy) (unsigned char *, uint32_t, char *, uint32_t *, crypto_algo_strategy, uint32_t);

#endif