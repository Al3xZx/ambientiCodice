#!/bin/bash
if [ -d $1 ];then
  rm -r $1
fi
mkdir $1
i=0;
cd $1
touch test.txt
while(($i<10));do
  if((($i%2)==0));then
    mkdir 'dir'$i
    cd 'dir'$i
    j=0
    while(($j<5));do
      if(($j%2 == 0));then
        touch 'file'$i'.exe'
      else
        touch 'file'$i'.txt'
      fi
      let j=$j+1
    done
    cd ..
  else
    echo "indicare nome file >>"
    read nomeFile
    touch $nomeFile
  fi
  let i=$i+1;
done
