#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <assert.h>
#include <time.h>


#include "ff_config.h"
#include "ff_api.h"


#define TOTAL_SEND 10000
#define PKT_SIZE  64


int main(int argc , char *argv[])
{
    int sockfd;
    struct sockaddr_in server;
    int total_length;
    struct timespec tps, tpe;
    long int latency;


    //Create socket
    // sock = socket(AF_INET , SOCK_STREAM , 0);

    ff_init(argc, argv);
    sockfd = ff_socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1){
        printf("Could not create socket");
    }
    puts("Socket created");


    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons( 80 );
    server.sin_addr.s_addr = inet_addr("10.218.111.252"); // TCP
    // server.sin_addr.s_addr = inet_addr("10.218.111.254"); // DPDK


    //Connect to remote server
    // if (connect(sockfd , (struct sockaddr *)&server , sizeof(server)) < 0){
    //     perror("connect failed. Error");
    //     return 1;
    // }

    if(ff_connect(sockfd, (struct linux_sockaddr*)&server, sizeof(server)) < 0 ){
      perror("connect failed. Error");
      return 1;
    }

    printf("PKT_SIZE: %d\n", PKT_SIZE);

    total_length = latency = 0;
    clock_gettime(CLOCK_REALTIME, &tps);

    // //keep communicating with server
    // for(int i =0; i<TOTAL_SEND*2; i++)
    // {
    //     char message[PKT_SIZE] , server_reply[PKT_SIZE];
    //
    //     if(i%2==0){
    //         memset( message, '*', sizeof(char)*PKT_SIZE);
    //
    //         //Send some data
    //         if( send(sock , message , strlen(message) , 0) < 0){
    //             puts("Send failed");
    //             return 1;
    //         }
    //         // usleep(1);
    //
    //     } else {
    //         //Receive a reply from the server
    //         if( recv(sock , server_reply , PKT_SIZE, 0) < 0){
    //             puts("recv failed");
    //             break;
    //         }
    //
    //         total_length += strlen(server_reply);
    //         // usleep(1);
    //     }
    //
    //     // puts(server_reply);
    // }
    //
    // clock_gettime(CLOCK_REALTIME, &tpe);
    //
    // if(total_length == TOTAL_SEND * PKT_SIZE)
    //   printf("identical total_length: %d\n", total_length);
    // else{
    //   printf("expected_length: %d\n", TOTAL_SEND * PKT_SIZE);
    //   printf("actual_length: %d\n", total_length);
    //   printf("unidentical total_length: %d\n", total_length);
    // }
    //
    // latency =  (tpe.tv_sec - tps.tv_sec) * 1000000000;
    // latency += (tpe.tv_nsec - tps.tv_nsec);
    // // latency =  tpe.tv_nsec - tps.tv_nsec;
    // latency /= TOTAL_SEND;
    //
    // printf("latency: %ld\n", latency);
    //

    ff_close(sockfd);
    return 0;
}
