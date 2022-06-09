#ifndef MODE_STRATEGY_H
#define MODE_STRATEGY_H

#include "../files/files.h"
#include "../strategy/stego_strategy.h"


//TODO define return and parameters
typedef void (*mode_strategy) (files f, stego_strategy stego_strategy_fn);

#endif