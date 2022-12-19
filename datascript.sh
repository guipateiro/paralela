#!/bin/bash
make time
mkdir -p data
for ((i = 5; i <= 8; i++)) # tamanho dos tabuleiros n x n
do
    for ((j = 1; j <= 16; j*=2)) # num de threads
    do
        FILE="thread${j}_board${i}.txt"
        echo "Preenchendo data/${FILE}..."
        > data/${FILE} # apaga o conteudo dos arquivos
        for ((NUMTIMES = 1; NUMTIMES <= 10; NUMTIMES++)) # num de execucoes do programa
        do
            echo $i $i $[ $RANDOM % $i] $[ $RANDOM % $i] | ./teste $j >> data/${FILE}
        done
    done
done
