#ifndef CRYPTO_CFG_H
#define CRYPTO_CFG_H
#include <stdint.h>

#include "../cli_parser/cli_parser.h" 
#include "../strategy/crypto_algo_strategy.h" 


#define AES128  "aes128"
#define AES192  "aes192"
#define AES256  "aes256"
#define DES     "des"

#define ECB "ecb"
#define CFB "cfb"
#define OFB "ofb"
#define CBC "cbc"

enum crypto_mode {
    ENCRYPT_MODE,
    DECRYPT_MODE
};


typedef struct crypto_cfg_struct * crypto_cfg;


crypto_cfg create_crypto_config(cli_options options);

void free_crypto_config(crypto_cfg config);

unsigned char * run_crypto_config(crypto_cfg config, unsigned char * input, uint32_t input_len, uint32_t * output_len);

#endif