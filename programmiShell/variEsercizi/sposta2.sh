#! /bin/bash
echo nome file:
read file
if [ ! -f $file ];then
    echo $file non è un file
    exit 1
fi
echo nome cartella:
read dir
if [ ! -d $dir ];then
    echo $dir non è un directory
    exit 2
fi
echo operazione in corso....
sleep 2
mv $file $dir
echo operazione conclusa con successo
exit 0
