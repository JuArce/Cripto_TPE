#ifndef FILES_H
#define FILES_H

#include <stdint.h>

#include "bmp.h"
#include "file.h"
#include "../cli_parser/cli_parser.h"


typedef struct files_struct * files;


files create_files_struct(cli_options options);

void free_files_struct(files f);

bmp_image read_carrier_file(files f);

void free_carrier_file(bmp_image image);

file read_input_file(files f);

void free_input_file(file f);

void write_output_file(files f, uint8_t * data, size_t size, char * extension);

void write_output_image(files f, bmp_image image);

#endif