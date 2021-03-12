#include "mpi.h"
#include <stdio.h>

#define M 1000000
#define N 4

int main(int argc, char *argv[])
{
    int numtasks, rank, next, prev, buf[2], tag1 = 1, tag2 = 2;
    int *incoming_buffer, *outgoing_buffer;
    MPI_Request reqs[4]; // required variable for non-blocking calls
    MPI_Status stats[4]; // required variable for Waitall routine

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    incoming_buffer = (int *)malloc(N * sizeof(int));
    outgoing_buffer = (int *)malloc(N * sizeof(int));
    outgoing_buffer[i] = rank;
    next = (rank + 1) % N;
    MPI_Isend(&outgoing_buffer, N, MPI_INT, next, tag2, MPI_COMM_WORLD, &reqs[2]);
    do
    {

        else
        {
            MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD,
                     &status);
            if (rank < size - 1)
                MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }
    } while (summation != N);

    //    if (rank == 0) {
    //         int array[M];

    //         for ()
    //         MPI_Isend(&rank, 1, MPI_INT, prev, tag2, MPI_COMM_WORLD, &reqs[2]);

    //    }
    //    else {
    //         while (received != N - 1) {

    //         }
    //    }
    //    // determine left and right neighbors
    //    prev = (rank == 0 ? numtasks - 1 : rank - 1 );
    //    next = (rank == (numtasks - 1) ? 0 : rank + 1);

    //    // post non-blocking receives and sends for neighbors
    //    MPI_Irecv(&buf[0], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &reqs[0]);
    //    MPI_Irecv(&buf[1], 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &reqs[1]);

    //    MPI_Isend(&rank, 1, MPI_INT, prev, tag2, MPI_COMM_WORLD, &reqs[2]);
    //    MPI_Isend(&rank, 1, MPI_INT, next, tag1, MPI_COMM_WORLD, &reqs[3]);

    // do some work while sends/receives progress in background
    // ...

    // wait for all non-blocking operations to complete
    MPI_Waitall(4, reqs, stats);

    // continue - do more work
    // ...

    MPI_Finalize();
    return (0);
}