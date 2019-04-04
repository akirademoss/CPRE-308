

CC=gcc
CFLAGS=-lpthread

all: threaded_count

threaded_count: threaded_count.o
	$(CC) threaded_count.o -o threaded_count $(CFLAGS) 
threaded_count.o: threaded_count.c
	$(CC) -c threaded_count.c

clean: 
rm -f threaded_count threaded_count.o
