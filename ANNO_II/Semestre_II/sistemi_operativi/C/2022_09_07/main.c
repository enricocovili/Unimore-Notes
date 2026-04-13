#include <stdio.h>     /* printf() */
#include <stdlib.h>    /* NULL, malloc(), free(), exit() */
#include <unistd.h>    /* pipe(), write(), read(), exec??(), lseek(), close() */
#include <fcntl.h>     /* open(), creat() */
#include <sys/wait.h>  /* wait(), WIFEXITED() WEXITSTATUS() */
#include <sys/types.h> /* kill() */
#include <memory.h>    /* memset() */
#include <signal.h>    /* signal(), SIGPIPE, SIGIGN ... */
#include <string.h>    /* strlen() */

#define PERM 0644 /* permessi file in ottale */
/* definizione del TIPO pipe_t come array di 2 interi */
typedef int pipe_t[2];

int main(int argc, char **argv)
{

    int pid;             /* array dinamico con i pid per fork */
    int N;               /* conterrà il numero di paramretri passati */
    int n, j;            /* iteratori per i cicli */
    pipe_t *pipes;       /* array dinamica per le N pipes di sincronizzazione padre figli */
    int fd, fcreato;     /* variabile usata dal figlio per open file e dal padre nel file "Covili" */
    char car;            /* carattere corrente letto dal file dal padre e dal figlio */
    char *cur;           /* array passato figlio per figlio fino al padre */
    int status, ritorno; /* per wait padre */

    /* controllo sul numero di parametri: maggiore o uguale a 2 */
    if (argc - 1 < 2)
    {
        printf("Errore numero di parametri: %s vuole almeno due parametri e invece argc = %d\n", argv[0], argc);
        exit(1);
    }
    N = argc - 1; /* salvo il numero di parametri N per usarlo nelle iterazioni */

    /* creazione file */
    if ((fcreato = open("Covili", O_WRONLY | O_CREAT | O_TRUNC, PERM)) < 0)
    {
        printf("Errore creazione del file \"Covili\"\n");
        exit(2);
    }

    /* allocazione array di caratteri */
    cur = (char *)malloc(N * sizeof(char));
    if (cur == NULL)
    {
        printf("errore allocazione array CUR\n");
        exit(3);
    }

    /* si alloca spazio per N pipes (una anche per il padre) */
    pipes = (pipe_t *)malloc((N) * sizeof(pipe_t));
    if (pipes == NULL)
    { /* controllo l'avvenuta allocazione della memoria */
        printf("Errore nell'allocazione dell'array per contenere le pipe\n");
        exit(4);
    }

    /* si creano le N+1 pipe per comporre il ring */
    for (n = 0; n < N + 1; n++)
    {
        if (pipe(pipes[n]) < 0)
        { /* controllo l'avvenuta creazione delle N+1 pipes */
            printf("Errore creazione della pipe padre padre figlio %d-esima\n", n);
            exit(5);
        }
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
            for (j = 0; j < N + 1; j++)
            {
                if (j != n)
                    close(pipes[j][1]);
                if (j > 0 && j != n - 1)
                    close(pipes[j][0]);
            }

            if ((fd = open(argv[n + 1], O_RDONLY)) < 0)
            { /* provo ad aprire il file */
                printf("Errore nella open del file %s\n", argv[1]);
                exit(-1); /*se non si apre mando -1 al figlio così sa che c'è stato un errore*/
            }

            while (read(fd, &car, sizeof(char)) == sizeof(char))
            {
                /* caso dispari */
                if (n != 0) /* la lettura è effettuata solo dal secondo in poi */
                {
                    if (read(pipes[n - 1][0], cur, N * sizeof(char)) != N * sizeof(char))
                    {
                        printf("Errore in lettura pipe nel figlio %d\n", n);
                        exit(-1);
                    }
                }
                cur[n] = car; /* inserisco il carattere corrente */
                if (write(pipes[n][1], cur, N * sizeof(char)) != N * sizeof(char))
                {
                    printf("Errore in scrittura pipe nel figlio %d\n", n);
                    exit(-1);
                }
            }

            // printf("ultimo car di %d. %c. %d\n", n, car, j);
            exit(car); /* vuol dire che sono terminato regolarmente quindi ritorno l'ultimo carattere */
            /* per specifica sarà dispari, senza controlli */
        }
    }

    /* codice del padre */

    /* chiusura pipe non usate */
    for (n = 0; n < N; n++)
    {
        close(pipes[n][1]);
        if (n != N - 1)
            close(pipes[n][0]);
    }

    while (read(pipes[N - 1][0], cur, N * sizeof(char)) == N * sizeof(char))
    {
        if (write(fcreato, cur, N * sizeof(char)) != N * sizeof(char))
        {
            printf("Errore in scrittura su file nel padre\n");
            exit(-1);
        }
    }

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
            printf("C'è stato un errore nel processo nipote %d che ha ritornato %d\n", pid, ritorno);
        else
            printf("Il figlio con pid=%d ha ritornato: %d (se 255 problemi!)\n", pid, ritorno);
    }

    /* ritorno con codice di uscita UNIX success */
    exit(0);
}