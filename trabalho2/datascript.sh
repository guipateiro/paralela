#!/bin/bash
make entrada
make
mkdir -p data
echo 1048576 | ./entrada > input.in
#for ((i = 1048576; i <= 1048576 ; i*=2)) # tamanho da entrada
#do
#    for ((j = 32; j >= 1; j/=2)) # num de threads
#    do
#        FILE="thread${j}_board${i}-128.txt"
#        echo "Preenchendo data/${FILE}..."
#        > data/128/${FILE} # apaga o conteudo dos arquivos
#        for ((NUMTIMES = 1; NUMTIMES <= 20; NUMTIMES++)) # num de execucoes do programa
#        do
#           mpirun -np $j ./base input.in $i 128 >> data/128/${FILE}
#        done
#    done
#
#    for ((j = 32; j >= 1; j/=2)) # num de threads
#    do
#        FILE="thread${j}_board${i}-16k.txt"
#        echo "Preenchendo data/${FILE}..."
#        > data/16k/${FILE} # apaga o conteudo dos arquivos
#        for ((NUMTIMES = 1; NUMTIMES <= 20; NUMTIMES++)) # num de execucoes do programa
#        do
#            mpirun -np $j ./base input.in $i 16374 >> data/16k/${FILE}
#        done
#    done
#
#	for ((j = 32; j >= 1; j/=2)) # num de threads
#    do
#        FILE="thread${j}_board${i}-2048.txt"
#        echo "Preenchendo data/${FILE}..."
#        > data/2048/${FILE} # apaga o conteudo dos arquivos
#        for ((NUMTIMES = 1; NUMTIMES <= 20; NUMTIMES++)) # num de execucoes do programa
#        do
#            mpirun -np $j ./base input.in $i 2048 >> data/2048/${FILE}
#        done
#    done
#    
#done

for ((i = 524288; i <= 1048576 ; i*=2)) # tamanho da entrada
do
	 for ((j = 32; j >= 1; j/=2)) # num de threads
    do
        FILE="thread${j}_board${i}-32k.txt"
        echo "Preenchendo data/${FILE}..."
        > data/32k/${FILE} # apaga o conteudo dos arquivos
        for ((NUMTIMES = 1; NUMTIMES <= 20; NUMTIMES++)) # num de execucoes do programa
        do
            mpirun -np $j ./base input.in $i 32768 >> data/32k/${FILE}
        done
    done


done
