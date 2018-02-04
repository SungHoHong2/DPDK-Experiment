#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

#define NUM_THREADS     5

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
  // add argument smp with number
  int total_thread = atoi(argv[1]);
  printf("total num of thread: %d\n", total_thread);

  // allocate the pthread by pointers
  pthread_t *threads;

  threads = (pthread_t*)malloc(sizeof(pthread_t)*total_thread);

   int rc;
   long t;
   for(t=0; t<total_thread; t++){
      printf("In main: creating thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
    if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }
   pthread_exit(NULL);

   return 0;
}
