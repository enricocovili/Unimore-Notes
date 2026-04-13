#define _POSIX_SOURCE /* necessario perchè altrimenti non riconosce la kill() */
#define PERM 0644     /* in ottale per diritti UNIX */
#define MSGSIZE 255   /* dimensione massima del buffer di lettura */

#include <stdio.h>     /* printf() */
#include <stdlib.h>    /* NULL, malloc(), free(), exit() */
#include <unistd.h>    /* pipe(), write(), read(), exec??(), lseek(), close() */
#include <fcntl.h>     /* open(), creat() */
#include <sys/wait.h>  /* wait(), WIFEXITED() WEXITSTATUS() */
#include <sys/types.h> /* kill() */
#include <memory.h>    /* memset() */
#include <signal.h>    /* signal(), SIGPIPE, SIGIGN ... */
#include <string.h>    /* strlen() */
#include <ctype.h>     /* isaplha(), isdigit(), islower(), isupper(), tolower(), toupper() */
#include <stdbool.h>   /* bool, true, false */

/* definizione del TIPO pipe_t come array di 2 interi */
typedef int pipe_t[2];

void handler(int signo)
{
    printf("DEBUG-i: Il padre ha ricevuto il segnale %d\n", signo);
}

/*
 * IL PADRE LEGGE UN FILE E I SUOI FIGLI ALTRI N FILE PER VERIFICARNE IL CONTENUTO
 * IL PADRE GESTISCE LA LETTURA TRAMITE SEGNALI (PIPE) DI SINCRONIZZAZIONE AI FIGLI
 */

int main(int argc, char **argv)
{

    int *pid;           /* array dinamico con i pid per fork (mi serviranno alla fine per stampare il file associato) */
    int *stato;         /* array dinamico con gli stati dei figli (0 fermato / 1 running)*/
    int N;              /* conterrà il numero di paramretri passati */
    int i, j;           /* variabili per iteratori dei cicli */
    pipe_t *pipes_comm; /* array dinamica per le N pipes di comunicazione figlio padre */
    pipe_t *pipes_sync; /* array dinamica per le N pipes di sincronizzazione padre figlio */
    int fd;             /* variabile usata dal figlio e dal padre per la open dei file */
    char car, c;        /* carattere corrente letto dal file dal figlio e dal padre */

    /* mi serve anche pidFiglio perchè non posso usare pid perchè sovrascriverebbe un pid utile */
    int pidFiglio, status, ritorno; /* per wait padre */

    /* controllo sul numero di parametri: maggiore o uguale a 3 */
    if (argc - 1 < 3)
    {
        printf("Errore numero di parametri: %s vuole almeno tre parametri e invece argc = %d\n", argv[0], argc);
        exit(1);
    }
    N = argc - 2; /* salvo il numero di N per usarlo nelle iterazioni */

    /* si alloca spazio per N pipes e si controlla se ha successo */
    pipes_comm = (pipe_t *)malloc(N * sizeof(pipe_t));
    pipes_sync = (pipe_t *)malloc(N * sizeof(pipe_t));
    if (pipes_comm == NULL || pipes_sync == NULL)
    {
        printf("Errore nell'allocazione dell'array per contenere le pipe\n");
        exit(2);
    }

    /* alloco lo spazio per contenere i PID dei processi */
    pid = (int *)malloc(N * sizeof(int));
    if (pid == NULL)
    { /* controllo l'allocazione avvenuta dell'array */
        printf("Errore nell'allocazione dell'array per i PID\n");
        exit(3);
    }

    /* alloco lo spazio per contenere lo stato attuale dei processi */
    stato = (int *)malloc(N * sizeof(int));
    if (stato == NULL)
    { /* controllo l'allocazione avvenuta dell'array */
        printf("Errore nell'allocazione dell'array per gli stati dei figli\n");
        exit(4);
    }
    memset(stato, 1, N * sizeof(int)); /* inizializzo tutti i processi in stato running */

    signal(SIGPIPE, handler); /* associo al padre la gestione del segnale SIGPIPE se nel figlio c'è un errore */

    /* si creano le N pipe una per ogni figlio e per ogni nipote */
    for (i = 0; i < N; i++)
    {
        if (pipe(pipes_comm[i]) < 0)
        {
            printf("Errore creazione della pipe figlio padre %d-esima\n", i);
            exit(5);
        } /* controllo sempre che la creazione abbia successo */
        if (pipe(pipes_sync[i]) < 0)
        {
            printf("Errore creazione della pipe padre figlio %d-esima\n", i);
            exit(6);
        }
    }

    for (i = 0; i < N; i++)
    {
        /* si crea il figlio i-esimo (controllando sempre!) */
        if ((pid[i] = fork()) < 0)
        {
            printf("Errore creazione figlio\n");
            exit(7);
        }

        if (pid[i] == 0)
        { /*codice che viene eseguito dal figlio*/
            printf("DEBUG-i: Sono il processo figlio di indice %d e pid %d e leggero' dal file %s\n", i, getpid(), argv[i + 1]);

            /* chiude la pipe comm in lettura perchè i figli scriveranno e quella sync in scrittura (+ le pipe non sue) */
            for (j = 0; j < N; j++)
            {
                close(pipes_comm[j][0]);
                close(pipes_sync[j][1]);
                if (j != i)
                {
                    close(pipes_comm[j][1]);
                    close(pipes_sync[j][0]);
                }
            }

            if ((fd = open(argv[i + 1], O_RDONLY)) < 0)
            { /* provo ad aprire il file che mi spetta */
                printf("Errore nella open del file %s\n", argv[i + 1]);
                exit(-1); /*se non si apre mando -1 al padre così sa che c'è stato un errore*/
            }

            /* attendo sempre la conferma dalla pipe di sync */
            while (read(pipes_sync[i][0], &car, sizeof(char)) > 0)
            {
                if (car == 't')
                    break; /* vuol dire che il padre ha ordinato di terminare gracefully */
                /* se sono qui allora avro ricevuto una 'v' e posso leggere il prossimo carattere dal file*/
                if (read(fd, &car, sizeof(char)) != sizeof(char))
                    exit(-1); /* non dovrebbe capitare perchè il padre gestisce la lettura dei caratteri */

                printf("DEBUG-i: Sono il figlio %d-esimo con PID %d ho letto %c da %s\n", i, getpid(), car, argv[i + 1]);

                if (write(pipes_comm[i][1], &car, sizeof(char)) != sizeof(char))
                { /* scrivo sulla pipe comm al padre il carattere letto */
                    printf("Errore nella scrittura dal figlio %d-esimo sulla pipe comm\n", i);
                    exit(-1);
                }
            }

            exit(0); /* vuol dire che sono terminato regolarmente quindi ritorno UNIX success */
        }
    }

    /* codice del padre */
    /* il padre chiude le pipe comm in scrittura e le sync in lettura */
    for (i = 0; i < N; i++)
    {
        close(pipes_comm[i][1]);
        close(pipes_sync[i][0]);
    }

    /* il padre prova ad aprire il file AF */
    if ((fd = open(argv[N + 1], O_RDONLY)) < 0)
    { /* se non esiste allora esco */
        printf("Il file AF di nome %s non esiste\n", argv[N + 1]);
        exit(8);
    }

    while (read(fd, &c, sizeof(char)) > 0)
    { /* finchè ci sono caratteri nel file AF */
        printf("DEBUG-i: Sono il padre e ho letto il carattere %c dal file %s\n", c, argv[N + 1]);
        for (i = 0; i < N; i++)
        {
            if (stato[i])
            { /* se sono in stato running allora gli mando l'ok */
                car = 'v';
                if (write(pipes_sync[i][1], &car, sizeof(char)) != sizeof(char))
                { /* invio al figlio i-esimo il carattere 'v' */
                    printf("Errore nella scrittura sulla pipe sync %d-esima\n", i);
                    exit(9);
                }
                if (read(pipes_comm[i][0], &car, sizeof(char)) != sizeof(char))
                { /* leggo il carattere che ha letto il figlio */
                    printf("Errore nella lettura sulla pipe comm %d-esima\n", i);
                    exit(10);
                }
                if (car != c)
                { /* i file non sono uguali quindi segnalo che tale figlio non deve più procedere */
                    printf("Il file %s non è uguale al file %s quindi non lo controllerò più\n", argv[N + 1], argv[i + 1]);
                    stato[i] = 0; /* imposto il figlio corrente in stato di fermo */
                }
            }
        }
    }

    /* solo dopo la fine del file vado a fare la kill() dei processi stoppato e termino gli altri gracefully*/
    for (i = 0; i < N; i++)
    {
        if (stato[i])
        {              /* se ha terminato di leggere il file in stato running */
            car = 't'; /* invio al figlio i-esimo sulla pipe sync di terminare */
            if (write(pipes_sync[i][1], &car, sizeof(char)) != sizeof(char))
            {
                printf("Errore nella scrittura sulla pipe sync %d-esima\n", i);
                exit(11);
            }
        }
        else
        {                                    /* è stato interrotto perchè i file non erano uguali */
            if (kill(pid[i], SIGKILL) == -1) /* controllo che anche la kill abbia successo */
                printf("Il processo con PID %d era già terminato\n", pid[i]);
        }
    }

    /* attendo i figli e stampo il valore di ritorno */
    for (i = 0; i < N; i++)
    {
        pidFiglio = wait(&status);
        if (pid < 0)
        { /* controllo che la wait sia andata a buon fine */
            printf("Errore nella wait del figlio P%d\n", i);
            exit(12);
        }
        /* controllo che non sia terminato in modo anomalo */
        /* avrei potuto usare la macro !WIFEXITED(status) per coerenza ma espande in ((status & 0x7f) == 0) che non è quello di cui ho bisogno */
        if ((status & 0xFF) != 0)
            printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
        else
        { /* controllo il valore di ritorno e lo stampo */
            ritorno = (int)WEXITSTATUS(status);
            for (j = 0; j < N; j++) /* con un ciclo vado a trovare l'indice del pidFiglio per trovare il file associato e stamparlo */
                if (pid[j] == pidFiglio)
                {
                    printf("Il figlio con pid=%d associato al file %s ha ritornato %d (se 255 problemi!)\n", pidFiglio, argv[j + 1], ritorno);
                }
        }
    }

    /* ritorno con codice di uscita UNIX success */
    exit(0);
}