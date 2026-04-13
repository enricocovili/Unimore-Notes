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
    int pidSpeciale; /* pid per il figlio speciale */
    int N;           /* conterrà il numero di paramretri passati */
    int n, j;        /* iteratori per i cicli */
    int fd;          /* descrittore per il file di lettura */
    int L, l;        /* numero delle linee letto dal figlio speciale */
    char linea[200]; /* contiene la linea letta da padre/figli */
    pipe_t *pipes;   /* array dinamica per le N pipes */
    pipe_t p;        /* pipe padre figlio speciale */

    int status, ritorno; /* per le wait */

    /* controllo sul numero di parametri: maggiore o uguale a 2 */
    if (argc - 1 < 2)
    {
        printf("Errore numero di parametri: %s vuole almeno due parametri e invece argc = %d\n", argv[0], argc);
        exit(1);
    }
    N = argc - 1; /* memorizzo il numero di file per usarlo nelle iterazioni */

    if ((fd = creat("/tmp/FabioSecchiari", PERM)) < 0)
    {
        printf("Errore nella creazione del file temporaneo\n");
        exit(2);
    }

    if (pipe(p) < 0)
    { /* controllo che la pipe sia stata creata */
        printf("Errore creazione della pipe per figlio speciale\n");
        exit(3);
    }

    if ((pidSpeciale = fork()) < 0)
    { /* creo il figlio speciale per il conteggio */
        printf("Errore creazione figlio speciale\n");
        exit(4);
    }

    if (pidSpeciale == 0)
    { /* codice del figlio speciale */
        printf("DEBUG-i: Sono il figlio speciale con pid %d\n", getpid());

        close(0); /* chiudo lo stdin perchè lo riceve dal file */
        if ((fd = open(argv[1], O_RDONLY)) < 0)
        { /* provo ad aprire il file che mi spetta come stdin */
            printf("Errore nella open del file %s\n", argv[1]);
            exit(-1); /* se non si apre mando -1 al figlio così sa che c'è stato un errore */
        }

        close(1);  /* chiudo lo stdout perchè lo ridireziono per piping alla pipe in scrittura */
        dup(p[1]); /* uso p[1] per lo stdout */

        close(p[0]); /* chiudo la lettura tra figlio-nipote */
        close(p[1]); /* ora la posso chiudere */

        execlp("wc", "wc", "-l", (char *)0); /* eseguo il conteggio e mando su stdout */

        /* usiamo perror che scrive su standard error, dato che lo standard output e' collegato alla pipe */
        perror("Problemi di esecuzione di wc da parte del figlio speciale");
        exit(-1); /* c'è stato un errore imprevisto qua non dovrebbe arrivare mai */
    }

    /* codice del padre */
    close(p[1]); /* chiudo la pipe in scrittura con il figlio speciale */

    /* ricevo dalla pipe il numero di linee e lo converto */
    j = 0;
    while (read(p[0], &(linea[j++]), sizeof(char)))
        ;
    if (!j)
    {
        printf("Errore nel calcolo numero di linee da parte del figlio speciale\n");
        exit(5); /* se il figlio speciale NON ha inviato nulla NON si possono creare i figli normali e quindi il padre termina */
    }
    linea[j - 1] = '\0'; /* rendo stringa inserendo il terminatore */
    L = atoi(linea);     /* converto in numero con la funziona atoi */
    printf("DEBUG-i: Il padre ha calcolato la lunghezza pari a %d\n", L);

    /* posso chiudere la pipe in lettura con il figlio speciale */
    close(p[0]);

    /* si alloca spazio per N pipes */
    pipes = (pipe_t *)malloc(N * sizeof(pipe_t));
    if (pipes == NULL)
    { /* controllo l'avvenuta allocazione */
        printf("Errore nell'allocazione dell'array per contenere le pipe\n");
        exit(6);
    }

    /* si creano le N pipe una per ogni figlio */
    for (n = 0; n < N; n++)
    {
        if (pipe(pipes[n]) < 0)
        { /* controllo che la pipe sia stata creata */
            printf("Errore creazione della pipe %d-esima\n", n);
            exit(7);
        }
    }

    for (n = 0; n < N; n++)
    {
        if ((pid = fork()) < 0)
        { /* creo il figlio n-esimo */
            printf("Errore creazione figlio %d-esimo\n", n);
            exit(8);
        }

        if (pid == 0)
        { /* codice del figlio */
            /* chiudo le pipes che non utilizzo quindi quelle in lettura e quelle in scrittura tranne la corrente */
            for (j = 0; j < N; j++)
            {
                close(pipes[j][0]);
                if (j != n)
                    close(pipes[j][1]);
            }

            if ((fd = open(argv[n + 1], O_RDONLY)) < 0)
            { /* provo ad aprire il file */
                printf("Errore nella open del file %s\n", argv[n + 1]);
                exit(-1); /*se non si apre mando -1 al figlio così sa che c'è stato un errore*/
            }

            j = 0;
            while (read(fd, &(linea[j]), sizeof(char)))
            { /* finchè ci sono caratteri leggo dal file */
                if (linea[j++] == '\n')
                {
                    /* ogni volta che finisce la linea scrivo la sua lunghezza sulla pipe e poi tale linea */
                    if (write(pipes[n][1], &j, sizeof(j)) != sizeof(j))
                    {
                        printf("Errore nella scrittura di %d sulla pipe %d-esima\n", j, n + 1);
                        exit(-1);
                    }
                    /* ora scrivo la linea sulla pipe al padre */
                    if (write(pipes[n][1], linea, j) != j)
                    {
                        printf("Errore nella scrittura della linea sulla pipe %d-esima\n", n + 1);
                        exit(-1);
                    }
                    ritorno = j;
                    j = 0;
                }
            }

            /* ritorno la lunghezza dell'ultima linea al padre */
            exit(ritorno);
        }
    }

    /* codice del padre */
    /* il padre chiude le pipe in scrittura */
    for (n = 0; n < N; n++)
    {
        close(pipes[n][1]);
    }

    /* il padre legge da ogni pipe il conteggio trasmesso in ordine */
    for (j = 0; j < L; j++)
    { /* scandaglio tutti i figli per ogni linea */
        for (n = 0; n < N; n++)
        {
            if (read(pipes[n][0], &l, sizeof(l)) != sizeof(l))
            { /* leggo dalla pipe la lunghezza della linea */
                printf("Errore nella lettura della lunghezza %d dalla pipe %d-esima\n", l, n);
                exit(9);
            }
            if (read(pipes[n][0], linea, l) != l)
            { /* leggo dalla pipe la lunghezza stessa */
                printf("Errore nella lettura della linea dalla pipe %d-esima\n", n);
                exit(10);
            }
            else
            { /* se non ci sono stati errori scrivo sul file temporaneo la linea */
                printf("DEBUG-i: E' stato letto dal padre la linea lunga %d dal figlio %d-esimo\n", l, n);
                if (write(fd, linea, l) != l)
                {
                    printf("Errore nella scrittura sul file temporaneo della linea %d\n", j);
                    exit(11);
                }
            }
        }
    }

    /* attendo i figli (speciali/normali) e stampo il valore di ritorno */
    for (n = 0; n < N + 1; n++)
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