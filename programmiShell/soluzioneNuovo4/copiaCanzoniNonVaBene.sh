#!/bin/bash
if(($#!=3));then
  echo "uso: $0 <origine> <destinazione> <fileTitoli.txt>"
  exit 1;
fi
if [ ! -f $3 ];then
  echo "il file $3 non esiste"
  exit 2;
fi
if [ ! -d $1 ];then
  echo "la cartella $1 non esiste"
  exit 3;
fi
if [ ! -d $2 ];then
  echo "la cartella $2 non esiste"
  exit 4;
fi
mp3=0; aac=0;
mp4=0; wave=0; other=0;
for titolo in $(cat $3);do
  if [[ $titolo != *.* ]];then
    #echo "entro nell'if"
    for file in $(ls $1/$titolo.*);do #il comando
      cp $1/$file $2/$file;#cp va in errore perchè facendo ls $1/$titolo.*
                           #$file è una stringa del tipo origine/titolo.mp3
                           #quindi quando vado a fare cp $1/$file
                           #la bash leggerà 'origine/origine/titolo.mp3'
      est=$(echo $file | sed 's/.*\.//');
      case $est in
        mp3) let mp3=$mp3+1;;
        mp4) let mp4=$mp4+1;;
        wave) let wave=$wave+1;;
        aac) let aac=$aac+1;;
        *) let other=$other+1;;
      esac
    done
  fi
done
echo " sono stati spostati mp3=$mp3, mp4=$mp4, wave=$wave, aac=$aac, altreEstensioni=$other  "
