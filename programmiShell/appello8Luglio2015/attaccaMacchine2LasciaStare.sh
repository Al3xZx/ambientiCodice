#!/bin/bash
#=========================================================================#
##########################= Funzioni =#####################################
#=========================================================================#
function attack() {
  ip=$(echo $1 | sed 's/\.//g')
  let ris=($ip+$RANDOM)%2
  echo $ris
}

function eseguiAttacco() {
  #$1=ip $2=file $3=cartella
  for i in $1;do
    echo $i
    ris=$(attack $i);
    if(($ris == 1));then
      echo "**attacco a $i avvenuto con successo"
      echo $i >> $2;
    else
      echo "##attacco a $i fallito"
    fi
  done
  nomeFile=$(echo $2 | sed 's_.*/__')
  if [ -f $3/$nomeFile ];then
    nome=$(echo $nomeFile | sed 's/\..*//')
    est=$(echo $nomeFile | sed 's/.*\./\./')
    cp $2 $3/$nome'(copia)'$est
  else
    cp $2 $3
  fi
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
    #echo $n
    continue;
  fi
  if((n>0));then
    ip=$ip''$l' ';
    #echo $ip
    let n=$n-1;
    #echo $n
    continue;
  fi
  if((n==0));then
    file=$l;
    #echo $l;
    if [ -f $file ];then
      echo -n > $file;#pulisco il file
      #echo "sto passando $ip $file $1"
      #eseguiAttacco $ip $file $1
      for i in $ip;do
        #echo $i
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
        data=$(date +%F'_'%T)
        cp $file $1/$nome'_'$data'(copia)'$est
      else
        cp $file $1
      fi
    else
      echo "il file $file non esiste vuoi crearlo y o n>>"
      read scelta
      if [ $scelta == y ];then
        echo "creo il file $file"
        touch $file;
        #eseguiAttacco $ip $file $1
        for i in $ip;do
          #echo $i
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
          data=$(date +%F'_'%T)
          cp $file $1/$nome'_'$data'(copia)'$est
        else
          cp $file $1
        fi
      fi
    fi
    let n=-1;
    ip=''
    #echo $n
  fi
done
echo "script terminato!"
exit 0
