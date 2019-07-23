#!/bin/bash
#riceve in imput 3 numeri come parametro
a=$1
b=$2
c=$4
s=$(somma $a $b $c)
echo $s

function somma() {
  let somma=$1+$2+$3
  echo $somma
}

string=''
i=0;
while((i<10));do
  string=$string' '$i
  let i=$i+1;
done
echo $string
