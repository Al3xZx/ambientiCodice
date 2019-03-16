#!/bin/bash
listaCartelle=$(cat $1)
k=0;
for linea in $listaCartelle;do
  echo $linea $k
  let k=($k+1)%2
done
