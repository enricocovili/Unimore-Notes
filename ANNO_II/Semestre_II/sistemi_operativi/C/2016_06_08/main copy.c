/*

*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define PERM 0644 /* in ottale per diritti UNIX */

int mia_random(int n)
{
  int casuale;
  casuale = rand() % n;
  return casuale;
}

typedef int pipe_t[2];

int main(int argc, char **argv)
{
  /* -------- Variabili locali ---------- */
  int pid;                  /* process identifier per le fork() del padre e del figlio */
  int N;                    /* numero passato sulla riga di comando, che saranno il numero di
                               processi figli e quindi nipoti da creare */
  int H;                    /* Numero di righe dei file */
  int lung_linea;           /* lunghezza linea attuale dei figli */
  int caratt_scritti;       /* numero caratteri scritti dai figli sul file /tmp/creato */
  int indice_figlio_random; /* identifica n-esimo figlio */
  int indice_linea_random;  /* indentifica indice random da scrivere per i figli */
  int status;               /* variabile di stato per la wait */
  pipe_t *pipePf;           /* Pipe padre figli */
  pipe_t *pipeFp;           /* Pipe figli padre */
  int n, j;                 /* indici per i cicli */
  int Fcreato;              /* fd per creazione file da parte del padre */
  int fd;                   /* file descriptor usato dai figli per la lettura del n+1 file */
  char linea[255];          /* buffer di lettura */
  /* nome indicato dal testo */
  int ritorno; /* variabile che viene ritornata da ogni figlio al padre */
               /* ------------------------------------ */

  /* Controllo sul numero di parametri: STRETTO! */
  if (argc < 6) /* Ci vogliono almeno 4 parametri */
  {
    printf(
        "Errore nel numero dei parametri dato che argc = %d, mentre ci "
        "vogliono almeno 5 parametri\n",
        argc);
    exit(1);
  }

  /* Calcoliamo il numero passato corrispondente al primo parametro e facciamo
   * il controllo che sia strettamente positivo */
  H = atoi(argv[argc - 1]); /* usiamo la funzione di libreria atoi: se si riesce a
                          convertire in un numero strettamente positivo lo
                          consideriamo un controllo sufficiente */
  if (H <= 0)
  {
    printf(
        "Errore: L'ultimo parametro %s non e' un numero strettamente maggiore "
        "di 0\n",
        argv[1]);
    exit(2);
  }

  /* Per prima cosa il processo padre deve creare un file con il nome passato
   * come secondo parametro */
  if ((Fcreato = creat("/tmp/creato", PERM)) < 0)
  /* ERRORE se non si riesce a creare il file */
  {
    printf("Errore nella creazione file per /tmp/creato dato che Fcreato = %d\n",
           Fcreato);
    exit(3);
  }

  N = argc - 1; /* numero di file */

  srand(time(NULL));

  /* Allocazione dell'array di N pipe descriptors */
  pipePf = (pipe_t *)malloc(N * sizeof(pipe_t));
  pipeFp = (pipe_t *)malloc(N * sizeof(pipe_t));
  if (pipePf == NULL || pipeFp == NULL)
  {
    printf("Errore nella allocazione della memoria\n");
    exit(4);
  }

  /* Creazione delle N pipe figli-padre */
  for (n = 0; n < N; n++)
  {
    if (pipe(pipePf[n]) < 0 || pipeFp[n] < 0)
    {
      printf("Errore nella creazione della pipe per l'indice %d\n",
             n);
      exit(5);
    }
  }

  /* Le N pipe figli-nipoti deriveranno dalla creazione di una pipe in ognuno
   * dei figli che poi creeranno un nipote */

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
      caratt_scritti = 0; /* azzero contatore caratteri scritti */
      /* codice del figlio */
      /* in caso di errori nei figli o nei nipoti decidiamo di tornare -1 che
       * corrispondera' al valore 255 che non puo' essere un valore accettabile
       * di ritorno */

      /* Chiusura delle pipe non usate nella comunicazione con il padre */
      /* chiusura pipes inutilizzate */
      for (j = 0; j < N; j++)
      { /* il figlio non legge dai nessuna pipeFP e non scrive su nessuna pipePF */
        close(pipeFp[j][0]);
        close(pipePf[j][1]);
        if (j != n)
        { /* inoltre non scrive e non legge se non su/dalle sue pipe */
          close(pipeFp[j][1]);
          close(pipePf[j][0]);
        }
      }

      if ((fd = open(argv[n + 1], O_RDONLY)) < 0)
      {
        printf("errore nella lettura del file %s\n", argv[n + 1]);
        exit(-1);
      }

      j = 0;
      while (read(fd, &linea[j], 1))
      {
        if (linea[j] == '\n')
        {
          j++;
          write(pipeFp[n][1], &j, sizeof(j));
          read(pipePf[n][0], &indice_linea_random, sizeof(indice_linea_random));
          if (indice_linea_random < j)
          {
            write(fd, &linea[j], 1); /* scrivo quel carattere sul file */
            caratt_scritti++;
          }
          j = 0;
        }
        else
        {
          j++;
        }
      }
      return caratt_scritti;
    }
  }

  /* codice del padre */
  /* chiusura pipes inutilizzate */
  for (j = 0; j < N; j++)
  { /* il padre non legge dai nessuna pipePF e non scrive su nessuna pipeFP */
    close(pipeFp[j][1]);
    close(pipePf[j][0]);
  }

  /* Il padre recupera le informazioni dai figli: seguendo la logica del numero di linee */
  for (j = 0; j < H; j++)
  {
    indice_figlio_random = mia_random(N);
    printf("DEBUG-padre. scelto randomicamente figlio n.%d\n", indice_figlio_random);
    /* FOR di lettura. ricevo da ogni figlio la lunghezza della linea corrente */
    for (n = 0; n < N; n++)
    {
      if (read(pipeFp[n][0], &lung_linea, sizeof(lung_linea)) < 0)
      {
        printf("errore nella lettura pipe figlio %d.\n", n);
        exit(6);
      }
      if (n == indice_figlio_random)
      {
        indice_linea_random = mia_random(lung_linea);
      }
    }
    /* FOR di scrittura. comunico ai figli l'indice random della linea scelta */
    for (n = 0; n < N; n++)
    {
      write(pipePf[n][1], &indice_linea_random, sizeof(indice_linea_random));
    }
  }

  /* Il padre aspetta i figli */
  for (n = 0; n < N; n++)
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
      printf("Il figlio con pid=%d ha ritornato %d\n", pid,
             ritorno);
    }
  }
  exit(0);
}
