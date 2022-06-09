#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"


typedef struct file_struct {
	char * filename;
	char * extension;
	uint8_t * data;
} file_struct;


static void set_filename(file f, char * filename);
static void set_extension(file f, char * extension);


/**
    Assume that the file is already open.
    Do not close the file.
*/
file read_file(FILE * fp, char * filename) {
	file f = calloc(1, sizeof(file_struct));

	if(NULL == f) {
		//TODO handle error
	}

	set_extension(f, strchr(filename, '.'));
	set_filename(f, strtok(filename, "."));


	return f;
}

void free_file(file f) {
	free(f->filename);
	free(f->extension);
	free(f->data);
	free(f);
}

void write_file(file f, FILE * fp) {

}

char * get_filename(file f) {
	return f->filename;
}

char * get_file_extension(file f) {
	return f->extension;
}

uint8_t * get_file_data(file f) {
	return f->data;
}

static void set_filename(file f, char * filename) {
	f->filename = calloc(1, strlen(filename) + 1);
	strcpy(f->filename, filename);
}

static void set_extension(file f, char * extension) {
	f->extension = calloc(1, strlen(extension) + 1);
	strcpy(f->extension, extension);
}