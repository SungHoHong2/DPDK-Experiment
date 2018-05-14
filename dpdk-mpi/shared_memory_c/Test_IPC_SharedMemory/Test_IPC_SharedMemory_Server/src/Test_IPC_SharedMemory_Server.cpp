//============================================================================
// Name        : Test_IPC_SharedMemory_Sender.cpp
// Author      : Harry
// Version     :
// Copyright   : Infobank
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#include "testIpcShardMemory.h"

using namespace std;

int main() {

    int running = 1;
    void *pShardMemory = (void*)0;
    struct shared_use_st *pShardStuff;
    int shmId;

    srand((unsigned int)getpid());

    shmId = shmget((key_t)KEY_ID, sizeof(struct shared_use_st), 0666 | IPC_CREAT);

    if(shmId == -1){
        cout << "[Servier][Error]shmget fail. id:" << shmId << endl;;
        exit(EXIT_FAILURE);
    }

    pShardMemory = shmat(shmId, (void*)0, 0);
    if(pShardMemory == (void*)-1){
        cout << "[Servier][Error]shmat fail."<< endl;;
        exit(EXIT_FAILURE);
    }
    else{
        pShardStuff = (struct shared_use_st *) pShardMemory;
        pShardStuff->written_by_you = 0;
        cout << "[Servier]shmat success. flag:" << pShardStuff->written_by_you << endl;;

        while(running){
//            cout << "[Servier]while()"<< endl;

            if(pShardStuff->written_by_you == 1){
                cout << "[Servier]echo data:" << pShardStuff->data << endl;

                pShardStuff->written_by_you = 0;


                if(strncmp(pShardStuff->data, "end", 3) == 0){
                    running = 0;
                }
            }
        }

        if(shmdt(pShardMemory) == -1){
            cout << "[Servier][Error] shmdt fail."<< endl;;
            exit(EXIT_FAILURE);
        }

        if(shmctl(shmId, IPC_RMID, 0) == -1){
            cout << "[Servier][Error] shmctl (IPC_RMID) failed."<< endl;;
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
	//return 0;
}
