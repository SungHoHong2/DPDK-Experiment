#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <pthread.h>
#include "testIpcShardMemory.h"

int running = 1;
void *pShardMemory = (void*)0;
void *pShardMemory2 = (void*)0;

struct shared_use_st *pShardStuff;
struct shared_use_st *pShardStuff2;

int shmId, shmId2;
char buffer[TEXT_SIZE];


void* rx_func(){
         printf("thread %ld\n", pthread_self());

         while(running){
             while(pShardStuff2->written_by_you == 0){
                 sleep(1);
             }

             printf("%s\n", pShardStuff2->data);
             pShardStuff2->written_by_you = 0;
         }

         pthread_exit(0);
}





int main() {

    srand((unsigned int)getpid());

    shmId = shmget((key_t)2016, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    shmId2 = shmget((key_t)2017, sizeof(struct shared_use_st), 0667 | IPC_CREAT);

    if((shmId ==-1) || (shmId2 == -1)){
        printf("[Daemon-interface][Error]shmget fail. id: %d\n", shmId2);
        exit(EXIT_FAILURE);
    }

    pShardMemory = shmat(shmId, (void*)0, 0);
    pShardMemory2 = shmat(shmId2, (void*)0, 0);

    if((pShardMemory == (void*)-1) && (pShardMemory2 == (void*)-1)){
        printf("[Daemon-interface][Error]shmat fail.\n");
        exit(EXIT_FAILURE);
    }
    else{
        pShardStuff = (struct shared_use_st *) pShardMemory;
        pShardStuff2 = (struct shared_use_st *) pShardMemory2;

        pthread_t tx_thread, rx_thread;
        pthread_create(&rx_thread,NULL, rx_func, NULL);
        // pthread_create(&rx_thread,NULL, func, NULL);
        pthread_join(rx_thread,NULL);


  }

    exit(EXIT_SUCCESS);
	//return 0;
}
