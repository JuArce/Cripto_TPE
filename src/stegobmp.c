#include <stdio.h>

#include "./cli_parser/cli_parser.h"
#include "./stego_cfg/stego_cfg.h"
#include "./logger/logger.h"

#define PADDING 25

int main(int argc, char * argv[]) {
    log(INFO, "Greetings Commander\n");
    cli_options options = parse_command_line(argc, argv);

    printf("Configuration\n");
    printf("%-*s%s\n", PADDING, "Mode: ", EMBED ==get_mode(options)  ? "Embed" : "Extract");
    if(EMBED == get_mode(options)) {
        printf("%-*s%s\n", PADDING, "Input File: ", get_input_file(options));
    }
    printf("%-*s%s\n", PADDING, "Carrier File: ", get_carrier_file(options));
    printf("%-*s%s\n", PADDING, "Output File: ", get_output_file(options));
    printf("%-*s%s\n", PADDING, "Stego Algorithm: ", get_stego_algo(options));
    if(NULL !=  get_password(options)) {
        printf("%-*s%s\n", PADDING, "Encryption Algorithm: ", NULL != get_enc_algo(options) ? get_enc_algo(options) : "aes128");
        printf("%-*s%s\n", PADDING, "Encryption Mode: ", NULL != get_enc_mode(options) ? get_enc_mode(options) : "CBC");
        printf("%-*s%s\n", PADDING, "Password: ", get_password(options));
    }
    printf("\n");

    stego_cfg cfg = create_stego_config(options);

    run_stego_config(cfg);

    free_options(options);
    free_stego_config(cfg);
}