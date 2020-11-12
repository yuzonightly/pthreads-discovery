#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 5

void *aThread(void *arg)
{
 long tid = (long)arg;
 long *square;

 square = (long*)malloc(sizeof(long));
 *square = tid*tid;
 printf("thread %ld: Hello World !\n", tid);
 pthread_exit((void*)square);
}

int main()
{
 pthread_t threads[NUM_THREADS];
 long t; int ret; void *status;

 for(t=0;t<NUM_THREADS;t++){
     printf("thread main: creating thread %ld\n", t);
     ret = pthread_create(&threads[t], NULL, aThread, (void *)t);
     if (ret){
         printf("ERROR; return code from pthread_create() is %d\n", ret);
         exit(ret);
     }
 }

 /* Wait for the other threads */
 for(t=0; t<NUM_THREADS; t++) {
     ret = pthread_join(threads[t], &status);
     if (ret) {
         printf("ERROR; return code from pthread_join() is %d\n", ret);
         exit(ret);
     }
     printf("thread main: joined with thread %ld: exit status is: %ld\n", t, *(long*)status);
     free(status);
 }

 printf("thread main: program completed: exiting\n");
 pthread_exit(NULL); 
}
