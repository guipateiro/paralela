#!/bin/bash
make media
mkdir -p estatistica
for ((j = 32; j >= 1; j/=2)) # num de threads
do
    FILEOUT="thread${j}-2048.txt"
    > estatistica/${FILEOUT} # apaga o conteudo dos arquivos
    echo "${j}" >> estatistica/${FILEOUT}
    for ((i = 16384; i <= 1048576 ; i*=2)) # tamanho dos tabuleiros n x n
    do
        FILEIN="thread${j}_board${i}-2048k.txt"
        ./media < data/2048/${FILEIN} >> estatistica/${FILEOUT} 
    done
    
done
cd estatistica
paste -d ";" ../data/header.txt thread1-2048.txt thread2-2048.txt thread4-2048.txt thread8-2048.txt thread16-2048.txt thread32-2048.txt > tabela2048.csv
cd ..

#for ((j = 32; j >= 1; j/=2)) # num de threads
#do
#    FILEOUT="thread${j}-16k.txt"
#    > estatistica/${FILEOUT} # apaga o conteudo dos arquivos
#    echo "${j}" >> estatistica/${FILEOUT}
#    for ((i = 16384; i <= 1048576 ; i*=2)) # tamanho dos tabuleiros n x n
#    do
#        FILEIN="thread${j}_board${i}-16k.txt"
#        ./media < data/${FILEIN} >> estatistica/${FILEOUT}
#    done
#    
#done
cd estatistica
#paste -d ";" ../data/header.txt thread1-16k.txt thread2-16k.txt thread4-16k.txt thread8-16k.txt thread16-16k.txt thread32-16k.txt > tabela16k.csv
rm -rf *.txt
cd .. 

