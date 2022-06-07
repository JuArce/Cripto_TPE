#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "files.h"
#include "bmp.h"


typedef struct files_struct {
	// TODO set correct types for files
	char * input_file; 
	char * carrier_file;
	char * output_file;
	bmp_image carrier_image;
	uint8_t * input_data;
} files_struct;


files create_files_struct(cli_options options) {
	files f = calloc(1, sizeof(files_struct));

	if(NULL == f) {
		//TODO Handle error
	}

	f->input_file = get_input_file(options);
	f->carrier_file = get_carrier_file(options);
	f->output_file = get_output_file(options);

	FILE * carrier = fopen(get_carrier_file(options), "r");
	f->carrier_image = read_image(carrier);
	fclose(carrier);

	
	return f;
}

void free_files_struct(files f) {
	free_image(f->carrier_image);
	free(f);
}
