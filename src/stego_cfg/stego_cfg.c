#include <stdlib.h>

#include "stego_cfg.h"


typedef struct stego_cfg_struct {
    int mode;
} stego_cfg_struct;


stego_cfg create_config(int mode) {
    stego_cfg config = calloc(1, sizeof(stego_cfg_struct));
    config->mode = mode;
    return config;
}