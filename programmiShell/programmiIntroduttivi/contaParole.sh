#!/bin/bash
#riceve come argomento una parola e un file e conta le occorrenze di tale parola
#nel file $1 parola $2 file
if [ $# -ne 2 ];then
  echo "uso: $0 <parola da cercare> <file sul quale cercare parola>"
  exit 1
fi
#verifiche su file
if [ ! -f $2 ];then
  echo "$2 non è un file oppure non esiste"
  exit 2
fi
if [ ! -r $2 ];then
  echo "non posso leggere $2"
  exit 3;
fi
#ricerca delle parole
testo=$(cat $2)
conta=0;
for i in $testo;do
  if [ $i == $1 ];then
    let conta=$conta+1;
  fi
done
echo "le occorrenze della parola $1 sono $conta"
