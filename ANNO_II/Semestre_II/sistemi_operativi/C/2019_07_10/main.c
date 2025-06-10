#include <stdio.h>    /* printf() */
#include <stdlib.h>   /* NULL, malloc(), free(), exit() */
#include <unistd.h>   /* pipe(), write(), read(), exec??(), lseek(), close() */
#include <fcntl.h>    /* open(), creat() */
#include <sys/wait.h> /* wait(), WIFEXITED() WEXITSTATUS() */
#include <string.h>
#include <ctype.h> /* isaplha(), isdigit(), islower(), isupper(), tolower(), toupper() */

#define PERM 0644

/* definizione del TIPO pipe_t come array di 2 interi */
typedef int pipe_t[2];

int main(int argc, char **argv)
{

    int pid;         /* pid per fork */
    int N;           /* conterrà il numero di paramretri passati */
    int n, j;        /* iteratori per i cicli */
    char Cz;         /* carattere da cercare */
    char buffer;     /* usato nei figli nella ricerca di Cz */
    int occorrenze;  /* numero da ritornare al padre da parte dei figli */
    int indice_file; /* in modo che ogni coppia capisca il file coordinato */
    long int pos;    /* posizione corrente nel file */
    int fd;          /* descrittore per il file letto */
    pipe_t *pipes;   /* array dinamica per le N pipes */

    int status, ritorno; /* per le wait */

    /* controllo sul numero di parametri: maggiore o uguale a 3 */
    if (argc - 1 < 3)
    {
        printf("Errore numero di parametri: %s vuole almeno un parametro e invece argc = %d\n", argv[0], argc);
        exit(1);
    }

    if (strlen(argv[argc - 1]) == 1)
    {
        Cz = argv[argc - 1][0];
    }
    else
    {
        printf("errore. ultimo parametro non carattere singolo\n");
        exit(2);
    }

    N = argc - 2; /* memorizzo il numero di file per usarlo nelle iterazioni */
    /* si alloca spazio per N pipes */
    pipes = (pipe_t *)malloc(2 * N * sizeof(pipe_t));
    if (pipes == NULL)
    { /* controllo l'avvenuta allocazione */
        printf("Errore nell'allocazione dell'array per contenere le pipe\n");
        exit(2);
    }

    /* si creano le N pipe una per ogni figlio */
    for (n = 0; n < N; n++)
    {
        if (pipe(pipes[n]) < 0)
        { /* controllo che la pipe sia stata creata */
            printf("Errore creazione della pipe %d-esima\n", n);
            exit(3);
        }
    }

    for (n = 0; n < 2 * N; n++)
    {
        /* si crea il figlio n-esimo (controllando sempre!) */
        if ((pid = fork()) < 0)
        {
            printf("Errore creazione figlio\n");
            exit(4);
        }

        if (pid == 0)
        { /* codice che viene eseguito dal figlio */
            /* provo ad aprire il file corrispondente che mi serve sia nel figlio n che 2n */
            for (j = 0; j < 2 * N; j++)
            {
                if (j != 2 * N - n - 1)
                    close(pipes[j][1]);
                if (j != n)
                    close(pipes[j][0]);
            }
            if (n < N)
            {
                indice_file = n;
            }
            else
            {
                indice_file = 2 * N - n - 1;
            }

            if ((fd = open(argv[indice_file], O_RDONLY)) < 0)
            {
                printf("Errore nell'apertura del file %s\n", argv[indice_file]);
                exit(-1);
            }

            if (n >= N) /* prima iterazione, secondi nella coppia. devono aspettare a partire */
            {
                // printf("sono il figlio %d (pid: %d) e aspetto il primo testimone\n", n, getpid());
                read(pipes[n][0], &pos, sizeof(pos));
                lseek(fd, pos + 1, SEEK_SET);
                // printf("sono il figlio %d (pid: %d) e ho ricevuto il primo testimone\n", n, getpid());
            }

            while (read(fd, &buffer, sizeof(char)) == 1)
            {
                if (buffer == Cz)
                {
                    /* passiamo il testimone */
                    /* il valore ricavato dalla lseek lo decrementiamo di 1 dato che dopo la lettura l'I/O pointer
                    e' posizionato sul carattere seguente quello letto */
                    pos = lseek(fd, 0L, SEEK_CUR) - 1L;
                    // printf("figlio %d ha letto il char %c nella posizione %ld\n", n, Cz, pos);
                    write(pipes[2 * N - n - 1][1], &pos, sizeof(pos)); /* scrivo nuova posizione sulla pipe */
                    // printf("figlio %d scrivo su pipe %d\n", n, 2 * N - n - 1);
                    occorrenze++;
                    /* aspetto nuovamente il testimone */
                    if (read(pipes[n][0], &pos, sizeof(pos)) != sizeof(pos))
                    {
                        break; /* raggiunta fine della lettura */
                    }
                    lseek(fd, pos + 1L, SEEK_SET); /* posizioni IO pointer nella posizione letta */
                }
            }

            exit(occorrenze); /* ritorno al padre la lunghezza massima delle linee */
        }
    }

    /* codice del padre */
    /* il padre chiude tutte le pipe perchè non entra nella comunicazione */
    for (n = 0; n < N; n++)
    {
        close(pipes[n][1]);
        close(pipes[n][0]);
    }

    /* attendo i figli e stampo il valore di ritorno */
    for (n = 0; n < 2 * N; n++)
    {
        pid = wait(&status);
        if (pid < 0)
        { /* controllo che la wait sia andata a buon fine */
            printf("Errore nella wait del figlio P%d\n", n);
            exit(5);
        }
        /* verifico l'interruzione in modo anomalo */
        /* avrei potuto usare la macro !WIFEXITED(status) per coerenza ma espande in ((status & 0x7f) == 0) che non è quello di cui ho bisogno */
        if ((status & 0xFF) != 0)
            printf("Figlio con pid %d terminato in modo anomalo\n", pid);
        else if ((ritorno = (int)WEXITSTATUS(status)) == 255) /* controllo il valore di ritorno e lo stampo */
            printf("Errore nel processo figlio %d: file %s non esistente\n", pid, argv[(n % N) + 1]);
        else
            printf("Il figlio con pid=%d ha letto %d occorrenze di %c\n", pid, ritorno, Cz);
    }

    /* esco con codice UNIX success */
    exit(0);
}