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
#define PKT_SIZE 60


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
                    printf("ff_kevent error:%d, %s\n", errno,
                        strerror(errno));
                        printf("EV_SET howdy\n");
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
            // printf("received packet size: %ld", strlen(buf));
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
}
