#include <stdio.h>     /* printf() */
#include <stdlib.h>    /* NULL, malloc(), free(), exit() */
#include <unistd.h>    /* pipe(), write(), read(), exec(), lseek(), close() */
#include <fcntl.h>     /* open(), creat() */
#include <sys/wait.h>  /* wait(), WIFEXITED() WEXITSTATUS() */
#include <sys/types.h> /* kill() */
#include <memory.h>    /* memset() */
#include <signal.h>    /* signal(), SIGPIPE, SIGIGN ... */
#include <string.h>    /* strlen() */

#define PERM 0644 /* permessi file in ottale */

/* definizione del TIPO pipe_t come array di 2 interi */
typedef int pipe_t[2];
typedef char L[250];

/* handler per la gestione dei segnali del padre */
void handler(int signo)
{
    printf("DEBUG-i: Il padre ha ricevuto il segnale %d\n", signo);
}

int main(int argc, char **argv)
{

    int pid;          /* array dinamico con i pid per fork */
    int N;            /* conterrà il numero di paramretri passati */
    int n, j, k;      /* iteratori per i cicli */
    int ultima_lungh; /* valore di ritorno dei figli */
    pipe_t *pipes;    /* array dinamica per le N+1 pipes di sincronizzazione padre figli */
    int fd;           /* variabile usata dal figlio per open file */
    int fcreato;      /* usata dal padre per creare il file principale */
    L linea;          /* buffer all'interno del figlio per ogni riga */
    L *linee;         /* ARRAY di LINEE da popolare nei figli */

    int status, ritorno; /* per wait padre */

    /* controllo sul numero di parametri: maggiore o uguale a 2 */
    N = argc - 1; /* salvo il numero di parametri N per usarlo nelle iterazioni */
    if (N < 2)
    {
        printf("Errore numero di parametri: %s vuole almeno 2 parametri e invece argc = %d\n", argv[0], argc);
        exit(1);
    }

    if ((fcreato = open("Covili", O_CREAT | O_WRONLY | O_TRUNC, PERM)) < 0)
    {
        printf("errore nella creazione del file \"Covili\"\n");
        exit(2);
    }

    /* si alloca spazio per N+1 pipes (una anche per il padre) */
    pipes = (pipe_t *)malloc((N + 1) * sizeof(pipe_t));
    if (pipes == NULL)
    { /* controllo l'avvenuta allocazione della memoria */
        printf("Errore nell'allocazione dell'array per contenere le pipe\n");
        exit(3);
    }

    signal(SIGPIPE, handler); /* associo al padre la gestione del segnale SIGPIPE se nel figlio c'è un errore */

    /* si creano le N+1 pipe per comporre il ring */
    for (n = 0; n < N; n++)
    {
        if (pipe(pipes[n]) < 0)
        { /* controllo l'avvenuta creazione delle N+1 pipes */
            printf("Errore creazione della pipe padre padre figlio %d-esima\n", n);
            exit(4);
        }
    }

    /* alloco spazio per le linee */
    linee = (L *)malloc((N + 1) * sizeof(L));
    if (linee == NULL)
    {
        printf("errore allocazione linee\n");
        exit(5);
    }

    for (n = 0; n < N; n++)
    {
        /* si crea il figlio n-esimo (controllando sempre!) */
        if ((pid = fork()) < 0)
        {
            printf("Errore creazione figlio\n");
            exit(6);
        }

        if (pid == 0)
        { /* codice che viene eseguito dal figlio */

            /* chiudo le pipe tranne la lettura attuale e la scrittura successiva */
            for (int j = 0; j < N; j++)
            {
                if (j != n)
                    close(pipes[j][0]);
                if (j != (n + 1) % N) /* in modo che l'ultimo tenga aperta la scrittura su pipes[0] */
                    close(pipes[j][1]);
            }

            if ((fd = open(argv[n + 1], O_RDONLY)) < 0)
            { /* provo ad aprire il file */
                printf("Errore nella open del file %s\n", argv[n + 1]);
                exit(-1); /*se non si apre mando -1 al figlio così sa che c'è stato un errore*/
            }

            j = 0;
            while (read(fd, &linea[j], sizeof(char)) != 0)
            { /* finchè ci sono caratteri leggo dal file */
                if (linea[j] == '\n')
                {
                    j++; /* IMPORTANTE: anche il terminatore di linea nella lunghezza */
                    ultima_lungh = j;
                    if (read(pipes[n][0], linee, N * sizeof(L)) != N * sizeof(L))
                    {
                        printf("errore lettura pipe nel figlio %d\n", n);
                        exit(-1);
                    }
                    for (k = 0; k < j; k++)
                    {
                        linee[n][k] = linea[k];
                    }
                    if (write(pipes[(n + 1) % N][1], linee, N * sizeof(L)) != N * sizeof(L))
                    {
                        printf("errore scrittura pipe nel figlio %d\n", n);
                        exit(-1);
                    }
                    if (n == N - 1)
                    {
                        /* ULTIMO FIGLIO: devo scrivere su fcreato */
                        for (j = 0; j < N; j++)
                        {
                            for (k = 0; k < sizeof(L); k++)
                            {
                                if (write(fcreato, &linee[j][k], 1) != 1)
                                {
                                    printf("errore nella write di fcreato\n");
                                    exit(-1);
                                }

                                if (linee[j][k] == '\n')
                                {
                                    /* fine linea */
                                    break;
                                }
                            }
                        }
                    }
                    /* inserisco ultima riga letta */
                    j = 0;
                }
                else
                {
                    j++;
                }
            }
            exit(ultima_lungh);
        }
    }

    /* codice del padre */

    /* il padre chiude le pipe sync in scrittura tranne la prima e tutte il lettura */
    for (n = 0; n < N + 1; n++)
    {
        close(pipes[n][0]);
        if (n != 0)
            close(pipes[n][1]);
    }

    /* il padre deve inviare lo START al primo figlio */
    if (write(pipes[0][1], linee, N * sizeof(L)) != N * sizeof(L))
    {
        printf("errore scrittura pipe nel primo figlio\n");
        exit(6);
    }

    close(pipes[0][1]);

    /* attendo i figli e stampo il valore di ritorno */
    for (n = 0; n < N; n++)
    {
        pid = wait(&status);
        if (pid < 0)
        { /* controllo che la wait sia andata a buon fine */
            printf("Errore nella wait del figlio P%d\n", n);
            exit(7);
        }
        /* controllo che non sia terminato in modo anomalo */
        if ((status & 0xFF) != 0)
            printf("Figlio con pid %d terminato in modo anomalo\n", pid);
        else if ((ritorno = (int)WEXITSTATUS(status)) == 255) /* controllo il valore di ritorno e lo stampo */
            printf("C'è stato un errore nel figlio %d che ha ritornato %d\n", pid, ritorno);
        else
            printf("Il figlio con pid=%d ha ritornato %d (se 255 problemi!)\n", pid, ritorno);
    }

    /* ritorno con codice di uscita UNIX success */
    exit(0);
}