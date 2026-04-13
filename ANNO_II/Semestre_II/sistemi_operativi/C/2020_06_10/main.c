/*
1ciaoc
*/

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define PERM 0644 /* in ottale per diritti UNIX */

typedef int pipe_t[2];

int main(int argc, char **argv) {
  /* -------- Variabili locali ---------- */
  int pid; /* process identifier per le fork() del padre e del figlio */
  int Q;   /* numero passato sulla riga di comando, che saranno il numero di
              processi figli e quindi nipoti da creare */
  /* nome indicato nel testo */
  int status;       /* variabile di stato per la wait */
  pipe_t *piped;    /* array dinamico di pipe descriptors per comunicazioni
                       figli-padre  */
  char linea[255];  /* array per salvare linee come descritto da testo */
  int q, j;         /* indici per i cicli */
  int outfile, fdf; /* fd padre e fd figlio */
  int numerorighe;  /* numero righe lette da ogni figlio */
  int ritorno;      /* variabile che viene ritornata da ogni figlio al padre */
                    /* ------------------------------------ */

  /* Controllo sul numero di parametri: STRETTO! */
  if (argc < 3) /* Ci vogliono solo due parametri */
  {
    printf(
        "Errore nel numero dei parametri dato che argc = %d, mentre ci "
        "vogliono almeno due parametri\n",
        argc);
    exit(1);
  }

  /* Per prima cosa il processo padre deve creare un file con il nome Camilla */
  if ((outfile = creat("Camilla", PERM)) < 0)
  /* ERRORE se non si riesce a creare il file */
  {
    printf("Errore nella creazione file per %s dato che outfile = %d\n",
           argv[2], outfile);
    exit(3);
  }

  Q = argc - 1; /* numero file */

  /* Allocazione dell'array di N pipe descriptors */
  piped = (pipe_t *)malloc(Q * sizeof(pipe_t));
  if (piped == NULL) {
    printf("Errore nella allocazione della memoria\n");
    exit(4);
  }

  /* Creazione delle N pipe figli-padre */
  for (q = 0; q < Q; q++) {
    if (pipe(piped[q]) < 0) {
      printf("Errore nella creazione della pipe figli-padre per l'indice %d\n",
             q);
      exit(5);
    }
  }

  /* Ciclo di generazione dei figli */
  for (q = 0; q < Q; q++) {
    if ((pid = fork()) < 0) {
      printf("Errore nella fork di indice %d\n", q);
      exit(6);
    }

    if (pid == 0) {
      /* codice del figlio */
      /* in caso di errori nei figli decidiamo di tornare -1 che
       * corrispondera' al valore 255 che non puo' essere un valore accettabile
       * di ritorno */

      /* Chiusura delle pipe non usate nella comunicazione con il padre */
      /* ogni figlio scrive solo su piped[n] */
      for (j = 0; j < Q; j++) {
        close(piped[j][0]);
        if (q != j) close(piped[j][1]);
      }

      if ((fdf = open(argv[q + 1], O_RDONLY)) < 0) {
        printf("errore nella lettura di %s\n", argv[q + 1]);
        exit(-1); /* esco con stato di errore 255 */
      }

      j = 0;
      numerorighe = 0;
      while (read(fdf, &linea[j], 1)) {
        if (linea[j] == '\n') {
          if (isdigit(linea[0]) && (j + 1 < 10)) {
            write(piped[q][1], linea, j + 1);
            numerorighe++;
          }
          j = 0;
        } else {
          j++;
        }
      }

      return (numerorighe);
    }
  }

  /* Codice del padre */
  /* Il padre chiude i lati delle pipe che non usa */
  for (q = 0; q < Q; q++) close(piped[q][1]);

  for (q = 0; q < Q; q++) {
    j = 0;
    while (read(piped[q][0], &linea[j], 1)) {
      if (linea[j] == '\n') {
        linea[j] = '\0';
        j = 0;
        printf("Ricevuta da figlio di indice %d (file %s) la linea: \"%s\"\n",
               q, argv[q + 1], linea);
      } else {
        j++;
      }
    }
  }

  /* Il padre aspetta i figli */
  for (q = 0; q < Q; q++) {
    pid = wait(&status);
    if (pid < 0) {
      printf("Errore in wait\n");
      exit(7);
    }

    if ((status & 0xFF) != 0)
      printf("Figlio con pid %d terminato in modo anomalo\n", pid);
    else {
      ritorno = (int)((status >> 8) & 0xFF);
      if (ritorno == 255) {
        printf("Figlio pid=%d ha avuto problemi.\n", pid);
      } else {
        printf("Il figlio con pid=%d ha ritornato %d\n", pid, ritorno);
      }
    }
  }
  exit(0);
}