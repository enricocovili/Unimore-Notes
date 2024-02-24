#include "matrix.h"

#include <stdlib.h>

extern struct matrix *mat_replicate(const struct matrix *m) {
  if (m == NULL) return NULL;
  struct matrix *res = malloc(sizeof(struct matrix));
  res->data = calloc(m->cols * m->rows * 2, sizeof(double));
  res->cols = m->cols * 2;
  res->rows = m->rows;
  for (int row = 0; row < m->rows; row++) {
    for (int col = 0; col < m->cols; col++) {
      res->data[row * res->cols + col] = m->data[row * m->cols + col];
      res->data[row * res->cols + col + m->cols] = m->data[row * m->cols + col];
    }
  }
  return res;
}