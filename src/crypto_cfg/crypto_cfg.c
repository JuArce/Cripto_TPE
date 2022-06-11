#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "crypto_cfg.h"
#include "../logger/logger.h"
#include "../strategy/crypto_algo_strategy.h"
#include "../strategy/crypto_mode_strategy.h"
#include "../algorithms/encrypt.h"
#include "../algorithms/decrypt.h"

typedef struct crypto_cfg_struct {
    crypto_algo_strategy crypto_algo_strategy_fn;
    crypto_mode_strategy crypto_mode_strategy_fn;
    char * password;
} crypto_cfg_struct;

static void set_crypto_mode(crypto_cfg config, int mode);
static void set_crypto_algo(crypto_cfg config, char * algo, char * algo_mode);

crypto_cfg create_crypto_cfg(cli_options cli_options) {
    crypto_cfg config = calloc(1, sizeof(crypto_cfg_struct));

    if(NULL == config) log(FATAL, "%s", sterror(errno));

    set_crypto_mode(config, get_mode(cli_options));
    set_crypto_algo(config,  get_enc_algo(cli_options), get_enc_mode(cli_options));
    config->password = get_password(cli_options);

    return config;
}

static void set_crypto_mode(crypto_cfg config, int mode) {
    switch (mode) {
    case EMBED:
        config->crypto_algo_strategy_fn = encrypt;
        break;
    case EXTRACT:
        config->crypto_algo_strategy_fn = decrypt;
        break;
    default:
        log(FATAL, "Invalid cryptography mode");
    }
}

static void set_crypto_algo(crypto_cfg config, char * algo, char * algo_mode) {
    
}