CC=gcc
CFLAGS= -lrt 


all: mq_test1 mq_test2 pipe_test shm_test1 shm_test2 sig_test

mq_test1: mq_test1.o
	$(CC) mq_test1.o -o mq_test1 $(CFLAGS) 

mq_test1.o: mq_test1.c
	$(CC) -c mq_test1.c

mq_test2: mq_test2.o
	$(CC) mq_test2.o -o mq_test2 $(CFLAGS) 
mq_test2.o: mq_test2.c
	$(CC) -c mq_test2.c

pipe_test: pipe_test.o
	$(CC) pipe_test.o -o pipe_test $(CFLAGS) 
pipe_test.o: pipe_test.c
	$(CC) -c pipe_test.c 

shm_test1: shm_test1.o
	$(CC) shm_test1.o -o shm_test1 $(CFLAGS) 
shm_test1.o: shm_test1.c shm_test.h
	$(CC) -c shm_test1.c  

shm_test2: shm_test2.o
	$(CC) shm_test1.o -o shm_test1 $(CFLAGS) 
shm_test2.o: shm_test2.c shm_test.h
	$(CC) -c shm_test2.c  

sig_test: sig_test.o
	$(CC) shm_test1.o -o shm_test1 $(CFLAGS) 
sig_test.o: sig_test.c
	$(CC) -c sig_test.c  

clean: 
	rm -f mq_test1 mq_test2 pipe_test shm_test1 mq_test1.o mq_test2.o pipe_test.o shm_test1.o
