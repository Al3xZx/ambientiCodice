#!/bin/bash
for i in $(ls *.$1 );do
  echo $i
done
e=$(echo testo.txt | sed 's/.*\.//')
echo $e
