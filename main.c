/*
 * Michał Piotr Stankiewicz <ms335789@students.mimuw.edu.pl>
 * A program to darken or lighten images in PPM
 */

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "darker.h"
#include "ppm_reader.h"

void usage() {
	fprintf(stderr, "Usage ./ppmdarker file_name.ppm change [output]\nChange is [-255..255]");
	exit(1);
}

int main(int argc, char** argv) {
	if (argc < 3 || argc > 4) {
		usage();
	}
	int change = atoi(argv[2]);
	if (change > 255 || change < -255) {
		usage();
	}
	struct ppm_image* img2 = ppm_read(argv[1]);
	if (change != 0) {
		darkerer(img2->fields, change, img2->rows, img2->columns, 0);
		darkerer(img2->fields, change, img2->rows, img2->columns, 1);
		darkerer(img2->fields, change, img2->rows, img2->columns, 2);
	}
	if (argc == 4) {
		ppm_save(img2, argv[3]);
	} else {
		ppm_save(img2, "out.ppm");
	}
	return 0;
}
