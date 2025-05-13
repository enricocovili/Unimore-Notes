#!/bin/sh

# File comandi ricorsivo che scrive il nome dei file trovati sul file temporaneo il cui nome e' passato come terzo argomento

# $1 = dir corrente, $2 = carattere, $3 = file temporaneo
cd $1
echo $1

case $1 in
*/$2?$2)	echo $1 >> $3;; # salvo il risultato nel file (3 caratteri, i dispari = a C)
*) ;;
esac

for i in *
do
	# effettuo la ricerca solo se i è una directory ed è traversabile
	if test -d $i -a -x $i
	then
		# chiamata ricorsiva con path assoluto della directory individuata
		FCR.sh `pwd`/$i $2 $3
	fi
done
