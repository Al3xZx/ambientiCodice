#!/bin/bash
touch listaTitoli.txt
mkdir origine
mkdir destinazione
i=0;
while(($i < 10));do
  echo -n "inserisci il nome del file da creare>> "
  read nomefile
  echo $nomefile >> listaTitoli.txt
  touch origine/$nomefile'.mp3'
  touch origine/$nomefile'.mp4'
  if((($i%2) == 0));then
    touch origine/$nomefile'.wave'
    touch origine/$nomefile'.aac'
  fi
  let i=$i+1;
done
