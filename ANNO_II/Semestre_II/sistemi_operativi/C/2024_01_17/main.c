/*

*/

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
  int N;   /* numero passato sulla riga di comando, che saranno il numero di
              processi figli e quindi nipoti da creare */
  /* nome indicato nel testo */
  int fdFiglio;   /* file descriptor del figlio */
  int status;     /* variabile di stato per la wait */
  pipe_t *pipePf; /* array dinamico di pipe descriptors per comunicazioni
                    padre-figlio  */
  pipe_t *pipeFp; /* pipes figlio padre */
  int n, j;       /* indici per i cicli */
  /* n nome indicato nel testo */
  char *car;       /* carattere di lettura per il padre */
  int lunLinea;    /* lunghezza ultime linee file */
  char linea[250]; /* array di caratteri usato sia dal figlio per la sprintf e
                       sia dal padre per ricevere dai figli */
  char segnale;    /* segnale per dire ai figli se scrivere o no */
  int indiceMin;   /* indice figlio con carattere minimo */
  /* nome indicato dal testo */
  int ritorno; /* variabile che viene ritornata da ogni figlio al padre */
  char test;
  /* ------------------------------------ */

  /* Controllo sul numero di parametri: STRETTO! */
  if (argc < 3) /* Ci vogliono almeno due parametri */
  {
    printf(
        "Errore nel numero dei parametri dato che argc = %d, mentre ci "
        "vogliono almeno due parametri\n",
        argc);
    exit(1);
  }

  N = argc - 1; /* numero di file */

  /* Allocazione dell'array di N pipe descriptors */
  pipePf = (pipe_t *)malloc(N * sizeof(pipe_t));
  if (pipePf == NULL) {
    printf("Errore nella allocazione della memoria per le pipe\n");
    exit(2);
  }
  pipeFp = (pipe_t *)malloc(N * sizeof(pipe_t));

  /* allocazione array di N caratteri */
  car = (char *)malloc(N * sizeof(char));
  if (car == NULL) {
    printf("errore allocazione della memoria per car\n");
    exit(3);
  }

  /* Creazione delle N pipe figli-padre */
  for (n = 0; n < N; n++) {
    if (pipe(pipePf[n]) < 0 || pipe(pipeFp[n]) < 0) {
      printf("Errore nella creazione della pipe figli-padre per l'indice %d\n",
             n);
      exit(4);
    }
  }

  /* Ciclo di generazione dei figli */
  for (n = 0; n < N; n++) {
    if ((pid = fork()) < 0) {
      printf("Errore nella fork di indice %d\n", n);
      exit(5);
    }

    if (pid == 0) {
      /* codice del figlio */
      /* in caso di errori nei figli o nei nipoti decidiamo di tornare -1 che
       * corrispondera' al valore 255 che non puo' essere un valore accettabile
       * di ritorno */

      for (j = 0; j < N; j++) {
        close(pipeFp[j][0]);
        close(pipePf[j][1]);
        if (n != j) {
          close(pipeFp[j][0]);
          close(pipeFp[j][1]);
        }
      }

      if ((fdFiglio = open(argv[n + 1], O_RDONLY)) <
          0) { /* lettura file dal figlio */
        printf("errore nella lettura di %s\n", argv[n + 1]);
        exit(-1);
      }

      j = 0; /* azzero contatore */
      while (read(fdFiglio, &(linea[j]), 1)) {
        if (linea[j] == '\n') {
          lunLinea = j;
          j = 0;
        } else
          j++;
      }

      write(pipeFp[n][1], &linea[0],
            1); /* mando primo carattere ultima linea al padre  */
      read(pipePf[n][0], &test, 1);
      printf("ricevuto %c, sono figlio %d\n", test, n);
      if (test == '1') { /* figlio "prediletto". agli altri sarà mandato 0 */
        linea[lunLinea + 1] = '\0';
        printf(
            "Sono il figlio %d, PID: %d, carattere selezionato: %c e ultima "
            "linea %s\n",
            n, getpid(), linea[0], linea);
        exit(1); /* una riga inviata */
      }

      exit(0); /* nessuna riga inviata */
    }
  }
  /* Codice del padre */

  /* Il padre recupera le informazioni dai figli: in ordine di indice */
  for (n = 0; n < N; n++) {
    close(pipeFp[n][1]);
    close(pipePf[n][0]);
    read(pipeFp[n][0], &car[n], 1);
    // NON chiudere pipePf[n][1] qui, serve dopo per scrivere!
  }

  printf("minIndex = %d\n", indiceMin);
  /* trova il minimo */
  indiceMin = 0;
  for (n = 1; n < N; n++) {
    if (car[indiceMin] < car[n]) {
      indiceMin = n;
    }
  }

  /* Il padre manda i segnali e chiude i lati delle pipe che non usa */
  for (n = 0; n < N; n++) {
    printf("a\n");
    if (n == indiceMin)
      test = '1';
    else
      test = '0';
    write(pipePf[n][1], &test, 1);
  }

  /* Il padre aspetta i figli */
  for (n = 0; n < N; n++) {
    pid = wait(&status);
    if (pid < 0) {
      printf("Errore wait\n");
      exit(6);
    }
    if ((status & 0xFF) != 0)
      printf("Figlio con pid %d terminato in modo anomalo\n", pid);
    else {
      ritorno = (int)((status >> 8) & 0xFF);
      printf("Il figlio con pid=%d ha ritornato %d (se 255 problemi)\n", pid,
             ritorno);
    }
  }
  exit(0);
}
