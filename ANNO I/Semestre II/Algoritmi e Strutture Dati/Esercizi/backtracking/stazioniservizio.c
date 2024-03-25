#include <limits.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool isIn(int vect[], int n, int elem) {
  for (int i = 0; i < n; i++) {
    if (vect[i] == elem) {
      return true;
    }
  }
  return false;
}

void StazioniServizioRec(double m, const double *d, const double *p, size_t n,
                         int i, int current[], int best[], double currentKm,
                         double kmFromLastFull, double currentCost,
                         double *bestCost) {
  if (i == n) {
    if (currentCost < *bestCost) {
      memmove(best, current, n * sizeof(int));
      *bestCost = currentCost;
    }
    return;
  }

  currentKm += d[i];
  kmFromLastFull += d[i];

  if (kmFromLastFull > 600) {
    return;
  }

  current[i] = 0;
  StazioniServizioRec(m, d, p, n, i + 1, current, best, currentKm,
                      kmFromLastFull, currentCost, bestCost);

  currentCost += kmFromLastFull * 0.05 * p[i];
  current[i] = 1;
  kmFromLastFull = 0;
  StazioniServizioRec(m, d, p, n, i + 1, current, best, currentKm,
                      kmFromLastFull, currentCost, bestCost);
}

void StazioniServizio(double m, const double *d, const double *p, size_t n) {
  int *best = malloc(sizeof(int) * n);
  int *current = malloc(sizeof(int) * n);
  for (int i = 0; i < n; i++) {
    best[i] = -1;  // reset index
  }
  memmove(current, best, n * sizeof(int));
  double bestCost = __DBL_MAX__;
  StazioniServizioRec(m, d, p, n, 0, current, best, 0, 0, 0, &bestCost);
  double totCost = 0;
  for (int i = 0; i < n; i++) {
    if (best[i] == 1) {
      printf("%d ", i);
    }
  }
  printf("\nSpesa totale: %.6f euro\n", bestCost);
  free(best);
  free(current);
}

// int main(void) {
//   double d[] = {260.000, 284.000, 308.000, 332.000, 356.000};
//   double p[] = {35, 35, 33, 29, 23};
//   double m = 1540.00;
//   size_t n = 5;
//   StazioniServizio(m, d, p, n);
//   return 0;
// }