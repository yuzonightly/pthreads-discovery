#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "5.h"

// https://stackoverflow.com/questions/16224469/pthreads-cancel-blocking-thread

#define NUM_THREADS 5
#define RN_RANGE 1000000

pthread_mutex_t LOCK;
pthread_t THREADS[5];
int TO_GUESS = 0;

void *guess(void *arg)
{
    long tid = (long)arg;
    int guess = 0;
    int tries = 0;
    srand(tid);

    for (;;)
    {
        guess = rand() % RN_RANGE;
        tries = tries + 1;
        if (guess == TO_GUESS)
        {
            pthread_mutex_lock(&LOCK);
            printf("Goodbye. --performs SolarBeam--\n");

            int i = 0;
            for (; i < NUM_THREADS; i++)
            {
                if (!pthread_equal(THREADS[i], pthread_self()))
                {
                    pthread_cancel(THREADS[i]);
                }
            }
            printf("All threads vaporized.\n");
            pthread_mutex_unlock(&LOCK);
            break;
        }
    }
    printf("%ld guessed %d after %d tries.\n", tid, guess, tries);
    pthread_exit(NULL);
}

void start_exercise_5()
{
    srand(time(NULL));
    TO_GUESS = rand() % RN_RANGE;
    printf("Secret number: %d.\n", TO_GUESS);

    long i = 0;
    for (; i < NUM_THREADS; i++)
    {
        pthread_create(&THREADS[i], NULL, guess, (void *)(i));
    }
    pthread_exit(NULL);
}
