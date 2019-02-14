CC = gcc
BIN=./bin/

all: 308sh

308sh: 308sh.o 
	$(CC) 308sh.o -o 308sh

308sh.o: 308sh.c include.h
	$(CC) -c 308sh.c

clean:
	rm -f include.o 308sh.o 
