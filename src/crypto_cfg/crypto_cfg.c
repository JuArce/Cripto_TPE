#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <openssl/evp.h>

#include "crypto_cfg.h"
#include "../logger/logger.h"
#include "../strategy/crypto_algo_strategy.h"
#include "../strategy/crypto_mode_strategy.h"
#include "../algorithms/encrypt.h"
#include "../algorithms/decrypt.h"


typedef enum {
    aes128 = 0,
    aes192,
    aes256,
    des
} CRYPTO_ALGO;

typedef enum {
    ecb = 0,
    cfb,
    ofb,
    cbc
} CRYPTO_ALGO_MODE;

static crypto_algo_strategy evp_cypto_fns[4][4] = {
    {EVP_aes_128_ecb,   EVP_aes_128_cfb8,   EVP_aes_128_ofb,    EVP_aes_128_cbc},
    {EVP_aes_192_ecb,   EVP_aes_192_cfb8,   EVP_aes_192_ofb,    EVP_aes_192_cbc},
    {EVP_aes_256_ecb,   EVP_aes_256_cfb8,   EVP_aes_256_ofb,    EVP_aes_256_cbc},
    {EVP_des_ecb,       EVP_des_cfb8,       EVP_des_ofb,        EVP_des_cbc}
};

typedef struct crypto_cfg_struct {
    crypto_mode_strategy crypto_mode_strategy_fn;
    crypto_algo_strategy crypto_algo_strategy_fn;
    char * password;
    uint32_t key_size;
} crypto_cfg_struct;


static void set_crypto_mode(crypto_cfg config, int mode);
static void set_crypto_algo(crypto_cfg config, char * algo, char * algo_mode);


crypto_cfg create_crypto_config(cli_options options) {
    if(NULL == get_password(options)) {
        log(ERROR, "Missing password, skipping %s", get_mode(options) == EMBED ? "encryption" : "decryption")
        return NULL;
    }

    crypto_cfg config = calloc(1, sizeof(crypto_cfg_struct));

    if(NULL == config) log(FATAL, "%s", strerror(errno));

    set_crypto_mode(config, get_mode(options));
    set_crypto_algo(config,  get_enc_algo(options), get_enc_mode(options));
    config->password = get_password(options);

    return config;
}

void free_crypto_config(crypto_cfg config) {
    free(config);
}

unsigned char * run_crypto_config(crypto_cfg config, unsigned char * input, uint32_t input_len, uint32_t * output_len) {
    return config->crypto_mode_strategy_fn(input, input_len, config->password, output_len, config->crypto_algo_strategy_fn, config->key_size);
}

static void set_crypto_mode(crypto_cfg config, int mode) {
    switch (mode) {
        case EMBED:
            config->crypto_mode_strategy_fn = encrypt;
            break;
        case EXTRACT:
            config->crypto_mode_strategy_fn = decrypt;
            break;
        default:
            log(FATAL, "Invalid cryptography mode");
        }
}

static void set_crypto_algo(crypto_cfg config, char * algo, char * algo_mode) {
    CRYPTO_ALGO crypto_algo = aes128;
    CRYPTO_ALGO_MODE crypto_algo_mode = cbc;

    if(strcmp(algo, AES128) == 0) {
        crypto_algo = aes128;

    } else if(strcmp(algo, AES192) == 0) {
        crypto_algo = aes192;
    } else if(strcmp(algo, AES256) == 0) {
        crypto_algo = aes256;
    } else if(strcmp(algo, DES) == 0) {
        crypto_algo = des;
    }

    if(strcmp(algo_mode, ECB) == 0) {
        crypto_algo_mode = ecb;
    } else if(strcmp(algo_mode, CFB) == 0) {
        crypto_algo_mode = cfb;
    } else if(strcmp(algo_mode, OFB) == 0) {
        crypto_algo_mode = ofb;
    } else if(strcmp(algo_mode, CBC) == 0) {
        crypto_algo_mode = cbc;
    }
    uint32_t KEY_SIZE[] = {16, 24, 32, 8}; /* KEY_SIZE is in bytes. ie: aes128 key_size = 128bits/8 */
    config->crypto_algo_strategy_fn = evp_cypto_fns[crypto_algo][crypto_algo_mode];
    config->key_size = KEY_SIZE[crypto_algo];
}