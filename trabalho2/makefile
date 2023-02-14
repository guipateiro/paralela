#preguissa
CC = mpicc
EXE = base

all: $(EXE).c
	$(CC) $(EXE).c -o $(EXE)

run: all
	mpirun -np 2 ./$(EXE)

entrada:
	gcc -o entrada geraentrada.c -Wall

media: media.cpp
	g++ -o media media.cpp -Wall

clear: 
	rm -f $(EXE)	
	rm -f *.o

purge: clear	
