#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "stego_cfg.h"
#include "../algorithms/stego_algorithms.h"
#include "../files/files.h"
#include "../strategy/stego_strategy.h"

typedef struct stego_cfg_struct {
    int mode;
    stego_strategy stego_strategy_fn;
    files files_ptr;
} stego_cfg_struct;


static void set_stego_mode(stego_cfg config, int mode);
static void set_stego_strategy(stego_cfg config, char * stego_alg);
static void set_files(stego_cfg config, cli_options options);


stego_cfg create_stego_config(cli_options options) {
    stego_cfg config = calloc(1, sizeof(stego_cfg_struct));

    if(NULL == config) {
        //TODO Handle error
    }

    set_stego_mode(config, get_mode(options));
    set_stego_strategy(config, get_stego_alg(options));
    set_files(config, options);
    return config;
}

void free_stego_config(stego_cfg config) {
    free_files_struct(config->files_ptr);
    free(config);
}

void run_stego_config(stego_cfg config) {
    config->stego_strategy_fn();
}

static void set_stego_mode(stego_cfg config, int mode) {
    switch(mode) {
        case EMBED:
            config->mode = EMBED_MODE;
            break;
        case EXTRACT:
            config->mode = EXTRACT_MODE;
            break;
        default:
            printf("%s\n", "error");
            //TODO Handle error and delete printf
    }
}

static void set_stego_strategy(stego_cfg config, char * stego_alg) {
    switch(config->mode) {
        case EMBED_MODE:
            if(strcmp(stego_alg, LSB1) == 0) {
                config->stego_strategy_fn = lsb1_embed;
            } else if(strcmp(stego_alg, LSB4) == 0) {
                config->stego_strategy_fn = lsb4_embed;
            } else if(strcmp(stego_alg, LSBI) == 0) {
                config->stego_strategy_fn = lsbi_embed;
            } else {
                //TODO Handle error
            }
            break;
        case EXTRACT_MODE:
            if(strcmp(stego_alg, LSB1) == 0) {
                config->stego_strategy_fn = lsb1_extract;
            } else if(strcmp(stego_alg, LSB4) == 0) {
                config->stego_strategy_fn = lsb4_extract;
            } else if(strcmp(stego_alg, LSBI) == 0) {
                config->stego_strategy_fn = lsbi_extract;
            } else {
                //TODO Handle error
            }
            break;
        default:
            printf("%s\n", "error");
            //TODO Handle error and delete printf
    }
}

static void set_files(stego_cfg config, cli_options options) {
    config->files_ptr = create_files_struct(options);
}