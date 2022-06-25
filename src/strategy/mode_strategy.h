#ifndef MODE_STRATEGY_H
#define MODE_STRATEGY_H

#include "../crypto_cfg/crypto_cfg.h"
#include "../files/files.h"
#include "../strategy/stego_strategy.h"


typedef void (*mode_strategy) (files f, stego_strategy stego_strategy_fn, crypto_cfg crypto_cfg_ptr);

#endif
