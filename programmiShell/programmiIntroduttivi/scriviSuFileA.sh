#!/bin/bash
#legge come parametri n volte scrivere "a" e il file sul quale scriverlo
if [ $# -ne 2 ];then
  echo "uso: $0 <numero volte> <file>"
else
  if [ ! -e $2 ];then
    echo "creo il file perchè non esiste"
    touch $2;
  fi
  i=0
  while [ $i -lt $1 ];do
    echo "a" >> $2
    let i=$i+1
  done
fi
