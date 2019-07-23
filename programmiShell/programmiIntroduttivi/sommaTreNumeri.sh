#!/bin/bash
if [ $# -ne 3 ];then
  echo "uso: $0 <numero> <numero> <numero>"
else
  somma=0;
  for i in $@;do
    let somma=$somma+$i;
  done
  echo "la somma è: $somma"
fi
