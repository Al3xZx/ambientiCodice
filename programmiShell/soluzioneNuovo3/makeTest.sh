#!/bin/bash
touch listaFile.txt
mkdir origine
mkdir destinazione
i=0;
while(($i < 10));do
  echo -n "inserisci il nome del file da creare>> "
  read nomefile
  echo $nomefile >> listaFile.txt
  touch origine/$nomefile
  let i=$i+1;
done
