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

// struct hostent and gethostbyname()
#include <netdb.h>

// sleep function
#include <unistd.h>


#include "ff_config.h"
#include "ff_api.h"

#define PKT_SIZE 64
#define MAX_EVENTS 512

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
            (n = ff_recv(sockfd, buf + offset, buf_size - offset, MSG_DONTWAIT)) > 0)
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


void process(FILE *fp, int sockfd){
  char sendline[PKT_SIZE], recvline[PKT_SIZE];
  int numbytes;

  while (getMessage(sendline, PKT_SIZE, fp) != NULL)
  {
      ff_send(sockfd, sendline, strlen(sendline), 0);
      sleep(1);
      if ((numbytes = recvFromServer(sockfd, recvline, PKT_SIZE)) == 0){
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

int kq;
struct kevent events[MAX_EVENTS];

int loop(){
  unsigned nevents = ff_kevent(kq, NULL, 0, events, MAX_EVENTS, NULL);

//   for (int i = 0; i < nevents; ++i) {
//     if (status++ == 0)
//         printf("connection establised, fd %d\n", events[i].data.fd);
//     else
//         printf("epoll %d times, fd %d\n", status, events[i].data.fd);
//
//
//     char *hello = "hello";
//     int n = strlen(hello);
//     int nsend = ff_write(events[i].data.fd, hello, n);
//     if(nsend < 0 && errno != EAGAIN) {
//           perror("send error");
//           close(events[i].data.fd);
//           exit(1);
//     }
//
// }
// printf("message delivered!\n");
//
//

  return 0;
}



int main(int argc,char* argv[]){

  int sock;
  struct hostent *hent;
  struct sockaddr_in server;
  char *host = "10.218.111.254";
  unsigned short port = 80;

  ff_init(argc, argv);
  if ((hent = gethostbyname(host)) == NULL)
    printf("gethostbyname failed.\n");
  if ((sock = ff_socket(PF_INET, SOCK_STREAM, 0)) < 0)
    printf("create socket failed: %s\n", strerror(errno));


  bzero(&server, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr = *((struct in_addr*)hent->h_addr);
  printf("[CLIENT] server addr: %s, port: %u\n", inet_ntoa(server.sin_addr), ntohs(server.sin_port));


  int on = 1;
  ff_ioctl(sockfd, FIONBIO, &on);
  if (ff_connect(sock, (struct linux_sockaddr *)&server, sizeof(server)) < 0){
      printf("connect to server failed: %s\n", strerror(errno));
      return -1;
  }

  printf("[CLIENT] connected to server %s\n", inet_ntoa(server.sin_addr));

  // process(stdin, sock);
  ff_run(loop, NULL);

  close(sock);

return 0;
}
