#pragma once

#include <stdlib.h>

struct matrix {
  size_t rows, cols;
  double* data;
};

double* bordo_esterno(const struct matrix* m, size_t* new_size);