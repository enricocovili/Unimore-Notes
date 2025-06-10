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

    int pid;          /* pid per fork */
    int N;            /* conterrà il numero di paramretri passati */
    int n, j;         /* iteratori per i cicli */
    int outfile;      /* file descriptor del file creato nel padre */
    char buffer[250]; /* variabile di lettura delle linee ricevute dal padre */
    pipe_t *pipes;    /* array dinamica per le N pipes */
    pipe_t p;         /* pipe utilizzata tra nipote e figlio */

    int status, ritorno; /* per le wait */

    /* controllo sul numero di parametri: esattamente uguale a 2 */
    if (argc - 1 != 2)
    {
        printf("Errore numero di parametri: %s vuole esattamente due parametri e invece argc = %d\n", argv[0], argc);
        exit(1);
    }

    if ((N = atoi(argv[1])) <= 0)
    {
        printf("Errore: il parametro %s deve essere un numero intero strettamente positivo\n", argv[1]);
        exit(2);
    }

    if ((outfile = creat(argv[2], PERM)) < 0)
    {
        printf("Errore: il padre non è riuscito a creare il file %s\n", argv[2]);
        exit(3);
    }

    /* si alloca spazio per N pipes */
    pipes = (pipe_t *)malloc(N * sizeof(pipe_t));
    if (pipes == NULL)
    { /* controllo l'avvenuta allocazione */
        printf("Errore nell'allocazione dell'array per contenere le pipe\n");
        exit(4);
    }

    /* si creano le N pipe una per ogni figlio */
    for (n = 0; n < N; n++)
    {
        if (pipe(pipes[n]) < 0)
        { /* controllo che la pipe sia stata creata */
            printf("Errore creazione della pipe %d-esima\n", n);
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
            printf("DEBUG-i: Sono il processo figlio di indice %d e pid %d e sto per creare il nipote\n", n, getpid());
            /* chiude la pipe in lettura perchè i figli scriveranno e quelle che non sono sue */
            for (j = 0; j < N; j++)
            {
                close(pipes[j][0]);
                if (j != n)
                    close(pipes[j][1]);
            }

            /* provo a creare la pipe tra figlio-nipote e se non riesce torno -1 al padre*/
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
                printf("DEBUG-i: Sono il processo nipote del figlio di indice %d e pid %d\n", n, getpid());
                /* chiudo la pipe figlio-padre che non uso (le altre sono già state chiuse dal figlio) */
                close(pipes[n][1]);

                close(1);  /* chiudo lo stdout perchè lo ridireziono per piping alla pipe in scrittura */
                dup(p[1]); /* uso p[1] per lo stdout */

                close(p[0]); /* chiudo la lettura tra figlio-nipote */
                close(p[1]); /* ora la posso chiudere */

                execlp("ps", "ps", (char *)0); /* eseguo il comando e mando su stdout */

                perror("Errore: c'è stato un errore imprevisto nel nipote nell'esecuzione del comando ps\n");
                exit(-1); /* c'è stato un errore imprevisto qua non dovrebbe arrivare mai */
            }

            /* codice del figlio */
            /* chiudo lo stdin perchè faccio la redirezione dalla pipe p che è il risultato di ps */
            close(0);
            dup(p[0]);

            /* chiudo lo stdout perchè lo redireziono sulla pipe con il padre il risultato di grep */
            close(1);
            dup(pipes[n][1]);

            /* chiudo lo stderr redirezionandolo a /dev/null */
            close(2);
            open("/dev/null", O_WRONLY);

            /* chiudo la pipe figlio-nipote */
            close(p[1]);
            close(p[0]);
            /* chiudo la pipe figlio-padre in scrittura */
            close(pipes[n][1]);

            /* converto il pid in una stringa per poterlo utilizzare nel grep */
            sprintf(buffer, "%d", pid);
            execlp("grep", "grep", buffer, (char *)0);

            perror("Errore: c'è stato un errore imprevisto nel figlio nell'esecuzione del comando grep\n");
            exit(-1); /* c'è stato un errore imprevisto qua non dovrebbe arrivare mai */
        }
    }

    /* codice del padre */
    /* il padre chiude le pipe in scrittura */
    for (n = 0; n < N; n++)
    {
        close(pipes[n][1]);
    }

    /* il padre legge da ogni pipe il conteggio trasmesso in ordine */
    for (n = 0; n < N; n++)
    {
        j = 0;
        while (read(pipes[n][0], &(buffer[j++]), sizeof(char)) > 0)
            ;
        /* scrivo sul file l'output del comando grep */
        if (write(outfile, buffer, j) != j)
        {
            printf("Errore: il padre non ha letto correttamente la linea inviata dal figlio %d\n", n);
            /* scelgo di non fare la exit perchè voglio comunque che il padre aspetti i figli */
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
        /* verifico l'interruzione in modo anomalo */
        /* avrei potuto usare la macro !WIFEXITED(status) per coerenza ma espande in ((status & 0x7f) == 0) che non è quello di cui ho bisogno */
        if ((status & 0xFF) != 0)
            printf("Figlio con pid %d terminato in modo anomalo\n", pid);
        else if ((ritorno = (int)WEXITSTATUS(status)) == 255) /* controllo il valore di ritorno e lo stampo */
            printf("Errore nel grep del processo figlio %d\n", pid);
        else
            printf("Il figlio con pid=%d ha ritornato %d\n", pid, ritorno);
    }

    /* esco con codice UNIX success */
    exit(0);
}