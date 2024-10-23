// matrix decomposition LU

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

extern bool LUdecomposition(const struct matrix* mat, struct matrix* lower,
                            struct matrix* upper) {
  if (mat->rows != mat->cols) {
    return false;
  }
  lower->rows = mat->rows;
  lower->cols = mat->cols;
  upper->rows = mat->rows;
  upper->cols = mat->cols;
  lower->data = (double*)malloc(lower->rows * lower->cols * sizeof(double));
  upper->data = (double*)malloc(upper->rows * upper->cols * sizeof(double));
  for (int i = 0; i < mat->rows; i++) {
    for (int j = 0; j < mat->cols; j++) {
      if (i > j) {
        lower->data[i * lower->cols + j] = mat->data[i * mat->cols + j];
        upper->data[i * upper->cols + j] = 0;
      } else if (i == j) {
        lower->data[i * lower->cols + j] = 1;
        upper->data[i * upper->cols + j] = mat->data[i * mat->cols + j];
      } else {
        lower->data[i * lower->cols + j] = 0;
        upper->data[i * upper->cols + j] = mat->data[i * mat->cols + j];
      }
    }
  }
  for (int i = 0; i < mat->rows; i++) {
    for (int j = 0; j < mat->cols; j++) {
      double sum = 0;
      for (int k = 0; k < mat->rows; k++) {
        sum +=
            lower->data[i * lower->cols + k] * upper->data[k * upper->cols + j];
      }
      upper->data[i * upper->cols + j] = mat->data[i * mat->cols + j] - sum;
    }
  }
  return true;
}

int main(void) {
  double** matrix = (double**)malloc(3 * sizeof(double*));
  for (int i = 0; i < 3; i++) {
    matrix[i] = (double*)malloc(3 * sizeof(double));
  }
  matrix[0][0] = 2;
  matrix[0][1] = 1;
  matrix[0][2] = 1;
  matrix[1][0] = 4;
  matrix[1][1] = 3;
  matrix[1][2] = 3;
  matrix[2][0] = 8;
  matrix[2][1] = 7;
  matrix[2][2] = 9;
  double** L = matrix_LU(matrix, 3);
  print_matrix(L, 3);
  free_matrix(matrix, 3);
  free_matrix(L, 3);
  return 0;
}