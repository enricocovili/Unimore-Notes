int Divisione(int a, int b) {
  if (a < 0 || b <= 0) {
    return -1;
  }
  if (a <= 0) {
    return 0;
  }
  return 1 + Divisione(a - b, b);
}
// int main() {
//   int test = Divisione(6, 4);
//   return 0;
// }