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
    struct shared_use_st *pShardStuff;
    int shmId;
    char buffer[TEXT_SIZE];

    srand((unsigned int)getpid());

    shmId = shmget((key_t)KEY_ID, sizeof(struct shared_use_st), 0666 | IPC_CREAT);

    if(shmId == -1){
        printf("[Client][Error]shmget fail. id: %d\n", shmId);
        exit(EXIT_FAILURE);
    }

    pShardMemory = shmat(shmId, (void*)0, 0);
    if(pShardMemory == (void*)-1){
        // cout << "[Client][Error]shmat fail."<< endl;;
        exit(EXIT_FAILURE);
    }
    else{
        pShardStuff = (struct shared_use_st *) pShardMemory;
        // cout << "[Client]shmat success. flag:" << pShardStuff->written_by_you << endl;;
        int test_case[] = {
          2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096
          // 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304
        };

        int s =0;
        while(running){

            while(pShardStuff->written_by_you == 1){
                sleep(1);
            }

            // printf("[Client]Enter text :\n");
            // fgets(buffer, TEXT_SIZE, stdin);

            printf("starting with %d", test_case[s]);
            int i=0;
            for(i=0; i<test_case[s]; i++){
              buffer[i]='*';
            }
            buffer[i]='\0';

            strncpy(pShardStuff->data, buffer, TEXT_SIZE);
            s++;
            pShardStuff->written_by_you = 1;
            if(s==sizeof(test_case)){
              break;
            }
        }

        if(shmdt(pShardMemory) == -1){
            printf("[Client][Error] shmdt fail.\n");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
	//return 0;
}
