#include "audio.h"

#include <stdio.h>
#include <stdlib.h>

extern int audio_read(const char *filename, struct audio *a) {
  FILE *f = fopen(filename, "rb");
  if (f == NULL) {
    return 0;
  }
  int i = 0;
  short temp;
  while (fread(&temp, sizeof(short), 1, f) == 1) {
    i++;
  }
  a->left = calloc(i / 2, sizeof(short));
  a->right = calloc(i / 2, sizeof(short));
  a->samples = i / 2;
  i = 0;
  rewind(f);
  while (fread(&temp, sizeof(short), 1, f) == 1) {
    if (i % 2 == 0 || i % 2 == 2) {
      a->left[i / 2] = temp;
    } else {
      a->right[i / 2] = temp;
    }
    i++;
  }
  fclose(f);
  return 1;
}