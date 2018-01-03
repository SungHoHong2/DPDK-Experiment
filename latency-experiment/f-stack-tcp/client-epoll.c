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
#include <sys/ioctl.h>


// struct hostent and gethostbyname()
#include <netdb.h>

// sleep function
#include <unistd.h>


#include "ff_config.h"
#include "ff_api.h"

#define PKT_SIZE 64
#define MAX_EVENTS 512

#define MAX_EVENTS 512
#define BUFSIZE 10

struct epoll_event ev;
struct epoll_event events[MAX_EVENTS];

int epfd;
int sockfd;
const char* hello = "hello";
char buffer[10];
int status = 0;
int succ = 0;


int main(int argc,char* argv[]){

  ff_init(argc, argv);
  sockfd = ff_socket(AF_INET, SOCK_STREAM, 0);
  printf("sockfd: %d\n", sockfd);

  if (sockfd < 0) {
      printf("ff_socket failed\n");
      exit(1);
  }

  int on = 1;
  ff_ioctl(sockfd, FIONBIO, &on);


  struct sockaddr_in serv_addr;
  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(2099);
  serv_addr.sin_addr.s_addr = inet_addr("192.168.32.1");

  assert((epfd = ff_epoll_create(0)) > 0);
  ev.data.fd = sockfd;
  ev.events = EPOLLOUT;
  ff_epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);
  fprintf(stderr, "epoll fd: %d\n", epfd);

  printf("connecting...\n");
  int ret = ff_connect(sockfd, (struct linux_sockaddr *)&serv_addr, sizeof(serv_addr));
  if (ret < 0) {
      perror("ff_connect");
  }


return 0;
}
