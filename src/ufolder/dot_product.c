#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "dot_product.h"

// 1GB of integers
#define SIZE 1000

// 2GB of integers
// #define SIZE 536870912

// 4GB of integers
// #define SIZE 1073741824

int VECTOR_A[SIZE];
int VECTOR_B[SIZE];
int DOT_PRODUCT = 0;
int DOT_CORES = 6;
pthread_mutex_t LOCK;
typedef struct
{
    int start;
    int end;
} range_t;

// How to properly return or let the main flow get the result.
void *dot(void *arg)
{
    range_t *args = (range_t *)arg;
    int i = args->start;
    int summation = 0;
    for (; i < args->end; i++)
    {
        summation += VECTOR_A[i] * VECTOR_B[i];
    }
    pthread_mutex_lock(&LOCK);
    DOT_PRODUCT += summation;
    pthread_mutex_unlock(&LOCK);
    pthread_exit(NULL);
}

void start_exercise_dot_product()
{
    // Fill array
    int i;
    for (i = 0; i < SIZE; i++)
    {
        VECTOR_A[i] = i;
        VECTOR_B[i] = i;

    }
    pthread_t threads[DOT_CORES];
    int slice = SIZE / DOT_CORES;

    // Search the array
    int start = 0;
    int end = SIZE;
    int j;
    // Initiate the MINIMUM_VALUE
    for (j = 0; j < DOT_CORES; j++)
    {
        if (j != DOT_CORES - 1)
        {
            end = start + slice;
        }
        else
        {
            end = SIZE;
        }
        range_t range = {.start = start, .end = end};
        pthread_create(&threads[j], NULL, dot, (void *)&range);

        start = end;
    }
    for (j = 0; j < DOT_CORES; j++)
    {
        pthread_join(threads[j], NULL);
    }
    printf("Dot Product : %d\n", DOT_PRODUCT);
}
