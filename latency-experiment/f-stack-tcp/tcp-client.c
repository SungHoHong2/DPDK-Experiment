// system types
#include <sys/types.h>
// socket API
#include <sys/socket.h>
// struct sockaddr_in
#include <netinet/in.h>
// inet_ntoa()
#include <arpa/inet.h>
// system call
#include <unistd.h>
// struct hostent and gethostbyname()
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
extern int errno;
#define BUFFSIZE 128
#define PORT 80



char* getMessage(char* buffer, int len, FILE* fp)
{
    printf(">> Input message: ");
    return fgets(buffer, len, fp);
}

int recvFromServer(int sockfd, char* buf, int buf_size)
{
    int n, offset = 0;
    errno = 0;
    while (buf_size - offset > 0 &&
            (n = recv(sockfd, buf + offset, buf_size - offset, MSG_DONTWAIT)) > 0)
    {
        offset += n;
    }
    if (offset == 0 && errno == EAGAIN)
    {
        printf("[CLIENT] no message received.\n");
        return -1;
    }
    else
    {
        return offset;
    }
}

// Handle socket session
void process(FILE *fp, int sockfd)
{
    char sendline[BUFFSIZE], recvline[BUFFSIZE];
    int numbytes;
    while (getMessage(sendline, BUFFSIZE, fp) != NULL)
    {
        send(sockfd, sendline, strlen(sendline), 0);
        sleep(1);
        if ((numbytes = recvFromServer(sockfd, recvline, BUFFSIZE)) == 0)
        {
            printf("[CLIENT] server terminated.\n");
            return;
        }
        else if (numbytes > 0)
        {
            recvline[numbytes] = '\0';
            printf("Received: %s\n", recvline);
        }
    }
    printf("[CLIENT] exit.\n");
}

// Main function
int main(int argc,char* argv[])
{
    int sock;
    struct hostent *hent;
    struct sockaddr_in server;
    char *host = "10.218.111.252";
    unsigned short port = PORT;

    // convert decimal IP to binary IP
    if ((hent = gethostbyname(host)) == NULL)
        printf("gethostbyname failed.\n");
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
        printf("create socket failed: %s\n", strerror(errno));

    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr = *((struct in_addr*)hent->h_addr);
    printf("[CLIENT] server addr: %s, port: %u\n", inet_ntoa(server.sin_addr), ntohs(server.sin_port));

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0){
        printf("connect to server failed: %s\n", strerror(errno));
        return 0;
      }

    printf("[CLIENT] connected to server %s\n", inet_ntoa(server.sin_addr));
    // Send request to server
    process(stdin, sock);
    close(sock);
}
