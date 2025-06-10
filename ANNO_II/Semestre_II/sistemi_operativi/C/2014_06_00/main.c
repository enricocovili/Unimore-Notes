/* Soluzione della Prova d'esame del 9 Giugno 2014 - Parte C */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

/* definizione del TIPO pipe_t come array di 2 interi */
typedef int pipe_t[2];

int main(int argc, char **argv) {
  /* -------- Variabili locali ---------- */
  int pid; /* process identifier per le fork() */
  int N;   /* numero di file passati sulla riga di comando (uguale al numero di
              figli) */
  pipe_t *piped;   /* array dinamico di pipe per comunicazioni figli-padre  */
  pipe_t p;        /* una sola pipe per ogni coppia figlio-nipote */
  int i, j;        /* indici per i cicli */
  char numero[11]; /* array di caratteri per memorizzare la stringa
                      corrispondente al numero di righe: ci vogliono 10 char per
                      rappresentare un intero di 16 bit e poi ci sara' il
                      carattere '\n' (trasformato poi in terminatore di
                      stringa!) */
  int valore;  /* variabile che viene comunicata da ogni figlio al padre e che
                  contiene la conversione della stringa in numero */
  int ritorno; /* variabile che viene ritornata da ogni figlio al padre e che
                  contiene il ritorno del nipote */
  long int somma = 0; /* variabile usata dal padre per calcolare la somma di
                         tutte le lunghezze comunicate dai figli */
  int status;         /* variabile di stato per la wait */
                      /* ------------------------------------ */

  /* controllo sul numero di parametri: almeno due nomi di file */
  if (argc < 3) {
    printf("Errore: Necessari almeno 2 parametri per %s e invece argc = %d\n",
           argv[0], argc);
    exit(1);
  }

  /* calcoliamo il numero di file passati e quindi di figli da creare */
  N = argc - 1;

  /* allocazione dell'array di N pipe */
  piped = (pipe_t *)malloc(N * sizeof(pipe_t));
  if (piped == NULL) {
    printf("Errore nella allocazione della memoria\n");
    exit(2);
  }

  /* creazione delle N pipe figli-padre */
  for (i = 0; i < N; i++) {
    if (pipe(piped[i]) < 0) {
      printf("Errore nella creazione della pipe di indice i = %d\n", i);
      exit(3);
    }
  }

  printf(
      "DEBUG-Sono il processo padre con pid %d e sto per generare %d figli\n",
      getpid(), N);

  /* ciclo di generazione dei figli */
  for (i = 0; i < N; i++) {
    if ((pid = fork()) < 0) {
      printf("Errore creazione figlio %d-esimo\n", i);
      exit(4);
    }

    if (pid == 0) {
      /* codice del figlio Pi */
      printf(
          "DEBUG-Sono il processo figlio di indice %d e pid %d sto per creare "
          "il nipote che calcolera' il numero di linee del file %s\n",
          i, getpid(), argv[i + 1]);
      /* in caso di errore nel figlio o nel nipote, decidiamo di tornare -1 che
       * verra' interpretato dal padre come 255 e quindi un valore non
       * ammissibile! */

      /* chiusura delle pipe non usate nella comunicazione con il padre */
      for (j = 0; j < N; j++) {
        /* ogni figlio NON legge da nessuna pipe e scrive solo sulla sua che e'
         * la i-esima! */
        close(piped[j][0]);
        if (i != j) close(piped[j][1]);
      }

      /* per prima cosa, creiamo la pipe di comunicazione fra nipote e figlio */
      if (pipe(p) < 0) {
        printf(
            "Errore nella creazione della pipe fra figlio e nipote per "
            "l'indice %d!\n",
            i);
        exit(-1); /* si veda commento precedente */
      }

      /* ogni figlio crea un nipote */
      if ((pid = fork()) < 0) {
        printf("Errore nella fork di creazione del nipote per l'indice %d!\n",
               i);
        exit(-1); /* si veda commento precedente */
      }

      if (pid == 0) {
        /* codice del nipote */
        printf(
            "DEBUG-Sono il processo nipote del figlio di indice %d e pid %d "
            "sto per calcolare il numero di linee del file %s\n",
            i, getpid(), argv[i + 1]);
        /* in caso di errore nel figlio o nel nipote, decidiamo di tornare -1
         * che verra' interpretato dal padre come 255 e quindi un valore non
         * ammissibile! */

        /* N.B. chiusura della pipe rimasta aperta di comunicazione fra
         * figlio-padre che il nipote non usa */
        close(piped[i][1]);

        /* ridirezione dello standard input: il file si trova usando l'indice i
         * incrementato di 1 (cioe' per il primo processo i=0 il file e'
         * argv[1])i; NOTA BENE: IN QUESTO CASO LA RIDIREZIONE ERA OBBLIGATORIA
         * (anche se il testo parlava di comando) PER AVERE SULLO STANDARD
         * OUTPUT SOLO IL NUMERO (e non anche il nome del file!) */
        close(0);
        if (open(argv[i + 1], O_RDONLY) < 0) {
          printf("Errore nella open del file %s\n", argv[i + 1]);
          exit(-1); /* si veda commento precedente */
        }

        /* ogni nipote deve simulare il piping dei comandi nei confronti del
         * figlio e quindi deve chiudere lo standard output e quindi usare la
         * dup sul lato di scrittura della propria pipe */
        close(1);
        dup(p[1]);
        /* ogni nipote adesso puo' chiudere entrambi i lati della pipe: il lato
         * 0 non viene usato e il lato 1 viene usato tramite lo standard output
         */
        close(p[0]);
        close(p[1]);

        /* ridirezione dello standard error su /dev/null (per evitare messaggi
         * di errore a video): facoltativo! */
        close(2);
        open("/dev/null", O_WRONLY);

        /* il nipote diventa il comando wc -l */
        execlp("wc", "wc", "-l", (char *)0);
        /* attenzione ai parametri nella esecuzione di wc: solo -l e terminatore
         * della lista */

        /* NON si dovrebbe mai tornare qui!!*/
        exit(-1); /* si veda commento precedente */
      }

      /* codice figlio */
      /* ogni figlio deve chiudere il lato che non usa della pipe di
       * comunicazione con il nipote */
      close(p[1]);

      /* adesso il figlio legge dalla pipe un carattere alla volta, fino a che
       * ci sono caratteri inviati dal nipote tramite il comando-filtro wc */
      j = 0; /* inizializziamo l'indice del buffer numero */
      while (read(p[0], &(numero[j]), 1)) {
        j++; /* incrementiamo l'indice */
      }

      /* all'uscita di questo ciclo while, nell'array numero ci saranno tutti i
       * caratteri numerici corrispondenti al numero di linee del file e come
       * ultimo carattere il terminatore di linea */
      /* trasformiamo l'array di char in stringa sostituendo allo '\n' il
       * terminatore di stringa, controllando pero' di avere letto in effetti
       * qualcosa */
      if (j != 0) /* se il figlio ha letto qualcosa */
      {
        numero[j - 1] = '\0';
        /* convertiamo la stringa nel numero che bisogna comunicare al padre */
        valore = atoi(numero);
      } else { /* questo e' il caso che il nipote sia incorso in un errore e che
                  quindi non abbia eseguito il wc -l */
        valore = 0; /* se il figlio non ha letto nulla, inviamo 0 */
      }

      /* il figlio comunica al padre */
      write(piped[i][1], &valore, sizeof(valore));

      /* il figlio deve aspettare il nipote per restituire il valore al padre */
      /* se il nipote e' terminato in modo anomalo decidiamo di tornare -1 e
       * verra' interpretato come 255 e quindi segnalando questo problema al
       * padre */
      ritorno = -1;
      if ((pid = wait(&status)) < 0) printf("Errore in wait\n");
      if ((status & 0xFF) != 0)
        printf("Nipote con pid %d terminato in modo anomalo\n", pid);
      else
        /* stampa non richiesta: SOLO DEBUGGING */
        printf("DEBUG-Il nipote con pid=%d ha ritornato %d\n", pid,
               ritorno = (int)((status >> 8) & 0xFF));
      exit(ritorno);
    }
  }

  /* Codice del padre */
  /* Il padre chiude i lati delle pipe che non usa */
  for (i = 0; i < N; i++) close(piped[i][1]);

  /* Il padre recupera le informazioni dai figli in ordine di indice */
  for (i = 0; i < N; i++) {
    /* il padre recupera tutti i valori interi dai figli */
    read(piped[i][0], &valore, sizeof(valore));
    /* stampa non richiesta, ma che male non fa */
    printf(
        "DEBUG-Il figlio di indice %d ha comunicato il valore %d per il file "
        "%s\n",
        i, valore, argv[i + 1]);
    somma = somma + (long int)valore;
  }
  printf(
      "La somma risultante derivante dai valori comunicati dai figli e' %ld\n",
      somma);

  /* Il padre aspetta i figli */
  for (i = 0; i < N; i++) {
    if ((pid = wait(&status)) < 0) {
      printf("Errore in wait\n");
      exit(5);
    }

    if ((status & 0xFF) != 0)
      printf("Figlio con pid %d terminato in modo anomalo\n", pid);
    else {
      ritorno = (int)((status >> 8) & 0xFF);
      if (ritorno == 255)
        printf(
            "Il figlio con pid=%d ha ritornato %d e quindi vuole dire che il "
            "figlio ha avuto dei problemi oppure il nipote non è riuscito ad "
            "eseguire il wc oppure è terminato in modo anormale\n",
            pid, ritorno);
      else
        printf("Il figlio con pid=%d ha ritornato %d\n", pid, ritorno);
    }
  }

  exit(0);
}