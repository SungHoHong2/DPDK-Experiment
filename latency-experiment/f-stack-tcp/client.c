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


#include "ff_config.h"
#include "ff_api.h"

#define MAX_EVENTS 512

/* kevent set */
struct kevent kevSet;
/* events */
struct kevent events[MAX_EVENTS];
/* kq */
int kq;
int sockfd;


int main(int argc , char *argv[])
{

  // int sock;
  // struct sockaddr_in server;
  char message[1000] , server_reply[2000];


  // //Create socket
  // sock = socket(AF_INET , SOCK_STREAM , 0);

    ff_init(argc, argv);
    sockfd = ff_socket(AF_INET, SOCK_STREAM, 0);
    printf("sockfd:%d\n", sockfd);

    // if (sock == -1)
    // {
    //     printf("Could not create socket");
    // }
    if (sockfd < 0) {
        printf("ff_socket failed\n");
        exit(1);
    }

    puts("Socket created");

    struct sockaddr_in my_addr;
    bzero(&my_addr, sizeof(my_addr));
    // server.sin_addr.s_addr = inet_addr("127.0.0.1");
    // server.sin_family = AF_INET;
    // server.sin_port = htons( 8888 );
    my_addr.sin_addr.s_addr = inet_addr("10.218.111.254");
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons( 80 );

    // //Connect to remote server
    // // int ff_connect(int s, const struct linux_sockaddr *name, socklen_t namelen);
    // if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    // {
    //     perror("connect failed. Error");
    //     return 1;
    // }
    int ret = ff_connect(1024, (struct linux_sockaddr *)&my_addr, sizeof(my_addr));
    puts("Connected\n");

    while(1){

        printf("Enter message : ");
        scanf("%s" , message);

        //Send some data
        if( ff_send(sockfd , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }

        //Receive a reply from the server
        if( ff_recv(sockfd , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }

        puts("Server reply :");
        puts(server_reply);
    }

    return 0;

    // //keep communicating with server
    // while(1)
    // {
    //     printf("Enter message : ");
    //     scanf("%s" , message);
    //
    //     //Send some data
    //     if( send(sock , message , strlen(message) , 0) < 0)
    //     {
    //         puts("Send failed");
    //         return 1;
    //     }
    //
    //     //Receive a reply from the server
    //     if( recv(sock , server_reply , 2000 , 0) < 0)
    //     {
    //         puts("recv failed");
    //         break;
    //     }
    //
    //     puts("Server reply :");
    //     puts(server_reply);
    // }
    //
    // close(sock);
    // return 0;
}
