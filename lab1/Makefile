CC = gcc

all: lab1

lab1: lab1.o message.o
	$(CC) lab1.o message.o -o lab1

message.o: message.c message.h
	$(CC) -c message.c

lab1.o: lab1.c message.h
	$(CC) -c lab1.c

clean:
	rm -f message.o lab1.o 
