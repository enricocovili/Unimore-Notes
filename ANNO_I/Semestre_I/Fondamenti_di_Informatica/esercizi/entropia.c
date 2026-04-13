#include <math.h>
#include <stdint.h>
#include <stdlib.h>

extern double entropia(uint64_t* count, size_t n) {
  if (count == NULL || n <= 0) {
    return NAN;
  }
  int N = 0;
  for (size_t i = 0; i < n; i++) {
    N += count[i];
  }
  double res = 0;
  for (size_t i = 0; i < n; i++) {
    if (count[i] != 0) {
      res += ((double)count[i] / N) * log2(N / (double)(count[i]));
    }
  }
  if (res == 0) {
    res = NAN;
  }
  return res;
}

// int main() {
//   uint64_t test[] = {100, 200, 300, 400};
//   entropia(test, 4);
// }