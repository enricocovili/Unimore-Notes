/*

*/

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define PERM 0644 /* in ottale per diritti UNIX */

#define N 26  // lettere alfabeto

typedef int pipe_t[2];

typedef struct {
  char caratt_i;        // carattere i
  long int occorrenze;  // numero occorrenze carattere i
} data;

/* funzione bubblesort che rispetto a quella fornita e' stata adattata alle
 * esigenze del testo e, quindi, ordina l'array di strutture di tipo data
 * passato in base al valore del campo occ delle strutture facenti parte
 * dell'array */
void bubbleSort(data *v, int dim) {
  int i;
  data tmp;
  int ordinato = 0;
  while (dim > 0 && !ordinato) {
    ordinato = 1;
    for (i = 0; i < dim - 1; i++) {
      if (v[i].occorrenze > v[i + 1].occorrenze) {
        tmp = v[i];
        v[i] = v[i + 1];
        v[i + 1] = tmp;
        ordinato = 0;
      }
    }
    dim--;
  }
}

int main(int argc, char **argv) {
  /* -------- Variabili locali ---------- */
  int pid[N]; /* process identifier per le fork() del padre e del figlio */
  /* nome indicato nel testo */
  int status;      /* variabile di stato per la wait */
  pipe_t piped[N]; /* array dinamico di pipe descriptors per comunicazioni
                    figli-figli e padre  */
  data d[N];       /* array strutture dati */
  int j, i;        /* indici per i cicli */
  /* n nome indicato nel testo */
  int nr, nw;  // valori di ritorno di read e write
  int pidFiglio,
      ritorno; /* variabile che viene ritornata da ogni figlio al padre */
  int fd;      /* file descriptor ritornato dallar read */
  char ch;     /* carattere temporaneo per leggere i file nei vari figli */
               /* ------------------------------------ */

  /* Controllo sul numero di parametri: STRETTO! */
  if (argc != 2) /* 1 parametro */
  {
    printf(
        "Errore nel numero dei parametri dato che argc = %d, mentre ci "
        "vuole esattamente un solo parametro\n",
        argc);
    exit(1);
  }

  /* Creazione delle N pipe figli-figli e figlio-padre per l'ultimo */
  for (i = 0; i < N; i++) {
    if (pipe(piped[i]) < 0) {
      printf("Errore nella creazione della pipe figli-figli per l'indice %d\n",
             i);
      exit(5);
    }
  }

  /* Ciclo di generazione dei figli */
  for (i = 0; i < N; i++) {
    if ((pid[i] = fork()) < 0) {
      printf("Errore nella fork di indice %d\n", i);
      exit(6);
    }

    if (pid[i] == 0) {
      /* codice del figlio */

      for (j = 0; j < N; j++) {
        if (j != i) {
          close(piped[j][1]); /* chiudo scrittura di ogni figlio non attivo */
        }
        if (i == 0 || j != i - 1) {
          close(piped[j][0]); /* chiudo scrittura nel primo figlio e per tutti
                                 gli altri non attivi (eccetto quello prima
                                 dell'attuale) */
        }

        if (i != 0) { /* procedo alla lettura dell'array */
          nr = read(piped[i - 1][0], d, sizeof(d));
          if (nr != sizeof(d)) {
            printf("Errore in lettura da pipe[%d]\n", i);
            exit(-1);
          }
        }

        if ((fd = open(argv[1], O_RDONLY)) < 0) {
          printf("errore nella read nel file nel figlio %d", i);
          exit(-1);
        }

        d[i].caratt_i = 'a' + i;
        d[i].occorrenze = 0;
        while (read(fd, &ch, 1)) {
          if (ch == 'a' + i) {
            d[i].occorrenze++;
          }
        }

        nw = write(piped[i][1], d, sizeof(d));
        if (nw != sizeof(d)) {
          printf("Errore in lettura da pipe[%d]\n", i);
          exit(-1);
        }
      }

      exit(ch);
    }
  }

  /* Codice del padre */
  /* Il padre chiude i lati delle pipe che non usa. tengo aperta solo lettura
   * ultimo figlio */
  for (i = 0; i < N; i++) {
    close(piped[i][1]);
    if (i != N - 1) {
      close(piped[i][0]);
    }
  }

  /* il padre deve leggere l'array di strutture che gli arriva dall'ultimo
   * figlio */
  /* quindi al padre arriva una singola informazione, rappresentata pero' da un
   * array che quindi contiene piu' elementi */
  nr = read(piped[N - 1][0], d, sizeof(d));
  /* N.B. anche il padre deve controllare di avere letto qualcosa! */
  if (nr != sizeof(d)) {
    printf("Errore in lettura da pipe[N-1] per il padre\n");
  }
  bubbleSort(d, N);
  for (i = 0; i < N; i++) {
    printf("pid %d, carattere %c, occorrenze %ld, indice %d.\n",
           pid[d[i].caratt_i - 'a'], d[i].caratt_i, d[i].occorrenze,
           d[i].caratt_i - 'a');
  }

  /* Il padre aspetta i figli */
  for (i = 0; i < N; i++) {
    pidFiglio = wait(&status);
    if (pidFiglio < 0) {
      printf("Errore in wait\n");
      exit(7);
    }

    if ((status & 0xFF) != 0)
      printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
    else {
      ritorno = (int)((status >> 8) & 0xFF);
      printf("Il figlio con pid=%d ha ritornato carattere %c (decimale: %d).\n",
             pidFiglio, ritorno, ritorno);
    }
  }
  exit(0);
}
