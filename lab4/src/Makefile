CC=gcc
CFLAGS=-lpthread

all: sem_example cond_example

sem_example: sem_example.o
	$(CC) sem_example.o -o sem_example $(CFLAGS) 
sem_example.o: sem_example.c
	$(CC) -c sem_example.c

cond_example: cond_example.o
	$(CC) cond_example.o -o cond_example $(CFLAGS) 
cond_example.o: cond_example.c
	$(CC) -c cond_example.c

clean: 
	rm -f sem_example sem_example.o cond_example cond_example.o





