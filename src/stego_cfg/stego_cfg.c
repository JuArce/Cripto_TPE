#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "stego_cfg.h"
#include "../algorithms/embed.h"
#include "../algorithms/extract.h"
#include "../algorithms/stego_algorithms.h"
#include "../files/files.h"
#include "../logger/logger.h"
#include "../strategy/mode_strategy.h"
#include "../strategy/stego_strategy.h"
#include "../crypto_cfg/crypto_cfg.h"


typedef struct stego_cfg_struct {
    int mode;
    mode_strategy mode_strategy_fn;
    stego_strategy stego_strategy_fn;
    files files_ptr;
    crypto_cfg crypto_cfg_ptr;
} stego_cfg_struct;


static void set_stego_mode(stego_cfg config, int mode);
static void set_stego_strategy(stego_cfg config, char * stego_alg);
static void set_files(stego_cfg config, cli_options options);


stego_cfg create_stego_config(cli_options options) {
    stego_cfg config = calloc(1, sizeof(stego_cfg_struct));

    if(NULL == config) log(FATAL, "%s", strerror(errno));

    set_stego_mode(config, get_mode(options));
    set_stego_strategy(config, get_stego_algo(options));
    set_files(config, options);
    config->crypto_cfg_ptr = create_crypto_config(options);
    return config;
}

void free_stego_config(stego_cfg config) {
    free_files_struct(config->files_ptr);
    free_crypto_config(config->crypto_cfg_ptr);
    free(config);
}

void run_stego_config(stego_cfg config) {
    config->mode_strategy_fn(config->files_ptr, config->stego_strategy_fn, config->crypto_cfg_ptr);
}

static void set_stego_mode(stego_cfg config, int mode) {
    switch(mode) {
        case EMBED:
            config->mode = EMBED_MODE;
            config->mode_strategy_fn = embed;
            break;
        case EXTRACT:
            config->mode = EXTRACT_MODE;
            config->mode_strategy_fn = extract;
            break;
        default:
            log(FATAL, "Invalid steganography mode");
    }
}

static void set_stego_strategy(stego_cfg config, char * stego_algo) {
    switch(config->mode) {
        case EMBED_MODE:
            if(strcmp(stego_algo, LSB1) == 0) {
                config->stego_strategy_fn = lsb1_embed;
            } else if(strcmp(stego_algo, LSB4) == 0) {
                config->stego_strategy_fn = lsb4_embed;
            } else if(strcmp(stego_algo, LSBI) == 0) {
                config->stego_strategy_fn = lsbi_embed;
            } else {
                log(FATAL, "Invalid steganography algorithm");
            }
            break;
        case EXTRACT_MODE:
            if(strcmp(stego_algo, LSB1) == 0) {
                config->stego_strategy_fn = lsb1_extract;
            } else if(strcmp(stego_algo, LSB4) == 0) {
                config->stego_strategy_fn = lsb4_extract;
            } else if(strcmp(stego_algo, LSBI) == 0) {
                config->stego_strategy_fn = lsbi_extract;
            } else {
                log(FATAL, "Invalid steganography algorithm");
            }
            break;
        default:
            log(FATAL, "Invalid steganography mode");
    }
}

static void set_files(stego_cfg config, cli_options options) {
    config->files_ptr = create_files_struct(options);
}
