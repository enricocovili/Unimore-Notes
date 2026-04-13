#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
La funzione riceve una stringa C con il nome di un file e un puntatore ad una
variabile di output n. La funzione deve aprire il file filename in modalità
lettura tradotta (testo) ed estrarne tutte le parole. Con "parola" intendiamo
una sequenza di caratteri diversi da spazio. Le parole estratte vanno inserite
in una sequenza (allocata dinamicamente) di stringhe C (anch'esse allocate
dinamicamente). La variabile n deve essere impostata al numero di parole
presenti nel file.

Se l'apertura del file fallisce, la funzione non alloca memoria e ritorna NULL,
senza modificare la variabile puntata da n. I file conterranno sempre almeno una
parola.
*/
extern char **extract_parole(const char *filename, size_t *n) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    return NULL;
  }
  char buffer[255];
  char **result = malloc(sizeof(char *));
  size_t word_count = 0;
  while (1) {
    int ret_code = fscanf(f, "%s", buffer);
    if (ret_code <= 0) {
      break;
    }
    word_count++;
    size_t current_word_len = strlen(buffer);
    result = realloc(result, word_count * (sizeof(char) * 255 + 1));
    result[word_count - 1] = malloc(sizeof(char) * 255 + 1);
    strncpy(result[word_count - 1], buffer, current_word_len);
    result[word_count - 1][current_word_len] = '\0';
  }
  *n = word_count;
  fclose(f);
  return result;
}