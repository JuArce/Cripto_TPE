#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <openssl/evp.h>

#include "encrypt.h"
#include "../logger/logger.h"


unsigned char * encrypt(unsigned char * plaintext, uint32_t plaintext_len, char * password, uint32_t * output_len, crypto_algo_strategy crypto_algo_fn, uint32_t key_size) {
        log(INFO, "Decrypting file, please wait...");

    log(INFO, "File decrypted correctly");
}