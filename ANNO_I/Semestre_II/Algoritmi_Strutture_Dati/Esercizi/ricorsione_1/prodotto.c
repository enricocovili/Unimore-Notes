int Prodotto(int a, int b) {
  if (a < 0 || b < 0) {
    return -1;
  }
  if (a == 0 || b == 0) {
    return 0;
  }
  if (b == 1) {
    return a;
  }
  return Prodotto(a, b - 1) + a;
}

// int main(void) {
//   int test = Prodotto(3, 4);
//   return 0;
// }