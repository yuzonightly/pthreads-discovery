#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "8.h"

#define CORES 6

// Lines and Columns
#define MATRIX_A_L 1000 // this
#define MATRIX_A_C_B_L 1000
#define MATRIX_B_C 1000 // and this

// matrix_A * matrix_B = matrix_C
int matrix_A[MATRIX_A_L][MATRIX_A_C_B_L];
int matrix_B[MATRIX_A_C_B_L][MATRIX_B_C];
int matrix_C[MATRIX_A_L][MATRIX_B_C]; // result

typedef struct
{
    int start;
    int end;
} range_t;

void *matrix_mult(void *arg)
{
    int i, j, k, sum;

    range_t *args = (range_t *)arg;
    // i: Index of matrix_C
    for (i = args->start; i < args->end; i++)
    {
        // Extract row and column of matrix_C from i
        // Accumulate the result for matrix_C[row][column]
        int row = i / MATRIX_A_L;
        int column = i % MATRIX_B_C;
        sum = 0;
        for (j = 0; j < MATRIX_A_C_B_L; j++)
        {
            sum += matrix_A[row][j] * matrix_B[j][column];
        }
        // Store the result
        matrix_C[row][column] = sum;
    }
    pthread_exit(NULL);
}

void start_exercise_8()
{
    // Fill matrixes
    int i, j, fill;
    fill = 0;
    for (i = 0; i < MATRIX_A_L; i++)
    {
        for (j = 0; j < MATRIX_A_C_B_L; j++)
        {
            matrix_A[i][j] = fill;
            fill++;
        }
    }
    fill = 0;
    for (i = 0; i < MATRIX_A_C_B_L; i++)
    {
        for (j = 0; j < MATRIX_B_C; j++)
        {
            matrix_B[i][j] = fill;
            fill++;
        }
    }

    // Create workers
    int total_cells = MATRIX_A_L * MATRIX_B_C;
    int slice = total_cells / CORES;

    int start = 0;
    int end = total_cells;
    pthread_t threads[CORES];
    for (i = 0; i < CORES; i++)
    {
        if (i != CORES - 1)
        {
            end = start + slice;
        }
        else
        {
            end = total_cells;
        }

        range_t range = {.start = start, .end = end};
        pthread_create(&threads[i], NULL, matrix_mult, (void *)&range);

        start = end;
    }
    for (i = 0; i < CORES; i++)
    {

        pthread_join(threads[i], NULL);
    }

    // Display matrix_C
    // for (i = 0; i < MATRIX_A_L; i++)
    // {
    //     for (j = 0; j < MATRIX_B_C; j++)
    //     {
    //         printf("%d     ", matrix_C[i][j]);
    //     }
    //     printf("\n");
    // }
    // pthread_exit(NULL);
}
