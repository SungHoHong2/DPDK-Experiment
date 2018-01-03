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
#include "ff_epoll.h"

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


int loop(void *arg) {
    int nevents = ff_epoll_wait(epfd, events, MAX_EVENTS, 0);
    printf("events number: %d\n", nevents);
    struct epoll_event event;
    printf("events value: %d\n", events[0].events);
    for (int i = 0; i < nevents; ++i) {
        if(events[i].events & EPOLLOUT) {
            if (status++ == 0)
                printf("connection establised, fd %d\n", events[i].data.fd);
            else
                printf("epoll %d times, fd %d\n", status, events[i].data.fd);
            int n = strlen(hello);
            int nsend = ff_write(events[i].data.fd, hello, n);
            if(nsend < 0 && errno != EAGAIN) {
                perror("send error");
                close(events[i].data.fd);
                exit(1);
            }
            printf("message delivered!\n");
            ev.data.fd = sockfd;
            ev.events = EPOLLIN;
            assert(ff_epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev)==0);
            printf("events modified!\n");
        }
        if(events[i].events & EPOLLIN) {
            printf("sockfd: %d\n", sockfd);
            printf("receiving data... fd %d\n", events[i].data.fd);
            printf("read success %d times\n", succ);

            struct epoll_event ev;
            ev.data.fd = sockfd;
            ev.events = EPOLLOUT;

            ff_epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);

            memset(buffer, 0, BUFSIZE);
            int nrecv = read(events[i].data.fd, buffer, BUFSIZE - 1) ;
            if(nrecv == -1 && errno != EAGAIN)
                perror("read error");
            if((nrecv == -1 && errno == EAGAIN) || nrecv == 0)
                break;
            if (nrecv > 0) succ++;
            printf("%s\n", buffer);
        }
    }
}

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
  serv_addr.sin_port = htons(80);
  serv_addr.sin_addr.s_addr = inet_addr("10.218.111.254");

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


  ff_run(loop, NULL);


return 0;
}
