CFLAGS = -fopenmp -Wall -g -B passeio.c

all:    passeio.c
	gcc passeio.c -o teste $(CFLAGS)

media:
	g++ -o media media.cpp

time: CFLAGS += -DTIMEONLY
time: all

clean: 
	rm -f teste


