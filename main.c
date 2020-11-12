#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "./src/ufolder/2.h"
#include "./src/ufolder/3.h"
#include "./src/ufolder/4.h"
#include "./src/ufolder/5.h"
#include "./src/ufolder/7.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("This program needs at least 1 argument, which is the number of the exercise.\n");
        return 1;
    }
    if (strcmp(argv[1], "2") == 0)
    {
        start_exercise_2();
    }
    else if (strcmp(argv[1], "3") == 0)
    {
        start_exercise_3();
    }
    else if (strcmp(argv[1], "4") == 0)
    {
        int n;

        printf("Depth of the Threaded Tree: ");
        scanf("%d", &n);

        start_exercise_4(n);
    }
    else if (strcmp(argv[1], "5") == 0)
    {
        start_exercise_5();
    }
    // else if (strcmp(argv[1], "7") == 0)
    // {
    //     start_exercise_7();
    // }
    else
    {
        printf("Goodbye.\n");
    }
    return 0;
}