#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "files.h"
#include "bmp.h"
#include "../logger/logger.h"

typedef struct files_struct {
	char * input_file; 
	char * carrier_file;
	char * output_file;
} files_struct;


files create_files_struct(cli_options options) {
	files f = calloc(1, sizeof(files_struct));

	if(NULL == f) log(FATAL, "%s", strerror(errno));

	f->input_file = get_input_file(options);
	f->carrier_file = get_carrier_file(options);
	f->output_file = get_output_file(options);
	
	return f;
}

void free_files_struct(files f) {
	free(f);
}

bmp_image read_carrier_file(files f) {
	if(NULL == f->carrier_file) log(FATAL, "Carrier filename can not be empty");

	FILE * carrier = fopen(f->carrier_file, "r");

	if(NULL == carrier) log(FATAL, "%s: %s", strerror(errno), f->carrier_file);

	bmp_image image = read_image(carrier);
	fclose(carrier);
	return image;
}

void free_carrier_file(bmp_image image) {
	free_image(image);
}

file read_input_file(files f) {
	if(NULL == f->input_file) log(FATAL, "Input filename can not be empty");

	FILE * input = fopen(f->input_file, "r");

	if(NULL == input) log(FATAL, "%s: %s", strerror(errno), f->input_file);

	file input_f = read_file(input, f->input_file);
	fclose(input);
	return input_f;
}

void free_input_file(file f) {
	free_file(f);
}

void write_output_file(files f, uint8_t * data, size_t size, char * extension) {
	if(NULL == f->output_file) log(FATAL, "Output filename can not be empty")

	char * filename = calloc(1, strlen(f->output_file) + strlen(extension) + 1);
	if(NULL == filename) log(FATAL, "%s", strerror(errno));
	
	strcat(filename, f->output_file);
	strcat(filename, extension);

	FILE * output = fopen(filename, "w");

	if(NULL == output) log(FATAL, "%s: %s", strerror(errno), f->output_file);

	write_file(data, size, output);

	free(filename);
	fclose(output);
}

void write_output_image(files f, bmp_image image) {
	if(NULL == f->output_file) log(FATAL, "Output filename can not be empty")

	FILE * output = fopen(f->output_file, "w");

	if(NULL == output) log(FATAL, "%s: %s", strerror(errno), f->output_file);

	write_image(image, output);
	fclose(output);
}
