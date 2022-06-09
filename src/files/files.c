#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "files.h"
#include "bmp.h"


typedef struct files_struct {
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

bmp_image read_carrier_file(files f) {
	if(NULL == f->carrier_file) {
		//TODO Handle error
	}

	FILE * carrier = fopen(f->carrier_file, "r");

	if(NULL == carrier) {
		//TODO Handle error
	}

	bmp_image image = read_image(carrier);
	fclose(carrier);
	return image;
}

void free_carrier_file(bmp_image image) {
	free_image(image);
}

file read_input_file(files f) {
	if(NULL == f->input_file) {
		//TODO Handle error
	}

	FILE * input = fopen(f->input_file, "r");

	if(NULL == input) {
		//TODO Handle error
	}

	file input_f = read_file(input, f->input_file);
	fclose(input);
	return input_f;
}

void free_input_file(file f) {
	free_file(f);
}

void write_output_file(files f, uint8_t * data, size_t size, char * extension) {

}

void write_output_image(files f, bmp_image image) {
	if(NULL == f->output_file) {
		//TODO Handle error
	}

	FILE * output = fopen(f->output_file, "w");

	if(NULL == output) {
		//TODO Handle error
	}

	write_image(image, output);
	fclose(output);
}
