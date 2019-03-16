#!/bin/bash
#deve ricevere come primo parametro un file con ogni riga del tipo file.txt n m
#come secono una cartella dovre creare i file
j=0; k=0;
for i in $(cat $1);do
  let k=$j%3;
  case $k in
    0) nomeFile=$i;;
    1) p=$i;;
    2) u=$i;;
  esac
  if(($k==2));then
    touch $2/$nomeFile
    t=0;
    let line=$u+$p+15;
    echo $line
    while(($t<$line));do
      let l=$t+1
      echo "questa è la linea $l del file $nomeFile" >> $2/$nomeFile
      let t=$t+1
    done
  fi
  let j=$j+1
done
