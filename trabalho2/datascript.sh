#!/bin/bash
make entrada
make
mkdir -p data
echo 1048576 | ./entrada > input.in
for ((i = 16384; i <= 1048576 ; i*=2)) # tamanho da entrada
do
    for ((j = 4; j >= 1; j/=2)) # num de threads
    do
        FILE="thread${j}_board${i}-128.txt"
        echo "Preenchendo data/${FILE}..."
        > data/${FILE} # apaga o conteudo dos arquivos
        for ((NUMTIMES = 1; NUMTIMES <= 20; NUMTIMES++)) # num de execucoes do programa
        do
           mpirun -np $j ./base input.in $i 128 >> data/${FILE}
        done
    done

    for ((j = 4; j >= 1; j/=2)) # num de threads
    do
        FILE="thread${j}_board${i}-16k.txt"
        echo "Preenchendo data/${FILE}..."
        > data/${FILE} # apaga o conteudo dos arquivos
        for ((NUMTIMES = 1; NUMTIMES <= 20; NUMTIMES++)) # num de execucoes do programa
        do
            mpirun -np $j ./base input.in $i 16384 >> data/${FILE}
        done
    done
    
done
