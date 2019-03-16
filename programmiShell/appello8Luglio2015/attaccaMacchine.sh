#!/bin/bash
#=========================================================================#
##########################= Funzioni =#####################################
#=========================================================================#
function attack() {
  ip=$(echo $1 | sed 's/\.//g')
  let ris=($ip+$RANDOM)%2
  echo $ris
}
#=========================================================================#
##########################= Programma =####################################
#=========================================================================#
#$1=cartella $2=file
if(($# != 2));then
  echo "uso: $0 <dir1> <file>"
  exit 1
fi
if [ ! -d $1 ];then
  echo "$1 non esiste"
  exit 2
fi
if [ ! -f $2 ];then
  echo "$2 non esiste"
  exit 2
fi
n=-1; ip='';
for l in $(cat $2);do
  if((n<0));then
    let n=$l
    continue;
  fi
  if((n>0));then
    ip=$ip''$l' ';
    let n=$n-1;
    continue;
  fi
  if((n==0));then
    file=$l;
    echo -n > $file;#pulisco il file
    for i in $ip;do
      ris=$(attack $i);
      if(($ris == 1));then
        echo "**attacco a $i avvenuto con successo"
        echo $i >> $file;
      else
        echo "##attacco a $i fallito"
      fi
    done
    nomeFile=$(echo $file | sed 's_.*/__')
    if [ -f $1/$nomeFile ];then
      nome=$(echo $nomeFile | sed 's/\..*//')
      est=$(echo $nomeFile | sed 's/.*\./\./')
      data=$(date +%F'_'%T':'%N)
      cp $file $1/$nome'_'$data'(copia)'$est
    else
      cp $file $1
    fi
    let n=-1;
    ip=''
  fi
done
echo "script terminato!"
exit 0
