#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <openssl/evp.h>

#include "encrypt.h"
#include "../logger/logger.h"


#define MAX_SIZE 64 * 1024 * 1024


unsigned char * encrypt(unsigned char * plaintext, uint32_t plaintext_len, char * password, uint32_t * output_len, crypto_algo_strategy crypto_algo_fn, uint32_t key_size) {
    log(INFO, "Encrypting file, please wait...");

    int len;

    EVP_CIPHER_CTX * ctx = EVP_CIPHER_CTX_new();
    if(NULL == ctx) log(FATAL, "%s", strerror(errno));

    unsigned char key[key_size];
    unsigned char iv[key_size];
    EVP_BytesToKey(crypto_algo_fn(), EVP_sha256(), NULL, (unsigned char *)password, strlen(password), 1, key, iv);

    if(1 != EVP_EncryptInit_ex(ctx, crypto_algo_fn(), NULL, key, iv)) {
        log(FATAL, "EVP Encrypt Init ex failed");
    }

    unsigned char * output = calloc(1, MAX_SIZE);
    if(NULL == output) log(FATAL, "%s", strerror(errno));

    if(1 != EVP_EncryptUpdate(ctx, output, &len, plaintext, plaintext_len)) {
        log(FATAL, "EVP Encrypt Update failed"); 
    }
    *output_len = len;

    if(1 != EVP_EncryptFinal_ex(ctx, output + len, &len)) {
        log(FATAL, "EVP Encrypt Final ex failed"); 
    }
    *output_len += len;

    EVP_CIPHER_CTX_free(ctx);
    log(INFO, "File encrypted correctly");

    return output;
}
