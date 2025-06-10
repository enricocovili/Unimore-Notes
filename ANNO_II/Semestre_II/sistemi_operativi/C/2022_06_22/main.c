/*
La  parte  in  C  accetta  un  numero  variabile  N  di  parametri  maggiore  o
uguale  a  3  (da  controllare)  che rappresentano  nomi  assoluti  di  file F1,
...  FN:  gli  N  file  hanno  le  linee  tutte  della  stessa  lunghezza
(MSGSIZE,  compreso  il  terminatore  di  linea).  Ognuno  degli  N  file  (come
fosse  un  file  temporaneo riempito da uno script shell) contiene in ogni linea
il nome di un file: come già detto, tali nomi hanno tutti la stessa lunghezza
data da MSGSIZE-1 (da non controllare). Il processo padre deve generare N
processi figli: i processi figli Pn sono associati agli N file Fh (con h= n+1).
Ognuno di tali figli, a parte il primo, deve creare a sua volta un processo
nipote PPn ogni volta che serve (si veda nel seguito). Il primo figlio P0 deve
leggere via via le linee dal proprio file associato F1 e, una volta trasformata
ogni linea  (linea)  in  stringa,  deve  mandare  linea  (che  rappresenta  il
nome  di  un  file)  via  via  a  tutti  gli  altri fratelli (P1 .. PN-1). Gli
altri processi P1 .. PN-1 devono ricevere via via i nomi inviati dal figlio P0
e, per ogni nome ricevuto (buffer), devono via via leggere i nomi presenti nel
proprio file associato (linea): per ogni coppia buffer- linea  il  processo  Pn
(con  n!=0)  deve  creare  un  processo  nipote.  Ogni  processo  nipote  PPi
esegue concorrentemente e deve confrontare i file di nome buffer e linea, usando
in modo opportuno il comando diff di UNIX/Linux. Ogni processo figlio Pn (con
n!=0) deve aspettare ogni nipote creato e, sulla base del valore di ritorno,
deve stampare su standard output se il contenuto del file di nome buffer è
uguale al contenuto del file di nome linea (esattamente in questo ordine): ad
esempio I file p1 e f1 sono uguali Al termine, ogni processo figlio Pn deve
ritornare al padre il proprio numero d’ordine (n) e il padre deve stampare su
standard output il PID di ogni figlio e il valore ritornato.
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define PERM 0644 /* in ottale per diritti UNIX */

#define MSGSIZE 6

typedef int pipe_t[2];

int main(int argc, char **argv)
{
  /* -------- Variabili locali ---------- */
  int pid; /* process identifier per le fork() del padre e del figlio */
  int N;   /* Numero di file */
  /* nome indicato nel testo */
  int status;       /* variabile di stato per la wait */
  pipe_t *pipeFrat; /* array dinamico di pipe descriptors per comunicazioni tra fratelli  */
  int n, j, i;      /* indici per i cicli */
  char linea[MSGSIZE];
  char buffer[MSGSIZE];
  int fd; /* per aprire gli N file in input */
  /* n nome indicato nel testo */
  /* nome indicato dal testo */
  int ritorno; /* variabile che viene ritornata da ogni figlio al padre */
               /* ------------------------------------ */

  /* Controllo sul numero di parametri: STRETTO! */
  if (argc < 4) /* Almeno 3 parametri */
  {
    printf("Ci vogliono almeno 3 parametri. Parametri passati: %d\n", argc);
    exit(1);
  }

  N = argc - 1;

  /* Allocazione dell'array di N pipe descriptors */
  pipeFrat = (pipe_t *)malloc(N * sizeof(pipe_t));
  if (pipeFrat == NULL)
  {
    printf("Errore nella allocazione della memoria\n");
    exit(4);
  }

  /* Creazione delle N pipe fratelli */
  for (n = 0; n < N; n++)
  {
    if (pipe(pipeFrat[n]) < 0)
    {
      printf("Errore nella creazione della pipe fratelli per l'indice %d\n",
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
      /* codice del figlio */
      /* in caso di errori nei figli o nei nipoti decidiamo di tornare -1 che
       * corrispondera' al valore 255 che non puo' essere un valore accettabile
       * di ritorno */

      printf("DEBUG-Sono il figlio %d di indice %d\n", getpid(), n);

      /* Chiusura delle pipe non usate nella comunicazione con il padre */
      /* ogni figlio scrive e legge solo su pipeFrat[n]*/
      if (n == 0) /* figlio "speciale" */
      {
        close(pipeFrat[0][0]); /* non leggo niente */
        if ((fd = open(argv[1], O_RDONLY)) < 0)
        {
          printf("Errore apertura file %s nel primo figlio\n", argv[1]);
          exit(-1);
        }
        j = 0;
        while (read(fd, &linea[j], 1) == 1)
        {
          if (linea[j] == '\n')
          {
            linea[j] = '\0'; /* trasformo in stringa */
            for (i = 0; i < N; i++)
            {
              if (write(pipeFrat[i][1], linea, MSGSIZE) < 0)
              {
                printf("Errore nella scrittura su pipe tra fratelli\n");
                exit(-1);
              }
            }
            j = 0;
          }
          else
          {
            j++;
          }
        }
      }
      else
      {
        for (j = 1; j < N; j++)
        {
          close(pipeFrat[j][1]); /* i fratelli "minori" non scrivono */
        }
        if ((fd = open(argv[1], O_RDONLY)) < 0)
        {
          printf("Errore apertura file %s figlio\n", argv[n + 1]);
          exit(-1);
        }
        j = 0;
        while (read(fd, &buffer[j], 1) == 1)
        {
          if (buffer[j] == '\n')
          {
            buffer[j] = '\0'; /* trasformo in stringa */
            if (read(pipeFrat[n][0], linea, MSGSIZE) != MSGSIZE)
            {
              printf("errore in lettura pipe\n");
              exit(-1);
            }
            if ((pid = fork()) < 0)
            {
              printf("Errore nella creazione di un nipote\n");
              exit(-1);
            }
            if (pid == 0) /* codice nipote */
            {
              close(1);
              close(2);
              execlp("diff", "diff", buffer, linea, (char *)0);
              /* non dovrebbe mai accadere */
              perror("Problemi di esecuzione del diff da parte del nipote");
              exit(-1); /* si veda commento precedente */
            }
            pid = wait(&status);
            ritorno = (int)((status >> 8) & 0xFF);
            if (ritorno == 0)
            {
              printf("i file %s e %s sono UGUALI\n", buffer, linea);
            }
            else
            {
              printf("i file %s e %s sono DIVERSI\n", buffer, linea);
            }
            j = 0;
          }
          else
          {
            j++;
          }
        }
        lseek(fd, 0L, 0);
      }
      exit(n);
    }
  }

  /* Codice del padre */
  /* Il padre chiude i lati delle pipe che non usa */
  for (n = 0; n < N; n++)
    close(pipeFrat[n][1]);

  /* Il padre recupera le informazioni dai figli: in ordine di indice */
  for (n = 0; n < N; n++)
  {
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
      if (ritorno != 0)
        printf("Il figlio con pid=%d ha ritornato %d, quindi tutto OK!\n", pid,
               ritorno);
    }
  }
  exit(0);
}
