#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct matrix {
  size_t rows, cols;
  double *data;
};

extern struct matrix *mat_diffup(const struct matrix *m);