#!/bin/bash
#ordina i file all'interno di una cartella secondo le estensioni passate come
#parametro preceduto dal path della directory da ordinare
if (($# < 2 || $# > 5));then
  echo "uso: $0 <path della directory da usare> massimo 4 estensioni per volta"
  exit 1;
fi
#creo le cartelle all'interno di $1
i=0
for es in $@;do
  if(($i>0));then
    mkdir $1/"file_$es"
    let i=$i+1;
  fi
  let i=$i+1;
done
#creo la lista di file nella directory $1
listaFile=$(ls $1);
for file in $listaFile;do
  case $file in
    *.$2) mv $1/$file $1/"file_$2";;
    *.$3) mv $1/$file $1/"file_$3";;
    *.$4) mv $1/$file $1/"file_$4";;
    *.$5) mv $1/$file $1/"file_$5";;
    *) echo "non devo spostere $file";;
  esac
done
exit 0
