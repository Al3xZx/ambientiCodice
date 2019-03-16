#!/bin/bash
if [ $# -ne 2 ];then
	echo "uso $0 <fie_coppie_cartelle> <file_output>"
	exit 1
fi
if [ ! -f $1 ];then
	echo "il file delle coppie specificato non esiste!"
	exit 2
fi
if [ -f $2 ];then
	echo "il file di output specificato esiste già: verrà quindi cancellato!"
	echo -n > $2
fi
k=0
linea=$(cat $1)
for i in $linea;do
	let k=$k%2
	if [ $k -eq 0 ];then
		cartA=$(ls $i) # nella variabile cartA inserisco tutti i file che sono presenti nella cartella A
	else
		cartB=$i # nella variabile cartB inserisco SOLO il nome della cartella B
		for j in $cartA;do
			if [ -f $cartB/$j ];then
				echo "il file $j verrà riportato sul file $2"
				echo "$j si trova in $cartB" >> $2
			fi
		done
	fi
	let k=$k+1
done
