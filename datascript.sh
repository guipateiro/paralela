#!/bin/bash
make time
mkdir -p data
for ((i = 7; i <= 7; i++)) # tamanho dos tabuleiros n x n
do
    for ((j = 32; j >= 1; j/=2)) # num de threads
    do
        FILE="thread${j}_board${i}-00.txt"
        echo "Preenchendo data/${FILE}..."
        > data/${FILE} # apaga o conteudo dos arquivos
        for ((NUMTIMES = 1; NUMTIMES <= 20; NUMTIMES++)) # num de execucoes do programa
        do
            echo $i $i $[0] $[0] | ./teste $j >> data/${FILE}
        done
    done

    for ((j = 32; j >= 1; j/=2)) # num de threads
    do
        FILE="thread${j}_board${i}-ndiv2.txt"
        echo "Preenchendo data/${FILE}..."
        > data/${FILE} # apaga o conteudo dos arquivos
        for ((NUMTIMES = 1; NUMTIMES <= 20; NUMTIMES++)) # num de execucoes do programa
        do
            echo $i $i $[$i/2] $[$i/2] | ./teste $j >> data/${FILE}
        done
    done
    
done
