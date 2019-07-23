#!/usr/bin/env bash

# Scrivere un programma shell (elimina_foto.sh) che riceva 3 parametri, i primi due sono i nomi di estensioni di foto
# (esempio jpg, gif), il terzo � il nome di una cartella (esempio cart_foto)
# Esempio d'uso sar� quindi: elimina_foto.sh jpg gif cart_foto.
# Il programma dovr� eliminare tutte le foto (contenute nella cartella cart_foto) con estensione jpg per le quali non
# esiste il corrispondente file gif (esempio: se nella cartella sono presenti i file:
# a.jpg b.jpg c.jpg d.jpg e.jpg a.gif c.gif e.gif, dovranno essere eliminati i file b.jpg d.jpg.
# Alla fine il programma dovr� stampare il numero di file eliminati e il numero di jpeg rimanenti.
# Gestire anche il controllo degli errori (parametri insufficienti, file di output gi� esistente, cartella inesistente, ecc..).

USAGE="Usage: $0 jpg gif cart_foto"

if [ $# -ne 3 -o ! -d $3 ]; then
    echo $USAGE
    exit 1
fi

EXT1=$1
EXT2=$1
CARTELLA=$3

numeroFileEliminati=0
esistenti=0


cd $CARTELLA
for f in $(ls *.$EXT1); do
    f2=$(echo -n "$f" | sed 's/'$EXT1'$/'$EXT2'/')
    if [ ! -f $f2 ]; then
        echo "elimino $f"
        rm -f $f
        let numeroFileEliminati=numeroFileEliminati+1
    else
        let esistenti=esistenti+1
    fi
done

echo "file eliminati: $numeroFileEliminati"
echo "numero $EXT1 rimanenti: $esistenti"

exit 0
