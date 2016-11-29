#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "ppm_reader.h"

void save_image(const struct image* const img, const char* const path) {
	FILE* file;
	file = fopen(path, "wb");
	fprintf(file, "P6\n");
	fprintf(stderr, "1");
	fprintf(file, "%ld %ld\n", img->columns, img->rows);
	fprintf(stderr, "2");
	fprintf(file, "255\n");
	fprintf(stderr, "3");
	for (int i = 0; i < img->rows; i++) {
		for (int j = 0; j < img->columns; j++) {
			static unsigned char c[3];
			c[0] = img->fields[j][i].r;
			c[1] = img->fields[j][i].g;
			c[2] = img->fields[j][i].b;
			fwrite(c, 1, 3, file);
		}
	}
	fclose(file);
}

struct image* read_image(const char* const path) {
	char type[3];
	FILE* file;
	int columns, rows, max_number;
	struct image* img;
	file = fopen(path, "rb");
	if (!file) {
		fprintf(stderr, "Could not open given file: %s", path);
		exit(1);
	}
	fscanf(file, "%2s", type);
	fprintf(stderr, "Given type is %s\n", type);
	if (strcmp(type, "P6") == 0) {
		fscanf(file, "%d", &columns);
		fscanf(file, "%d", &rows);
		fscanf(file, "%d", &max_number);
		fprintf(stderr, "File is of %d columns and %d rows and %d max_number\n", columns, rows, max_number);
		img = empty_image(columns, rows);
		fseek(file, 1, SEEK_CUR);
		unsigned char c[3];
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				fread(c, 3, 1, file);
				img->fields[j][i].r = c[0];
				img->fields[j][i].g = c[1];
				img->fields[j][i].b = c[2];
			}
		}
	} else {
		fprintf(stderr, "File is not P6");
		exit(1);
	}
	fclose(file);
	return img;
}

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
			printf("%3ld %3ld %3ld   ", img->fields[i][j].r, img->fields[i][j].g, img->fields[i][j].b);
		}
		printf("\n");
	}
}
