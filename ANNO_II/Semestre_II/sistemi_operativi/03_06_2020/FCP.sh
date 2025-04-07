#!/bin/sh

# controllo sul numero dei parametri N >= 2 e quindi N+1 >=3
case $# in
0|1|2)  echo Errore: il numero parametri deve essere maggiore o uguale a 3, mentre ne hai passati $# - Usage is $0 \<char\> \<dir_assoluta1\> \<dir_assoluta2\> ...
	exit 1;;
*) 	echo Numero parametri $# è ok ;;
esac

# Controllo primo parametro: deve essere un carattere singolo diverso da /
#controllo su primo parametro (DEVE ASSOLUTAMENTE ESSERE FATTO CON UN CASE): deve essere un singolo carattere
case $1 in
?) ;;
*)      echo Errore: $1 non singolo carattere
        exit 2;;
esac


C=$1 # salviamo il numero positivo nella variabile della consegna
# shiftiamo per avere solo le gerarchie in $*
shift

# E' possibile fare i controlli sui nomi assoluti e sulle directory in un for
for G 	# usiamo il nome G specificato nella consegna
do
	case $G in
	/*) if test ! -d $G -o ! -x $G
	    then
	    echo Errore: $G non directory o non attraversabile
	    exit 3
	    fi;;
	*)  echo Errore: $G non nome assoluto; exit 4;;
	esac
done

# I parametri sono OK. passo alle Q fasi, dopo aver modificato PATH per poter usare il file comandi FCR.sh
PATH=`pwd`:$PATH
export PATH
> /tmp/nomiAssoluti-$$ 	#creiamo/azzeriamo ogni file temporaneo, usando come parte iniziale del nome quello specificato nel testo!


for G	# G nome indicato nel testo. itera sempre nei parametri passati
do
	echo DEBUG-fase $n per la gerarchia $G
	# invochiamo il file comandi ricorsivo con la gerarchia, il numero X e il file temporaneo corrente
	FCR.sh $G $C /tmp/nomiAssoluti-$$
	# la specifica indicava che doveva essere riportato su standard output il conteggio di OGNI SINGOLA gerarchia!
	# echo Il numero di file trovati in questa fase e\' `wc -l < /tmp/nomiAssoluti-$n`
done

echo Numero totale directory trovate: `wc -l < /tmp/nomiAssoluti-$$`

# terminate tutte le ricerche ricorsive cioe' le N fasi, dobbiamo procedere con il confronto richiesto
for directory in `cat  /tmp/nomiAssoluti-$$`	# per ogni file trovato nella gerarchia
do
	echo Trovata directory $directory
	echo Elena, vuoi visualizzare tutti i contenuti \(anche quelli nascosti\) di $directory \(Si,si,Yes,yes\)?
	read answer
	case $answer in
	S*|s*|Y*|y*) ls -a $directory;;
	*) ;;
	esac
done

# pulizia file temporanei
rm /tmp/nomiAssoluti-$$
