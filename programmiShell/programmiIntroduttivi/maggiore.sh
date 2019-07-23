#!/bin/bash
if [ $# -ne 1 ];then
  echo "uso: $0 <numero>"
else
  if (($1 >= 10));then
    echo "$1 è maggiore di 10"
  else
    echo "$1 non è maggiore di 10"
  fi
fi
