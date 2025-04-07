#include <stdio.h>

void stampa_quadrati_concentrici(int n) {
  if (n <= 0) {
    // printf("Il valore di n deve essere maggiore di zero.\n");
    return;
  }

  for (int i = 0; i < 2 * n - 1; i++) {
    for (int j = 0; j < 2 * n - 1; j++) {
      // Calcola il valore da stampare in base alla posizione nel quadrato
      int dist_vert = i < 2 * n - 1 - i ? i : 2 * n - 1 - i - 1;
      int dist_oriz = j < 2 * n - 1 - j ? j : 2 * n - 1 - j - 1;
      int dist = dist_vert < dist_oriz ? dist_vert : dist_oriz;
      printf("%d", (n - dist) % 10);
    }
    printf("\n");
  }
}