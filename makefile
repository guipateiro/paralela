all:    passeio.c
	gcc passeio.c -o teste -fopenmp -Wall

clean: 
	rm -f teste


