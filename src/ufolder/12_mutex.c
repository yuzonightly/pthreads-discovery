#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "12_mutex.h"

#define NUM_THREADS 5
pthread_mutex_t lock[NUM_THREADS];

// Just use a counter.
void *mutex_12(void *arg)
{
    long tid = (long)arg;

    printf("thread %ld: Hello World !\n", tid);

    pthread_mutex_unlock(&lock[(int)tid]);
    pthread_exit(NULL);
}

int start_exercise_12_mutex()
{
    pthread_t threads[NUM_THREADS];
    long t;
    int ret;

    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("thread main: creating thread %ld\n", t);
        pthread_mutex_lock(&lock[t]);
        pthread_create(&threads[t], NULL, mutex_12, (void *)t);
    }

    /* Wait for the other threads */
    pthread_mutex_lock(&lock[0]);
    pthread_mutex_lock(&lock[1]);
    pthread_mutex_lock(&lock[2]);
    pthread_mutex_lock(&lock[3]);
    pthread_mutex_lock(&lock[4]);
    printf("thread mainnnn hereeee");

    printf("thread main: program completed: exiting\n"); // (*)
    pthread_exit(NULL);
}
