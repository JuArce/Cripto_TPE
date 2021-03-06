#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "file.h"
#include "../logger/logger.h"


typedef struct file_struct {
	char * filename;
	char * extension;
	uint8_t * data;
	uint32_t data_size;
} file_struct;


static void set_filename(file f, char * filename);
static void set_extension(file f, char * extension);
static void read_data(FILE * fp, file f);
static void resize_data(file f, uint32_t size);


/**
    Assume that the file is already open.
    Do not close the file.
*/
file read_file(FILE * fp, char * filename) {
	log(DEBUG, "Reading file");

	file f = calloc(1, sizeof(file_struct));

	if(NULL == f) log(FATAL, "%s", strerror(errno));

	set_extension(f, strchr(filename, '.')); //The order of these operations is important
	set_filename(f, strtok(filename, ".")); //Strtok sets '.' to '\0' 

	read_data(fp, f);

	return f;
}

void free_file(file f) {
	free(f->filename);
	free(f->extension);
	free(f->data);
	free(f);
}

void write_file(uint8_t * data, uint32_t size, FILE * fp) {
	log(DEBUG, "Writing file")

	fwrite(data, 1, size, fp);
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

uint32_t get_file_data_size(file f) {
	return f->data_size;
}

static void set_filename(file f, char * filename) {
	f->filename = calloc(1, strlen(filename) + 1);
	if(NULL == f->filename) log(FATAL, "%s", strerror(errno));
	strcpy(f->filename, filename);
}

static void set_extension(file f, char * extension) {
	f->extension = calloc(1, strlen(extension) + 1);
	if(NULL == f->extension) log(FATAL, "%s", strerror(errno));
	strcpy(f->extension, extension);
}

static void read_data(FILE * fp, file f) {
	int read = -1;
	char * buffer[BLOCK];

	while(read != 0) {
		read = fread(buffer, 1, BLOCK, fp);

		if(f->data_size % BLOCK == 0) {
			resize_data(f, f->data_size + BLOCK);
		}

		memcpy(f->data + f->data_size, buffer, read);
		f->data_size += read;
	};
	resize_data(f, f->data_size);
}

static void resize_data(file f, uint32_t size) {
	f->data = realloc(f->data, size);
	if(NULL == f->data) log(FATAL, "%s", strerror(errno));
}
