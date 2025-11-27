#include <stdlib.h>

#include "matrix.h"

double* bordo_esterno(const struct matrix* m, size_t* new_size) {
  // 2*numero colonne + 2*(numero di righe - 2)
  if (m == NULL) {
    return NULL;
  }
  int k = 0;
  double* bordo =
      malloc(((2 * m->cols) + 2 * (m->rows - 2)) *
             sizeof(double));  // aggiunte parentesi, moltiplicavi solo m->rows
                               // - 2 per sizeof(double)
  // int indice = 0;

  for (size_t c = 0; c < m->cols; ++c) {
    // prima riga
    bordo[c] = m->data[c];
  }

  for (size_t r = 1; r < m->rows - 1; r++) {
    bordo[m->cols + r - 1] =
        m->data[(r * m->cols) + m->cols -
                1];  // aggiunto -1, altrimenti prendevamo l'elemento successivo
    // m->cols - 1 --> arrivo all'ultimo elemento
  }

  for (int c = m->cols - 1; c >= 0;
       c--) {  // c >= 0 se no non prende il primo elemento della riga
    bordo[m->cols + m->rows - 2 + k] = m->data[(m->rows - 1) * m->cols + c];
    k++;
    // m->rows - 1)*m->cols ultima riga NEGA
  }
  k = 0;
  for (size_t r = 1; r < m->rows - 1; r++) {
    bordo[m->cols + m->rows - 2 + m->cols + k] = m->data[r * m->cols];
    k++;
  }
  *new_size = (2 * m->cols) + 2 * (m->rows - 2);
  return bordo;
}