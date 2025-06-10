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

typedef struct {
  char c1[12]; /* TROVATA o NON TROVATA */
  int c2;      /* pid processo nipote */
} Strut;

int main(int argc, char **argv) {
  /* -------- Variabili locali ---------- */
  int pid; /* process identifier per le fork() del padre e del figlio */
  int N;   /* numero passato sulla riga di comando, che saranno il numero di
              processi figli e quindi nipoti da creare */
  /* nome indicato nel testo */
  int status;    /* variabile di stato per la wait */
  pipe_t *piped; /* array dinamico di pipe descriptors per comunicazioni
                    figli-padre  */
  int n, j;      /* indici per i cicli */
  /* n nome indicato nel testo */
  Strut *cur; /* array di strutture dati */
  /* nome indicato dal testo */
  int ritorno; /* variabile che viene ritornata da ogni figlio al padre */
               /* ------------------------------------ */

  /* Controllo sul numero di parametri: STRETTO! */
  if (argc < 4) /* Ci vogliono almeno tre parametri */
  {
    printf(
        "Errore nel numero dei parametri dato che argc = %d, mentre ci "
        "vogliono almeno tre parametri\n",
        argc);
    exit(1);
  }

  N = argc - 2; /* numero figli */

  /* Allocazione dell'array di N pipe descriptors e array Strut */
  piped = (pipe_t *)malloc(N * sizeof(pipe_t));
  if (piped == NULL) {
    printf("Errore nella allocazione della memoria\n");
    exit(2);
  }

  /* Creazione delle N pipe figli-padre */
  for (n = 0; n < N; n++) {
    if (pipe(piped[n]) < 0) {
      printf("Errore nella creazione della pipe figli-padre per l'indice %d\n",
             n);
      exit(5);
    }
  }

  /* Le N pipe figli-nipoti deriveranno dalla creazione di una pipe in ognuno
   * dei figli che poi creeranno un nipote */

  /* Ciclo di generazione dei figli */
  for (n = 0; n < N; n++) {
    if ((pid = fork()) < 0) {
      printf("Errore nella fork di indice %d\n", n);
      exit(6);
    }

    if (pid == 0) {
      /* codice del figlio */
      /* in caso di errori nei figli o nei nipoti decidiamo di tornare -1 che
       * corrispondera' al valore 255 che non puo' essere un valore accettabile
       * di ritorno */

      /* Chiusura delle pipe non usate nella comunicazione con il padre */
      for (j = 0; j < N; j++) {
        if (j != n) close(piped[j][1]);
        if ((n == 0) || (j != n - 1)) close(piped[j][0]);
      }

      if ((pid = fork()) < 0) /* poi ogni figlio crea un nipote */
      {
        printf("Errore nella fork di creazione del nipote\n");
        exit(-1); /* si veda commento precedente */
      }
      if (pid == 0) {
        /* codice del nipote */
        /* in caso di errori nei figli o nei nipoti decidiamo di tornare -1 che
         * corrispondera' al valore 255 che non puo' essere un valore
         * accettabile di ritorno */

        /* chiusura della pipe rimasta aperta di comunicazione fra figlio-padre
         * che il nipote non usa */
        close(piped[n][1]);

        /* Ridirezione dello standard output su /dev/null (per evitare messaggi
         * di grep a video)*/
        close(1);
        open("/dev/null", O_WRONLY);

        /* ridirezionamo anche lo standard error su /dev/null perche' ci
         * interessa solo se il comando grep ha successo o meno */
        close(2);
        open("/dev/null", O_WRONLY);

        /* Il nipote diventa il comando grep, con execlp per path */
        execlp("grep", "grep", argv[n + 2], argv[1], (char *)0);

        /* Non si dovrebbe mai tornare qui!!*/
        /* usiamo perror che scrive su standard error, dato che lo standard
         * output e' collegato alla pipe */
        perror("Problemi di esecuzione del grep da parte del nipote");
        exit(-1); /* si veda commento precedente */
      };

      cur = (Strut *)malloc(sizeof(Strut) * n + 1);
      if (cur == NULL) {
        printf("errore allocazione cur\n");
        exit(1);
      }
      if (n != 0) {
        if (read(piped[n - 1][0], cur, n * sizeof(Strut)) !=
            n * sizeof(Strut)) {
          printf("errore nella lettura della pipe del figlio %d\n", n);
          exit(1);
        }
      }
      cur[n].c2 = pid; /* assegnamento pid nipote */

      /* figlio aspetta nipote */
      pid = wait(&status);
      if (pid < 0) {
        printf("Errore in wait\n");
        exit(7);
      }

      if ((status & 0xFF) != 0)
        printf("Nipote con pid %d terminato in modo anomalo\n", pid);
      else {
        ritorno = (int)((status >> 8) & 0xFF);
        if (ritorno == 0) { /* ha trovato qualcosa */
          strcpy(cur[n].c1, "TROVATA");
        } else {
          strcpy(cur[n].c1, "NON TROVATA");
        }
      }

      if (write(piped[n][1], cur, (n + 1) * sizeof(Strut)) !=
          (n + 1) * sizeof(Strut)) {
        printf("errore in scrittura nel figlio %d\n", n);
        exit(1);
      }
      exit(ritorno); /* ritorno valore nipote */
    }
  }

  /* Codice del padre */
  /* Il padre chiude i lati delle pipe che non usa */
  for (n = 0; n < N - 1; n++) {
    close(piped[n][0]);
    close(piped[n][1]);
  }
  close(piped[N - 1][1]);

  /* allocazione dell'array di strutture specifico per il padre */
  /* creiamo un array di dimensione N quanto il numero di figli! */
  if ((cur = (Strut *)malloc(N * sizeof(Strut))) == NULL) {
    printf("Errore allocazione cur nel padre\n");
    exit(5);
  }

  /* legge struttura da ultimo figlio */
  if (read(piped[N - 1][0], cur, N * sizeof(Strut)) != N * sizeof(Strut)) {
    printf("errore nella lettura della pipe finale del padre\n");
    exit(1);
  }

  /* stampo informazioni */
  for (n = 0; n < N; n++) {
    printf("Figlio n. %d, stringa \"%s\" %s, pidNipote=%d, file=%s\n", n,
           argv[n + 2], cur[n].c1, cur[n].c2, argv[1]);
  }

  /* Il padre aspetta i figli */
  for (n = 0; n < N; n++) {
    pid = wait(&status);
    if (pid < 0) {
      printf("Errore in wait\n");
      exit(7);
    }

    if ((status & 0xFF) != 0)
      printf("Figlio con pid %d terminato in modo anomalo\n", pid);
    else {
      ritorno = (int)((status >> 8) & 0xFF);
      printf("Il figlio con pid=%d ha ritornato %d!\n", pid, ritorno);
    }
  }
  exit(0);
}
