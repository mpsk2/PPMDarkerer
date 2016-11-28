#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "ppm_reader.h"

struct image* empty_image(int64_t columns, int64_t rows) {
	struct image* img=(struct image*) malloc(sizeof(struct image));
	img->columns = columns;
	img->rows = rows;
	img->fields = (struct color**) malloc(columns*sizeof(struct rows*));
	for (int i = 0; i < rows; i++) {
		img->fields[i]=(struct color*) malloc(columns*sizeof(struct color));
		for (int j = 0; j < columns; j++) {
			img->fields[i][j].r = 100*j+10*i+1;
			img->fields[i][j].g = 100*j+10*i+2;
			img->fields[i][j].b = 100*j+10*i+3;
		}
	}
	return img;
}

void print_image (const struct image* const img) {
	for (int i = 0; i < img->rows; i++) {
		for (int j = 0; j < img->columns; j++) {
			printf("%5ld %5ld %5ld   ", img->fields[i][j].r, img->fields[i][j].g, img->fields[i][j].b);
		}
		printf("\n");
	}
}
