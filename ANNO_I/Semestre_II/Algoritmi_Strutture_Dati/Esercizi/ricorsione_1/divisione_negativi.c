#include "limits.h"

int DivisioneNegativi(int a, int b) {
  if (b == 0) {
    return INT_MAX;
  }
  if (b == 1) {
    return a;
  } else if (b == -1) {
    return -a;
  }
  if (a < 0 && b < 0) {
    a = -a;
    b = -b;
  }
  if (a < 0 && b > 0) {
    int temp = a;
    a = b;
    b = temp;
  }
  if ((a < b && b > 0) || (a < -b && b < 0)) {
    return 0;
  }
  if (b < 0) {
    return -1 + DivisioneNegativi(a + b, b);
  }
  return 1 + DivisioneNegativi(a - b, b);
}

// int main(void) {
//   int test = DivisioneNegativi(-2, 1);
//   return 0;
// }