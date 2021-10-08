#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "7.h"

// 1GB of integers
#define SIZE 268435456

// 2GB of integers
// #define SIZE 536870912

// 4GB of integers
// #define SIZE 1073741824

int VECTOR[SIZE];
int CORES = 6;
int MINIMUM_VALUE;
pthread_mutex_t LOCK;
typedef struct
{
    int start;
    int end;
} range_t;

// How to properly return or let main flow get the result.
void *minimum(void *arg)
{
    range_t *args = (range_t *)arg;
    int min = VECTOR[args->start];
    int i = args->start;
    for (; i < args->end; i++)
    {
        if (VECTOR[i] < min)
        {
            min = VECTOR[i];
        }
    }
    pthread_mutex_lock(&LOCK);
    if (min < MINIMUM_VALUE)
    {
        MINIMUM_VALUE = min;
    }
    pthread_mutex_unlock(&LOCK);
    pthread_exit(NULL);
}

void start_exercise_7()
{
    // Fill array
    int i = 0;
    for (; i < SIZE; i++)
    {
        VECTOR[i] = i;
    }

    pthread_t threads[CORES];
    int slice = SIZE / CORES;
    void *ret[CORES];

    // Search the array
    int start = 0;
    int end = SIZE;
    int j;
    // Initiate the MINIMUM_VALUE
    MINIMUM_VALUE = VECTOR[0];
    for (j = 0; j < CORES; j++)
    {
        if (j != CORES - 1)
        {
            end = start + slice;
        }
        else
        {
            end = SIZE;
        }
        range_t range = {.start = start, .end = end};
        pthread_create(&threads[j], NULL, minimum, (void *)&range);

        start = end;
    }
    for (j = 0; j < CORES; j++)
    {
        pthread_join(threads[j], NULL);
    }
    printf("MINIMUM VALUE: %d\n", MINIMUM_VALUE);
}
