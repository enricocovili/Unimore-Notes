#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    return -1;
  }
  char *pEnd;
  long n = strtol(argv[1], &pEnd, 10);
  if (n <= 0) {
    return 0;
  }
  int i = 0;
  while (1) {
    i++;
    printf("%ld", n);  // Fix the incorrect usage of printf
    if (n == 1) {
      break;
    }
    if (n % 2 == 0) {  // pari
      n /= 2;
    } else {
      n = 3 * n + 1;
    }
    printf(", ");
  }
  return i;
}