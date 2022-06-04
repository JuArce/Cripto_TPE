#ifndef STEGO_CFG_H
#define STEGO_CFG_H


enum stego_mode {
    EMBED_MODE,
    EXTRACT_MODE
};

typedef struct stego_cfg_struct * stego_cfg;


stego_cfg create_config();

#endif