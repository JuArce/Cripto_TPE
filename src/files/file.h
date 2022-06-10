#ifndef FILE_H
#define FILE_H

#include <stdint.h>


#define BLOCK 256


typedef struct file_struct * file;


file read_file(FILE * fp, char * filename);

void free_file(file f);

void write_file(uint8_t * data, uint32_t size, FILE * fp);

char * get_filename(file f);

char * get_file_extension(file f);

uint8_t * get_file_data(file f);

uint32_t get_file_data_size(file f);

#endif