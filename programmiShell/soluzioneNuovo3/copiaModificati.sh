#!/bin/bash
if(($#!=3));then
  echo "uso: $0 <fileDaCopiare.txt> <cartellaOut> <cartellaIn>"
  exit 1
fi
if [ ! -f $1 ];then
  echo "il file $1 non esiste"
  exit 2
fi
if [ ! -d $2 ];then
  echo "la cartella $2 non esiste"
  exit 3
fi
if [ ! -d $3 ];then
  echo "la cartella $3 non esiste"
  exit 4
fi
numeroFile=0;
touch fileCopiati;
for file in $(cat $1);do
  if [ -f $2/$file ];then
    if [[ $file != *.exe ]];then
      if [ -f $3/$file ];then
        echo "il file $file è presente in $3 vuoi sostituito? y o n"
        read consenso;
        if [ $consenso == y ];then
          echo "*** il file $file verrà sovrascritto ***"
          cp $2/$file $3/$file;
          let numeroFile=$numeroFile+1;
          echo $file >> fileCopiati;
        else
          echo "### il file $file non è stato sostituito ###"
        fi
      else
        cp $2/$file $3/$file;
        let numeroFile=$numeroFile+1;
        echo $file >> fileCopiati;
      fi
    else
      echo "***non copio $file perchè ha estensione .exe***"
    fi
  fi
done
echo " il numero di file copiati è: $numeroFile e sono:"
for f in $(cat fileCopiati);do
  echo $f
done
rm fileCopiati
