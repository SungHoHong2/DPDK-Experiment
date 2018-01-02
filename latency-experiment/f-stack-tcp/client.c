/*
    C ECHO client example using sockets
*/

#include <unistd.h>
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr

#define TOTAL_SEND 10000

int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    int total_length;
    char start[64];

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1){
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("10.218.111.254");
    server.sin_family = AF_INET;
    server.sin_port = htons( 80 );

    //Connect to remote server
    // int ff_connect(int s, const struct linux_sockaddr *name, socklen_t namelen);
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");

    total_length = 0;
    //keep communicating with server
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
    //         usleep(1);
    //
    //     } else {
    //         //Receive a reply from the server
    //         if( recv(sock , server_reply , PKT_SIZE , 0) < 0){
    //             puts("recv failed");
    //             break;
    //         }
    //
    //         total_length += strlen(server_reply);
    //         usleep(1);
    //     }
    //
    //
    //
    //
    //     // puts("Server reply :");
    //     // puts(server_reply);
    // }


    int pkt_size;
    while(1)
    {

        put("total size of the packet: ");
        scanf("%s", start);
        pkt_size = atoi(start);
        char message[pkt_size] , server_reply[pkt_size];

            memset( message, '*', sizeof(char)*pkt_size);

            //Send some data
            if( send(sock , message , strlen(message) , 0) < 0){
                puts("Send failed");
                return 1;
            }

            //Receive a reply from the server
            if( recv(sock , server_reply , pkt_size , 0) < 0){
                puts("recv failed");
                break;
            }
            total_length = strlen(server_reply);
            printf("total_length: %d\n", total_length);
    }


    close(sock);
    return 0;
}
