#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "ff_api.h"

int sockfd = -1;
int check_connection = 0;


int loop(void *arg) {
    struct sockaddr_in my_addr;
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(80);
    // my_addr.sin_port = htons(22);
    my_addr.sin_addr.s_addr = inet_addr("10.218.111.254");
    // my_addr.sin_addr.s_addr = inet_addr("10.218.111.252");


    int on = 1;
    ff_ioctl(sockfd, FIONBIO, &on);
    if (ff_connect(sockfd, (struct linux_sockaddr *)&my_addr, sizeof(my_addr)) == -1) {
        printf("ff_connect failed %d: %s\n", errno, strerror(errno));
    } else {
        printf("ff_connect OK\n");
        while(1){}
    }



}

int main(int argc, char * argv[]) {
    ff_init(argc, argv);

    sockfd = ff_socket(AF_INET, SOCK_STREAM, 0);
    printf("sockfd:%d\n", sockfd);
    if (sockfd < 0) {
        printf("ff_socket failed\n");
        exit(1);
    }

    ff_run(loop, NULL);
    return 0;
}
