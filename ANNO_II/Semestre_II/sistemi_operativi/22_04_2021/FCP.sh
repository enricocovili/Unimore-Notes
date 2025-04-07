#!/bin/sh

# controllo sul numero dei parametri Q >= 2 e quindi Q+1 >=3
case $# in
0|1|2)  echo Errore: il numero parametri deve essere maggiore o uguale a 3, mentre ne hai passati $# - Usage is $0 \<num_pos\> \<dir_assoluta1\> \<dir_assoluta2\> ...
	exit 1;;
*) 	echo Numero parametri $# è ok ;;
esac

# Controllo primo parametro (fatto con case): deve essere un numero intero strettamente positivo
case $1 in
*[!0-9]*) echo Errore: $1 non numerico o non positivo
	  exit 2;;
*) if test $1 -eq 0
   then
	echo Errore: $1 uguale a 0
	exit 3
   fi;;
esac

W=$1 # salviamo il numero positivo nella variabile della consegna
# shiftiamo per il controllo sul secondo parametro S
shift

case $1 in
*/*) 	echo Errore: carattere non permesso in $1
	exit 4;;
*)	;; # tutto ok
esac

S=$1
shift # salvo la stringa e ora ho solo gerachie nei parametri

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
> /tmp/nomiAssoluti 	#creiamo/azzeriamo il file temporaneo


for G	# G nome indicato nel testo. itera sempre nei parametri passati
do
	echo DEBUG-fase $G
	# invochiamo il file comandi ricorsivo con la gerarchia, la Stringa e il path del file temporaneo
	FCR.sh $G $S /tmp/nomiAssoluti
done

NUMDIR=`wc -l < /tmp/nomiAssoluti` # mi salvo il conteggio in una variabile
echo Numero directory che rispettano i vincoli: $NUMDIR

if test $NUMDIR -ge $W
then
	echo -n Gentilmente $USER, selezionare un numero da 1 a $W: 
	read X
	case $X in
	*[!0-9]*)	echo $X non numerico o non positivo
			rm /tmp/nomiAssoluti
			exit 0;;
	*)		if test ! $X -ge 1 -o ! $X -le $W
			then
				echo $X minore di 1 o maggiore di $W
				rm /tmp/nomiAssoluti
				exit 0
			else
				echo Directory numero $X: `head -$X /tmp/nomiAssoluti | tail -1`
			fi;;
	esac
fi

# pulizia file temporanei
rm /tmp/nomiAssoluti
