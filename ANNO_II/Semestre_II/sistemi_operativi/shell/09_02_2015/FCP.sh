#!/bin/bash

# controllo numero parametri
case $# in
2) 	echo OK! numero parametri corretto;;
*) 	echo Numero parametri sbagliato! usage: $0 \<dir_assoluta\> \<num_positivo\>
	exit 1;;
esac

# controllo dir assoluta primo parametro (esistere e traversabile)
case $1 in
*/*) 	if test ! -d $1 -o ! -x $1
	then
		echo $1 non dir o non traversabile
	fi;;
*) 	echo $1 non è dir assoluta
	exit 2;;
esac

# controllo numero positivo secondo parametro
#Controllo secondo parametro (fatto con case): deve essere un numero intero strettamente positivo
case $2 in
*[!0-9]*) echo Errore: $2 non numerico o non positivo
	  exit 5;;
*) 	  if test $2 -eq 0
	  then 	echo Errore: secondo parametro $2 uguale a zero
		exit 6
	  fi ;;
esac

# finiti i controlli preliminari
K=$2
G=$1

# esporto PATH
PATH=`pwd`:$PATH
export PATH

# creo file temp che mi salva i match
touch /tmp/tmp$$

# chiamo ricorsione
FCR.sh $1 $2 /tmp/tmp$$
