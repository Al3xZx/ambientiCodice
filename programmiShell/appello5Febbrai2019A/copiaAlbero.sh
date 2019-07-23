#!/bin/bash
if(($# != 2));then
  echo "uso: $0 <dir1> <dir2>"
  exit 1
fi
if [ ! -d $1 ];then
  echo "$1 non esiste"
  exit 2
fi
if [ ! -d $2 ];then
  echo "$2 non esiste"
  exit 2
fi
for e in $(ls $1);do
  if [ -f $1/$e ];then
    if [[ $e != *.exe ]];then
      cp $1/$e $2
    else
      nome=$(echo $e | sed 's/\..*$/.sh/')
      cp $1/$e $2/$nome
    fi
  else
    if [ -d $1/$e ];then
      mkdir $2/$e 2>/dev/null
      for f in $(ls $1/$e);do
        nomeFile=$(echo $f | sed 's_.*/__')
        if [ -f $1/$nomeFile -o ! -d $1/$nomeFile ];then
          if [[ $nomeFile != *.exe ]];then
            cp $1/$e/$nomeFile $2/$e;
          else
            nomeMod=$(echo $nomeFile | sed 's/\..*$/.sh/')
            cp $1/$e/$nomeFile $2/$e/$nomeMod
          fi
        fi
      done
    fi
  fi
done
