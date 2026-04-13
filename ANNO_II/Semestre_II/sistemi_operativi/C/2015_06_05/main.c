#include <stdio.h>    /* printf() */
#include <stdlib.h>   /* NULL, malloc(), free(), exit() */
#include <unistd.h>   /* pipe(), write(), read(), exec??(), lseek(), close() */
#include <fcntl.h>    /* open(), creat() */
#include <sys/wait.h> /* wait(), WIFEXITED() WEXITSTATUS() */
#include <ctype.h>    /* isaplha(), isdigit(), islower(), isupper(), tolower(), toupper() */

/* definizione del TIPO pipe_t come array di 2 interi */
typedef int pipe_t[2];

int main(int argc, char **argv)
{

    int pid;         /* pid per fork */
    int N;           /* conterrà il numero di paramretri passati */
    int i, j;        /* iteratori per i cicli */
    pipe_t *pipes;   /* array dinamica per le N pipes */
    pipe_t p;        /* pipe utilizzata tra nipote e figlio */
    char linea[250]; /* usata dal figlio per leggere output nipote */
    int lunghezza;   /* dal padre per ricevere le lunghezze delle ultime righe */

    int status, ritorno; /* per le wait */

    /* controllo sul numero di parametri: maggiore o uguale a 2 */
    if (argc - 1 < 2)
    {
        printf("Errore numero di parametri: %s vuole almeno tre due e invece argc = %d\n", argv[0], argc);
        exit(1);
    }
    N = argc - 1; /* memorizzo il numero di file per usarlo nelle iterazioni */

    /* si alloca spazio per N pipes */
    pipes = (pipe_t *)malloc(N * sizeof(pipe_t));
    if (pipes == NULL)
    { /* controllo l'avvenuta allocazione */
        printf("Errore nell'allocazione dell'array per contenere le pipe\n");
        exit(2);
    }

    /* si creano le N pipe una per ogni figlio */
    for (i = 0; i < N; i++)
    {
        if (pipe(pipes[i]) < 0)
        { /* controllo che la pipe sia stata creata */
            printf("Errore creazione della pipe %d-esima\n", i);
            exit(3);
        }
    }

    for (i = 0; i < N; i++)
    {
        /* si crea il figlio n-esimo (controllando sempre!) */
        if ((pid = fork()) < 0)
        {
            printf("Errore creazione figlio\n");
            exit(4);
        }

        if (pid == 0)
        { /* codice che viene eseguito dal figlio */
            printf("DEBUG-i: Sono il processo figlio di indice %d e pid %d e sto per creare il nipote\n", i, getpid());
            /* chiude la pipe in lettura perchè i figli scriveranno e quelle che non sono sue */
            for (j = 0; j < N; j++)
            {
                close(pipes[j][0]);
                if (j != i)
                    close(pipes[j][1]);
            }

            /* provo a creare la pipe tra figlio-nipote e se non riesce torno -1 al padre*/
            if (pipe(p) < 0)
            {
                printf("Errore creazione della pipe tra figlio %d e il suo nipote\n", i);
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
                printf("DEBUG-i: Sono il processo nipote del figlio di indice %d e pid %d\n", i, getpid());
                /* chiudo la pipe figlio-padre che non uso (le altre sono già state chiuse dal figlio) */
                close(pipes[i][1]);

                close(1);  /* chiudo lo stdout perchè lo ridireziono per piping alla pipe in scrittura */
                dup(p[1]); /* uso p[1] per lo stdout */

                close(p[0]); /* chiudo la lettura tra figlio-nipote */
                close(p[1]); /* ora la posso chiudere */

                close(2);
                open("/dev/null", O_WRONLY); /* chiudo stderr per evitare errori a schermo */

                execlp("tail", "tail", "-1", argv[i + 1], (char *)0); /* eseguo il comando e mando su stdout */

                exit(-1); /* c'è stato un errore imprevisto qua non dovrebbe arrivare mai */
            }

            /* codice del figlio */
            /* chiudo la pipe in scrittura figlio-nipote */
            close(p[1]);

            j = 0;
            while (read(p[0], &linea[j], sizeof(char)) == 1)
            {
                j++;
            }

            /* mando lunghezza al padre */
            if (write(pipes[i][1], &j, sizeof(j)) != sizeof(j))
            {
                printf("ERRORE in scrittura pipe nel figlio %d\n", i);
                exit(-1);
            }

            /* attendo che il processo nipote sia terminato per correttezza */
            if ((pid = wait(&status)) < 0)
            {
                printf("Errore durante la wait del nipote con pid %d\n", pid);
                exit(-1);
            }
            /* verifico l'interruzione in modo anomalo */
            /* avrei potuto usare la macro !WIFEXITED(status) per coerenza ma espande in ((status & 0x7f) == 0) che non è quello di cui ho bisogno */
            if ((status & 0xFF) != 0)
            {
                printf("Processo nipote %d terminato in modo anomalo\n", pid);
                exit(-1);
            }
            else if ((ritorno = (int)WEXITSTATUS(status)) == 255)
            { /* verifico il codice di ritorno */
                printf("C'è stato un errore nel processo %d che ha ritornato %d\n", pid, ritorno);
                exit(-1);
            }

            exit(ritorno); /* ritorno al padre il codice di ritorno del nipote */
        }
    }

    /* codice del padre */
    /* il padre chiude le pipe in scrittura */
    for (i = 0; i < N; i++)
    {
        close(pipes[i][1]);
    }

    /* il padre legge da ogni pipe il conteggio trasmesso in ordine */
    for (i = N - 1; i >= 0; i--)
    {
        if (read(pipes[i][0], &lunghezza, sizeof(lunghezza)) != sizeof(lunghezza))
        {
            printf("ERRORE nella lettura pipe nel padre\n");
            exit(7);
        }
        printf("Ultima riga del file %s (figlio n %d): %d\n", argv[i + 1], i, lunghezza);
    }

    /* attendo i figli e stampo il valore di ritorno */
    for (i = N - 1; i >= 0; i--)
    {
        pid = wait(&status);
        if (pid < 0)
        { /* controllo che la wait sia andata a buon fine */
            printf("Errore nella wait del figlio P%d\n", i);
            exit(5);
        }
        /* verifico l'interruzione in modo anomalo */
        /* avrei potuto usare la macro !WIFEXITED(status) per coerenza ma espande in ((status & 0x7f) == 0) che non è quello di cui ho bisogno */
        if ((status & 0xFF) != 0)
            printf("Figlio con pid %d terminato in modo anomalo\n", pid);
        else if ((ritorno = (int)WEXITSTATUS(status)) == 255) /* controllo il valore di ritorno e lo stampo */
            printf("Errore nel processo figlio %d: file %s non esistente\n", pid, argv[i + 1]);
        else
            printf("Il figlio con pid=%d ha ritornato %d (se 255 problemi!)\n", pid, ritorno);
    }

    /* esco con codice UNIX success */
    exit(0);
}