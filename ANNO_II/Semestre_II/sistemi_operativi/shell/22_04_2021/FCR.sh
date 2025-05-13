#!/bin/sh

# $1 = dir corrente, $2 = Estensione da cercare, $3 file temporaneo

cd $1

for F in *	#per ogni elemento della directory corrente, F nome indicato nella consegna
do
	if test -f $F
	then
		case $F in
		*.$2)	echo $1 >> $3 # Trovato un match. posso terminare il loop dopo aver aggiornato il file temporaneo
			break;;
		*)	;; # ignora
		esac
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
