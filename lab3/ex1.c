#include <stdio.h>
#include <pthread.h>

// Thread function prototypes
void* thread1();
void* thread2();

void
main()
{
	// Pthread vars
	pthread_t	i1;
	pthread_t	i2;
	
	// Thread definitions
	pthread_create(&i1, NULL, (void*)&thread1, NULL);
	pthread_create(&i2, NULL, (void*)&thread2, NULL);
	
	// Wait for thread completion
	pthread_join(i1, NULL);
	pthread_join(i2, NULL);
	printf("Hello, I am main process.\n");
}

// Function definitions
void* thread1()
{
	sleep(5);
	printf("Hello, I am thread 1.\n");
	return NULL;
}

void* thread2()
{
	sleep(5);
	printf("Hello, I am thread 2.\n");
	return NULL;
}