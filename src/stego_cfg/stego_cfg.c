#include <stdlib.h>
#include <string.h>

#include "stego_cfg.h"
#include "../strategy/stego_strategy.h"
#include "../algorithms/stego_algorithms.h"

typedef struct stego_cfg_struct {
    int mode;
    stego_strategy stego_strategy_fn;
} stego_cfg_struct;


static void set_stego_strategy(stego_cfg config, char * stego_alg);


stego_cfg create_stego_config(cli_options options) {
    stego_cfg config = calloc(1, sizeof(stego_cfg_struct));
    config->mode = get_mode(options);
    set_stego_strategy(config, get_stego_alg(options));
    return config;
}

void free_stego_config(stego_cfg config) {
    free(config);
}

void run_stego_config(stego_cfg config) {
    config->stego_strategy_fn();
}

static void set_stego_strategy(stego_cfg config, char * stego_alg) {
    if(strcmp(stego_alg, LSB1) == 0) {
        config->stego_strategy_fn = lsb1;
    } else if(strcmp(stego_alg, LSB4) == 0) {
        config->stego_strategy_fn = lsb4;
    } else if(strcmp(stego_alg, LSBI) == 0) {
        config->stego_strategy_fn = lsbi;
    } else {
        //TODO Handle error
    }
}