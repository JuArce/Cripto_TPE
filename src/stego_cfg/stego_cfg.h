#ifndef STEGO_CFG_H
#define STEGO_CFG_H

#include "../cli_parser/cli_parser.h"


#define LSB1 "LSB1"
#define LSB4 "LSB4"
#define LSBI "LSBI"

enum stego_mode {
    EMBED_MODE,
    EXTRACT_MODE
};


typedef struct stego_cfg_struct * stego_cfg;


stego_cfg create_stego_config(cli_options options);

void free_stego_config(stego_cfg config);

void run_stego_config(stego_cfg config);

#endif
