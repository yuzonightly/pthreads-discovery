#include <stdio.h>
#include <pthread.h>

void *aThread(void *arg) {	
 printf("another thread: my thread ID: %lu\n", pthread_self());
 pthread_exit(NULL);
}

int main()
{
 pthread_t thread;

 printf("main thread: my thread ID: %lu\n", pthread_self());
 pthread_create(&thread, NULL, aThread, NULL);
 if (pthread_equal(pthread_self(), thread))
     printf("ERROR: threads seem to be the same and should be not.\n");
 else
     printf("SUCCESS: threads are not the same, which is correct.\n");
 
 pthread_exit(NULL);
}
