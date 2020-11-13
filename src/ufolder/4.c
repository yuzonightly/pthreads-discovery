#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

#include "4.h"

int DEPTH = 1;

//          1
//     2          3
//  4    5     6     7
// 8 9 10 11 12 13 14 15

int next_thread_tid(long tid)
{
    // From math.h: M_LOG2E.
    int depth = log(tid) * M_LOG2E;
    int off = tid - pow(2, depth);
    int next_tid = pow(2, (depth + 1)) + (2 * off);
    return next_tid;
}

void *depth(void *arg)
{
    long tid = (long)arg;
    printf("%ld says HELLO!!!.\n", tid);

    // The current depth: log(tid) * M_LOG2E.
    if ((int)(log(tid) * M_LOG2E) < DEPTH)
    {
        long next_tid = next_thread_tid(tid);
        pthread_t thread[2];
        pthread_create(&thread[0], NULL, depth, (void *)(next_tid));
        pthread_create(&thread[1], NULL, depth, (void *)(next_tid + 1));
    }
    printf("%ld says Goodbye___.\n", tid);
    pthread_exit(NULL);
}

void start_exercise_4(int tree_depth)
{
    long tid = 1;
    DEPTH = tree_depth;
    printf("%ld says HELLO!!!.\n", tid);

    if (DEPTH > 0)
    {
        pthread_t thread[2];
        pthread_create(&thread[0], NULL, depth, (void *)(tid + 1));
        pthread_create(&thread[1], NULL, depth, (void *)(tid + 2));
    }
    printf("%ld says Goodbye___.\n", tid);
    pthread_exit(NULL);
}
