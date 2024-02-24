#include "finance.h"

#include <stdio.h>
#include <stdlib.h>
extern struct value *read_historical_series(const char *filename, size_t *n) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    return NULL;
  }
  char *dump = malloc(1000 * sizeof(char));
  fgets(dump, 1000, f);
  int len = 0;
  while (1) {
    if (fgets(dump, 1000, f) == NULL) {
      break;
    }
    len++;
  }
  *n = len;
  struct value *values = malloc(len * sizeof(struct value));
  rewind(f);
  fgets(dump, 1000, f);
  for (int i = 0; i < len; i++) {
    fscanf(f, "%[^,],%lf,%lf,%lf,%lf,%lf,%lld\n", &values[i].Date,
           &values[i].Open, &values[i].High, &values[i].Low, &values[i].Close,
           &values[i].AdjClose, &values[i].Volume);
  }
  free(dump);
  fclose(f);
  return values;
}