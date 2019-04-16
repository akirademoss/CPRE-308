CC = cc

all: memory_mgmt

memory_mgmt: memory_mgmt.o 
	$(CC) memory_mgmt.o -o memory_mgmt

memory_mgmt.o: memory_mgmt.c 
	$(CC) -c memory_mgmt.c

clean:
	rm -f memory_mgmt.o memory_mgmt
