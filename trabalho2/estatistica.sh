#!/bin/bash
make media
mkdir -p estatistica

for k in 128 2048 16k 32k 
do
	for ((j = 32; j >= 1; j/=2)) # num de threads
	do
		FILEOUT="thread${j}-${k}.txt"
		> estatistica/${FILEOUT} # apaga o conteudo dos arquivos
		echo "${j}" >> estatistica/${FILEOUT}
		for ((i = 16384; i <= 1048576 ; i*=2)) # tamanho dos tabuleiros n x n
		do
			FILEIN="thread${j}_board${i}-${k}.txt"
			./media < data/${k}/${FILEIN} >> estatistica/${FILEOUT} 
		done
		
	done
	cd estatistica
	paste -d ";" ../data/header.txt thread1-${k}.txt thread2-${k}.txt thread4-${k}.txt thread8-${k}.txt thread16-${k}.txt thread32-${k}.txt > tabela-${k}.csv
	cd ..
done
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

