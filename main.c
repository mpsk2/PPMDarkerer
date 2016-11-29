/*
 * Michał Piotr Stankiewicz <ms335789@students.mimuw.edu.pl>
 * A program to darken or lighten images in PPM
 */

#include <stdio.h>
#include <inttypes.h>
#include "darker.h"
#include "ppm_reader.h"

void darkerer(struct color** colors, int64_t rows, int64_t cols, int64_t color, int64_t change);

int main(int argc, char** argv) {
	printf("Should be 6: %ld\n", darker(7, -1));
	printf("Should be 0: %ld\n", darker(100, -120));
	printf("Should be 255: %ld\n", darker(200, 64));
	printf("Should be 128: %ld\n", darker(64, 64));
	struct image* img = empty_image(3,4);
	
	print_image(img);
	struct color a[3][4];
	darkerer(img->fields, 3, 4, 0, 15);
	if (argc > 1) {
		struct image* img2;
		img2 = read_image(argv[1]);
		save_image(img2, "out.ppm");
	}
	return 0;
}
