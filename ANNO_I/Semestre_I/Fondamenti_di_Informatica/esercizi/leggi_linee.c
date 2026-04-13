#include <stdio.h>
#include <stdlib.h>
// #include "dictionary.h"
#include <string.h>

#include "leggi_linee.h"

char** leggi_linee(const char* filename) {
  FILE* file = fopen(filename, "r");
  /*La funzione accetta in input una stringa C che contiene il nome di un file
da aprire in modalità lettura tradotta. La funzione deve ritornare un vettore di
stringhe C contenente tutte le linee del file. Il doppio puntatore ritornato
dalla funzione dovrà puntare alla prima stringa (la prima linea del file). Per
indicare il termine del vettore ritornato dalla funzione non si usa un'altra
variabile per memorizzare la dimensione ma, similmente a come viene fatto per le
stringhe C, dopo il suo ultimo elemento viene allocato spazio anche per un
puntatore NULL.*/

  if (file == NULL) {
    return NULL;
  }

  char** linee = (char**)malloc(sizeof(char*));
  if (linee == NULL) {
    fclose(file);
    return NULL;
  }

  char* riga = malloc(255);
  int numero_linee = 0;

  while (fgets(riga, 255, file) != NULL) {
    char* newline = strchr(riga, '\n');
    if (newline != NULL) {
      *newline = '\0';  // sostituisco con il terminatore finale
    }

    linee = realloc(linee, (numero_linee + 1) * sizeof(char*));
    char* copy = malloc(strlen(riga) + 1);
    strcpy(copy, riga);
    linee[numero_linee] = copy;
    numero_linee++;
  }
  linee[numero_linee] = '\0';
  free(file);
  free(riga);
  return linee;
}