CFLAGS = -fopenmp -Wall -B passeio.c -O3

all:    passeio.c
	gcc passeio.c -o teste $(CFLAGS)

media: media.cpp
	g++ -o media media.cpp -Wall

time: CFLAGS += -DTIMEONLY
time: all

clean: 
	rm -f teste
	rm -f media


