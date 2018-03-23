#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <assert.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_EVENTS 512
#define PKT_SIZE 256

struct epoll_event ev;
struct epoll_event events[MAX_EVENTS];

int epfd;
int sockfd;

char html[] =
"HTTP/1.1 200 OK\r\n"
"Server: F-Stack\r\n"
"Date: Sat, 25 Feb 2017 09:26:33 GMT\r\n"
"Content-Type: text/html\r\n"
"Content-Length: 439\r\n"
"Last-Modified: Tue, 21 Feb 2017 09:44:03 GMT\r\n"
"Connection: keep-alive\r\n"
"Accept-Ranges: bytes\r\n"
"\r\n"
"<!DOCTYPE html>\r\n"
"<html>\r\n"
"<head>\r\n"
"<title>Welcome to F-Stack!</title>\r\n"
"<style>\r\n"
"    body {  \r\n"
"        width: 35em;\r\n"
"        margin: 0 auto; \r\n"
"        font-family: Tahoma, Verdana, Arial, sans-serif;\r\n"
"    }\r\n"
"</style>\r\n"
"</head>\r\n"
"<body>\r\n"
"<h1>Welcome to F-Stack!</h1>\r\n"
"\r\n"
"<p>For online documentation and support please refer to\r\n"
"<a href=\"http://F-Stack.org/\">F-Stack.org</a>.<br/>\r\n"
"\r\n"
"<p><em>Thank you for using F-Stack.</em></p>\r\n"
"</body>\r\n"
"</html>";



void *run(void *threadid)
{
  while(1){
    /* Wait for events to happen */
    int nevents = epoll_wait(epfd,  events, MAX_EVENTS, 0);
    int i;

    for (i = 0; i < nevents; ++i) {
        /* Handle new connect */
        if (events[i].data.fd == sockfd) {
            while (1) {
                int nclientfd = accept(sockfd, NULL, NULL);
                if (nclientfd < 0) {
                    break;
                }

                /* Add to event list */
                ev.data.fd = nclientfd;
                ev.events  = EPOLLIN;
                if (epoll_ctl(epfd, EPOLL_CTL_ADD, nclientfd, &ev) != 0) {
                    printf("ff_epoll_ctl failed:%d, %s\n", errno,
                        strerror(errno));
                    break;
                }
            }
        } else {
            if (events[i].events & EPOLLERR ) {
                /* Simply close socket */
                epoll_ctl(epfd, EPOLL_CTL_DEL,  events[i].data.fd, NULL);
                close(events[i].data.fd);
            } else if (events[i].events & EPOLLIN) {
                char buf[PKT_SIZE];
                size_t readlen = read( events[i].data.fd, buf, sizeof(buf));
                if(readlen > 0) {

                    // for pingpong purposes
                    //send(events[i].data.fd, buf, sizeof(buf), 0);
                    write( events[i].data.fd, html, sizeof(html));
                } else {
                    epoll_ctl(epfd, EPOLL_CTL_DEL,  events[i].data.fd, NULL);
                    close( events[i].data.fd);
                }
            } else {
                printf("unknown event: %8.8X\n", events[i].events);
            }
        }
    }
  }
}

int main (int argc, char *argv[])
{
  // add argument smp with number
  int total_thread = atoi(argv[1]);
  printf("total num of thread: %d\n", total_thread);

  // allocate the pthread by pointers
  pthread_t *threads;
  threads = malloc(sizeof(pthread_t)*total_thread);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("server pktsize: %d\n",PKT_SIZE);

  if (sockfd < 0) {
      printf("ff_socket failed\n");
      exit(1);
  }

  int on = 1;
  ioctl(sockfd, FIONBIO, &on);

  struct sockaddr_in my_addr;
  bzero(&my_addr, sizeof(my_addr));
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(8888);
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  int ret = bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));
  if (ret < 0) {
      printf("ff_bind failed\n");
      exit(1);
  }

  ret = listen(sockfd, MAX_EVENTS);
  if (ret < 0) {
      printf("ff_listen failed\n");
      exit(1);
  }

  epfd = epoll_create(1);
  ev.data.fd = sockfd;
  ev.events = EPOLLIN;
  epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);

   int rc;
   long t;
   for(t=0; t<total_thread; t++){
      printf("In main: creating thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, run, (void *)t);
    if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }
   pthread_exit(NULL);

   return 0;
}
