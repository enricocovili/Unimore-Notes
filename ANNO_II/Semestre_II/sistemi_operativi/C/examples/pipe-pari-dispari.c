#define MSGSIZE 255     /* dimensione massima del buffer di lettura */

#include <stdio.h>      /* printf() */
#include <stdlib.h>     /* NULL, malloc(), free(), exit() */
#include <unistd.h>     /* pipe(), write(), read(), exec??(), lseek(), close() */
#include <fcntl.h>      /* open(), creat() */
#include <sys/wait.h>   /* wait(), WIFEXITED() WEXITSTATUS() */
#include <ctype.h>      /* isaplha(), isdigit(), islower(), isupper(), tolower(), toupper() */

int main (int argc, char **argv){
   
    int pid; 		            /* pid per fork */
    int N;                      /* conterrà il numero di paramretri passati */
    int p[2][2]; 	            /* p e' un array di due pipe: l'elemento di posto 0 (p[0]) serve per la comunicazione fra i processi dispari e il padre, mentre l'elemento di posto 1 (p[1]) serve per la comunicazione fra i processi pari e il padre */
    char car, car1;			    /* char usato dal figlio per inviare la stringa al padre e char usato dal padre per ricevere la stringa inviata dal figlio */
    int fd;			        	/* variabile usata dal figlio per open file */
    int n1, n2;                 /* variabili che contengono i caratteri letti dalle pipe alternativamente */
    int tot;                    /* numero totale di caratteri letti */
    int i;                      /* iteratore per cicli */

    int status, ritorno;        /* per wait padre */

    /* controllo sul numero di parametri: maggiore o uguale a 2 */
    if(argc-1 < 2){
        printf("Errore numero di parametri: %s vuole almeno due parametri e invece argc = %d\n", argv[0], argc);
        exit(1);
    }
    N=argc-1; /* salvo il numero reale di parametri per usarlo nelle iterazioni */

    /* si crea una pipe: si DEVE sempre controllare che la creazione abbia successo! */
    if(pipe(p[0]) < 0){
        printf("Errore creazione pipe per processi dispari\n");
        exit(2); 
    }

    /* si crea una pipe: si DEVE sempre controllare che la creazione abbia successo!  */
    if(pipe(p[1]) < 0){
        printf("Errore creazione pipe per processi pari\n");
        exit(3); 
    }

    for(i=0; i<N; i++){
        /* si crea il figlio i-esimo (controllando sempre!) */
        if((pid = fork()) < 0){
            printf("Errore creazione figlio\n");
            exit(4); 
        }

        if(pid == 0){ /* codice che viene eseguito dal figlio */
            printf("DEBUG-i: Sono il processo figlio di indice %d e pid %d\n", i, getpid());
            /* chiude le pipe in lettura perchè i figli scriveranno */
            close(p[0][0]);
            close(p[1][0]);
            /* chiudo la pipe in scrittura che il figlio non usa */
            close(p[(i+1)%2][1]);

            if((fd = open(argv[i+1], O_RDONLY)) < 0){ /* provo ad aprire il file che mi spetta */
                printf("Errore nell'apertura del file %s\n", argv[i+1]);
                exit(-1); /* se non si apre mando -1 al padre così sa che c'è stato un errore */
            }

            while(read(fd, &car, sizeof(char)) == sizeof(char)){ /* leggo dal file finchè ci sono caratteri */
                /* per processi pari trasmetto caratteri alfabetici, per dispari solo numerici */
                if((((i % 2) == 0) && isalpha(car)) || (((i % 2) == 1) && isdigit(car))){
                    if(write(p[(i+1)%2][1], &car, sizeof(char)) != sizeof(char)){ /* scrivo i caratteri corretti sulla pipe corretta */
                        printf("Errore nella scrittura sulla pipe di indice %d\n", (i+1)%2);
                        exit(-1);
                    }
                }
            }

            exit(car); /* ritorno al padre l'ultimo carattere letto */
        }
    }

    /* il padre chiude i lati di scrittura delle pipe perchè deve leggere */
    close(p[0][1]); 
  	close(p[1][1]);

    /* dopo che ha creato tutti i figli inizia a leggere prima da una pipe poi dall'altra */
    printf("I caratteri che sono stati inviati dai figli sono:\n");

    tot=0; /* inizializzo il contatore dei caratteri */
    /* finchè ci sono dei caratteri su almeno una delle due pipe eseguo la stampa alternata */
    while((n1 = read(p[0][0], &car, sizeof(char))) == sizeof(char) || 
                (n2 = read(p[1][0], &car1, sizeof(char))) == sizeof(char)){
        tot = tot + n1 + n2; /* sommo il numero di caratteri letti (n1 o n2 potrebbero essere almeno uno 0) */
		write(1, &car, n1); /* uso le write e non le printf così non succede niente se n1 o n2 sono 0 */
        write(1, &car1, n2);
    }

    /*stampo il numero di caratteri ricevuti*/
    printf("\nIl numero totale di caratteri ricevuti è %d\n", tot);

    /*attendo i figli e stampo il valore di ritorno*/
    for(i=0; i<N; i++){
        pid = wait(&status);
        if(pid < 0){ /*controllo che l wait sia andata a buon fine*/
            printf("Errore nella wait del figlio P%d\n", i);
            exit(5);
        }
        /* controllo che non sia terminato in modo anomalo */
        /* avrei potuto usare la macro !WIFEXITED(status) per coerenza ma espande in ((status & 0x7f) == 0) che non è quello di cui ho bisogno */
        if ((status & 0xFF) != 0)
        	printf("Figlio con pid %d terminato in modo anomalo\n", pid);
        else if((ritorno=(int)WEXITSTATUS(status)) == 255) /* controllo il valore di ritorno e lo stampo */
            printf("Errore nel processo figlio %d: file %s non esistente\n", pid, argv[i+1]);
        else printf("Il figlio con pid=%d ha ritornato %c (se 255 problemi!)\n", pid, (char)ritorno);
    }

    /* esco con codice UNIX success */
    exit(0);
}