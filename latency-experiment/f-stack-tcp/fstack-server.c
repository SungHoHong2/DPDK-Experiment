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
#define PKT_SIZE 64


/* kevent set */
struct kevent kevSet;
/* events */
struct kevent events[MAX_EVENTS];
/* kq */
int kq;
int sockfd;


int loop(void *arg)
{
    /* Wait for events to happen */
    unsigned nevents = ff_kevent(kq, NULL, 0, events, MAX_EVENTS, NULL);
    unsigned i;

    for (i = 0; i < nevents; ++i) {
        struct kevent event = events[i];
        int clientfd = (int)event.ident;

        /* Handle disconnect */
        if (event.flags & EV_EOF) {
            /* Simply close socket */
            ff_close(clientfd);

          } else if (clientfd == sockfd) { // I think this is the reason why it is only available to connect with your own
        // } else if (clientfd != sockfd) { // this allows outside servers to communicate with the hosts
            int available = (int)event.data;
            do {
                int nclientfd = ff_accept(sockfd, NULL, NULL);
                if (nclientfd < 0) {
                    printf("ff_accept failed:%d, %s\n", errno,
                        strerror(errno));
                    break;
                }

                /* Add to event list */
                EV_SET(&kevSet, nclientfd, EVFILT_READ, EV_ADD, 0, 0, NULL); // if this pass then

                if(ff_kevent(kq, &kevSet, 1, NULL, 0, NULL) < 0) {
                    printf("ff_kevent error:%d, %s\n", errno, strerror(errno));
                    return -1;
                }

                available--;
            } while (available);
        } else if (event.filter == EVFILT_READ) { // this will work
            char buf[PKT_SIZE];
            size_t readlen = ff_read(clientfd, buf, sizeof(buf));

            // if(readlen>0){
            //   printf("readlen :%ld\n", readlen);
            // }
            printf("%s: %ld\n", buf, strlen(buf));
            ff_write(clientfd, buf, sizeof(buf));

        } else {  // or this one will work
            printf("unknown event: %8.8X\n", event.flags);
        }
    }
}

int main(int argc, char * argv[])
{
    ff_init(argc, argv);

    sockfd = ff_socket(AF_INET, SOCK_STREAM, 0);
    printf("sockfd:%d\n", sockfd);
    printf("PKT_SIZE: %d\n", PKT_SIZE);
    if (sockfd < 0) {
        printf("ff_socket failed\n");
        exit(1);
    }

    struct sockaddr_in my_addr;
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(80);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = ff_bind(sockfd, (struct linux_sockaddr *)&my_addr, sizeof(my_addr));
    if (ret < 0) {
        printf("ff_bind failed\n");
        exit(1);
    }

    ret = ff_listen(sockfd, MAX_EVENTS);
    if (ret < 0) {
        printf("ff_listen failed\n");
        exit(1);
    }

    EV_SET(&kevSet, sockfd, EVFILT_READ, EV_ADD, 0, MAX_EVENTS, NULL);

    assert((kq = ff_kqueue()) > 0);

    /* Update kqueue */
    ff_kevent(kq, &kevSet, 1, NULL, 0, NULL);

    ff_run(loop, NULL);
    return 0;


    // int socket_desc , client_sock , c , read_size;
    // struct sockaddr_in server , client;
    // char client_message[PKT_SIZE];
    //
    // //Create socket
    // socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    // if (socket_desc == -1)
    // {
    //     printf("Could not create socket");
    // }
    // puts("Socket created");
    //
    // //Prepare the sockaddr_in structure
    // server.sin_family = AF_INET;
    // server.sin_addr.s_addr = INADDR_ANY;
    // server.sin_port = htons( 80 );
    //
    // //Bind
    // if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    // {
    //     //print the error message
    //     perror("bind failed. Error");
    //     return 1;
    // }
    // puts("bind done");
    //
    // //Listen
    // listen(socket_desc , 3);
    //
    // //Accept and incoming connection
    // puts("Waiting for incoming connections...");
    // c = sizeof(struct sockaddr_in);
    //
    // //accept connection from an incoming client
    // client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    // if (client_sock < 0)
    // {
    //     perror("accept failed");
    //     return 1;
    // }
    // printf("PKT_SIZE: %d\n", PKT_SIZE);
    //
    // //Receive a message from client
    // while( (read_size = recv(client_sock , client_message , PKT_SIZE , 0)) > 0 )
    // {
    //     //Send the message back to client
    //     write(client_sock , client_message , PKT_SIZE);
    // }
    //
    // if(read_size == 0)
    // {
    //     puts("Client disconnected");
    //     fflush(stdout);
    // }
    // else if(read_size == -1)
    // {
    //     perror("recv failed");
    // }


}
