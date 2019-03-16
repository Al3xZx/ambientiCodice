#!/bin/bash
uso="uso $0 <ext1> <ext2> <dir>"
if(($#!=3));then
  echo $uso;
  exit 1;
fi
if [ ! -d $3 ];then
  echo $uso;
  exit 1;
fi

eliminati=0
rimanenti=0
cd $3;
lFile=$(ls *.$1)
for file in $lFile;do
  fex2=$(echo $file | sed 's/'$1'$/'$2'/')
  if [ ! -f $fex2 ];then
    rm $file;
    let eliminati=$eliminati+1;
  else
    let rimanenti=$rimanenti+1;
  fi
done
echo "il numero dei file $1 eliminati è $eliminati
il numero dei file $1 rimanenti è $rimanenti"
exit 0
