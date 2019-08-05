#! /bin/bash
#Scrivere un programma che riceva come argomento
#(da linea di comando) il nome di un file ed il nome di
#una directory, e sposti il file nella directory:
#Ad esempio:
# sposta fileA directoryB
if [ $# -ne 2 ]; then
    echo uso: sposta file cartella
    exit 1
fi
if [ ! -f $1 ]; then
    echo $1 non è un file
    exit 2
fi
if [ ! -d $2 ]; then
    echo $2 non è una cartella
    exit 3
fi
echo operazione in corso....
sleep 2
mv $1 $2
echo operazione conclusa con successo
exit 0
