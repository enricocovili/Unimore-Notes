#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void tiroAllaFuneRec(int n, int I[], int k, int i, bool* current, bool* best,
                     int count, int* bestDif) {
  if (count == k) {
    int sum1 = 0, sum2 = 0;
    for (int j = 0; j < n; j++) {
      if (current[j] == 0) {
        sum2 += I[j];
      } else {
        sum1 += I[j];
      }
    }
    int totDif = sum1 - sum2;
    if (totDif < 0) {
      totDif = -1 * totDif;
    }
    if (totDif < *bestDif) {
      *bestDif = totDif;
      for (int j = 0; j < n; j++) {
        best[j] = current[j];
      }
    }
    return;
  }
  if (i == n) {
    return;
  }
  current[i] = 0;
  tiroAllaFuneRec(n, I, k, i + 1, current, best, count, bestDif);
  current[i] = 1;
  tiroAllaFuneRec(n, I, k, i + 1, current, best, count + 1, bestDif);
  current[i] = 0;
}

void tiroAllaFune(int n, int I[]) {
  int size1 = n / 2;
  bool* v = calloc(n, sizeof(bool));
  bool* best = calloc(n, sizeof(bool));

  int bestDif = INT_MAX;
  tiroAllaFuneRec(n, I, size1, 0, v, best, 0, &bestDif);
  bool first = true;
  printf("{");
  for (int i = 0; i < n; i++) {
    if (best[i] == 1) {
      if (first) {
        printf(" %d", I[i]);
        first = false;
      } else {
        printf(", %d", I[i]);
      }
    }
  }
  printf(" }, {");
  first = true;
  for (int i = 0; i < n; i++) {
    if (best[i] == 0) {
      if (first) {
        first = false;
        printf(" %d", I[i]);
      } else {
        printf(", %d", I[i]);
      }
    }
  }
  printf(" }\n");
  free(v);
  free(best);
  return;
}

int main(int argc, char** argv) {
  int* I = malloc(sizeof(int) * (argc - 1));
  char* pEnd;
  for (int i = 1; i < argc; i++) {
    I[i - 1] = strtol(argv[i], &pEnd, 10);
  }
  tiroAllaFune(argc - 1, I);
  free(I);
  return 0;
}