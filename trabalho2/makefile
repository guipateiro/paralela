#preguissa
CC = mpicc
EXE = base

all: $(EXE).c
	$(CC) $(EXE).c -g -o $(EXE)

run: all
	mpirun -np 2 ./$(EXE)

entrada:
	gcc -o entrada geraentrada.c -Wall

clear: 
	rm -f $(EXE)	