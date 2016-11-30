#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netpbm/ppm.h>
#include "ppm_reader.h"

#define PPMREADBUFLEN 256

void ppm_save(const struct ppm_image* const img, const char* const path) {
	FILE* file;
	file = fopen(path, "wb");
	fprintf(file, "P6\n");
	fprintf(file, "%ld %ld 255\n", img->columns, img->rows);
	for (int i = 0; i < img->rows; i++) {
		for (int j = 0; j < img->columns; j++) {
			static unsigned char c[3];
			c[0] = img->fields[i][j].r;
			c[1] = img->fields[i][j].g;
			c[2] = img->fields[i][j].b;
			fwrite(c, 1, 3, file);
		}
	}
	fclose(file);
}

struct ppm_image* ppm_read(const char* const path) {
	struct ppm_image* img;
	FILE* fb;
	int columns, rows;
	pixel** pixels;
	pixval maxvalP;
	fb = fopen(path, "rb");
	if (!fb) {
		fprintf(stderr, "file open error: %s", path);
		exit(1);
	}
	pixels = ppm_readppm(fb, &columns, &rows, &maxvalP);
	fprintf(stderr, "%d %d %d", columns, rows, maxvalP);
	img = ppm_empty(rows, columns);
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			img->fields[i][j].r = pixels[i][j].r;
			img->fields[i][j].g = pixels[i][j].g;
			img->fields[i][j].b = pixels[i][j].b;
		}
	}
	
	fclose(fb);
	return img;
}

struct ppm_image* ppm_empty(int64_t rows, int64_t columns) {
	if (rows <= 0 || columns <= 0) {
		fprintf(stderr, "rows: %ld, columns: %ld\n", rows, columns);
		exit(1);
	}
	struct ppm_image* img=(struct ppm_image*) malloc(sizeof(struct ppm_image));
	img->columns = columns;
	img->rows = rows;
	img->fields = (struct color**) malloc(rows*sizeof(struct color*));
	for (int i = 0; i < rows; i++) {
		img->fields[i]=(struct color*) malloc(columns*sizeof(struct color));
		for (int j = 0; j < columns; j++) {
			img->fields[i][j].r = 128;
			img->fields[i][j].g = 128;
			img->fields[i][j].b = 128;
		}
	}
	return img;
}

void ppm_print(const struct ppm_image* const img) {
	for (int i = 0; i < img->rows; i++) {
		for (int j = 0; j < img->columns; j++) {
			printf("%2x %2x %2x  ", img->fields[i][j].r, img->fields[i][j].g, img->fields[i][j].b);
		}
		printf("\n");
	}
	printf("rows: %ld, columns: %ld\n", img->rows, img->columns);
}
