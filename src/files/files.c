#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "files.h"

typedef struct files_struct {
	// TODO set correct types for files
	char * input_file; 
	char * carrier_file;
	char * output_file;
} files_struct;


files create_files_struct(cli_options options) {
	files f = calloc(1, sizeof(files_struct));

	if(NULL == f) {
		//TODO Handle error
	}

	f->input_file = get_input_file(options);
	f->carrier_file = get_carrier_file(options);
	f->output_file = get_output_file(options);
	return f;
}

void free_files_struct(files f) {
	free(f);
}
