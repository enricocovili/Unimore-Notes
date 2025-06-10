#include <ctype.h>  //for isalpha, isDigit
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Errore numero di parametri: infatti argc e' %d\n", argc - 1);
    exit(1);
  }
  int N = atoi(argv[1]);
  pid_t pidPadre = getpid();
  printf("N: %d, pidPadre: %d\n", N, pidPadre);

  int n;                          /* indice per i figli */
  int pidFiglio, status, ritorno; /* per wait e valore di ritorno figli */
  for (n = 0; n < N; n++) {
    if ((pidFiglio = fork()) == 0) {
      printf("nel figlio. PID: %d, codice d'ordine: %d\n", getpid(), n);
      exit(n);  // or some value
    }
    pidFiglio = wait(&status);
    if (pidFiglio < 0) {
      printf("finito tutto");
      exit(0);
    }
    if ((status & 0xFF) != 0)
      printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
    else {
      ritorno = (int)((status >> 8) & 0xFF);
      printf("Il figlio con pid=%d ha ritornato %d\n", pidFiglio, ritorno);
    }
  }
  exit(0);
}