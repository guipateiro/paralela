#preguissa
CC = mpicc -O3
EXE = base

all: $(EXE).c
	$(CC) $(EXE).c -g -o $(EXE)

run: all
	mpirun -np 2 ./$(EXE)

entrada:
	gcc -o entrada geraentrada.c -Wall

media: media.cpp
	g++ -o media media.cpp -Wall

clear: 
	rm -f $(EXE)	

purge: clear	