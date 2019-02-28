
CC=gcc
CFLAGS=-lpthread

all: ex1 t1 t2 t3

ex1: ex1.o
	$(CC) ex1.o -o ex1 $(CFLAGS) 

ex1.o: ex1.c
	$(CC) -c ex1.c

t1: t1.o
	$(CC) t1.o -o t1 $(CFLAGS) 
t1.o: t1.c
	$(CC) -c t1.c

t2: t2.o
	$(CC) t2.o -o t2 $(CFLAGS) 
t2.o: t2.c
	$(CC) -c t2.c 

t3: t3.o
	$(CC) t3.o -o t3 $(CFLAGS) 
t3.o: t3.c
	$(CC) -c t3.c  

clean: 
	rm -f ex1 t1 t2 t3 ex1.o t1.o t2.o t3.o