#! /bin/bash
#Scrivere un programma che riceve come argomenti
#una parola e un file e verifica quante volte la parola è
#presente in tale file
#Esempio: conta_parole casa file_testo
#Restituisce quante volte la parola casa è presente in
#file testo
if [ $# -ne 2 ];then
    echo uso: $0 parole file_testo
    exit 1
fi
if [ ! -f $2 -o ! -r $2 ]; then
    echo file non disponibile
    exit 2
fi
testo=$(cat $2)
cont=0
for parola in $testo;do
    if [ $parola == $1 ];then
        let cont=$cont+1
    fi
    echo $parola
done
echo nel file sono presenti $cont occorrenze della parola $1
exit 0
