#ifndef __PPM_READER_H__
#define __PPM_READER_H__

struct color {
	int64_t r;
	int64_t g;
	int64_t b;
};

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
