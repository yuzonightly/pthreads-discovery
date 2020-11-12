#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_THREADS 5

char *messages[NUM_THREADS] = {"English: Hello World!", "French: Bonjour, le monde!", "Spanish: Hola al mundo",
                               "German: Guten Tag, Welt!", "Russian: Zdravstvytye, mir!"};

void *aThread(void *arg)
{
  long tid = (long)arg;

  printf("Process %d: thread %ld: %s\n", getpid(), tid, messages[tid]);
  pthread_exit(NULL);
}

int main()
{
  pthread_t threads[NUM_THREADS];
  long t;
  int ret;

  for (t = 0; t < NUM_THREADS; t++)
  {
    printf("Process %d: thread main: creating thread %ld\n", getpid(), t);
    ret = pthread_create(&threads[t], NULL, aThread, (void *)t);
    if (ret)
    {
      printf("ERROR; return code from pthread_create() is %d\n", ret);
      exit(ret);
    }
  }
  printf("Process %d: thread main: program completed: exiting\n", getpid());
  pthread_exit(NULL); /* Last thing that main() should do */
}
