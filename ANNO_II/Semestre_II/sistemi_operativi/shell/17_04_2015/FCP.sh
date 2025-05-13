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

X=$1 # salviamo il numero positivo nella variabile della consegna
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
> /tmp/nomiAssoluti

n=1 # indicatore della fase attuale. necessario per creare i file temporanei
for G	# G nome indicato nel testo. itera sempre nei parametri passati
do
	# chiamata ricorsiva
done

echo num tot file: `wc -l < /tmp/nomiAssoluti`
# terminate tutte le ricerche ricorsive cioe' le Q fasi, dobbiamo procedere con il confronto richiesto
for F in `cat  /tmp/nomiAssoluti`	# per ogni file trovato nella prima gerarchia
do
	echo nome assoluto file $F
	echo -n "inserire numero 1 <= K <= $X"
	read K
done

# pulizia file temporanei
rm /tmp/nomiAssoluti-* # * l'uso dell'asterisco ci risparmia un for aggiuntivo
