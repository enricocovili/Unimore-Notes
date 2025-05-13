#!/bin/bash

cd $1

NR=

found=false

for i in *
do
	if test -f $i -a -r $i
	then
		NR=`wc -l < $i`
		if test $NR -eq $2
		then
			# file found
			echo `pwd`/$1 >> $3
			found=true
		fi
	fi
done

if test $found = true
then
	echo `pwd` trovata
fi

# recursive call

for i in *
do
	if test -d $i -a -r $i
	then
		$0 `pwd`/$i $2 $3
	fi
done
