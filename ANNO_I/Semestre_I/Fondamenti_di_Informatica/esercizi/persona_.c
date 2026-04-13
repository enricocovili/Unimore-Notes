#include "persona.h"

#include <string.h>

extern struct persona *leggi_persone(const char *filename, size_t *size) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    *size = 0;
    return NULL;
  }
  int n;
  int res = fscanf(f, "%d\n", &n);
  if (res <= 0) {  // empty file
    fclose(f);
    *size = 0;
    return NULL;
  }
  struct persona *people = calloc(n, sizeof(struct persona));
  for (int i = 0; i < n; i++) {
    int age;
    char *name = calloc(50, sizeof(char));
    char line[2000];
    if (fgets(line, 2000, f) == NULL) {
      for (int j = 0; j < i; j++) {
        free(people[j].nome);
      }
      free(name);
      free(people);
      *size = 0;
      fclose(f);
      return NULL;
    }
    sscanf(line, "%d", &age);
    int c = 0;
    int j;
    for (j = 0; line[j] != '\n'; j++) {
      if (c == 0 && line[j] >= 65 && line[j] <= 90) {  // A-Z
        c = j;
      }
      if (c != 0) {
        name[j - c] = line[j];
      }
    }
    name[j - c] = '\0';
    struct persona person;
    person.anni = age;
    strcpy(person.nome, name);
    people[i] = person;
  }
  *size = n;
  fclose(f);
  return people;
}