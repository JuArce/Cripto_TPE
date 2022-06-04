#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "cli_parser.h"


static struct option long_options[] = {
   {"embed",    no_argument,        0,  EMBED   },
   {"extract",  no_argument,        0,  EXTRACT },
   {"in",       required_argument,  0,  IN      },
   {"p",        required_argument,  0,  P       },
   {"out",      required_argument,  0,  OUT     },
   {"steg",     required_argument,  0,  STEG    },
   {"a",        required_argument,  0,  A       },
   {"m",        required_argument,  0,  M       },
   {"pass",     required_argument,  0,  PASS    },
   {"help",     no_argument,        0,  HELP    },
   {0,          0,                  0,  0       }
};


typedef struct cli_options_struct {
    int mode;
    char * input_file;
    char * carrier_file;
    char * output_file;
    char * stego_alg; // < LSB1 | LSB4 | LSBI >
    char * enc_alg; // < aes128 | aes196 | aes256 | des >
    char * enc_mode; // < ecb | cfb | ofb | cbc >
    char * password;
} cli_options_struct;


static void print_help();


cli_options parse_command_line(int argc, char * argv[]) {
    cli_options options = calloc(1, sizeof(cli_options_struct));

    if (NULL == options) {
        // TODO handle error        
    }

    int c = 0;
    //int digit_optind = 0;

    while (1) {
        //int this_option_optind = optind ? optind : 1;
        int option_index = 0;

        c = getopt_long_only(argc, argv, "", long_options, &option_index);
        if (c == -1) break;

        switch(c) {
            case EMBED:
                options->mode = EMBED;
                break;
            case EXTRACT:
                options->mode = EXTRACT;
                break;
            case IN: 
                options->input_file = optarg;
                break;
            case P:
                options->carrier_file = optarg;
                break;
            case OUT:
                options->output_file = optarg;
                break;
            case STEG:
                options->stego_alg = optarg;
                break;
            case A:
                options->enc_alg = optarg;
                break;
            case M:
                options->enc_mode = optarg;
                break;
            case PASS:
                options->password = optarg;
                break;
            case HELP: 
                print_help();
                break;
            default:
               printf("Unknown argument: 0%o\n", c);
        }
    }

    if (optind < argc) {
       printf("non-option ARGV-elements: ");
       while (optind < argc)
           printf("%s ", argv[optind++]);
       printf("\n");
    }

    return options;
}

void free_options(cli_options options) {
    free(options);
}

int get_mode(cli_options options) {
    return options->mode;
}

char * get_input_file(cli_options options) {
    return options->input_file;
}

char * get_carrier_file(cli_options options) {
    return options->carrier_file;
}

char * get_output_file(cli_options options) {
    return options->output_file;
}

char * get_stego_alg(cli_options options) {
    return options->stego_alg;
}

char * get_enc_alg(cli_options options) {
    return options->enc_alg;
}

char * get_enc_mode(cli_options options) {
    return options->enc_mode;
}

char * get_password(cli_options options) {
    return options->password;
}

// TODO 
static void print_help() {
    printf("Usage: ...\n");
    printf("...\n");
    exit(EXIT_SUCCESS);
}