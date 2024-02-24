#include <stdio.h>

// extern void capsula(FILE *f, unsigned char n);

// int main() {
//   // Esempio di utilizzo
//   FILE *file = fopen("output.txt", "w");
//   if (file == NULL) {
//     fprintf(stderr, "Impossibile aprire il file.\n");
//     return 1;
//   }

//   unsigned char n = 1;
//   capsula(file, n);

//   fclose(file);

//   return 0;
// }

void capsula(FILE *f, unsigned char n) {
  // Stampare la parte superiore della capsula
  for (int i = 0; i < n; i++) {
    fprintf(f, " ");
  }
  for (unsigned char i = 0; i < n; ++i) {
    fprintf(f, "_");
  }
  fprintf(f, "\n");

  for (unsigned char i = 0; i < n; ++i) {
    // Spazi all'inizio di ogni riga
    for (unsigned char j = 0; j < n - i - 1; ++j) {
      fprintf(f, " ");
    }

    // Parte sinistra della capsula
    fprintf(f, "/");
    for (unsigned char j = 0; j < n + i * 2; ++j) {
      fprintf(f, " ");
    }
    fprintf(f, "\\\n");
  }

  // Parte inferiore della capsula
  for (int j = 0; j < n; j++) {
    fprintf(f, "|");
    for (unsigned char i = 0; i < n + (2 * n - 2); ++i) {
      fprintf(f, " ");
    }
    fprintf(f, "|");
    fprintf(f, "\n");
  }

  for (unsigned char i = 0; i < n; ++i) {
    // Spazi all'inizio di ogni riga
    for (unsigned char j = 0; j < i; ++j) {
      fprintf(f, " ");
    }

    // Parte destra della capsula
    fprintf(f, "\\");
    for (unsigned char j = 0; j < n + (2 * n - 2) - i * 2; ++j) {
      fprintf(f, " ");
    }
    fprintf(f, "/");
    fprintf(f, "\n");
  }

  for (int i = 0; i < n; i++) {
    fprintf(f, " ");
  }
  for (unsigned char i = 0; i < n; ++i) {
    fprintf(f, "_");
  }
  fprintf(f, "\n");
}
