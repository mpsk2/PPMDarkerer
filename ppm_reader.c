#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	char type[3];
	FILE* file;
	int columns, rows, max_number;
	struct ppm_image* img;
	file = fopen(path, "rb");
	if (!file) {
		fprintf(stderr, "Could not open given file: %s", path);
		exit(1);
	}
	fscanf(file, "%2s", type);
	fprintf(stderr, "Given type is %s\n", type);
	if (strncmp(type, "P6", 3) == 0 || strcmp(type, "P3") == 0) {
		fscanf(file, "%d %d%d", &columns, &rows, &max_number);
		fprintf(stderr, "File is of %d columns and %d rows and %d max_number\n", columns, rows, max_number);
		img = ppm_empty(rows, columns);
		fseek(file, 1, SEEK_CUR);
		unsigned char c[3];
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				fread(c, 3, 1, file);
				img->fields[i][j].r = c[0];
				img->fields[i][j].g = c[1];
				img->fields[i][j].b = c[2];
			}
		}
	} else {
		fprintf(stderr, "File is not P6");
		exit(1);
	}
	fclose(file);
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
