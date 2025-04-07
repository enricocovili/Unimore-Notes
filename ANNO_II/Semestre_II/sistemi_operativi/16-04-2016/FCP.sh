#!/bin/sh

# controllo sul numero dei parametri N >= 2 cioè N+1>=3
case $# in
0|1|2)  echo Errore: il numero parametri deve essere maggiore o uguale a 3, mentre ne hai passati $# - Usage is $0 \<dir_assoluta1\> \<dir_assoluta2\> ... \<num_pos\>
	exit 1;;
*) 	echo Numero parametri $# è ok ;;
esac

X=

# Controllo parametri in un unico for
n=1
for G
do
	echo $G
	if test $n -eq $# # Ultimo parametro: deve essere numero strettamente positivo
	then
		case $G in
		*[!0-9]*) 	echo Errore: $G non numerico o non positivo
	  			exit 2;;
		*) 		if test $G -eq 0
   	   			then
					echo Errore: $G uguale a 0
	   				exit 3
				else # caso corretto
					X=$G # salvo il numero positivo
   	   			fi;;
		esac
	else # primi N parametri: devono essere nomi assoluti di directory
		case $G in
		/*) 	if test ! -d $G -o ! -x $G
	    		then
	    			echo Errore: $G non directory o non attraversabile
	    			exit 3
	    		fi;;
		*) 	echo Errore: $G non nome assoluto; exit 4;;
		esac
	fi
	n=`expr $n + 1`
done

# I parametri sono OK. passo alle N fasi, dopo aver modificato PATH per poter usare il file comandi FCR.sh
PATH=`pwd`:$PATH
export PATH

> /tmp/nomiAssoluti

n=1 # indicatore della fase attuale. necessario per creare i file temporanei
for G	# G nome indicato nel testo. itera sempre nei parametri passati
do
	if test $n -ne $#
	then
		# creiamo/azzeriamo il file temporaneo
		# echo DEBUG-fase $n per la gerarchia $G
		# invochiamo il file comandi ricorsivo con la gerarchia, il numero X e il file temporaneo corrente
		FCR.sh $G $X /tmp/nomiAssoluti
	fi
	n=`expr $n + 1`		# n++
done

# output numero totale directory trovate
echo Numero totale delle gerarchie che rispettano i requisiti: `wc -l < /tmp/nomiAssoluti`

# terminate tutte le ricerche ricorsive cioe' le N fasi, dobbiamo procedere con il confronto richiesto
for curr_dir in `cat  /tmp/nomiAssoluti`	# per ogni directory trovata
do
	echo Analizzando la directory $curr_dir
	for curr_file in `ls $curr_dir`
	do
		echo file trovato: $curr_file. Riga numero $X partendo dalla fine: `tail -$X $curr_dir/$curr_file | head -1`
	done
done

# pulizia file temporaneo
rm /tmp/nomiAssoluti
