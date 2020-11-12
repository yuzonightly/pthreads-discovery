#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

#include "4.h"

#define DEPTH 5

//          1
//     2          3
//  4    5     6     7
// 8 9 10 11 12 13 14 15

// off = tid - 2^(log(tid))
// sum = 2 * off = 4
// next = 2^(next depth) + 4
// next2 = 2^(next depth) + 4 + (1)

void next_thread_tid(int tid) {
    long off = tid - 2**(log);
}

void *depth(void *arg)
{
    long tid = (long)arg;
    printf("%ld says HELLO!!!.\n", tid);

    if (tid < DEPTH)
    {
        pthread_t thread;
        pthread_create(&thread, NULL, depth, (void *)(tid + 1));
        pthread_join(thread, NULL);
    }
    printf("I am thread number %ld, farewell.\n", tid);
    pthread_exit(NULL);
}

void start_exercise_4(int n)
{

    long tid = 1;
    printf("%ld says HELLO!!!.\n", tid);

    pthread_t thread;

    pthread_create(&thread, NULL, depth, (void *)(tid + 1));
    pthread_join(thread, NULL);

    printf("%ld says Goodbye___.\n", tid);
    pthread_exit(NULL);
}
