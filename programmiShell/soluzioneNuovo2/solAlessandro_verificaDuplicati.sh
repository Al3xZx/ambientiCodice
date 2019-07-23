#!/bin/bash
if(($#!=2));then
  echo "uso: $0 <fileCoppieCartelle> <fileOutput>"
  exit 1
fi
if [ ! -f $1 ];then
  echo "il file $1 non esiste"
  exit 1
fi
if [ -f $2 ];then
  echo "il file $2 esiste già dunque verrà sovrascritto"
  echo -n > $2
fi
listaC=$(cat $1)
k=0;
for cartella in $listaC;do
  if((k == 0));then
    #echo "creo lista file cartella $cartella"
    cartA=$(ls $cartella);
  else
    cartB=$cartella;
    #echo "verifico cartella $cartella"
    for file in $cartA;do
      if [ -f $cartB/$file ];then
        echo "il file $file esiste nella cartella $cartB, verrà riportato in $2"
        echo "$file $cartB" >> $2
      #else
        #echo "il file $file non è nella cartella $cartB"
      fi

    done
  fi
  #incremento modulare di k
  let k=($k+1)%2;
done
