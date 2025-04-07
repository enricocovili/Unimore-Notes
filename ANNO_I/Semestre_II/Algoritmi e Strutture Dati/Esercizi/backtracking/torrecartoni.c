#include "torrecartoni.h"

bool notIn(int vect[], int n, int elem) {
  for (int i = 0; i < n; i++) {
    if (vect[i] == elem) {
      return true;
    }
  }
  return false;
}
// current = current vector
// best = best vector yet
// w = current weight on pack
// i = index
// h = current height
// bestH = best height
extern void TorreCartoniRec(const Cartone *c, size_t n, int current[],
                            int best[], unsigned w, int i, unsigned h,
                            unsigned *bestH) {
  // caso base
  if (h > *bestH) {
    memmove(best, current, n * sizeof(int));
    *bestH = h;
  }
  if (i == n) {
    return;
  }
  for (int j = 0; j < n; j++) {
    if ((c[j].l > w) && !notIn(current, n, j)) {
      current[i] = j;
      TorreCartoniRec(c, n, current, best, w + c[j].p, i + 1, h + c[j].a,
                      bestH);
    }
  }
}

extern void TorreCartoni(const Cartone *c, size_t n) {
  int *best = malloc(sizeof(int) * n);
  int *current = malloc(sizeof(int) * n);
  for (int i = 0; i < n; i++) {
    best[i] = -1;  // reset index
  }
  memmove(current, best, n * sizeof(int));
  unsigned bestSum = 0;
  unsigned bestH = 0;
  for (int i = 0; i < n; i++) {
    current[0] = i;
    // for (int j = 1; j < n; j++) {
    //   current[j] = -1;
    // }
    TorreCartoniRec(c, n, current, best, c[i].p, 1, c[i].a, &bestH);
  }
  for (int i = 0; i < n && best[i] != -1; i++) {
    bestSum += c[best[i]].a;
    printf("%d\n", best[i]);
  }
  printf("Altezza: %d cm", bestSum);
  free(best);
  free(current);
}

/*
 int main(void) {
  Cartone c[] = {{.p = 25, .a = 20, .l = 50},  {.p = 10, .a = 10, .l = 8},
                 {.p = 9, .a = 3, .l = 5},     {.p = 5, .a = 20, .l = 200},
                 {.p = 10, .a = 10, .l = 202}, {.p = 24, .a = 3, .l = 55}};
  TorreCartoni(c, 6);
} */
