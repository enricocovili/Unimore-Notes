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

    int pid;         /* pid per fork */
    int Q;           /* conterrà il numero di paramretri passati */
    int q, j;        /* iteratori per i cicli */
    int fd;          /* descrittore per il file letto dai figli */
    pipe_t *pipes;   /* array dinamica per le N pipes */
    char linea[250]; /* array per memorizzare la linea (compreso \n e \0) */

    int status, ritorno; /* per le wait */

    /* controllo sul numero di parametri: maggiore o uguale a 2 */
    if (argc - 1 < 2)
    {
        printf("Errore numero di parametri: %s vuole almeno due parametri e invece argc = %d\n", argv[0], argc);
        exit(1);
    }
    Q = argc - 1; /* memorizzo il numero di file per usarlo nelle iterazioni */

    if ((fd = creat("Camilla", PERM)) < 0)
    { /* creo il file temporaneo e controllo la creazione */
        printf("Errore nella creazione del file di output Camilla\n");
        exit(2);
    }

    /* si alloca spazio per N pipes */
    pipes = (pipe_t *)malloc(Q * sizeof(pipe_t));
    if (pipes == NULL)
    { /* controllo l'avvenuta allocazione */
        printf("Errore nell'allocazione dell'array per contenere le pipe\n");
        exit(3);
    }

    /* si creano le N pipe una per ogni figlio */
    for (q = 0; q < Q; q++)
    {
        if (pipe(pipes[q]) < 0)
        { /* controllo che la pipe sia stata creata */
            printf("Errore creazione della pipe %d-esima\n", q);
            exit(4);
        }
    }

    for (q = 0; q < Q; q++)
    {
        /* si crea il figlio n-esimo (controllando sempre!) */
        if ((pid = fork()) < 0)
        {
            printf("Errore creazione figlio\n");
            exit(5);
        }

        if (pid == 0)
        { /* codice che viene eseguito dal figlio */
            printf("DEBUG-i: Sono il processo figlio di indice %d e pid %d associato al file %s\n", q, getpid(), argv[q + 1]);
            /* chiude la pipe in lettura perchè i figli scriveranno e quelle che non sono sue */
            for (j = 0; j < Q; j++)
            {
                close(pipes[j][0]);
                if (j != q)
                    close(pipes[j][1]);
            }

            if ((fd = open(argv[q + 1], O_RDONLY)) < 0)
            {
                printf("Errore nell'apertura del file %s\n", argv[q + 1]);
                exit(-1);
            }

            j = 0;       /* inizializzo a 0 j che uso come cursore per la scrittura */
            ritorno = 0; /* inizializzo il contatore delle linea totali inviate al padre */
            while (read(fd, &(linea[j]), sizeof(char)) > 0)
            { /* provo a leggere dal file un carattere */
                if (linea[j] == '\n')
                { /* è terminata la riga */
                    if (isdigit(linea[0]) && (j + 1) < 10)
                    { /* allora se supera i requisiti viene inviata al padre */
                        if (write(pipes[q][1], linea, j + 1) != j + 1)
                        { /* controllo sempre se è stata inviata correttamente */
                            printf("Errore nella scrittura sulla pipe %d-esima\n", j);
                            exit(-1);
                        }
                        ritorno++;
                    }
                    j = 0;
                }
                else
                    j++;
            }

            exit(ritorno); /* ritorno al padre il numero di linee inviate */
        }
    }

    /* codice del padre */
    /* il padre chiude le pipe in scrittura */
    for (q = 0; q < Q; q++)
        close(pipes[q][1]);

    /* il padre legge da ogni pipe il conteggio trasmesso in ordine */
    for (q = 0; q < Q; q++)
    {
        j = 0;
        while (read(pipes[q][0], &(linea[j]), sizeof(char)) > 0)
        {
            if (linea[j] == '\n')
            {
                linea[j + 1] = '\0'; /* inserisco il terminatore di stringa */
                printf("Il file %s è stato letto dal processo figlio di indice %d e ha ritornato la linea: %s\n", argv[q + 1], q, linea);
                if (write(fd, linea, j + 1) != j + 1)
                { /* scrivo sul file di output la linea letta */
                    printf("Errore nella scrittura di %s sul file Camilla\n", linea);
                    exit(6);
                }
                j = 0;
            }
            else
                j++;
        }
    }

    /* attendo i figli e stampo il valore di ritorno */
    for (q = 0; q < Q; q++)
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
            printf("Il figlio con pid=%d ha inviato %d linee totali\n", pid, ritorno);
    }

    /* esco con codice UNIX success */
    exit(0);
}