#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

void *threadCounter(void *param){
  int *args = (int *)param;
  int i;
  for(i = 0; i < 1000000; i++){
    (*args)++;
  }
}
int main(int argc, char** argv){
  pthread_t t1;
  pthread_t t2;
  int shared = 0;
  int err;
  err = pthread_create(&t1, NULL, threadCounter, (void *)&shared);
    if(err != 0){
    errno = err;
    perror("pthread_create");
    exit(1);
  }
  err = pthread_create(&t2, NULL, threadCounter, (void *)&shared);
  if(err != 0){
    errno = err;
    perror("pthread_create");
    exit(1);
  }
  err = pthread_join(t1, NULL);
  if(err != 0){
    errno = err;
    perror("pthread_join");
    exit(1);
  }
  err = pthread_join(t2, NULL);
  if(err != 0){
    errno = err;
    perror("pthread_join");
    exit(1);
  }
  printf("After both threads are done executing, `shared` = %d\n", shared);
  return 0;
}