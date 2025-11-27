#include <stdio.h>

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr,
            "Il numero di parametri non e' corretto. Sintassi del programma: "
            "\"occorrenze <s> <c>\"");

    return 1;
  }
  int c = 0;
  for (int i = 0; argv[1][i] != '\0'; i++) {
    if (argv[1][i] == argv[2][0]) {
      c++;
    }
  }
  printf("%d", c);
  return 0;
}