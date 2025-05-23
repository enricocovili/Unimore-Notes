#!/bin/sh

# controllo sul numero dei parametri N >= 2 e quindi N+1 >=3
case $# in
0|1|2)  echo Errore: il numero parametri deve essere maggiore o uguale a 3, mentre ne hai passati $# - Usage is $0 \<dir_assoluta\> \<dir_assoluta\> ...  \<string\>
	exit 1;;
*) 	echo Numero parametri $# è ok ;;
esac

# E' possibile fare i controlli sui nomi assoluti e sulle directory in un for
n=1 # tenuto per l'ultima stringa
S= # contiene l'ultimo parametro
for G 	# usiamo il nome G specificato nella consegna
do
	if test $n -ne $# # ignoro l'ultimo parametro stringa
	then
		case $G in
		/*) 	if test ! -d $G -o ! -x $G
	    		then
	    			echo Errore: $G non directory o non attraversabile
	    			exit 3
	    		fi;;
		*)  	echo Errore: $G non nome assoluto; exit 4;;
		esac
	else
		S=$G
	fi
	n=`expr $n + 1`
done

# I parametri sono OK. passo alle N fasi, dopo aver modificato PATH per poter usare il file comandi FCR.sh
PATH=`pwd`:$PATH
export PATH

n=1 # indicatore della fase attuale. necessario per creare i file temporanei
for G	# G nome indicato nel testo. itera sempre nei parametri passati
do
	> /tmp/nomiAssoluti-$n 	#creiamo/azzeriamo ogni file temporaneo, usando come parte iniziale del nome quello specificato nel testo!
	echo DEBUG-fase $n per la gerarchia $G
	# invochiamo il file comandi ricorsivo con la gerarchia, il numero X e il file temporaneo corrente
	FCR.sh $G $X /tmp/nomiAssoluti-$n   
	# la specifica indicava che doveva essere riportato su standard output il conteggio di OGNI SINGOLA gerarchia!
	echo Il numero di file trovati in questa fase e\' `wc -l < /tmp/nomiAssoluti-$n`
	n=`expr $n + 1`		# n++
done

# terminate tutte le ricerche ricorsive cioe' le Q fasi, dobbiamo procedere con il confronto richiesto
for file1 in `cat  /tmp/nomiAssoluti-1`	# per ogni file trovato nella prima gerarchia
do
	n=1 	# idem come prima
	for i	#per ognuna delle gerarchie
	do
		if test $n -gt 1	#saltiamo il file temporaneo della prima gerarchia
		then
			for file2 in `cat  /tmp/nomiAssoluti-$n` #per ogni file trovato nelle altre gerarchie
			do
				# uso diff che riporta 0 se i file sono uguali, altrimenti un numero diverso da 0
				# la ridirezione dello standard output che dello standard error su /dev/null
				if diff $file1 $file2 > /dev/null 2>&1
				then
					echo I file $file1 e $file2 sono uguali
				fi
			done
		fi
		n=`expr $n + 1` # n++
	done
done

# pulizia file temporanei
rm /tmp/nomiAssoluti-* # * l'uso dell'asterisco ci risparmia un for aggiuntivo
