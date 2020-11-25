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
int CORES = 9;

typedef struct
{
    int start;
    int end;
} range_t;

// How to properly return or let the main flow get the result.
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
    pthread_exit((void *)min);
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
    int j = 0;
    for (; j < CORES; j++)
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
        pthread_join(threads[j], &ret[j]);

        start = end;
    }
}
