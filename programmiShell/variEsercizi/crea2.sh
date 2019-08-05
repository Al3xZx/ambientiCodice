#!/bin/bash
# crea nomefile dimensione ciao
#  $0     $1        $2      $3
if [ $# -ne 3 ]; then
    echo uso: $0 nomeFile dimensione stringa
    exit 1
fi
touch $1
x=0
while [ $x -lt $2 ]; do
    echo $3 >> $1
    let x=$x+1
done
echo finito
exit 0
