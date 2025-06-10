/* Soluzione parte C esame del 17 Gennaio 2024: versione che calcola il minimo
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef int
    pipe_t[2]; /* tipo di dato per contenere i file descriptors di una pipe */

int main(int argc, char **argv) {
  int N; /* numero di processi figli */
  /* nome stabilito dal testo */
  int pid;         /* variabile per fork */
  pipe_t *pipe_fp; /* array di pipe per la comunicazione figli-padre*/
  pipe_t *pipe_pf; /* array di pipe per l'indicazione padre-figli */
  int fd;          /* variabile per open */
  char linea[250]; /* variabile per leggere le linee dai file (si suppone
                      bastino 250 caratteri) */
  /* nome stabilito dal testo */
  char car; /* variabile usata dal padre per leggere gli ultimi caratteri delle
               linee inviati dai figli */
  /* nome stabilito dal testo */
  char chMin; /* variabile per tenere traccia del carattere di codice ASCII
                 minimo */
  char chControllo; /* variabile per inviare indicazione ai figli */
  int indice; /* usata dal padre per tenere traccia dell'indice del figlio che
                 ha calcolato il minimo */
  int stampe; /* numero di stampe fatte dai figli che va ritornato al padre */
  int status, pidFiglio, ritorno; /* per wait */
  int n, j;                       /* indici per cicli */
  /* n nome stabilito dal testo */
  int lastj;  /* per salvare il valore di j se e' ultima linea letta dal figlio
               */
  int nr, nw; /* per controlli read e write su/da pipe */

  /* Controllo sul numero di parametri */
  if (argc < 3) {
    printf("Errore numero parametri %d\n", argc);
    exit(1);
  }

  N = argc - 1;

  /* allocazione memoria dinamica per pipe_fp e pipe_pf */
  pipe_fp = malloc(N * sizeof(pipe_t));
  pipe_pf = malloc(N * sizeof(pipe_t));
  if ((pipe_fp == NULL) || (pipe_pf == NULL)) {
    printf("Errore nelle malloc\n");
    exit(2);
  }

  /* creazione delle pipe */
  for (n = 0; n < N; n++) {
    if (pipe(pipe_fp[n]) != 0) {
      printf("Errore creazione delle pipe figli-padre\n");
      exit(3);
    }
    if (pipe(pipe_pf[n]) != 0) {
      printf("Errore creazione delle pipe padre-figli\n");
      exit(4);
    }
  }

  /* creazione dei processi figli */
  for (n = 0; n < N; n++) {
    pid = fork();
    if (pid < 0) /* errore */
    {
      printf("Errore nella fork con indice %d\n", n);
      exit(5);
    }
    if (pid == 0) {
      /* codice del figlio */
      /* stampa di debugging */
      printf("DEBUG-Figlio di indice %d e pid %d associato al file %s\n", n,
             getpid(), argv[n + 1]);
      /* chiudiamo le pipe che non servono */
      /* ogni figlio scrive solo su pipe_fp[n] e legge solo da pipe_pf[n] */
      for (j = 0; j < N; j++) {
        close(pipe_fp[j][0]);
        close(pipe_pf[j][1]);
        if (j != n) {
          close(pipe_fp[j][1]);
          close(pipe_pf[j][0]);
        }
      }

      fd = open(argv[n + 1], O_RDONLY);
      if (fd < 0) {
        printf("Impossibile aprire il file %s\n", argv[n + 1]);
        exit(-1); /* in caso di errore torniamo -1 che verra' interpretato dal
                     padre come 255 che non e' un valore accettabile */
      }

      /* inizializziamo stampe */
      stampe = 0;
      j = 0; /* inizializzazione indice per la linea */
      while (read(fd, &linea[j], 1)) {
        if (linea[j] == '\n') /* se siamo a fine linea */
        {
          lastj = j; /* salviamo l'ultimo indice */
          j = 0;     /* riportiamo a 0 l'indice della linea */
        } else
          j++; /* incrementiamo il valore di j per il prossimo carattere */
      }
      /* arrivati qui in linea abbiamo l'ultima linea del file e in lastj
       * l'ultimo indice di tale linea */
      /* inviamo il primo carattere (escluso il terminatore di linea) al padre
       */
      nw = write(pipe_fp[n][1], &linea[0], 1);
      if (nw != 1) {
        printf("Impossibile scrivere sulla pipe per il processo di indice %d\n",
               n);
        exit(-1);
      }
      /* aspettiamo dal padre se dobbiamo scrivere o meno */
      nr = read(pipe_pf[n][0], &chControllo, 1);
      if (nr != 1) {
        printf("Impossibile leggere dalla pipe per il processo di indice %d\n",
               n);
        exit(-1);
      }
      /* printf("FIGLIO indice %d ho ricevuto dal padre %c\n", n, chControllo);
       */
      if (chControllo == 'S') {
        /* autorizzato, scriviamo */
        /* ma prima convertiamo la linea in stringa: ATTENZIONE IL TERMINATORE
         * DI LINEA DEVE RIMANERE E QUINDI USIAMO L'INDICE lastj+1! */
        linea[lastj + 1] = '\0';
        printf(
            "Sono il figlio di indice %d e pid %d e ho trovato l'ultima linea "
            "con primo carattere '%c' con codice ASCII minore degli altri nel "
            "file %s. Ecco la linea:\n%s",
            n, getpid(), linea[0], argv[n + 1], linea);
        /* dato che linea ha gia' lo '\n' NON lo inseriamo nella printf */
        stampe++; /* incrementiamo il numero di stampe fatte */
      }
      exit(stampe); /* torniamo il numero di stampe fatte (sara' o 0 o 1 al
                       massimo) */
    }
  }

  /*codice del padre*/
  /* chiudiamo le pipe che non usiamo */
  for (n = 0; n < N; n++) {
    close(pipe_fp[n][1]);
    close(pipe_pf[n][0]);
  }

  chMin = 127;

  for (n = 0; n < N; n++) {
    /* leggiamo il carattere dal figlio i-esimo */
    read(pipe_fp[n][0], &car, 1);
    if (car < chMin) {
      /* dobbiamo aggiornare il minimo */
      chMin = car;
      /* debbiamo tenere conto dell'indice del processo che ha inviato il minimo
       */
      indice = n;
    }
  }
  /* bisogna mandare ai figli l'indicazione giusta (S per scrivere, N per NON
   * scrivere) */
  for (n = 0; n < N; n++) {
    if (n == indice) /* figlio che deve scrivere */
      chControllo = 'S';
    else
      chControllo = 'N';
    /* printf("PADRE per indice %d sta per mandare %c\n", i, chControllo); */
    nw = write(pipe_pf[n][1], &chControllo, 1);
    if (nw != 1)
      printf("PADRE non e' riuscito ad inviare nulla al figlio di indice %d \n",
             n);
  }

  /* Attesa della terminazione dei figli */
  for (n = 0; n < N; n++) {
    pidFiglio = wait(&status);
    if (pidFiglio < 0) {
      printf("Errore wait\n");
      exit(6);
    }
    if ((status & 0xFF) != 0)
      printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
    else {
      ritorno = (int)((status >> 8) & 0xFF);
      printf("Il figlio con pid=%d ha ritornato %d (se 255 problemi)\n",
             pidFiglio, ritorno);
    }
  }
  exit(0);
} /* fine del main */