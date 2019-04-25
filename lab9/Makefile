CC=gcc
CFLAGS=

all: bsdump bytedump


bytedump: bytedump.o 
	$(CC) bytedump.o -o bytedump

bsdump: bsdump.o 
	$(CC) bsdump.o -o bsdump


bsdump.o: bsdump.c
	$(CC) -c bsdump.c

bytedump.o: bytedump.c
	$(CC) -c bytedump.c

clean: 
	rm bsdump.o
	rm bytedump.o
	rm bsdump
	rm bytedump
