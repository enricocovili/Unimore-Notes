#!/bin/sh

# File comandi ricorsivo che scrive il nome delle directory che rispettano le due condizoni della consegna

cd $1

#la variabile NR ci serve per il numero di linee
NR=
flag=true # questa variabile indica se la directory rispetta le due condizioni

for F in *	# per ogni elemento della directory corrente
do
	# controllo solo file e che siano leggibili
	if test ! -f $F -o ! -r $F
	then
		flag=false
		break
	fi
	NR=`wc -l < $F`
	if test $NR -le $2	# se il numero di linee e' strettamente maggiore di $2
	then
		flag=false
		break
	fi
done

if test $flag = true
then
	echo `pwd` >> $3 # salvo nel file temporaneo se la dir rispetta tutte le caratteristiche
fi

for i in *
do
	# effettuo la ricerca solo se i è una directory ed è traversabile
	if test -d $i -a -x $i
	then
		# chiamata ricorsiva con path assoluto della directory individuata
		FCR.sh `pwd`/$i $2 $3
	fi
done
