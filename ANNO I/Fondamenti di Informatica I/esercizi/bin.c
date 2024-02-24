#include <stdlib.h>

// aa
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv) {
  if (argc != 2) {
    return 1;
  }
  char *pEnd;
  long n = strtol(argv[1], &pEnd, 10);
  if (n < 0) return 1;
  if (n == 0) {
    printf("0");
  }
  char output[100];
  int i = 98;
  while (n > 0) {
    output[i] = n % 2;
    n /= 2;
    i--;
  }
  i++;
  for (i; i < 99; i++) {
    printf("%d", output[i]);
  }
  return 0;
}