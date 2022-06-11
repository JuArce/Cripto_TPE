#ifndef _CRYPTO_CFG__
#define _CRYPTO_CFG__

#include "../cli_parser/cli_parser.h"  


enum crypto_mode {
    ENCRYPT_MODE,
    DECRYPT_MODE
};

enum crypto_algo {
    aes128 = 0,
    aes192,
    aes256,
    des
};

enum crypto_algo_mode {
    ecb = 0,
    cfb,
    ofb,
    cbc
};

typedef struct crypto_cfg_struct * crypto_cfg;

#endif