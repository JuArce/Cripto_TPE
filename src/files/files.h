#ifndef FILES_H
#define FILES_H

#include "../cli_parser/cli_parser.h"


typedef struct files_struct * files;


files create_files_struct(cli_options options);

void free_files_struct(files f);

/* TODO getters */

#endif