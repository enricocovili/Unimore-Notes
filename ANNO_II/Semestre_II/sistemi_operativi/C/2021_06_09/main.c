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

int main(int argc, char **argv)
{
  /* -------- Variabili locali ---------- */
  int pid; /* process identifier per le fork() del padre e del figlio */
  int N;   /* numero passato sulla riga di comando, che saranno il numero di
              processi figli e quindi nipoti da creare */
  /* nome indicato nel testo */
  int status;    /* variabile di stato per la wait */
  pipe_t *piped; /* array dinamico di pipe descriptors per comunicazioni
                    figli-padre  */
  pipe_t p;      /* una sola pipe per padre-primo figlio */
  int n, j;      /* indici per i cicli */
  /* n nome indicato nel testo */
  int fcreato;     /* fd per creazione file da parte del padre */
  char linea[200]; /* array di caratteri usato sia dal figlio per la sprintf e
                       sia dal padre per ricevere dai figli */
  /* nome indicato dal testo */
  int fd;               /* usato dai figli per leggere gli N file */
  int numLinee;         /* lunghezza file calcolata dal figlio speciale */
  int lung_linea;       /* variabile che contiene figlio per figlio la lunghezzza della linea inviata */
  int ultima_lunghezza; /* usato dai figli per valore di ritorno */
  int ritorno;          /* variabile che viene ritornata da ogni figlio al padre */
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

  N = argc - 1;

  /* creo file come da consegna */
  fcreato = creat("/tmp/EnricoCovili", PERM);
  if (fcreato < 0)
  {
    printf("Errore creazione file temporaneo\n");
    exit(2);
  }

  /* Allocazione dell'array di N pipe descriptors */
  piped = (pipe_t *)malloc(N * sizeof(pipe_t));
  if (piped == NULL)
  {
    printf("Errore nella allocazione della memoria\n");
    exit(4);
  }

  /* Creazione delle N pipe figli-padre */
  for (n = 0; n < N; n++)
  {
    if (pipe(piped[n]) < 0)
    {
      printf("Errore nella creazione della pipe figli-padre per l'indice %d\n",
             n);
      exit(5);
    }
  }

  pipe(p); /* creazione pipe */

  /* Primo figlio speciale che diventa il comando wc */
  if ((pid = fork()) < 0)
  {
    printf("Errore nella creazione figlio speciale\n");
    exit(6);
  }
  if (pid == 0)
  {
    close(0);
    if (open(argv[1], O_RDONLY) < 0)
    {
      printf("Errore nella open del file %s\n", argv[1]);
      exit(-1); /* si veda commento precedente */
    }
    close(1);
    dup(p[1]);
    close(p[0]);
    close(p[1]);
    /* ridirezione dello standard error su /dev/null (per evitare messaggi di errore a video): facoltativo! */
    close(2);
    open("/dev/null", O_WRONLY);

    /* il figlio diventa il comando wc -l */
    execlp("wc", "wc", "-l", (char *)0);
    /* attenzione ai parametri nella esecuzione di wc: solo -l e terminatore della lista */

    /* NON si dovrebbe mai tornare qui!!*/
    exit(-1); /* si veda commento precedente */
  }
  close(p[1]);

  j = 0;
  while (read(p[0], &linea[j], 1))
    j++;

  if (j == 0)
  {
    printf("errore nella lettura del primo file\n");
    exit(7);
  }
  linea[j - 1] = '\0';
  numLinee = atoi(linea); /* trovato numero righe */

  /* Ciclo di generazione dei figli */
  for (n = 0; n < N; n++)
  {
    if ((pid = fork()) < 0)
    {
      printf("Errore nella fork di indice %d\n", n);
      exit(6);
    }

    if (pid == 0)
    {
      /* codice del figlio */
      /* in caso di errori nei figli o nei nipoti decidiamo di tornare -1 che
       * corrispondera' al valore 255 che non puo' essere un valore accettabile
       * di ritorno */

      /* Chiusura delle pipe non usate nella comunicazione con il padre */
      /* ogni figlio scrive solo su piped[n] */
      for (j = 0; j < N; j++)
      {
        close(piped[j][0]);
        if (n != j)
          close(piped[j][1]);
      }

      if ((fd = open(argv[n + 1], O_RDONLY)) < 0)
      {
        printf("Errore apertura file %s\n", argv[n + 1]);
        exit(-1);
      }

      j = 0;
      while (read(fd, &linea[j], 1))
      {
        j++;
        if (linea[j - 1] == '\n')
        {
          // printf("DEBUG-figlio %d. scrivo %d di %ld byte\n", n, j, sizeof(j));
          write(piped[n][1], &j, sizeof(j));
          write(piped[n][1], linea, j);
          ultima_lunghezza = j;
          j = 0;
        }
      }
      return ultima_lunghezza;
    }
  }

  /* Codice del padre */
  /* Il padre chiude i lati delle pipe che non usa */
  for (n = 0; n < N; n++)
    close(piped[n][1]);

  /* doppio for: per numero di righe e per numero di figli */
  for (j = 0; j < numLinee; j++)
  {
    for (n = 0; n < N; n++)
    {
      read(piped[n][0], &lung_linea, sizeof(lung_linea)); /* leggo prima la lunghezza della linea */
      read(piped[n][0], linea, lung_linea);               /* leggo effettivamente la linea */
      // printf("DEBUG-padre. Sto per scrivere %d byte su /tmp\n", lung_linea);
      write(fcreato, linea, lung_linea); /* scrivo su file. ho già il terminatore di linea */
    }
  }

  /* Il padre aspetta i figli */
  for (n = 0; n < N + 1; n++)
  {
    pid = wait(&status);
    if (pid < 0)
    {
      printf("Errore in wait\n");
      exit(7);
    }

    if ((status & 0xFF) != 0)
      printf("Figlio con pid %d terminato in modo anomalo\n", pid);
    else
    {
      ritorno = (int)((status >> 8) & 0xFF);
      printf("Il figlio con pid=%d ha ritornato %d, quindi tutto OK!\n", pid,
             ritorno);
    }
  }
  exit(0);
}
