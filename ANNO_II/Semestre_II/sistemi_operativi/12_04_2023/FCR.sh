#!/bin/sh

# File comandi ricorsivo che esplora le gerarchie. Argomenti:
# $1 = dir corrente, $2 = prima estensione (stringa), $3 = seconda estensione (stringa). $4 = primo file temporaneo, $5 = secondo file temporaneo
cd $1

for F in *	#per ogni elemento della directory corrente, F nome indicato nella consegna
do
	# controllo solo file e che siano leggibili
	if test -f $F -a -r $F
	then
		case $F in
		*.$2) echo `pwd`/$F >> $4;; # controlli rispettivi sulle estensioni
		*.$3) echo `pwd`/$F >> $5;;
		*) ;; # ignora. file non rispetta le condizioni
		esac
	fi
done

for i in *
do
	# effettuo la ricerca solo se i è una directory ed è traversabile
	if test -d $i -a -x $i
	then
		# chiamata ricorsiva con path assoluto della directory individuata
		FCR.sh `pwd`/$i $2 $3 $4 $5
	fi
done
