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
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>


#define MAX_EVENTS 512
#define PKT_SIZE 64


int main(int argc, char * argv[])
{
   int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
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

    /*
      * Create epoll context.
      */
    int epollfd;
    int epfd;

    epollfd = epoll_create(MAX_EVENTS);
    if(-1 == epollfd)
    {
        printf("Failed to create epoll context.%s", strerror(errno));
        exit(1);
    }

    struct epoll_event ev;
    struct epoll_event events[MAX_EVENTS];
    while(1){

       int nevents = epoll_wait(epollfd, events, MAX_EVENTS, -1);
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
                       printf("received length: %ld\n", strlen(buf));
                       send(events[i].data.fd, buf, sizeof(buf), 0);
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





    // EV_SET(&kevSet, sockfd, EVFILT_READ, EV_ADD, 0, MAX_EVENTS, NULL);
    //
    // assert((kq = ff_kqueue()) > 0);
    //
    // /* Update kqueue */
    // ff_kevent(kq, &kevSet, 1, NULL, 0, NULL);
    //
    // ff_run(loop, NULL);
    return 0;


}
