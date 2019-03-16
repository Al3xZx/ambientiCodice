#!/bin/bash
for i in $(cat $1);do
  j=0;
  while((j<3));do
    touch $i/'cart'$i'File'$j
    let j=$j+1;
  done
done
