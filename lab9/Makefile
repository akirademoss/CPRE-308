CC=gcc
CFLAGS=

all: bsdump bytedump fat12ls


bytedump: bytedump.o 
	$(CC) bytedump.o -o bytedump

bsdump: bsdump.o 
	$(CC) bsdump.o -o bsdump

fat12ls: fat12ls.o
	$(CC) fat12ls.o -o fat12ls


bsdump.o: bsdump.c
	$(CC) -c bsdump.c

bytedump.o: bytedump.c
	$(CC) -c bytedump.c

fat12ls.o: fat12ls.c
	$(CC) -c fat12ls.c



clean: 
	rm bsdump.o
	rm bytedump.o
	rm bsdump
	rm bytedump
