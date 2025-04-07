#!/bin/sh

# File comandi ricorsivo
# $1 = directory corrente, $2 numero X, $3 file temporaneo in cui salvare i nomi dei file adatti


cd $1

#la variabile NR ci serve per il numero di linee che rispettano la richiesta
NR=

for F in *	#per ogni elemento della directory corrente, F nome indicato nella consegna
do
	# controllo solo file e che siano leggibili
	if test -f $F -a -r $F
	then
		NR=`grep -E "t$" $F | wc -l` # t$ è la regex per vedere se t è l'ultima lettera della riga
		echo DEBUG `pwd`/$F - $NR
		# wc -l in pipe ritorna il numero effettivo di match del grep
		if test $NR -eq $2	# se il numero di linee e' esattamente uguale a $2
		then
			# trovato un file che soddisfa le specifiche e quindi inseriamo il suo nome assoluto nel file temporaneo
			echo `pwd`/$F >> $3
		fi
	fi
done

for i in *
do
	# effettuo la ricerca solo se i è una directory ed è traversabile
	if test -d $i -a -x $i
	then
		# chiamata ricorsiva con path assoluto della directory individuata
		FCR.sh `pwd`/$i $2 $3
	fi
done
