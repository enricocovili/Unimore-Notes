#!/bin/sh

# File comandi ricorsivo
# $0 = nome del file comandi, $1 = dir corrente, $2 = F (nome file semplice), $3 = Nome file temporaneo
cd $1

#la variabile NR ci serve per il numero di linee
NR=

for F in *	#per ogni elemento della directory corrente, F nome indicato nella consegna
do
	# controllo solo file e che siano leggibili
	if test -f $F -a -r $F
	then
		NR=`wc -l < $F`
		if test $NR -ge 4 -a $F = $2	# se il numero di linee e' >= 4 e il nome del file è F
		then
			# trovato un file che soddisfa le specifiche e quindi inseriamo il suo nome assoluto nel file temporaneo insieme al numero righe
			echo `pwd`/$F $NR >> $3
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
