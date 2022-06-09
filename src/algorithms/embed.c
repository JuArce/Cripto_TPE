#include <stdio.h>
#include <stdlib.h>

#include "embed.h"
#include "../files/bmp.h"
#include "../files/file.h"

void embed(files f) {
	printf("Hello embed\n");

	bmp_image image = read_carrier_file(f);
	file input_file = read_input_file(f);

	printf("Image Size: %d\n", get_image_size(image));
	printf("Filename: %s\n", get_filename(input_file));
	printf("Extension: %s\n", get_file_extension(input_file));
	//printf("%.*s\n", (int)get_file_data_size(input_file), get_file_data(input_file));
	printf("Data size: %ld\n", get_file_data_size(input_file));

	/*
	Puedo trabajar sobre la data de image
	get_image_data y modificar los bits de ese array
	Y luego llamar a write_output_image
	*/

	write_output_image(f, image);

	free_carrier_file(image);
	free_file(input_file);
}