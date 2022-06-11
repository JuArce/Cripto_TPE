#ifndef CRYPTO_MODE_STRATEGY_H
#define CRYPTO_MODE_STRATEGY_H

#include "crypto_algo_strategy.h"

typedef void (* crypto_mode_strategy) (unsigned char *, int, unsigned char *, char *, crypto_algo_strategy);

#endif