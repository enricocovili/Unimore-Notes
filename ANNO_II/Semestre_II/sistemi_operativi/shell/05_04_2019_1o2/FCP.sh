#!/bin/sh

# controllo sul numero dei parametri N >= 2 e quindi N+1 >=3
case $# in
0|1|2)  echo Errore: il numero parametri deve essere maggiore o uguale a 3, mentre ne hai passati $# - Usage is $0 \<num_pos\> \<dir_assoluta1\> \<dir_assoluta2\> ...
	exit 1;;
*) 	echo Numero parametri $# è ok ;;
esac

F=$1 # salviamo il nome relativo semplice della consegna
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

# I parametri sono OK. passo alle N fasi, dopo aver modificato PATH per poter usare il file comandi FCR.sh
PATH=`pwd`:$PATH
export PATH
> /tmp/nomiAssoluti # azzero / creo il file temporaneo

for G	# G nome indicato nel testo. itera sempre nei parametri passati
do
	FCR.sh $G $F /tmp/nomiAssoluti
done

n=1 # contatore per differenziare nomi assoluti da numero di righe
last_file= # stringa per salvarmi il file attuale
# terminate tutte le ricerche ricorsive cioe' le N fasi
for STR in `cat  /tmp/nomiAssoluti`	# per ogni file trovato nella prima gerarchia
do
	# se n è dispari, siamo in un percorso assoluto
	if test `expr $n % 2` -eq 1
	then
		echo -n "Percorso assoluto: $STR "
		last_file=$STR
	else
		echo Numero righe: $STR
		echo "Inserire numero 1 <= X <= $STR: "
		read X
		if test $X -ge 1 -a $X -le $STR
		then
			echo prime $X linee di $last_file:
			head -$X $last_file
		else
			echo Numero $X non valido
		fi
	fi
	n=`expr $n + 1` # incremento n
done

# pulizia file temporanei
rm /tmp/nomiAssoluti
