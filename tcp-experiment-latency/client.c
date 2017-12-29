/*
    C ECHO client example using sockets
*/
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#define PKT_SIZE 64



int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");


    server.sin_addr.s_addr = inet_addr("172.24.30.31");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");

    //keep communicating with server

    // memset( message, '*', PKT_SIZE * sizeof(char));

    for(int i=0; i<10; i++)
    {
        char message[PKT_SIZE] , server_reply[PKT_SIZE];

        // printf("Enter message : ");
        // scanf("%s" , message);

        memset( message, '*', PKT_SIZE * sizeof(char));

        //Send some data
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
        memset( message, '\0', PKT_SIZE * sizeof(char));

        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }

        printf("Server reply - strlen(server_reply):  %ld",strlen(server_reply));
        // puts(server_reply);
        memset( server_reply, '\0', PKT_SIZE * sizeof(char));
    }

    close(sock);
    return 0;
}
