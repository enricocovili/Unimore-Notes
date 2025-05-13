#!/bin/sh
#File comandi principale da invocare con numerostrettpos dirass1 dirass2 ...
#Viene usato un file temporaneo e FCR.sh e' usato per tutte le fasi

#controllo sul numero dei parametri N >= 2 e quindi N+1 >=3
case $# in
0|1|2)	echo Errore: voglio un numero parametri maggiore o uguale a 3, mentre ne hai passati $# - Usage is $0 numerostrettpos dirass1 dirass2 ...
	exit 1;;
*) 	echo DEBUG-OK: da qui in poi proseguiamo con $# parametri ;;
esac

#controllo sul primo parametro, che deve essere un numero strettamente positivo
case $1 in
*[!0-9]*) echo Errore: $1 non numerico o negativo
	  exit 2;;
*) ;; # siamo gia' anche sicuri che e' positivo dato che $1 puo' contenere solo caratteri numerici e quindi non e' presente il carattere -
esac
if test $1 -eq 0
then echo Errore: $1 uguale a 0
    exit 3
fi

X=$1 	#salviamo il primo parametro
#quindi ora possiamo usare il comando shift
shift

#ora in $* abbiamo solo i nomi delle gerarchie e quindi possiamo fare i controlli sui nomi assoluti e sulle directory in un for
for i
do
	case $i in
	/*) if test ! -d $i -o ! -x $i
	    then
	    	echo Errore: $i non directory o non traversabile
	    	exit 4
	    fi;;
	*)  echo Errore: $i non nome assoluto; exit 5;;
	esac
done

#controlli sui parametri finiti possiamo passare alle N fasi, dopo aver settato il path
PATH=`pwd`:$PATH
export PATH

> /tmp/conta$$ #creiamo/azzeriamo il file temporaneo.

for i
do
	echo DEBUG-fase per $i
	#invochiamo il file comandi ricorsivo con la gerarchia, il numero e il file temporaneo
	FCR.sh $i $X /tmp/conta$$
done

#terminate tutte le ricerche ricorsive cioe' le N fasi
#N.B. Andiamo a contare le linee del file /tmp/conta$$
echo Il numero di file totali che soddisfano la specifica = `wc -l < /tmp/conta$$`
for i in `cat /tmp/conta$$`
do
	#Stampiamo (come richiesto dal testo) i nomi assoluti dei file trovati
	echo Trovato il file $i
	#chiediamo all'utente il numero K per ogni file trovato
	echo -n "Dammi il numero K (strettamente maggiore di 0 e strettamente minore di $X): "
	read K
	#Controllo K (sempre con expr, se prima lo abbiamo fatto con expr, altrimenti sempre con case se prima lo abbiamo fatto con case!)
	case $K in
	*[!0-9]*)
		echo Errore: $K non numerico
		rm /tmp/conta$$ ;; # poiche' stiamo uscendo a causa di un errore, cancelliamo il file temporaneo!
	*)
		if test $K -le 0 -o $K -ge $X
		then
			echo Errore: $K non positivo o non minore di $X
			rm /tmp/conta$$ # poiche' stiamo uscendo a causa di un errore, cancelliamo il file temporaneo!
		fi;;
	esac
	#selezioniamo direttamente la $K-esima linea del file corrente
	echo -n $K riga del file:
	head -$K $i | tail -1
done

#da ultimo eliminiamo il file temporaneo
rm /tmp/conta$$
