#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include <getopt.h>

enum {
    EMBED = 1000,
    EXTRACT,
    IN,
    P,
    OUT,
    STEG,
    A,
    M,
    PASS,
    HELP
};

typedef struct cli_options_struct * cli_options;


cli_options parse_command_line(int argc, char * argv[]);

void free_options(cli_options options);

int get_mode(cli_options options);

char * get_input_file(cli_options options);

char * get_carrier_file(cli_options options);

char * get_output_file(cli_options options);

char * get_stego_algo(cli_options options);

char * get_enc_algo(cli_options options);

char * get_enc_mode(cli_options options);

char * get_password(cli_options options);

#endif
