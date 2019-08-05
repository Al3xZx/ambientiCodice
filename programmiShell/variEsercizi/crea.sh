#! /bin/bash
# crea nomeFile N
#   $0    $1   $2

if [ $# -ne 2 ];then
    echo uso: crea nomeFile numeroDiVolte
    exit 1
fi
touch $1
i=$2
while [ $i -gt 0 ]; do
    echo test >> $1
    let i=$i-1
done
echo finito
exit 0
