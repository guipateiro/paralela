CFLAGS = -fopenmp -Wall -g -B passeio.c

all:    passeio.c
	gcc passeio.c -o teste $(CFLAGS)

time: CFLAGS += -DTIMEONLY
time: all

clean: 
	rm -f teste


