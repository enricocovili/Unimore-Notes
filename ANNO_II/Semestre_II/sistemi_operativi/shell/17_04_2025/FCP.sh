#!/bin/sh

# controllo sul numero dei parametri N >= 2 e quindi N+1 >=3
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
> /tmp/nomiAssoluti-$$ # creo/azzero il file temporaneo


for G	# G nome indicato nel testo. itera sempre nei parametri passati
do
	# invochiamo il file comandi ricorsivo con la gerarchia, il numero X e il file temporaneo corrente
	FCR.sh $G $X /tmp/nomiAssoluti-$$
	# la specifica indicava che doveva essere riportato su standard output il conteggio di OGNI SINGOLA gerarchia!
done

echo Numero totale file trovati: `wc -l < /tmp/nomiAssoluti-$$`

# terminate tutte le ricerche ricorsive cioe' le Q fasi, dobbiamo procedere con il confronto richiesto
for F in `cat  /tmp/nomiAssoluti-$$`	# per ogni file trovato nella prima gerarchia
do
	echo File corrente: $F
	echo -n "Inserire numero K tale che 0 < K < $X: "
	read K
	if test $K -le 0 -o $K -ge $X
	then
		echo Numero non valido
	else
		echo Riga numero $K: `head -$K $F | tail -1`
	fi
done

# pulizia file temporanei
rm /tmp/nomiAssoluti-* # * l'uso dell'asterisco ci risparmia un for aggiuntivo
