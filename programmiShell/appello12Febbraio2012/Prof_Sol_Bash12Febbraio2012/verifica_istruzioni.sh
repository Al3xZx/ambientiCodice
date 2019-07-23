if [ $# -ne 3 ]; then
	echo "Errore! Istruzione: $0 [file] [dirA] [dirB]"
	exit 1
fi
if [ ! -f $1 ]; then
	echo "$1 non è un file!"
	exit 2
fi
if [ ! -d $2 ]; then
	echo "$2 non è una directory!"
	exit 2
fi
if [ ! -d $3 ]; then
	echo "$3 non è una directory!"
	exit 2
fi
files=$(cat $1)
count=0
doc=''
h=''
t=''
for i in $files ; do
	if [ $count -eq 0 ]; then
		doc=$i
		let count=$count+1
		continue
	fi
	if [ $count -eq 1 ]; then
		h=$i
		let count=$count+1
		continue
	fi
	if [ $count -eq 2 ]; then
		t=$i
		count=0
		if [ -f $2/$doc ]; then
			tmp=$(echo $doc | sed -e 's/\.txt//g')
			newFile="$tmp"_"$h"_"$t.txt"
			if [ -f $3/$newFile ]; then
				echo echo "File $newFile già esistente"
			else
				touch $3/$newFile
				head -n $h $2/$doc >> $3/$newFile
				tail -n $t $2/$doc >> $3/$newFile
			fi
		else
			echo "$doc non presente in $2"
		fi
	fi
done
echo "Script terminato!"
