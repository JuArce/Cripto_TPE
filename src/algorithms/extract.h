#ifndef EXTRACT_H
#define EXTRACT_H

#include "../crypto_cfg/crypto_cfg.h"
#include "../files/files.h"
#include "../strategy/stego_strategy.h"


void extract(files f, stego_strategy stego_strategy_fn, crypto_cfg crypto_cfg_ptr);

#endif
