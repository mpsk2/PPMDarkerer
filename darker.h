#ifndef __DARKER_H__
#define __DARKER_H__

#include "ppm_reader.h"

int16_t darker(int16_t base, int16_t change);
int16_t darkerer(struct color** colors, int64_t change, int64_t rows, int64_t cols, int64_t color);

#endif
