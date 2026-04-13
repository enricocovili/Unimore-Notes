#include <stdio.h>    /* printf() */
#include <stdlib.h>   /* NULL, malloc(), free(), exit() */
#include <unistd.h>   /* pipe(), write(), read(), exec??(), lseek(), close() */
#include <fcntl.h>    /* open(), creat() */
#include <sys/wait.h> /* wait(), WIFEXITED() WEXITSTATUS() */
#include <ctype.h>    /* isaplha(), isdigit(), islower(), isupper(), tolower(), toupper() */

#define MSGSIZE 3 /* costante che determina la lunghezza dei nomi dei file */

/* definizione del TIPO pipe_t come array di 2 interi */
typedef int pipe_t[2];

int main(int argc, char **argv)
{

    int pid;              /* pid per fork */
    int N;                /* conterrà il numero di paramretri passati */
    pipe_t *pipes;        /* array dinamica per le N-1 pipes P0 con gli altri fratelli */
    int n, j;             /* iteratori utilizzati nei cicli */
    int fd;               /* variabile usata dal figlio per open file */
    char linea[MSGSIZE];  /* array per contenere la stringa letta dal file */
    char buffer[MSGSIZE]; /* array per contenere la stringa letta dal file */

    int status, ritorno; /* per wait padre */

    /* controllo sul numero di parametri: maggiore o uguale a 3 */
    if (argc - 1 < 3)
    {
        printf("Errore numero di parametri: %s vuole almeno tre parametri e invece argc = %d\n", argv[0], argc);
        exit(1);
    }
    N = argc - 1; /* salvo il numero di parametri per usarlo nelle iterazioni */

    /* si alloca spazio per N-1 pipes una per ogni fratello di P0 */
    pipes = (pipe_t *)malloc((N - 1) * sizeof(pipe_t));
    if (pipes == NULL)
    { /* controllo l'avvenuta locazione della memoria */
        printf("Errore nell'allocazione dell'array per contenere le pipe\n");
        exit(2);
    }

    /*si creano le N-1 pipes una per ogni fratello di P0 */
    for (n = 0; n < N - 1; n++)
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
            printf("DEBUG-i: Sono il figlio di indice %d e pid %d associato al file %s\n", n, getpid(), argv[n + 1]);

            if ((fd = open(argv[n + 1], O_RDONLY)) < 0)
            { /* provo ad aprire il file associato a Pn */
                printf("Errore nella open del file %s\n", argv[n + 1]);
                exit(-1); /*se non si apre mando -1 al figlio così sa che c'è stato un errore*/
            }

            if (n == 0)
            { /* codice eseguito la figlio P0 */
                /* chiude le pipe in lettura perchè P0 deve scrivere */
                for (j = 0; j < N - 1; j++)
                    close(pipes[j][0]);

                while (read(fd, linea, MSGSIZE))
                {                              /* finchè ci sono caratteri sul file */
                    linea[MSGSIZE - 1] = '\0'; /* sostituisco il \n con il terminatore \0 */
                    for (j = 0; j < N - 1; j++)
                    {
                        if (write(pipes[j][1], linea, MSGSIZE) != MSGSIZE)
                        {
                            printf("Errore nell'invio della stringa %s sulla pipe %d-esima\n", linea, j);
                        }
                    }
                }
            }
            else
            { /* codice eseguito dai figli Pn con n!=0 */
                /* chiude la pipe in scrittura perchè gli altri figli leggeranno (e quelle non sue) */
                for (j = 0; j < N - 1; j++)
                {
                    close(pipes[j][1]);
                    if (j != (n - 1))
                        close(pipes[j][0]);
                }

                /* leggo dalla pipe il nome del file inviato dal fratello P0 */
                while (read(pipes[n - 1][0], buffer, MSGSIZE))
                {
                    while (read(fd, linea, MSGSIZE))
                    {
                        linea[MSGSIZE - 1] = '\0';

                        /* provo a creare il nipote e se non riesce ritorno al padre -1*/
                        if ((pid = fork()) < 0)
                        {
                            printf("Errore creazione nipote\n");
                            exit(-1);
                        }

                        if (pid == 0)
                        { /* codice del nipote */
                            printf("DEBUG-i: Sono il nipote di indice %d e pid %d per il file %s\n", n, getpid(), argv[n + 1]);
                            close(pipes[n - 1][0]); /* chiudo la pipe rimasta aperta dal figlio */

                            close(STDOUT_FILENO); /* elimino lo STDOUT */
                            open("/dev/null", O_WRONLY);

                            close(STDERR_FILENO); /* elimino lo STDERR */
                            open("/dev/null", O_WRONLY);

                            execlp("diff", "diff", buffer, linea, (char *)0); /* attenzione prima il nome ricevuto e poi il proprio */

                            /* usiamo perror che scrive su standard error, dato che lo standard output e' collegato alla pipe */
                            perror("Problemi di esecuzione della diff da parte del nipote");
                            exit(-1); /* c'è stato un errore imprevisto qua non dovrebbe arrivare mai */
                        }

                        /* codice del figlio */
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
                        else if ((ritorno = (int)WEXITSTATUS(status)) != 0)
                        { /* verifico il codice di ritorno */
                            printf("I file %s e %s sono diversi\n", buffer, linea);
                        }
                        else
                            printf("I file %s e %s sono uguali\n", buffer, linea);
                    }

                    lseek(fd, 0, SEEK_SET); /* posiziono il cursore all'inizio del file */
                }
            }

            exit(n); /* ritorno al padre il codice di ritorno del nipote */
        }
    }

    /* codice del padre */
    /* il padre chiude le pipe in scrittura/lettura */
    for (n = 0; n < N - 1; n++)
    {
        close(pipes[n][1]);
        close(pipes[n][0]);
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
            printf("Errore nel processo figlio %d: file %s non esistente\n", pid, argv[n + 1]);
        else
            printf("Il figlio con pid=%d ha ritornato %d (se 255 problemi!)\n", pid, ritorno);
    }

    /* esco con codice UNIX success */
    exit(0);
}