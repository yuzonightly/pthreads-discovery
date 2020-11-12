#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "2.h"

#define NUM_THREADS 5

void *chain(void *arg)
{
    long tid = (long)arg;
    printf("Greetings, I am thread number %ld.\n", tid + 1);

    if (tid < NUM_THREADS)
    {
        pthread_t thread;
        pthread_create(&thread, NULL, chain, (void *)(tid + 1));
    }
    printf("I am thread number %ld, farewell.\n", tid + 1);
    pthread_exit(NULL);
}

void start_exercise_2()
{
    long tid = 0;
    printf("Greetings, I am thread number %ld.\n", tid);

    pthread_t thread;
    pthread_create(&thread, NULL, chain, (void *)(tid));

    printf("I am thread number %ld, farewell.\n", tid + 1);
    pthread_exit(NULL);
}
