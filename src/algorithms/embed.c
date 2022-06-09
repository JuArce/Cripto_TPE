#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "embed.h"
#include "../files/bmp.h"
#include "../files/file.h"
#include "../logger/logger.h"


void embed(files f, stego_strategy stego_strategy_fn) {

	bmp_image image = read_carrier_file(f);
	file input_file = read_input_file(f);

	uint8_t * image_data = get_image_data(image);
	size_t image_data_size = get_image_size(image);
	uint8_t * file_data = get_file_data(input_file);
	size_t file_data_size = get_file_data_size(input_file);

	stego_strategy_fn(image_data, &image_data_size, file_data, &file_data_size);

	write_output_image(f, image);

	free_carrier_file(image);
	free_file(input_file);

	log(INFO, "File embed correctly");
}