/*
 * Michał Piotr Stankiewicz <ms335789@students.mimuw.edu.pl>
 * A program to darken or lighten images in PPM
 */

#include <stdio.h>
#include <inttypes.h>
#include "darker.h"
#include "ppm_reader.h"


int main(int argc, char** argv) {
	printf("Should be 6: %d\n", darker(7, -1));
	printf("Should be 0: %d\n", darker(100, -120));
	printf("Should be 255: %d\n", darker(200, 64));
	printf("Should be 128: %d\n", darker(64, 64));
	struct ppm_image* img = ppm_empty(3,4);
	
	ppm_print(img);
	darkerer(img->fields, 3, 4, 0, 15);
	if (argc > 1) {
		struct ppm_image* img2;
		img2 = ppm_read(argv[1]);
		ppm_save(img2, "out.ppm");
	}
	return 0;
}
