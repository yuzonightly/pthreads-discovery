#ifndef __7_H__
#define __7_H__

// Develop a program to search for the minimum value of a vector of integers in parallel.
// The main thread should define a vector of N>=2^28 random integers (this takes
// >=1GB, once each integers takes 4 bytes). Then, T<=N worker threads should be used
// to search for the minimum. It will be up to the the main thread to show the minimum
// found. For a fixed value of N, execute the search with T=1,2,3,... and register in a
// worksheet the search time (for each value of T, execute the program 3 times and
// register the minimum time); stop increasing T when the search times start to increase
// instead of decreasing; draw graphs of execution times, speedup and efficiency, as a
// function of the number of threads. What conclusions can you take ?
// Note: for very large arrays special GCC options may be needed; if you get some error
// from the compiler, use that error to search for a solution ...

//just pass the vector by reference instead of using global values.
#define SIZE 1000

int VECTOR[SIZE];
int WORK_SLICE = 0;
int CORES = 6;

// struct range
// {
//     int start;
//     int end;
// } range_t;

// void *minimum(void *arg)
// {
//     int start =
//         int min = VECTOR[];
//     pthread_exit();
// }
// void start_exercise_7()
// {
//     int i = 0;
//     for (; i < 10000; i++)
//     {
//         VECTOR[i] = i;
//     }
//     WORK_SLICE = SIZE / 6;
// }

#endif