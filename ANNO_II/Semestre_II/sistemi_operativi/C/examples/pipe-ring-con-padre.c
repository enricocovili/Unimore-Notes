#include <stdio.h>     /* printf() */
#include <stdlib.h>    /* NULL, malloc(), free(), exit() */
#include <unistd.h>    /* pipe(), write(), read(), exec??(), lseek(), close() */
#include <fcntl.h>     /* open(), creat() */
#include <sys/wait.h>  /* wait(), WIFEXITED() WEXITSTATUS() */
#include <sys/types.h> /* kill() */
#include <memory.h>    /* memset() */
#include <signal.h>    /* signal(), SIGPIPE, SIGIGN ... */
#include <string.h>    /* strlen() */

/* definizione del TIPO pipe_t come array di 2 interi */
typedef int pipe_t[2];

/* handler per la gestione dei segnali del padre */
void handler(int signo)
{
    printf("DEBUG-i: Il padre ha ricevuto il segnale %d\n", signo);
}

int main(int argc, char **argv)
{

    int pid;            /* array dinamico con i pid per fork */
    int L;              /* numero di righe del file F */
    long int tot;       /* contatore del numero di occorrenze */
    int Q;              /* conterrà il numero di paramretri passati */
    int q, j;           /* iteratori per i cicli */
    pipe_t *pipes_sync; /* array dinamica per le N+1 pipes di sincronizzazione padre figli */
    int fd;             /* variabile usata dal figlio per open file */
    char car;           /* carattere corrente letto dal file dal padre e dal figlio */

    int status, ritorno; /* per wait padre */

    /* controllo sul numero di parametri: maggiore o uguale a 4 */
    if (argc - 1 < 4)
    {
        printf("Errore numero di parametri: %s vuole almeno quattro parametri e invece argc = %d\n", argv[0], argc);
        exit(1);
    }
    Q = argc - 3; /* salvo il numero di parametri Q per usarlo nelle iterazioni */

    /* controllo il secondo parametro passato */
    if ((L = atoi(argv[2])) < 0)
    { /* verifico che sia un numero e sia > 0 */
        printf("Il secondo parametro deve essere un numero strettamente positivo e invece è %s\n", argv[2]);
        exit(2);
    }

    for (q = 0; q < Q; q++)
    { /* itero sui successivi Q caratteri */
        if (strlen(argv[q + 3]) != 1)
        { /* calcolo la lunghezza per vedere se è un carattere solo */
            printf("Il parametro indice %d deve essere un carattere e invece è %s\n", q + 2, argv[q + 3]);
            exit(3);
        }
    }

    /* si alloca spazio per Q+1 pipes (una anche per il padre) */
    pipes_sync = (pipe_t *)malloc((Q + 1) * sizeof(pipe_t));
    if (pipes_sync == NULL)
    { /* controllo l'avvenuta allocazione della memoria */
        printf("Errore nell'allocazione dell'array per contenere le pipe\n");
        exit(4);
    }

    signal(SIGPIPE, handler); /* associo al padre la gestione del segnale SIGPIPE se nel figlio c'è un errore */

    /* si creano le Q+1 pipe per comporre il ring */
    for (q = 0; q < Q + 1; q++)
    {
        if (pipe(pipes_sync[q]) < 0)
        { /* controllo l'avvenuta creazione delle Q+1 pipes */
            printf("Errore creazione della pipe padre padre figlio %d-esima\n", q);
            exit(5);
        }
    }

    for (q = 0; q < Q; q++)
    {
        /* si crea il figlio n-esimo (controllando sempre!) */
        if ((pid = fork()) < 0)
        {
            printf("Errore creazione figlio\n");
            exit(6);
        }

        if (pid == 0)
        { /* codice che viene eseguito dal figlio */
            printf("DEBUG-i: Sono il processo figlio di indice %d e pid %d e sono associato al carattere %c\n", q, getpid(), argv[q + 3][0]);

            /* chiudo le pipe tranne la lettura attuale e la scrittura successiva */
            for (int j = 0; j < Q + 1; j++)
            {
                if (j != q)
                    close(pipes_sync[j][0]);
                if (j != (q + 1))
                    close(pipes_sync[j][1]);
            }

            if ((fd = open(argv[1], O_RDONLY)) < 0)
            { /* provo ad aprire il file */
                printf("Errore nella open del file %s\n", argv[1]);
                exit(-1); /*se non si apre mando -1 al figlio così sa che c'è stato un errore*/
            }

            tot = 0; /* inizializzazione a 0 della variabile che conta le occorrenze */
            while (read(fd, &car, sizeof(char)) != sizeof(char))
            { /* finchè ci sono caratteri leggo dal file */
                if (car == '\n')
                {
                    /* ogni volta che finisce la linea aspetto la conferma per stampare dal precedente elemento del ring */
                    if (read(pipes_sync[q][0], &car, sizeof(char)) != sizeof(char))
                    {
                        printf("Errore nella lettura dalla pipe di sync %d-esima\n", q);
                        exit(-1);
                    }
                    printf("Il figlio con indice %d e pid %d ha trovato %ld occorrenze di %c\n", q, getpid(), tot, argv[q + 3][0]);
                    /* ora mando l'ok (non importa che carattere mando) alla pipe successiva nel ring */
                    if (write(pipes_sync[q + 1][1], &car, sizeof(char)) != sizeof(char))
                    {
                        printf("Errore nella scrittura sulla pipe di sync %d-esima\n", q + 1);
                        exit(-1);
                    }
                    tot = 0; /* resetto il contatore delle occorrenza sulla linea */
                }
                else if (car == argv[q + 3][0])
                    tot++; /* controllo che il carattere faccia match e incremento il contatore */
            }

            exit(tot); /* vuol dire che sono terminato regolarmente quindi ritorno l'ultimo conteggio linea */
        }
    }

    /* codice del padre */

    /* il padre chiude le pipe sync in scrittura tranne la prima e in lettura tranne la Q+1 esima */
    for (q = 0; q < Q + 1; q++)
    {
        if (q != Q)
            close(pipes_sync[q][0]);
        if (q != 0)
            close(pipes_sync[q][1]);
    }

    /* itero per il numero di linee del file */
    for (q = 0; q < L; q++)
    {
        printf("Linea %d del file %s\n", q + 1, argv[1]); /* per ogni linea stampo l'intestazione */
        /* scrivo sulla pipe di sincronizzazione per far partire il primo elemento */
        if (write(pipes_sync[0][1], &car, sizeof(char)) != sizeof(char))
        {
            printf("Errore nella scrittura della pipe sync di indice %d\n", 0);
        }
        /* attendo che l'ultimo figlio scriva sulla pipe di sincronia per segnalare che è finito l'anello */
        if (read(pipes_sync[Q][0], &car, sizeof(char)) != sizeof(char))
        {
            printf("Errore nella lettura della pipe sync di indice %d\n", Q);
        }
    }

    /* attendo i figli e stampo il valore di ritorno */
    for (q = 0; q < Q; q++)
    {
        pid = wait(&status);
        if (pid < 0)
        { /* controllo che la wait sia andata a buon fine */
            printf("Errore nella wait del figlio P%d\n", q);
            exit(7);
        }
        /* controllo che non sia terminato in modo anomalo */
        if ((status & 0xFF) != 0)
            printf("Figlio con pid %d terminato in modo anomalo\n", pid);
        else if ((ritorno = (int)WEXITSTATUS(status)) == 255) /* controllo il valore di ritorno e lo stampo */
            printf("C'è stato un errore nel processo nipote %d che ha ritornato %d\n", pid, ritorno);
        else
            printf("Il figlio con pid=%d ha ritornato %d (se 255 problemi!)\n", pid, ritorno);
    }

    /* ritorno con codice di uscita UNIX success */
    exit(0);
}