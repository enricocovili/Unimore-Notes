/*
La  parte  in  C  accetta  un  numero  variabile  N  di  parametri  maggiore  o
uguale  a  2  (da  controllare)  che rappresentano  nomi  assoluti  di  file F1,
...,  FN.  Il  processo  padre  deve  generare  N  processi  figli:  ogni
processo figlio Pn è associato ad uno dei file F1, ..., FN.  Ognuno di tali
figli deve creare a sua volta un processo nipote PPn: ogni processo nipote PPn è
associato allo stesso file del figlio che lo ha creato ed esegue
concorrentemente; il compito dei processi nipote PPn  è quello di ‘rovesciare’
il contenuto del file associato al figlio usando in modo opportuno il comando
rev di UNIX/Linux. Ogni processo figlio Pn deve ricevere tutte le linee inviate
dal suo processo nipote PPn e, solo al termine della ricezione di tutte le
linee, deve inviare al processo padre una struttura dati che deve contenere tre
campi: 1) c1, di tipo int, che deve contenere il PID del nipote PPn; 2) c2, di
tipo char[250]*, che deve contenere l’ULTIMA linea ricevuta dal nipote; 3) c3,
di tipo int, che deve contenere la lunghezza della linea compreso il terminatore
di linea. Il padre deve ricevere, rispettando l'ordine dei file, le singole
strutture inviate dai figli e deve stampare su standard output, per ogni
struttura ricevuta, ognuno dei campi (chiaramente con indicazione di cosa
rappresentano)  insieme  al  nome  del  file  cui  le  informazioni  si
riferiscono:  si  faccia  attenzione  che  è demandato al padre il compito di
trasformare in una stringa quanto ricevuto nel campo c2 di ogni struttura,
mantenendo però il fatto che sia una linea! Al termine, ogni processo figlio Pn
deve ritornare al padre la lunghezza della linea inviata al padre, ma non
compreso il terminatore di linea e il padre deve stampare su standard output il
PID di ogni figlio e il valore ritornato
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define PERM 0644 /* in ottale per diritti UNIX */

typedef struct {
  int c1;        // pid nipote
  char c2[250];  // ultima linea ricevuta dal nipote
  int c3;        // lunghezza di c2 compreso terminatore
} Struct;

typedef int pipe_t[2];

int main(int argc, char **argv) {
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
  Struct S; /* struttura inviata dai figli e ricevuta mano a mano dal padre */
  int n, j; /* indici per i cicli */
  /* n nome indicato nel testo */
  char buffer[250]; /* array di caratteri usato sia dal figlio per la sprintf e
                       sia dal padre per ricevere dai figli */
  /* nome indicato dal testo */
  int nr;      /* variabile per valore di ritorno della read */
  int ritorno; /* variabile che viene ritornata da ogni figlio al padre */
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

  /* numero figli e conseguentemente nipoti */
  N = argc - 1;

  /* Allocazione dell'array di N pipe descriptors */
  piped = (pipe_t *)malloc(N * sizeof(pipe_t));
  if (piped == NULL) {
    printf("Errore nella allocazione della memoria\n");
    exit(4);
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
      /* ogni figlio scrive solo su piped[n] */
      for (j = 0; j < N; j++) {
        close(piped[j][0]);
        if (n != j) close(piped[j][1]);
      }

      /* prima creiamo la pipe di comunicazione fra figlio e nipote */
      if (pipe(p) < 0) {
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
      if (pid == 0) {
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

        /* Il nipote diventa il comando rev: bisogna usare le versioni dell'exec
         * con la p in fondo in modo da usare la variabile di ambiente PATH  */
        execlp("rev", "rev", argv[n + 1], (char *)0);

        /* Non si dovrebbe mai tornare qui!!*/
        /* usiamo perror che scrive su standard error, dato che lo standard
         * output e' collegato alla pipe */
        perror("Problemi di esecuzione del ps da parte del nipote");
        exit(-1); /* si veda commento precedente */
      }
      /* codice figlio */
      // chiudo pipe nipote figlio inutilizzata
      close(p[1]);

      // leggo sequenzialmente le righe dal rev
      j = 0;
      S.c1 = pid;

      while (read(p[0], &(buffer[j]), 1)) {
        if (buffer[j] == '\n') {
          S.c3 = j + 1;  // + 1 per il terminatore
          j = 0;
        } else {
          j++;
        }
      }

      // ora abbiamo solo l'ultima linea in buffer. la copio nella struct
      for (j = 0; j < S.c3; j++) {
        S.c2[j] = buffer[j];
      }

      // comunico al padre
      write(piped[n][1], &S, sizeof(S));

      pid = wait(&status);  // figlio aspetta nipote
      if (pid < 0) {
        printf("Errore in wait\n");
        exit(-1); /* si veda commento precedente */
      }
      if ((status & 0xFF) != 0) {
        printf("Nipote con pid %d terminato in modo anomalo\n", pid);
        exit(-1); /* si veda commento precedente */
        /* ATTENZIONE VA FATTA L'EXIT ANCHE IN QUESTO CASO, MENTRE NEL PADRE NON
         * SI FA PERCHE' DEVE ASPETTARE TUTTI I FIGLI */
      } else
        /* printf("DEBUG-Il nipote con pid=%d ha ritornato %d\n", pid,
         * (int)((status >> 8) & 0xFF)); */
        /* il figlio ritorna la lunghezza della linea inviata NON compreso il
         * terminatore */
        ritorno = S.c3 - 1; /* se il file NON esiste il nipote non avrà mandato
                               nulla e quindi S.lung_linea sara' uguale a zero e
                               quindi togliendo 1 si ottiene di tornare al padre
                               un -1 che viene interpretato come un errore */
      /* in alternativa si poteva controllare il valore di ritorno del nipote
       * che se diverso 0 vuol dire che c'e' stato un errore */
      exit(ritorno);
    }
  }

  /* Codice del padre */
  /* Il padre chiude i lati delle pipe che non usa */
  for (n = 0; n < N; n++) close(piped[n][1]);
  /* si legge la struttura inviata  dal figlio i-esimo */
  for (n = 0; n < N; n++) {
    nr = read(piped[n][0], &S, sizeof(S));
    if (nr != 0) {
      /* Nota bene: la stampa della linea con il formato %s richiede che il
       * padre inserisca il terminatore di stringa nel posto giusto, cioe' dopo
       * il terminatore di linea dato che il testo specificava "mantenendo pero'
       * il fatto che sia una linea!" */
      S.c2[S.c3] = '\0'; /* dato che lung_linea rappresenta la lunghezza della
                            linea, compreso il terminatore, per avere l'indice
                            giusto lo usiamo direttamente */
      printf(
          "Il nipote con pid %d ha letto dal file %s questa linea '%s' che ha "
          "lunghezza (compreso il terminatore) di %d caratteri:\n",
          S.c1, argv[n + 1], S.c2, S.c3);
    }
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
      printf("ritorno figlio pid %d: %d\n", pid, ritorno);
    }
  }
  exit(0);
}
