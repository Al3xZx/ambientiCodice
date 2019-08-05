#!/bin/bash
mkdir prog_c
mkdir prog_java
mkdir programmi
numeroFile=20
i=0
rd=0
while [ $i -lt $numeroFile ]; do
    let rd=$RANDOM%2
    if (($i%2==0));then
        touch "./programmi/file_$i.c"
    else
        touch "./programmi/file_$i.java"
    fi
    echo $rd
    if [ $rd -eq 0 ];then
        touch "./programmi/file_$i.txt"
    fi
    let i=$i+1
done
