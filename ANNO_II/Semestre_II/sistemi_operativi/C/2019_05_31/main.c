/*
Con un editor, scrivere un programma in C 31Mag19.c che risolva la seconda prova
in itinere del 31 Maggio 2019 che si riporta qui di seguito per comodità: N.B.
Sul sito si trovano in totale 4 testi per questa prova; quello riportato nel
seguito è la versione 1 dei turni 1 e 2. La parte in C accetta un numero
variabile N di parametri maggiore o uguale a 3 (da controllare) che
rappresentano nomi assoluti di file F1...FN. Il processo padre deve generare N
processi figli: i processi figli Pi sono associati agli N file Fh (con h = i+1).
Ognuno di tali figli deve creare a sua volta un processo nipote PPi: ogni
processo nipote PPi esegue concorrentemente e deve ordinare il file Fh secondo
il normale ordine alfabetico, senza differenziare maiuscole e minuscole, usando
in modo opportuno il comando sort di UNIX/Linux. Ogni processo figlio Pi deve
ricevere solo la PRIMA linea inviata dal suo processo nipote PPi e deve inviare
al processo padre una struttura dati, che deve contenere tre campi: 1) c1, di
tipo int, che deve contenere il PID del nipote; 2) c2, di tipo int, che deve
contenere la lunghezza della linea compreso il terminatore di linea; 3) c3, di
tipo char[250]*, che deve contenere la linea corrente ricevuta dal nipote. Il
padre deve ricevere, rispettando l'ordine dei file, le singole strutture inviate
dai figli e deve stampare su standard output, per ogni struttura ricevuta,
ognuno dei campi insieme al nome del file cui le informazioni si riferiscono: si
faccia attenzione al fatto che è demandato al padre il compito di trasformare,
in una stringa, la linea ricevuta nel campo c3 di ogni struttura! Al termine,
ogni processo figlio Pi deve ritornare al padre la lunghezza della linea inviata
al padre, ma non compreso il terminatore di linea e il padre deve stampare su
standard output il PID di ogni figlio e il valore ritornato.
* Ogni linea si può supporre che abbia una lunghezza massima di 250 caratteri,
compreso il terminatore di linea e il terminatore di stringa.
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define PERM 0644 /* in ottale per diritti UNIX */

typedef int pipe_t[2];

/* definizione del TIPO Strut per le singole strutture dati, che verranno
 * inviate sulle pipe da parte dei figli al padre */
typedef struct
{
  int pid_nipote;        /* campo c1 del testo */
  int lung_linea;        /* campo c2 del testo */
  char linea_letta[250]; /* campo c3 del testo */
} Strut;

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
  pipe_t p;      /* una sola pipe per ogni coppia figlio-nipote: chiaramente
                    complessivamente saranno N pipe una per ogni coppia */
  int n, j;      /* indici per i cicli */
  /* n nome indicato nel testo */
  char buffer[250]; /* array di caratteri usato sia dal figlio per la sprintf e
                       sia dal padre per ricevere dai figli */
  /* nome indicato dal testo */
  int ritorno; /* variabile che viene ritornata da ogni figlio al padre */
  Strut S;     /* Strut di comunicazione tra figlio e padre */
  /* ------------------------------------ */

  /* Controllo sul numero di parametri: STRETTO! */
  if (argc <= 3) /* Ci vogliono solo due parametri */
  {
    printf(
        "Errore nel numero dei parametri dato che argc = %d, mentre ci "
        "vogliono almeno 3 parametri\n",
        argc);
    exit(1);
  }

  N = argc - 1; // numero processi (e file)

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

      /* Chiusura delle pipe non usate nella comunicazione con il padre */
      /* ogni figlio scrive solo su piped[n] */
      for (j = 0; j < N; j++)
      {
        close(piped[j][0]);
        if (n != j)
          close(piped[j][1]);
      }

      /* prima creiamo la pipe di comunicazione fra figlio e nipote */
      if (pipe(p) < 0)
      {
        printf(
            "Errore nella creazione della pipe figlio-nipote per l'indice %d\n",
            n);
        exit(-1); /* si veda commento precedente */
      }

      if ((pid = fork()) < 0) /* poi ogni figlio crea un nipote */
      {
        printf("Errore nella fork di creazione del nipote\n");
        exit(-1); /* si veda commento precedente */
      }
      if (pid == 0)
      {
        /* codice del nipote */
        /* in caso di errori nei figli o nei nipoti decidiamo di tornare -1 che
         * corrispondera' al valore 255 che non puo' essere un valore
         * accettabile di ritorno */

        /* chiusura della pipe rimasta aperta di comunicazione fra figlio-padre
         * che il nipote non usa */
        close(piped[n][1]);

        /* ogni nipote deve simulare il piping dei comandi nei confronti del
         * figlio e quindi deve chiudere lo standard output e quindi usare la
         * dup sul lato di scrittura della pipe p */
        close(1);
        dup(p[1]);
        /* ogni nipote adesso puo' chiudere entrambi i lati della pipe: il lato
         * 0 NON viene usato e il lato 1 viene usato tramite lo standard output
         */
        close(p[0]);
        close(p[1]);

        close(2);

        /* Il nipote diventa il comando ps: bisogna usare le versioni dell'exec
         * con la p in fondo in modo da usare la variabile di ambiente PATH  */
        execlp("sort", "sort", "-f", argv[n + 1], (char *)0);

        /* Non si dovrebbe mai tornare qui!!*/
        /* usiamo perror che scrive su standard error, dato che lo standard
         * output e' collegato alla pipe */
        perror("Problemi di esecuzione del sort da parte del nipote");
        exit(-1); /* si veda commento precedente */
      }
      /* codice figlio */

      /* ogni figlio deve simulare il piping dei comandi nei confronti del
       * nipote e poi nei confronti del padre: */
      /* quindi prima deve chiudere lo standard input e quindi usare la dup sul
       * lato di lettura della pipe p */
      /* quindi dopo deve chiudere lo standard output e quindi usare la dup sul
       * lato di scrittura della pipe piped[n] */
      close(1);
      dup(piped[n][1]);

      /* ogni figlio adesso puo' chiudere entrambi i lati della pipe p e la
       * scrittura di piped[n] */
      close(p[0]);
      close(p[1]);
      close(piped[n][1]);

      S.pid_nipote = getpid();
      j = 0;
      while (read(piped[n][0], &(S.linea_letta[j]), 1))
      {
        if (buffer[j] == '\n')
        { // finita prima linea
          S.lung_linea = j - 1;
          break;
        }
        j++; /* incrementiamo l'indice della linea */
      }

      write(piped[n][1], &S, sizeof(S));

      /* il figlio deve aspettare il nipote non solo per correttezza ma per
       * evitare che il nipote riceva il segnale SIGPIPE dato che il figlio
       * legge solo la PRIMA linea */
      ritorno = -1; /* si veda commento precedente */
      pid = wait(&status);
      if (pid < 0)
        printf("Errore in wait\n");
      if ((status & 0xFF) != 0)
        printf("Nipote con pid %d terminato in modo anomalo\n", pid);
      else
      {
        /* questa stampa non e' richiesta dal testo */
        /* printf("DEBUG-Il nipote con pid=%d ha ritornato %d\n", pid,
         * (int)((status >> 8) & 0xFF)); */
        /* il figlio ritorna la lunghezza della linea inviata NON compreso il
         * terminatore (se fosse compreso il terminatore il valore di lung_linea
         * NON andrebbe decrementato) */
        ritorno = S.lung_linea - 1;
      }

      exit(ritorno);
    }
  }

  /* Codice del padre */
  /* Il padre chiude i lati delle pipe che non usa */
  for (n = 0; n < N; n++)
    close(piped[n][1]);

  /* Il padre recupera le informazioni dai figli: in ordine di indice */
  for (n = 0; n < N; n++)
  {
    j = 0; /* inizializziamo l'indice della linea per la singola linea inviata
              da ogni figlio */
    /* per ogni figlio si devono leggere le informazioni che il figlio con la
     * grep ha scritto sul suo standard output che corrisponde al lato di
     * scrittura della pipe piped[n]; il padre legge, a questo punto, dal lato
     * di lettura di questa pipe */
    while (read(piped[n][0], &(buffer[j]), 1))
    {
      /* dato che arriva una sola linea leggiamo tutti i caratteri dalla pipe */
      j++; /* incrementiamo l'indice della linea */
    }
    /* scriviamo sul file, creato precedentemente, il numero di caratteri
     * corretti e quindi anche con il terminatore di linea! N.B. Il valore di j
     * e' stato incrementato e quindi e' giusto! */
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
