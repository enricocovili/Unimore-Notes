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

    int pid;          /* pid per fork */
    int N;            /* conterrà il numero di paramretri passati */
    int i, j;         /* iteratori per i cicli */
    pipe_t *pipes_fp; /* array dinamica per le N pipes figlio padre */
    pipe_t *pipes_np; /* array dinamica per le N pipes nipote padre */
    int fd;           /* variabile usata dal figlio per open file */
    long int tot;     /* contatore totale di caratteri che fanno match */
    char car;         /* carattere corrente letto dal file*/

    int status, ritorno; /* per wait padre */

    /* controllo sul numero di parametri: maggiore o uguale a 2 */
    if (argc - 1 < 2)
    {
        printf("Errore numero di parametri: %s vuole almeno due parametri e invece argc = %d\n", argv[0], argc);
        exit(1);
    }
    N = argc - 1; /* salvo il numero di N per usarlo nelle iterazioni */

    /* si alloca spazio per N pipes */
    pipes_fp = (pipe_t *)malloc(N * sizeof(pipe_t));
    pipes_np = (pipe_t *)malloc(N * sizeof(pipe_t));
    if (pipes_fp == NULL || pipes_np == NULL)
    { /* controllo sempre l'avvenuta allocazione */
        printf("Errore nell'allocazione dell'array per contenere le pipe\n");
        exit(2);
    }

    /* si creano le N pipe una per ogni figlio e per ogni nipote */
    for (i = 0; i < N; i++)
    {
        if (pipe(pipes_fp[i]) < 0)
        {
            printf("Errore creazione della pipe figlio padre %d-esima\n", i);
            exit(3);
        } /* anche qui controllo l'avvenuta creazione di entrambe le pipe */
        if (pipe(pipes_np[i]) < 0)
        {
            printf("Errore creazione della pipe nipote padre %d-esima\n", i);
            exit(4);
        }
    }

    for (i = 0; i < N; i++)
    {
        /* si crea il figlio i-esimo (controllando sempre!) */
        if ((pid = fork()) < 0)
        {
            printf("Errore creazione figlio\n");
            exit(5);
        }

        if (pid == 0)
        { /*codice che viene eseguito dal figlio*/
            printf("DEBUG-i: Sono il processo figlio di indice %d e pid %d sto per creare il nipote che leggera' sempre dal mio stesso file %s\n", i, getpid(), argv[i + 1]);

            /*chiude le pipe figlio-padre in lettura perchè i figli scriveranno (e quelle non sue in scrittura) */
            for (j = 0; j < N; j++)
            {
                close(pipes_fp[j][0]);
                if (j != i)
                    close(pipes_fp[j][1]);
            }

            /* provo a creare il nipote e se non riesce ritorno al figlio -1*/
            if ((pid = fork()) < 0)
            {
                printf("Errore creazione nipote\n");
                exit(-1);
            }

            if (pid == 0)
            { /*codice del nipote*/
                printf("DEBUG-i: Sono il processo nipote del figlio di indice %d e pid %d\n", i, getpid());
                /*chiudo la pipe figlio-padre in scrittura che non uso (le altre sono già state chiuse dal figlio)*/
                close(pipes_fp[i][1]);

                /* chiudo le pipe nipote-padre in lettura che non uso e quelle in scrittura tranne la propria */
                for (j = 0; j < N; j++)
                {
                    close(pipes_np[j][0]);
                    if (i != j)
                        close(pipes_np[j][1]);
                }

                if ((fd = open(argv[i + 1], O_RDWR)) < 0)
                { /* provo ad aprire il file che mi spetta in lettura+scrittura */
                    printf("Errore nella open del file %s\n", argv[i + 1]);
                    exit(-1); /*se non si apre mando -1 al figlio così sa che c'è stato un errore */
                }

                tot = 0; /* inizializzo a 0 il contatore dei caratteri */
                /* finchè ci sono caratteri da leggere nel file li conto e li sostituisco */
                while (read(fd, &car, sizeof(char)) > 0)
                {
                    if (car <= 'z' && car >= 'a')
                    {                            /* controllo che sia un carattere minuscolo */
                        tot++;                   /* incremento il contatore di caratteri trovati */
                        lseek(fd, -1, SEEK_CUR); /* ritorno con il cursore indietro di una posizione */
                        car = toupper(car);      /* converto in maiuscolo il carattere e lo scrivo */

                        if (write(fd, &car, sizeof(char)) != sizeof(char))
                            printf("Errore nel rimpiazzare ul carattere sul file %s\n", argv[i + 1]);
                    }
                }

                /* scrivo il long int con il conteggio sulla pipe al padre */
                if (write(pipes_np[i][1], &tot, sizeof(tot)) != sizeof(tot))
                    printf("Errore nella scrittura sulla pipe nipote-padre %d-esima\n", i);

                /* ritorno il numero di byte occupati dal conteggio */
                exit(tot / 256);
            }

            /* codice del figlio */
            /* chiudo le pipe nipote-padre (solo dopo aver creato i nipoti) */
            for (j = 0; j < N; j++)
            {
                close(pipes_np[j][0]);
                close(pipes_np[j][1]);
            }

            if ((fd = open(argv[i + 1], O_RDWR)) < 0)
            { /* provo ad aprire il file che mi spetta in lettura+scrittura */
                printf("Errore nella open del file %s\n", argv[i + 1]);
                exit(-1); /* se non si apre mando -1 al figlio così sa che c'è stato un errore */
            }

            tot = 0; /* inizializzo il contatore dei caratteri a 0 */
            /* finchè ci sono caratteri da leggere nel file li conto e li sostituisco */
            while (read(fd, &car, sizeof(char)) > 0)
            {
                if (isdigit(car))
                {                            /* se il carattere è numerico*/
                    tot++;                   /* incremento il contatore di caratteri trovati */
                    lseek(fd, -1, SEEK_CUR); /* ritorno con il cursore indietro di una posizione */
                    car = ' ';               /* scrivo lo spazio al posto del numero */
                    if (write(fd, &car, sizeof(char)) != sizeof(char))
                        printf("Errore nel rimpiazzare ul carattere sul file %s\n", argv[i + 1]);
                }
            }

            /* scrivo sull'unica pipe aperta il numero di linee */
            if (write(pipes_fp[i][1], &tot, sizeof(tot)) != sizeof(tot))
                printf("Errore nella scrittura sulla pipe figlio-padre %d-esima\n", i);

            /* attendo che il processo nipote sia terminato */
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
            else if ((ritorno = (int)WEXITSTATUS(status)) == 255) /* verifico il codice di ritorno */
                printf("C'è stato un errore nel processo nipote %d che ha ritornato %d\n", pid, ritorno);
            else
                printf("Il nipote %d-esimo con pid %d ha ritornato: %d\n", i, pid, ritorno);

            exit(tot / 256); /*ritorno al padre il codice legato al conteggio del FIGLIO */
        }
    }

    /* codice del padre */
    /* il padre chiude le pipe in scrittura con il nipote e con il figlio */
    for (i = 0; i < N; i++)
    {
        close(pipes_fp[i][1]);
        close(pipes_np[i][1]);
    }

    /* il padre legge da ogni pipe il conteggio trasmesso in ordine*/
    for (i = 0; i < N; i++)
    {
        if (read(pipes_fp[i][0], &tot, sizeof(tot)) != sizeof(tot)) /* leggo dalla pipe figlio-padre */
            printf("Errore nella lettura dal padre della pipe figlio-padre %d-esima\n", i);
        else
            printf("Il conteggio dei caratteri numerici per il file %s è %ld\n", argv[i + 1], tot);
        if (read(pipes_np[i][0], &tot, sizeof(tot)) != sizeof(tot)) /* leggo dalla pipe nipote-padre */
            printf("Errore nella lettura dal padre della pipe nipote-padre %d-esima\n", i);
        else
            printf("Il conteggio dei caratteri alfabetici minuscoli per il file %s è %ld\n", argv[i + 1], tot);
    }

    /* attendo i figli e stampo il valore di ritorno */
    for (i = 0; i < N; i++)
    {
        pid = wait(&status);
        if (pid < 0)
        { /* controllo che la wait sia andata a buon fine */
            printf("Errore nella wait del figlio P%d\n", i);
            exit(6);
        }
        /* controllo che non sia terminato in modo anomalo */
        /* avrei potuto usare la macro !WIFEXITED(status) per coerenza ma espande in ((status & 0x7f) == 0) che non è quello di cui ho bisogno */
        if ((status & 0xFF) != 0)
            printf("Figlio con pid %d terminato in modo anomalo\n", pid);
        else if ((ritorno = (int)WEXITSTATUS(status)) == 255) /* controllo il valore di ritorno e lo stampo */
            printf("Errore nel processo figlio %d: file %s non esistente\n", pid, argv[i + 1]);
        else
            printf("Il figlio con pid=%d ha ritornato %d (se 255 problemi!)\n", pid, ritorno);
    }

    /* ritorno con codice di uscita UNIX success */
    exit(0);
}