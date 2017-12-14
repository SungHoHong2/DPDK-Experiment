#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT "3490" // the port client will be connecting to
#define MAXDATASIZE 1464 // max number of bytes we can get at once


const char clr[] = { 27, '[', '2', 'J', '\0' };
const char topLeft[] = { 27, '[', '1', ';', '1', 'H','\0' };
struct sockaddr_storage their_addr; // connector's address information

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa){
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    int sockfd, numbytes, new_fd;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    socklen_t sin_size;
    long int tx_throughput;
    long int rx_throughput;
    double latency;
    double latency_timelimit = 10.0;
    static time_t start; //adding timer
    int intervals;


    intervals = tx_throughput = rx_throughput = 0;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    // get information of the server
    if ((rv = getaddrinfo("lab01", PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }
        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    //
    // while(1){
    //   send(sockfd, "Hello, world! from client", 100, 0);
    // }
    // CHARA begin

    time (&start); //useful call
    while(1){

                char *data;
                data = (char *)malloc(MAXDATASIZE * sizeof(char));
                memset( data, '\0', MAXDATASIZE * sizeof(char) );

                send(sockfd, data, MAXDATASIZE, 0);

                tx_throughput+=strlen(data);

                if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
                    perror("recv");
                    exit(1);
                }

                rx_throughput+=strlen(buf);
                latency = difftime( time(0), start);

                if(++intervals==2000){
                    /* Clear screen and move to top left */
                    printf("%s%s", clr, topLeft);
                    printf("\nTCP Pingpong Client ====================================");
                    printf("\nStatistics for port  ------------------------------"
                         "\nRX: %ld"
                         "\nTX: %ld"
                         "\nLatency: %f"
                         ,rx_throughput
                         ,tx_throughput
                         ,latency);
                    printf("\n====================================================\n");
                    intervals = 0;

                    if(latency==10) break;
                }
            }

    close(sockfd);
    return 0;
}
