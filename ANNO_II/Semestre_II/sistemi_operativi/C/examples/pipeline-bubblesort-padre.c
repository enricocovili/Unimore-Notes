#include <stdio.h>      /* printf() */
#include <stdlib.h>     /* NULL, malloc(), free(), exit() */
#include <unistd.h>     /* pipe(), write(), read(), exec??(), lseek(), close() */
#include <fcntl.h>      /* open(), creat() */
#include <sys/wait.h>   /* wait(), WIFEXITED() WEXITSTATUS() */
#include <stdbool.h>    /* bool, true, false */

#define NUM_EL 26 

/* definizione del TIPO pipe_t come array di 2 interi */
typedef int pipe_t[2];

/* creo un array alfabeto (avrei potuto incrementare un char a partire da 'a')*/
char alfabeto[27] = "abcdefghijklmnopqrstuvwxyz";

/* definisco la struttura che scriverò volta per volta sulla pipeline */
typedef struct {
    char v1;
    long int v2;
} Strut;

/* definisco la funzione per l'ordinamento di un vettore di oggetti Strut */
void bubbleSort(Strut v[], int dim){
    int i; bool ordinato = false;
    while (dim>0 && !ordinato){
        ordinato = true; /* hp: è ordinato */
        for (i=0; i<dim-1; i++)
            if (v[i].v2>v[i+1].v2){
                Strut temp = v[i];
                v[i] = v[i+1];
                v[i+1] = temp;
                ordinato = false;
            }
        dim--;
    }
} 

int main (int argc, char **argv){
   
    int pid[NUM_EL]; 		    /* pid per fork */
    pipe_t pipes[NUM_EL]; 	    /* array statico per le 26 pipes */
    int fd;			        	/* variabile usata dal figlio per open file */
    int i, j;                      /* iteratori per i cicli */
    char car;                   /* variabile per memorizzare il carattere letto */
    Strut arr[NUM_EL];          /* array di strutture per contenere i vari dati */
    Strut temp;                 /* struttura temporanea mentre aspetto gli altri elementi della pipeline */

    int pidFiglio, status, ritorno;      /* per wait padre */

    /* controllo sul numero di parametri: uguale a 1 */
    if(argc-1 < 1){
        printf("Errore numero di parametri: %s vuole esattamente un parametro e invece argc = %d\n", argv[0], argc);
        exit(1);
    }

    /* si creano le N pipe una per ogni figlio */
    for(i=0; i<NUM_EL; i++){
        if(pipe(pipes[i]) < 0){ /* controllo sull'avvenuta creazione della pipe */
            printf("Errore creazione della pipe %d-esima\n", i);
            exit(2); 
        }
    }

    for(i=0; i<NUM_EL; i++){
        /* si crea il figlio i-esimo (controllando sempre!) */
        if((pid[i] = fork()) < 0){
            printf("Errore creazione figlio\n");
            exit(3);
        }

        if(pid[i] == 0){ /* codice che viene eseguito dal figlio */
            printf("DEBUG-i: Sono il figlio di indice %d e pid %d e sto per cercare il carattere %c nel file %s\n", i, getpid(), alfabeto[i], argv[1]); 
            /* chiusura dei lati delle pipe non usate nella pipeline */
			for (j=0; j<NUM_EL; j++){
				if (j != i) close (pipes[j][1]); /* chiudo le pipe di scrittura tranne quella corrente */
				if ((i == 0) || (j != i-1)) /* chiudo tutte le pipe di lettura se è il primo figlio altrimenti tutte tranne la precedente */
					close (pipes[j][0]);
			}

            /* tento l'apertura del file passato */
            if((fd = open(argv[1], O_RDONLY)) < 0){
                /* non eseguo un print perchè altrimenti me lo farebbe 26 volte se non esiste il file */
                exit(-1);
            }

            /* inizializzo la struttura che mi serve */
            temp.v2=0;
            temp.v1=alfabeto[i];
            /* leggo carattere x carattere per controllare se c'è Ci */
            while((read(fd, &car, 1)) > 0){
                if(car == alfabeto[i]) (arr[i].v2)++;
            }

            if(i != 0){ /* devo leggere i valori precedenti */
                if(read(pipes[i-1][0], arr, sizeof(arr)) != sizeof(arr)){
                    printf("Errore nella lettura dalla pipeline indice %d", i-1);
                    exit(-1);
                }
            }

            /* faccio l'echo dell'array con l'aggiunta del nuovo elemento */
            arr[i].v1 = temp.v1;
            arr[i].v2 = temp.v2;
            if(write(pipes[i][1], arr, sizeof(arr)) != sizeof(arr)){ /* scrivo sulla pipeline l'array aggionrata */
                printf("Errore nella scritura sulla pipe di indice %d\n", i);
                exit(-1);
            }

            exit(car); /*ritorno al padre l'ultimo carattere letto */
        }
    }

    /* codice del padre */
    /* il padre chiude le pipe in scrittura e anche in lettura tranne l'ultima */
    for(i=0; i<NUM_EL; i++){
        close(pipes[i][1]);
        if(i!=NUM_EL-1) close(pipes[i][0]);
    }

    /* il padre legge l'array finale A25 e la ordina in modo crescente */
    if(read(pipes[NUM_EL-1][0], arr, sizeof(arr)) != sizeof(arr)){
        printf("Errore nella lettura della pipeline ricevuta dal padre\n");
        exit(4);
    }
    bubbleSort(arr, NUM_EL); /* ordino l'array finale */

    for(i=0; i<NUM_EL; i++)
        /* per ottenere l'indice guardo il carattere associato a quella struttura e ci tolgo 'a' */
        printf("Il processo %d-esimo con PID %d associato a \'%c\' ha trovato %ld occorrenze\n", arr[i].v1-'a', pid[arr[i].v1-'a'], arr[i].v1, arr[i].v2);

    /* attendo i figli e stampo il valore di ritorno */
    for(i=0; i<NUM_EL; i++){
        pidFiglio = wait(&status);
        if(pidFiglio < 0){ /*controllo che la wait sia andata a buon fine*/
            printf("Errore nella wait del figlio P%d\n", i);
            exit(5);
        }
        /* controllo che non sia terminato in modo anomalo */
        /* avrei potuto usare la macro !WIFEXITED(status) per coerenza ma espande in ((status & 0x7f) == 0) che non è quello di cui ho bisogno */
        if ((status & 0xFF) != 0)
        	printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
        else if((ritorno=(int)WEXITSTATUS(status)) == 255) /* controllo il valore di ritorno e lo stampo */
            printf("Errore nel processo figlio %d: file %s non esistente\n", pidFiglio, argv[i+1]);
        else printf("Il figlio con pid=%d ha ritornato %c (%d) (se 255 problemi!)\n", pidFiglio, (char)ritorno, ritorno);
    }

    /* esco con codice UNIX success */
    exit(0);
}