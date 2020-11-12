#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "3.h"

#define NUM_THREADS 5

void *wait(void *arg)
{
    long tid = (long)arg;
    printf("Greetings, I am thread number %ld.\n", tid);

    if (tid < NUM_THREADS)
    {
        pthread_t thread;
        pthread_create(&thread, NULL, wait, (void *)(tid + 1));
        pthread_join(thread, NULL);
    }
    printf("I am thread number %ld, farewell.\n", tid);
    pthread_exit(NULL);
}

void start_exercise_3()
{
    printf("Greetings, I am the main thread.\n");

    long tid = 0;
    pthread_t thread;
    pthread_create(&thread, NULL, wait, (void *)(tid));
    pthread_join(thread, NULL);

    printf("I am the main thread, farewell.\n");
    pthread_exit(NULL);
}
