#include "matrix.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern struct matrix *mat_diffup(const struct matrix *m) {
  if (m == NULL) {
    return NULL;
  }
  struct matrix *res = malloc(sizeof(struct matrix));
  res->cols = m->cols;
  res->rows = m->rows;
  res->data = calloc(res->cols * res->rows, sizeof(double));
  for (int i = 0; i < res->rows; i++) {
    for (int j = 0; j < res->cols; j++) {
      if (i == 0) {
        res->data[j] = m->data[j];
      } else {
        res->data[i * res->cols + j] =
            m->data[i * m->cols + j] - m->data[(i - 1) * m->cols + j];
      }
    }
  }
  return res;
}