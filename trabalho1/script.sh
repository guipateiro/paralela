#!/bin/bash  
echo "" > saida.txt
echo "" > debug.txt
for i in 1 2 3 4 5 6 7 8 9; do
    for j in 1 2 3 4 5 6 7 8 9; do
        timeout 5 ./teste $i $j
        VAR=$?
        if [ $VAR -eq 1 ]; then
            echo "$i $j ok" >> saida.txt
        elif [ $VAR -eq 2 ]; then
            echo "$i $j erro" >> saida.txt
        else 
            echo "$i $j TEMPO" >> saida.txt   
        fi    
    done
done            