#! /bin/bash
#Scrivere un programma che riceve come argomenti tre
#nomi di cartelle e copia tutti i file con estensione .c
#contenuti nella prima cartella nella seconda cartella e
#quelli con estensione .java nella terza cartella
#Esempio: copiafile programmi prog_c prog_java

if [ $# -ne 3 ];then
    echo uso: $0 dir dir_C dir_J
    exit 1
fi
for dir in $@; do
    if [ ! -d $dir ]; then
        echo $dir non è una directory oppure non esiste.
        exit 2
    fi
done
listaFile=$(ls $1)
for file in $listaFile;do
    case $file in
        *.c ) cp $1/$file $2;;
        *.java ) cp $1/$file $3;;
        #* ) echo il file $file non è stato copiato #facoltativo
    esac
done
