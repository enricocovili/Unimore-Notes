// #include "conta_occorrenze.h"

extern int ContaOccorrenze(const char *filename, const char *str) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    return 0;
  };
  int c = 0;
  while (1) {
    char *dummy = malloc(sizeof(char) * 100);  // no more than 99 chars
    int ret = fscanf(f, "%s", dummy);
    if (ret <= 0) {
      break;
    }
    while (1) {
      char *pch = strstr(dummy, str);
      if (pch == NULL) {
        break;
      }
      c++;
      dummy += 1;
    }
    free(dummy);
  }
  return c;
}

// int main() {
//   int c = ContaOccorrenze("file2.txt", "file");
//   return 0;
// }