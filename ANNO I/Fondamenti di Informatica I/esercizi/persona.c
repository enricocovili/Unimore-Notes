#include "persona.h"

#include <string.h>

extern struct persona *leggi_persone(const char *filename, size_t *size) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    *size = 0;
    return NULL;
  }
  int n;
  int res = fscanf(f, "%d", &n);
  if (res <= 0) {  // empty file
    fclose(f);
    *size = 0;
    return NULL;
  }
  int i = -1;
  struct persona *people = calloc(n, sizeof(struct persona));
  while (1) {
    char dummy = fgetc(f);
    if (dummy == EOF) {
      break;
    }
    if (dummy == '\n') {
      i++;
      int anni;
      int test = fscanf(f, "%d", &anni);
      if (test <= 0) {
        break;
      }
      people[i].anni = anni;
    } else if (dummy != '\t' && dummy != ',' && dummy != ' ' && dummy != '\r') {
      for (int j = 0;; j++) {
        people[i].nome[j] = dummy;
        dummy = fgetc(f);
        if (dummy == '\n' || dummy == '\r' || dummy == EOF) {
          people[i].nome[j + 1] = '\0';
          break;
        }
      }
    }
  }
  if (n != i + 1) {
    *size = 0;
    free(people);
    fclose(f);
    return NULL;
  }
  *size = n;
  fclose(f);
  return people;
}