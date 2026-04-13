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
    int N;           /* conterrà il numero di paramretri passati */
    int n, j;        /* iteratori per i cicli */
    int fcreato, fd; /* descrittore per il file creato dal secondo figlio di ogni coppia e per file letto */
    int nro = 0;     /* la lunghezza massima di linee pari/dispari da tornare al padre */
    int nlinea;      /* memorizzo il numero di linea */
    int lunghezza;   /* per leggere la lunghezza della linea dal secondo figlio */
    pipe_t *pipes;   /* array dinamica per le N pipes */
    char linea[250]; /* array per memorizzare la linea (compreso \n) */
    char letta[250]; /* array per contenere la linea letta dall'altro figlio */

    int status, ritorno; /* per le wait */

    /* controllo sul numero di parametri: maggiore o uguale a 1 */
    if (argc - 1 < 1)
    {
        printf("Errore numero di parametri: %s vuole almeno un parametro e invece argc = %d\n", argv[0], argc);
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
            printf("DEBUG-i: Sono il processo figlio di indice %d e pid %d associato al file %s\n", n, getpid(), argv[(n % N) + 1]);

            /* provo ad aprire il file corrispondente che mi serve sia nel figlio n che 2n */
            if ((fd = open(argv[(n % N) + 1], O_RDONLY)) < 0)
            {
                printf("Errore nell'apertura del file %s\n", argv[(n % N) + 1]);
                exit(-1);
            }

            if (n >= N)
            { /* è il secondo figlio della coppia */
                /* chiude la pipe in scrittura perchè i figli 2n leggeranno e quelle che non sono sue */
                for (j = 0; j < N; j++)
                {
                    close(pipes[j][1]);
                    if (j != (n - N))
                        close(pipes[j][0]);
                }

                /* costruisco il nome del file output usando temporaneamente linea */
                sprintf(linea, "%s.max", argv[(n - N) + 1]);
                if ((fcreato = creat(linea, PERM)) < 0)
                { /* provo a creare il file ed esco se fallisce */
                    printf("Errore nella creazione del file di output %s\n", linea);
                    exit(-1);
                }

                j = 0; /* inizializzo il cursore per la lettura e anche il numero di linee */
                nlinea = 0;
                while (read(fd, &(linea[j]), sizeof(char)) > 0)
                {
                    if (linea[j++] == '\n')
                    {             /* ho finito di leggere una riga */
                        nlinea++; /* incremento il numero di righe totali (subito perchè le linee partono da 1) */
                        if (nlinea % 2 == 0)
                        { /* sto leggendo una riga pari (mi interessa) */
                            if (j > nro)
                                nro = j; /* se la lunghezza di questa riga è > del massimo la aggiorno */
                            if (read(pipes[n - N][0], &lunghezza, sizeof(lunghezza)) != sizeof(lunghezza))
                            { /* leggo la lunghezza della linea dall'altro figlio */
                                printf("Errore: il figlio di indice %d non ha letto correttamente la lunghezza dalla pipe\n", n - N);
                                exit(-1);
                            }
                            if (read(pipes[n - N][0], letta, lunghezza) != lunghezza)
                            { /* leggo la linea dall'altro figlio */
                                printf("Errore: il figlio di indice %d non ha letto correttamente la linea dalla pipe\n", n);
                                exit(-1);
                            }
                            /* valuto in base alla lunghezza la linea da scrivere sul file e la scrivo */
                            if (j > lunghezza)
                                write(fcreato, linea, j);
                            else
                                write(fcreato, letta, lunghezza);
                        }
                        j = 0; /* riporto il cursore all'inizio pronto per leggere la linea successiva */
                    }
                }
            }
            else
            { /* è il primo figlio della coppia */
                /* chiude la pipe in lettura perchè i figli n scriveranno e quelle che non sono sue */
                for (j = 0; j < N; j++)
                {
                    close(pipes[j][0]);
                    if (j != n)
                        close(pipes[j][1]);
                }

                j = 0;
                nlinea = 0;
                while (read(fd, &(linea[j]), sizeof(char)) > 0)
                {
                    if (linea[j++] == '\n')
                    {             /* ho finito di leggere una riga */
                        nlinea++; /* incremento il numero di righe totali */
                        if (nlinea % 2 == 1)
                        { /* sto leggendo una riga dispari (mi interessa) */
                            if (j > nro)
                                nro = j;
                            if (write(pipes[n][1], &j, sizeof(j)) != sizeof(j))
                            { /* comunico la lunghezza della linea all'altro figlio */
                                printf("Errore: il figlio di indice %d non ha scritto correttamente la lunghezza sulla pipe\n", n);
                                exit(-1);
                            }
                            if (write(pipes[n][1], linea, j) != j)
                            { /* comunico la linea all'altro figlio */
                                printf("Errore: il figlio di indice %d non ha scritto correttamente la linea sulla pipe\n", n);
                                exit(-1);
                            }
                        }
                        j = 0;
                    }
                }
            }

            exit(nro); /* ritorno al padre la lunghezza massima delle linee */
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
            printf("Il figlio con pid=%d ha letto un massimo di %d caratteri per linea\n", pid, ritorno);
    }

    /* esco con codice UNIX success */
    exit(0);
}