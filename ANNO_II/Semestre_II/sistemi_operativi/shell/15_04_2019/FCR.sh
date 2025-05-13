#!/bin/sh

# File comandi ricorsivo che scrive il nome dei file trovati sul file temporaneo il cui nome e' passato come terzo argomento

cd $1

#la variabile NR ci serve per il numero di linee
NR=

for F in *	#per ogni elemento della directory corrente, F nome indicato nella consegna
do
	# controllo solo file e che siano leggibili
	if test -f $F -a -r $F
	then
		NR=`wc -l < $F`
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
