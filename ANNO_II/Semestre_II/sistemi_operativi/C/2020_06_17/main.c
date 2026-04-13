#include <stdio.h>    /* printf() */
#include <stdlib.h>   /* NULL, malloc(), free(), exit() */
#include <unistd.h>   /* pipe(), write(), read(), exec??(), lseek(), close() */
#include <fcntl.h>    /* open(), creat() */
#include <sys/wait.h> /* wait(), WIFEXITED() WEXITSTATUS() */
#include <ctype.h>    /* isaplha(), isdigit(), islower(), isupper(), tolower(), toupper() */

#define PERM 0644

/* definizione del TIPO pipe_t come array di 2 interi */
typedef int pipe_t[2];

int main(int argc, char **argv)
{

    int pid;            /* pid per fork */
    int B;              /* conterrà il numero di figli */
    int L;              /* Strettamente positivo, multiplo di B, dimensione in caratteri del file */
    int q, j;           /* iteratori per i cicli */
    int fd;             /* descrittore per il file letto dai figli */
    char car;           /* usato come variabile per salvare caratteri inviati dai figli */
    pipe_t *pipes;      /* array dinamica per le N pipes */
    char filename[250]; /* nome del nuovo file */
    int outfile;        /* scrittura file */
    char buff[250];     /* array per memorizzare la linea (compreso \n e \0) */

    int status, ritorno; /* per le wait */

    /* controllo sul numero di parametri: esattamente o uguale a 3 */
    if (argc - 1 != 3)
    {
        printf("Errore numero di parametri: %s vuole tre parametri e invece argc = %d\n", argv[0], argc);
        exit(1);
    }

    B = atoi(argv[2]);
    L = atoi(argv[3]);

    if (B < 0 || L < 0 || L % B != 0)
    {
        printf("Errore. B o L negativi oppure L non multiplo di B.\n");
        exit(2);
    }

    sprintf(filename, "%s.Chiara", argv[1]);
    if ((outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, PERM)) < 0)
    { /* creo il file temporaneo e controllo la creazione */
        printf("Errore nella creazione del file di output Camilla\n");
        exit(2);
    }

    /* si alloca spazio per N pipes */
    pipes = (pipe_t *)malloc(B * sizeof(pipe_t));
    if (pipes == NULL)
    { /* controllo l'avvenuta allocazione */
        printf("Errore nell'allocazione dell'array per contenere le pipe\n");
        exit(3);
    }

    /* si creano le N pipe una per ogni figlio */
    for (q = 0; q < B; q++)
    {
        if (pipe(pipes[q]) < 0)
        { /* controllo che la pipe sia stata creata */
            printf("Errore creazione della pipe %d-esima\n", q);
            exit(4);
        }
    }

    for (q = 0; q < B; q++)
    {
        /* si crea il figlio n-esimo (controllando sempre!) */
        if ((pid = fork()) < 0)
        {
            printf("Errore creazione figlio\n");
            exit(5);
        }

        if (pid == 0)
        { /* codice che viene eseguito dal figlio */

            for (j = 0; j < B; j++)
            {
                close(pipes[j][0]); /* non leggo nulla */
                if (j != q)
                    close(pipes[j][1]); /* tengo aperto solo il mio lato in scrittura */
            }

            if ((fd = open(argv[1], O_RDONLY)) < 0)
            {
                printf("Errore nell'apertura del file %s\n", argv[q + 1]);
                exit(-1);
            }

            lseek(fd, q * (L / B), SEEK_SET); /* mi sposto nella posizione corretta */
            j = read(fd, buff, L / B);
            if (j != L / B) /* leggo con una sola read */
            {
                printf("Errore lettura file figlio n.%d\n", q);
            }

            write(pipes[q][1], &buff[j - 1], sizeof(char));

            exit(j); /* dimensione buffer */
        }
    }

    /* codice del padre */
    /* il padre chiude le pipe in scrittura */
    for (q = 0; q < B; q++)
        close(pipes[q][1]);

    /* il padre legge da ogni pipe */
    for (q = 0; q < B; q++)
    {
        if (read(pipes[q][0], &car, sizeof(char)) == sizeof(char))
        {
            write(outfile, &car, sizeof(char));
        }
    }

    /* attendo i figli e stampo il valore di ritorno */
    for (q = 0; q < B; q++)
    {
        pid = wait(&status);
        if (pid < 0)
        { /* controllo che la wait sia andata a buon fine */
            printf("Errore nella wait del figlio P%d\n", q);
            exit(5);
        }
        /* verifico l'interruzione in modo anomalo */
        /* avrei potuto usare la macro !WIFEXITED(status) per coerenza ma espande in ((status & 0x7f) == 0) che non è quello di cui ho bisogno */
        if ((status & 0xFF) != 0)
            printf("Figlio con pid %d terminato in modo anomalo\n", pid);
        else if ((ritorno = (int)WEXITSTATUS(status)) == 255) /* controllo il valore di ritorno e lo stampo */
            printf("Errore nel processo figlio %d: file %s non esistente\n", pid, argv[q + 1]);
        else
            printf("Il figlio con pid=%d, q=%d ha ritornato %d \n", pid, q, ritorno);
    }

    /* esco con codice UNIX success */
    exit(0);
}