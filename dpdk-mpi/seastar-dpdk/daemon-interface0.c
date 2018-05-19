#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "testIpcShardMemory.h"

int main() {

    int running = 1;
    void *pShardMemory = (void*)0;
    void *pShardMemory2 = (void*)0;

    struct shared_use_st *pShardStuff;
    struct shared_use_st *pShardStuff2;

    int shmId, shmId2;
    char buffer[TEXT_SIZE];

    srand((unsigned int)getpid());

    shmId = shmget((key_t)KEY_ID, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    shmId2 = shmget((key_t)KEY_ID, sizeof(struct shared_use_st), 0667 | IPC_CREAT);

    if(shmId2 == -1){
        printf("[Client][Error]shmget fail. id: %d\n", shmId2);
        exit(EXIT_FAILURE);
    }

    // pShardMemory = shmat(shmId, (void*)0, 0);
    pShardMemory2 = shmat(shmId2, (void*)0, 0);

    //  gcc daemon-interface0.c -o daemon-interface0
    if(pShardMemory2 == (void*)-1){
        // cout << "[Client][Error]shmat fail."<< endl;;
        exit(EXIT_FAILURE);
    }
    else{
        pShardStuff2 = (struct shared_use_st *) pShardMemory2;
        while(running){
            while(pShardStuff2->written_by_you == 0){
                sleep(1);
            }

        printf("%s\n", pShardStuff2->data);
        pShardStuff2->written_by_you = 0;
        if(shmdt(pShardMemory) == -1){
            printf("[Client][Error] shmdt fail.\n");
            exit(EXIT_FAILURE);
        }
    }
  }

    exit(EXIT_SUCCESS);
	//return 0;
}
