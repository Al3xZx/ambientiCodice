#!/bin/bash
if(($#!=3));then
  echo "uso: $0 <file> <dirOut> <dirIn>"
  exit 1;
fi
if [ ! -f $1 ];then
  echo "il file $1 non esiste"
  exit 2;
fi
if [ ! -d $3 ];then
  echo "la cartella $3 non esiste"
  exit 3;
fi
if [ ! -d $2 ];then
  echo "la cartella $2 non esiste"
  exit 4;
fi
j=0; k=0;
for i in $(cat $1);do
  let k=$j%3;
  case $k in
    0) nomeFile=$i;;
    1) p=$i;;
    2) u=$i;;
  esac
  if(($k==2));then
    if [ -f $2/$nomeFile ];then
      nome=$(echo $nomeFile | sed 's/\..*//')
      est=$(echo $nomeFile | sed 's/.*\.//')
      nuovoFile=$nome'_'$p'_'$u'.'$est;
      touch $3/$nuovoFile
      head -n $p $2/$nomeFile >> $3/$nuovoFile
      tail -n $u $2/$nomeFile >> $3/$nuovoFile
    else
      echo "il file $nomeFile non esiste"
    fi
  fi
  let j=$j+1
done
echo "Script terminato!"
