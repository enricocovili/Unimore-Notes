#!/bin/sh

# controllo sul numero dei parametri Q >= 2 e quindi Q+2 >=4
case $# in
0|1|2|3)  echo Errore: il numero parametri deve essere maggiore o uguale a 4, mentre ne hai passati $# - Usage is $0 \<str\>  \<str\> \<dir_assoluta1\> \<dir_assoluta2\> ...
	exit 1;;
*) 	echo Numero parametri $# è ok ;;
esac

# salvo le due stringe in S2 e S3 effettuando i relativi shift per avere solo gerarchie nel for successivo
S1=$1
shift
S2=$1
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
> /tmp/nomiAssoluti-$S1 	#creiamo/azzeriamo ogni file temporaneo, usando come parte iniziale del nome quello specificato nel testo!
> /tmp/nomiAssoluti-$S2

for G	# G nome indicato nel testo. itera sempre nei parametri passati
do
	echo DEBUG-fase per la gerarchia $G
	# invochiamo il file comandi ricorsivo con la gerarchia, il numero X e il file temporaneo corrente
	FCR.sh $G $S1 $S2 /tmp/nomiAssoluti-$S1 /tmp/nomiAssoluti-$S2
	# la specifica indicava che doveva essere riportato su standard output il conteggio di OGNI SINGOLA gerarchia!
done

TOT1=`wc -l < /tmp/nomiAssoluti-$S1` # salvo i due risultati delle ricerche
TOT2=`wc -l < /tmp/nomiAssoluti-$S2`

echo Numero di file con estensione $S1: $TOT1
echo Numero di file con estensione $S2: $TOT2

if test $TOT1 -le $TOT2
then
	echo -n "Utente $USER, inserisca un numero compreso tra 1 e $TOT1: "
	read X
	if test $X -ge 1 -a $X -le $TOT1
	then
		echo File numero $X con estensione $S1: `head -$X /tmp/nomiAssoluti-$S1 | tail -1`
		echo File numero $X con estensione $S2: `head -$X /tmp/nomiAssoluti-$S2 | tail -1`
	else
		echo Numero $X non compreso nel range specificato
	fi
fi

# pulizia file temporanei
rm /tmp/nomiAssoluti-* # * l'uso dell'asterisco ci risparmia un for aggiuntivo
