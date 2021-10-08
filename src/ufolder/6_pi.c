#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#include "6_pi.h"

#define NUM_THREADS 4

// N cannot be more than INT_MAX (2^32-1 = 4294967295)
#define NUM_RANDOM_POINTS 100000

int INSIDE_CIRCLE = 0;
int SLICE = NUM_RANDOM_POINTS / NUM_THREADS;

pthread_mutex_t LOCK;

void *pi_6(void *arg)
{
    long tid = (long)arg;
    unsigned int seed = (unsigned int)tid;
    double x, y;
    int local_summation = 0;
    for (int i = 0; i < SLICE; i++)
    {
        x = (double)rand_r(&seed) / (double)(RAND_MAX);
        y = (double)rand_r(&seed) / (double)(RAND_MAX);
        if (sqrt(x * x + y * y) <= 1.0)
        {
            local_summation++;
        }
    }
    pthread_mutex_lock(&LOCK);
    INSIDE_CIRCLE += local_summation;
    pthread_mutex_unlock(&LOCK);
    pthread_exit(NULL);
}

int start_exercise_pi_6()
{
    long t;
    int ret;
    pthread_t threads[NUM_THREADS];

    if (NUM_RANDOM_POINTS % NUM_THREADS != 0)
    {
        printf("ERROR; N is not divisible by n\n");
        exit(1);
    }
    for (t = 0; t < NUM_THREADS; t++)
    {
        ret = pthread_create(&threads[t], NULL, pi_6, (void *)t);
        if (ret)
        {
            printf("ERROR; return code from pthread_create() is %d\n", ret);
            exit(ret);
        }
    }
    for (t = 0; t < NUM_THREADS; t++)
    {
        pthread_join(threads[t], NULL);
    }

    double approxPI = 4.0 * ((double)INSIDE_CIRCLE / (double)NUM_RANDOM_POINTS);
    printf("thread main: approx PI = %.20g\n", approxPI);
    printf("thread main: \"true\" PI = %.20g\n", M_PI);
    printf("thread main: abs error = %.20g\n", fabs(M_PI - approxPI));

    pthread_exit(NULL);
}