#include <stdio.h>
#include <stdlib.h>

#define N 5
#define DOUBLE_MAX 1000000

typedef struct {
  double costo;     // costo soluzioni
  int stazione[N];  // lista fermate
} piano;

void StazioniServizioRec(double m, const double *d, const double *p, size_t n,
                         int i, piano *best, piano current, double currentKm,
                         double kmFromLastFull) {
  if ((currentKm + (600 - kmFromLastFull) > m) &&
      (current.costo < best->costo)) {
    for (int i = 0; i < n; i++) {
      best->stazione[i] = current.stazione[i];
    }
    best->costo = current.costo;
  }
  if (i == n) {
    return;
  }

  kmFromLastFull += d[i];
  currentKm += d[i];

  if (kmFromLastFull > 600) {
    return;  // not valid
  }

  current.stazione[i] = 0;  // skipping fuel
  StazioniServizioRec(m, d, p, n, i + 1, best, current, currentKm,
                      kmFromLastFull);

  current.stazione[i] = 1;  // filling fuel
  current.costo += p[i] * 0.05 * kmFromLastFull;
  kmFromLastFull = 0;
  StazioniServizioRec(m, d, p, n, i + 1, best, current, currentKm,
                      kmFromLastFull);
}

void StazioniServizio(double m, const double *d, const double *p, size_t n) {
  piano best = {.costo = __DBL_MAX__};
  piano current = {.costo = 0};
  StazioniServizioRec(m, d, p, n, 0, &best, current, 0, 0);
  if (best.costo == __DBL_MAX__) {
    printf("Non esistono soluzioni\n");
    return;
  }
  for (int i = 0; i < n; i++) {
    if (best.stazione[i] == 1) {
      printf("%d ", i);
    }
  }
  printf("\nSpesa totale: %.6f euro\n", best.costo);
}

// int main(void) {
//   double d[] = {260.000, 284.000, 308.000, 332.000, 356.000};
//   double p[] = {35, 35, 33, 29, 23};
//   double m = 2220.00;
//   StazioniServizio(m, d, p, N);
//   return 0;
// }