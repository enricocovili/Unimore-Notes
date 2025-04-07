#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_prime(int n) {
  if (n == 1 || n == 0) {
    return 0;
  }
  for (int i = 2; i < n / 2 + 1; i++) {
    if (n % i == 0) {
      return 0;
    }
  }
  return 1;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    return 1;
  }
  char *pEnd;
  long n = strtol(argv[1], pEnd, 10);
  if (n < 0) return 1;
  if (is_prime(n) == 1) {
    printf("true");
  } else {
    printf("false");
  }
}