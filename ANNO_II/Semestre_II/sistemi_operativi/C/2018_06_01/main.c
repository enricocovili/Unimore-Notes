/*
La parte in C accetta un numero variabile N+1 (con N maggiore o uguale a 2, da
controllare) che rappresentano, i primi N, i nomi assoluti di file F1, F2, …
FN-1 (con lunghezza in linee media uguale a K, da non controllare) mentre
l’ultimo rappresenta un numero intero strettamente positivo (K, da controllare).
Il processo padre deve innanzitutto chiedere all’utente di fornire un numero
intero X strettamente positivo e minore o uguale a K e quindi deve generare N
processi figli (P0 … PN-1): i processi figli Pi (con i che varia da 0 a N-1)
sono associati agli N file Fa (con a= i+1). . Ogni processo figlio Pi deve
leggere, dal suo file associato, la linea X-esima se esiste. Nel caso la linea
esista, il processo figlio Pi, calcolata (come int) la lunghezza L di tale
linea. compreso il terminatore di linea, deve mandare L al processo padre e
quindi la linea (solo chiaramente i caratteri significativi della linea,
compreso il terminatore di linea). Nel caso la linea NON esista, il processo
figlio Pi, deve comunque mandare al processo padre una coppia di informazioni
corrispondente ad L e linea con contenuti tali che il padre possa capire che la
linea NON ESISTE! Il processo padre ha il compito di ricevere, rispettando
l’ordine dei file, prima il valore intero L e quindi, usando in modo opportuno
questa informazione, la linea: per ogni linea ricevuta, il processo padre deve
riportare sullo standard output il pid del processo figlio che gli ha inviato le
informazioni, il nome del file cui le informazioni si riferiscono e la linea. Al
termine, ogni processo figlio Pi deve ritornare al padre il valore di L
(supposto strettamente minore di 255) se la linea è stata trovata, altrimenti il
valore 0. Il padre, dopo che i figli sono terminati, deve stampare, su standard
output, i PID di ogni figlio con il corrispondente valore ritornato.
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
  int pid;  /* process identifier per le fork() del padre e del figlio */
  int N;    /* numero passato sulla riga di comando, che saranno il numero di
               processi figli e quindi nipoti da creare */
  int K, X; /* ultimo parametro e input utente*/
  int L;    /* lunghezza linea letta dal figlio */
  int fd;   /* file descriptor del nipote */
  int riga_attuale; /* riga attuale nel figlio */
  char buff[255];   /* buffer usato dal figlio per leggere riga per riga */
  /* nome indicato nel testo */
  int status;    /* variabile di stato per la wait */
  pipe_t *piped; /* array dinamico di pipe descriptors per comunicazioni
                    figli-padre  */
  int i, j;      /* indici per i cicli */
  /* nome indicato dal testo */
  int ritorno; /* variabile che viene ritornata da ogni figlio al padre */
               /* ------------------------------------ */

  /* Controllo sul numero di parametri: STRETTO! */
  if (argc <= 3) /* Ci vogliono almeno 3 parametri */
  {
    printf(
        "Errore nel numero dei parametri dato che argc = %d, mentre ci "
        "vogliono almeno 3 parametri\n",
        argc);
    exit(1);
  }

  K = atoi(argv[argc - 1]); /* converto l'ultimo numero */
  N = argc - 2;             /* numero file passati */
  if (K <= 0) {
    printf("K deve essere strettamente positivo.\n");
    exit(2);
  }

  /* chiediamo all'utente di inserire un numero X da tastiera */
  printf(
      "Inserire un numero intero strettamente positivo X e minore o uguale a "
      "%d\n",
      K);
  scanf("%d", &X);
  /* controlliamo X */
  if (X <= 0 || X > K) {
    printf("Il valore X inserito non e' valido\n");
    exit(3);
  }

  /* Allocazione dell'array di N pipe descriptors */
  piped = (pipe_t *)malloc(N * sizeof(pipe_t));
  if (piped == NULL) {
    printf("Errore nella allocazione della memoria\n");
    exit(4);
  }

  /* Creazione delle N pipe figli-padre */
  for (i = 0; i < N; i++) {
    if (pipe(piped[i]) < 0) {
      printf("Errore nella creazione della pipe figli-padre per l'indice %d\n",
             i);
      exit(5);
    }
  }

  /* Ciclo di generazione dei figli */
  for (i = 0; i < N; i++) {
    if ((pid = fork()) < 0) {
      printf("Errore nella fork di indice %d\n", i);
      exit(6);
    }

    if (pid == 0) {
      /* codice del figlio */
      /* in caso di errori nei figli o nei nipoti decidiamo di tornare -1 che
       * corrispondera' al valore 255 che non puo' essere un valore accettabile
       * di ritorno */

      /* Chiusura delle pipe non usate nella comunicazione con il padre */
      /* ogni figlio scrive solo su piped[n] */
      for (j = 0; j < N; j++) {
        close(piped[j][0]);
        if (i != j) close(piped[j][1]);
      }

      L = 0;
      /* codice figlio */
      if (fd = open(argv[i + 1], O_RDONLY) < 0) {
        printf("Errore nell'apertura del file %s\n", argv[i + 1]);
        exit(-1);
      }
      L = 0;
      riga_attuale = 1;
      while (read(fd, &buff[L], 1)) {
        if (buff[j] == '\n') {
          riga_attuale++;
          L++;
          if (riga_attuale == X) { /* siamo alla riga target */
            write(piped[i][1], buff, L);
            break;
          }
        }
        L++;
      }
      close(fd);
      exit(L);
    }
  }

  /* Codice del padre */
  /* Il padre chiude i lati delle pipe che non usa */
  for (i = 0; i < N; i++) close(piped[i][1]);

  /* Il padre recupera le informazioni dai figli: in ordine di indice */
  for (i = 0; i < N; i++) {
  }

  /* Il padre aspetta i figli */
  for (i = 0; i < N; i++) {
    pid = wait(&status);
    if (pid < 0) {
      printf("Errore in wait\n");
      exit(7);
    }

    if ((status & 0xFF) != 0)
      printf("Figlio con pid %d terminato in modo anomalo\n", pid);
    else {
      ritorno = (int)((status >> 8) & 0xFF);
      if (ritorno != 0)
        printf(
            "Il figlio con pid=%d ha fallito l'esecuzione del comando-filtro "
            "grep oppure se 255 ha avuto dei problemi\n",
            pid); /* se tutto e' stato svolto correttamente dal figlio questa
                     eventualita' NON potra' MAI CAPITARE */
      else
        printf("Il figlio con pid=%d ha ritornato %d, quindi tutto OK!\n", pid,
               ritorno);
    }
  }
  exit(0);
}