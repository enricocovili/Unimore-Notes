#include "libri.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern bool libro_scrivi(const struct libro *p, FILE *f) {
  if (p == NULL || f == NULL) return false;
  size_t title_len = strlen(p->titolo);
  fwrite(p->titolo, sizeof(char), title_len + 1, f);
  size_t i = 0;
  for (i; p->anni_ristampe[i] != 0; i++) {
    fwrite(&p->anni_ristampe[i], sizeof(uint16_t), 1, f);
  }
  fwrite(&p->anni_ristampe[i], sizeof(uint16_t), 1, f);
  return true;
}
