#include <stdio.h>

#include "extract.h"


void extract(files f, stego_strategy stego_strategy_fn) {
	printf("Hello extract\n");
	bmp_image image = read_carrier_file(f);
	printf("%p\n", (void *)image);
}