all:    passeio.c
	gcc passeio.c -o teste -fopenmp -Wall -g

clean: 
	rm -f teste


