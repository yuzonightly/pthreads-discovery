#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

#include "12.h"

int TREE_DEPTH = 3;

//          1
//     2          3
//  4    5     6     7
// 8 9 10 11 12 13 14 15

// -2 because thread main also counts
pthread_t threads[6];

void *binary_tree_but(void *arg)
{
    long tid = (long)arg;
    int depth = (int)(log(tid) / log(2));
    printf("%ld says HELLO!!! DEPTH: %d.\n", tid, depth);

    // The current TREE_DEPTH: log(tid) * M_LOG2E.
    if ((int)(log(tid) / log(2)) < TREE_DEPTH)
    {
        pthread_create(&threads[tid * 2 - 2], NULL, binary_tree_but, (void *)(tid * 2));
        pthread_create(&threads[tid * 2 - 1], NULL, binary_tree_but, (void *)(tid * 2 + 1));
    }
    // printf("%ld says Goodbye___.\n", tid);
    pthread_exit(NULL);
}

void start_exercise_12()
{
    long tid = 1;
    printf("%ld says HELLO!!! DEPTH: %d.\n", tid, 0);

    if (TREE_DEPTH > 0)
    {
        pthread_create(&threads[tid * 2 - 2], NULL, binary_tree_but, (void *)(tid * 2));
        pthread_create(&threads[tid * 2 - 1], NULL, binary_tree_but, (void *)(tid * 2 + 1));
    }
    // printf("%ld says Goodbye___.\n", tid);
    pthread_exit(NULL);
}
