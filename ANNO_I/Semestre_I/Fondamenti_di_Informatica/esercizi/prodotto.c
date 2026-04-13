#include <stdlib.h>

struct product {
  int res;
  int p1, p2;
};

extern int prodotto_altri_due(const int *v, size_t n) {
  if (n == 0 || v == NULL) return -1;
  size_t prod_totali = 0;
  for (int i = n - 1; i > 0; i--) {
    prod_totali += i;
  }
  struct product *products = calloc(prod_totali, sizeof(struct product));
  int c = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      products[c].res = v[i] * v[j];
      products[c].p1 = i;
      products[c].p2 = j;
      c++;
    }
  }
  int res = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < prod_totali; j++) {
      if (products[j].res == v[i] && products[j].p1 != i &&
          products[j].p2 != i) {
        res++;
        break;
      }
    }
  }
  free(products);
  return res;
}