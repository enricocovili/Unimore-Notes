#include "stdio.h"

int radice_num(int n) {
  int res = 0;
  while (n > 0) {
    res += n % 10;
    n /= 10;
  }
  if (res > 9) {
    return radice_num(res);
  }
  return res;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    return 1;
  }
  char *pEnd;
  long n = strtol(argv[1], pEnd, 10);
  if (n < 0) return 1;
  printf("%d", radice_num(n));
}