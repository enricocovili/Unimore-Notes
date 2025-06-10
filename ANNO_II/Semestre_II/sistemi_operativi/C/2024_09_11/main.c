#include <stdio.h>    /* printf() */
#include <stdlib.h>   /* NULL, malloc(), free(), exit() */
#include <unistd.h>   /* pipe(), write(), read(), exec??(), lseek(), close() */
#include <fcntl.h>    /* open(), creat() */
#include <sys/wait.h> /* wait(), WIFEXITED() WEXITSTATUS() */
#include <ctype.h>    /* isaplha(), isdigit(), islower(), isupper(), tolower(), toupper() */
#include <string.h>

#define PERM 0644 /* permessi file linux */

/* definizione del TIPO pipe_t come array di 2 interi */
typedef int pipe_t[2];

int main(int argc, char **argv)
{

    int pid;         /* pid per fork */
    int N;           /* conterrà il numero di paramretri passati */
    pipe_t *pipes;   /* array dinamica per le N pipes figlio padre */
    pipe_t p;        /* pipe utilizzata tra nipote e figlio */
    int n, j;        /* iteratori utilizzati nei cicli */
    int outfile;     /* variabile usata dal padre per il file sotto /tmp */
    char linea[250]; /* usata dal padre per leggere le linee inviate dai figli */

    int status, ritorno; /* per wait padre */

    /* controllo sul numero di parametri: maggiore o uguale a 3 */
    if (argc - 1 < 3)
    {
        printf("Errore numero di parametri: %s vuole almeno due parametri e invece argc = %d\n", argv[0], argc);
        exit(1);
    }

    N = argc - 2; /* salvo il numero di file per usarlo nelle iterazioni */
    /* creo file come da testo */
    if ((outfile = open("/tmp/RISULTATO", O_WRONLY | O_CREAT | O_APPEND, PERM)) < 0)
    {
        printf("errore nella creazione/apertura del file temporaneo\n");
        exit(2);
    }
    write(outfile, argv[1], strlen(argv[1]));
    write(outfile, "\n", 1);

    /* si alloca spazio per N pipes */
    pipes = (pipe_t *)malloc(N * sizeof(pipe_t));
    if (pipes == NULL)
    { /* controllo l'avvenuta locazione della memoria */
        printf("Errore nell'allocazione dell'array per contenere le pipe\n");
        exit(2);
    }

    /*si creano le N pipe una per ogni figlio-nipote */
    for (n = 0; n < N; n++)
    {
        if (pipe(pipes[n]) < 0)
        { /* verifico anche la corretta creazione della pipe padre-figlio */
            printf("Errore creazione della pipe %d-esima\n", n);
            exit(3);
        }
    }

    for (n = 0; n < N; n++)
    {
        /* si crea il figlio i-esimo (controllando sempre!) */
        if ((pid = fork()) < 0)
        {
            printf("Errore creazione figlio\n");
            exit(4);
        }

        if (pid == 0)
        { /* codice che viene eseguito dal figlio */
            // printf("DEBUG-i: Sono il figlio di indice %d e pid %d e sto per creare il nipote per il file %s\n", n, getpid(), argv[n + 1]);
            /* chiude la pipe in lettura perchè i figli scriveranno (e quelle non sue) */
            for (j = 0; j < N; j++)
            {
                close(pipes[j][0]);
                if (j != n)
                    close(pipes[j][1]);
            }

            /* provo a creare la pipe tra figlio-nipote e se non riesce torno -1 al padre */
            if (pipe(p) < 0)
            {
                printf("Errore creazione della pipe tra figlio %d e il suo nipote\n", n);
                exit(-1);
            }

            /* provo a creare il nipote e se non riesce ritorno al padre -1*/
            if ((pid = fork()) < 0)
            {
                printf("Errore creazione nipote\n");
                exit(-1);
            }

            if (pid == 0)
            { /* codice del nipote */
                // printf("DEBUG-i: Sono il nipote di indice %d e pid %d per il file %s\n", n, getpid(), argv[n + 1]);
                /* chiudo la pipe figlio-padre che non uso (le altre sono già state chiuse dal figlio) */
                close(pipes[n][1]);

                close(1);  /* chiudo lo stdout perchè lo ridireziono per piping alla pipe in scrittura */
                dup(p[1]); /* uso p[1] per lo stdout */

                close(p[0]); /* chiudo la lettura tra figlio-nipote */
                close(p[1]); /* ora la posso chiudere */

                execlp("ls", "ls", "-li", (char *)0); /* eseguo il comando ls con le specifiche indicate */

                /* usiamo perror che scrive su standard error, dato che lo standard output e' collegato alla pipe */
                perror("Problemi di esecuzione di ls da parte del nipote");
                exit(-1); /* c'è stato un errore imprevisto qua non dovrebbe arrivare mai */
            }

            /* codice del figlio */
            /* ogni figlio deve simulare il piping dei comandi nei confronti del
             * nipote e poi nei confronti del padre: */
            /* quindi prima deve chiudere lo standard input e quindi usare la dup sul
             * lato di lettura della pipe p */
            close(0);
            dup(p[0]);
            /* quindi dopo deve chiudere lo standard output e quindi usare la dup sul
             * lato di scrittura della pipe piped[n] */
            close(1);
            dup(pipes[n][1]);

            /* ogni figlio adesso puo' chiudere entrambi i lati della pipe p e la
             * scrittura di piped[n] */
            close(p[0]);
            close(p[1]);
            close(pipes[n][1]);

            execlp("grep", "grep", argv[n + 2], (char *)0); /* esecuzione grep sull'input di ls */

            /* usiamo perror che scrive su standard error, dato che lo standard output e' collegato alla pipe */
            perror("Problemi di esecuzione di grep da parte del figlio");
            exit(-1); /* c'è stato un errore imprevisto qua non dovrebbe arrivare mai */
        }
    }

    /* codice del padre */
    /* il padre chiude le pipe in scrittura */
    for (n = 0; n < N; n++)
    {
        close(pipes[n][1]);
    }

    for (n = 0; n < N; n++)
    {
        j = 0;
        while (read(pipes[n][0], &linea[j], 1) == 1)
        {
            if (linea[j] == '\n')
            {
                if (write(outfile, linea, j + 1) != j + 1)
                {
                    printf("errore nella write del file temporaneo.\n");
                    exit(6);
                }
                j = 0;
            }
            else
            {
                j++;
            }
        }
    }

    /*attendo i figli e stampo il valore di ritorno*/
    for (n = 0; n < N; n++)
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
            printf("Errore nel processo figlio %d: file %s non esistente\n", pid, argv[n + 2]);
        else
            printf("Il figlio con pid=%d ha ritornato %d (se 255 problemi!)\n", pid, ritorno);
    }

    /* esco con codice UNIX success */
    exit(0);
}