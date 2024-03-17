double potenza(double x, double n) {
  double esp = 2 * n + 1, potx = 1;
  if (x == 0) return 0;
  for (int i = 0; i < esp; i++) {
    potx *= x;
  }
  return potx;
}

double factorial(double n) {
  double den = 2 * n + 1, fact = 1;
  if (n == 0) return 1;
  for (int i = 1; i <= den; i++) {
    fact *= i;
  }
  return fact;
}

double segno(int n) {
  double sign = -1;
  if (n == 0) return 1;
  for (int i = 0; i <= n; i++) {
    sign *= (-1);
  }
  return sign;
}

double calcola_seno(double x) {
  double check = 1, sen = 0, n = 0;
  while (check != sen) {
    check = sen;
    sen += (segno(n) * potenza(x, n)) / factorial(n);
    n++;
  }
  return sen;
}

int main() {
  double x = 2, n = 1, t = 4;
  double prova1 = potenza(x, n);
  double prova2 = factorial(t);
  double prova3 = segno(5);
  double prova_dft = calcola_seno(1);
  return 0;
}