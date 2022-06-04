#include <stdio.h>

#include "./cli_parser/cli_parser.h"
#include "./stego_cfg/stego_cfg.h"


int main(int argc, char * argv[]) {
    printf("Hello stego\n\n");
    cli_options options = parse_command_line(argc, argv);
    printf("#### Config ####\n");
    printf("Mode: %s\n", get_mode(options) == EMBED_MODE ? "Embed" : "Extract");
    printf("Input: %s\n", get_input_file(options));
    printf("Carrier: %s\n", get_carrier_file(options));
    printf("Output: %s\n", get_output_file(options));
    printf("Stego Algorithm: %s\n", get_stego_alg(options));
    printf("Enc Algorithm: %s\n", get_enc_alg(options));
    printf("Enc Mode: %s\n", get_enc_mode(options));
    printf("Password: %s\n", get_password(options));
    printf("################\n");
    free_options(options);
}