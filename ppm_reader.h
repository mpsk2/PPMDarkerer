#ifndef __PPM_READER_H__
#define __PPM_READER_H__

struct color {
	int64_t r;
	int64_t g;
	int64_t b;
};

struct image {
	int64_t columns;
	int64_t rows;
	struct color** fields;
};

void save_image(const struct image* const, const char* const);
struct image* read_image(const char* const);
struct image* empty_image(int64_t, int64_t);
void print_image (const struct image* const);

#endif
