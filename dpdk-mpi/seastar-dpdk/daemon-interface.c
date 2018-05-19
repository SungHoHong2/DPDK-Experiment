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
void *TxShareMemory = (void*)0;
void *RxShareMemory = (void*)0;

struct shared_use_st *TxShardInstance;
struct shared_use_st *RxShardInstance;

int shmTX, shmRX;
char buffer[TEXT_SIZE];


void* rx_func(){
         while(running){
             while(RxShardInstance->written_by_you == 0){
                 sleep(1);
             }
             printf("%s\n", RxShardInstance->data);
             RxShardInstance->written_by_you = 0;
         }
         pthread_exit(0);
}


void* tx_func(){
         printf("thread %ld\n", pthread_self());
         while(running){

             while(TxShardInstance->written_by_you == 1){
                 sleep(1);
             }

             printf("[Client]Enter text :\n");
             fgets(buffer, TEXT_SIZE, stdin);

             // printf("starting with %d", test_case[s]);
             // int i=0;
             // for(i=0; i<test_case[s]; i++){
             //   buffer[i]='*';
             // }
             // buffer[i]='\0';

             strncpy(TxShardInstance->data, buffer, TEXT_SIZE);
             // s++;
             TxShardInstance->written_by_you = 1;
             // if(s==sizeof(test_case)){
             //   break;
             // }
         }
         pthread_exit(0);
}



int main() {

    srand((unsigned int)getpid());

    shmTX = shmget((key_t)2016, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    shmRX = shmget((key_t)2017, sizeof(struct shared_use_st), 0667 | IPC_CREAT);

    if((shmTX ==-1) || (shmRX == -1)){
        printf("[Daemon-interface][Error]shmget fail. id: %d\n", shmRX);
        exit(EXIT_FAILURE);
    }

    TxShareMemory = shmat(shmTX, (void*)0, 0);
    RxShareMemory = shmat(shmRX, (void*)0, 0);

    if((TxShareMemory == (void*)-1) && (RxShareMemory == (void*)-1)){
        printf("[Daemon-interface][Error]shmat fail.\n");
        exit(EXIT_FAILURE);
    }
    else{
        TxShardInstance = (struct shared_use_st *) TxShareMemory;
        RxShardInstance = (struct shared_use_st *) RxShareMemory;

        pthread_t tx_thread, rx_thread;
        pthread_create(&rx_thread,NULL, rx_func, NULL);
        pthread_create(&tx_thread,NULL, tx_func, NULL);
        pthread_join(rx_thread,NULL);
        pthread_join(tx_thread,NULL);
  }

    exit(EXIT_SUCCESS);
	//return 0;
}
