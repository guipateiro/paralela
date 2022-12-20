#!/bin/bash
make media
mkdir -p estatistica
> estatistica/tabela00.txt 
for ((j = 32; j >= 1; j/=2)) # num de threads
do
    FILEOUT="thread${j}-00.txt"
    > estatistica/${FILEOUT} # apaga o conteudo dos arquivos
    for ((i = 5; i <= 7; i++)) # tamanho dos tabuleiros n x n
    do
        FILEIN="thread${j}_board${i}-00.txt"
        ./media < data/${FILEIN} >> estatistica/${FILEOUT} 
    done
    
done
cd estatistica
paste -d ";" thread1-00.txt thread2-00.txt thread4-00.txt thread8-00.txt thread16-00.txt thread32-00.txt > tabela00.csv
> tabelaN2.txt 
cd ..

for ((j = 32; j >= 1; j/=2)) # num de threads
do
    FILEOUT="thread${j}-N2.txt"
    > estatistica/${FILEOUT} # apaga o conteudo dos arquivos
    for ((i = 5; i <= 7; i++)) # tamanho dos tabuleiros n x n
    do
        FILEIN="thread${j}_board${i}-ndiv2.txt"
        ./media < data/${FILEIN} >> estatistica/${FILEOUT}
    done
    
done
cd estatistica
paste -d ";" thread1-N2.txt thread2-N2.txt thread4-N2.txt thread8-N2.txt thread16-N2.txt thread32-N2.txt > tabelaN2.csv
rm -rf *.txt
cd .. 

