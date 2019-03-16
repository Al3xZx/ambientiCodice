#!/bin/bash
if [ $# -ne 3 ];then
  echo "uso: $0 <numeroVolte> <file> <stringa>"
else
  i=0;
  while(($i<$1));do
    echo $3 >> $2
    let i=$i+1;
  done
fi
