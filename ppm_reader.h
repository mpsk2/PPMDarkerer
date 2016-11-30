/*
 * Michał Piotr Stankiewicz <ms335789@students.mimuw.edu.pl>
 * A program to darken or lighten images in PPM
 * Header containing ppm operations structs and functions
 */
#ifndef __PPM_READER_H__
#define __PPM_READER_H__

struct color {
	int16_t r;
	int16_t g;
	int16_t b;
} __attribute__ ((packed));

struct ppm_image {
	int64_t columns;
	int64_t rows;
	struct color** fields;
};

void ppm_save(const struct ppm_image* const, const char* const);
struct ppm_image* ppm_read(const char* const);
struct ppm_image* ppm_empty(int64_t, int64_t);
void ppm_print(const struct ppm_image* const);

#endif
