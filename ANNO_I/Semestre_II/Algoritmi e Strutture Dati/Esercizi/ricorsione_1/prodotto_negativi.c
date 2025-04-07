int ProdottoNegativi(int a, int b) {
  if ((a < 0 && b < 0)) {
    a = -a;
    b = -b;
  }
  if (a > 0 && b < 0) {
    int temp = a;
    a = b;
    b = temp;
  }
  if (a == 0 || b == 0) {
    return 0;
  }
  if (b == 1) {
    return a;
  }
  return ProdottoNegativi(a, b - 1) + a;
}

// int main() {
//   int test = ProdottoNegativi(3, -4);
//   int test2 = ProdottoNegativi(3, 2);
//   return 0;
// }