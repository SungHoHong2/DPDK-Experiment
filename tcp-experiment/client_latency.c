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
#include <sys/fcntl.h>

#define PORT "3490" // the port client will be connecting to
// #define PKTSIZE 1464 // max number of bytes we can get at once
#define PKT_SIZE 64
#define NUM_ROUNDS 100000

const char clr[] = { 27, '[', '2', 'J', '\0' };
const char topLeft[] = { 27, '[', '1', ';', '1', 'H','\0' };
struct sockaddr_storage their_addr; // connector's address information
static long int tx_throughput;
static long int rx_throughput;
static int packets;
static double latency, prev_latency;
static long int real_latency;
;


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa){
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void print_log(){
  /* Clear screen and move to top left */
  printf("%s%s", clr, topLeft);
  printf("\nTCP Pingpong Client ====================================");
  printf("\nByte Statistics ------------------------------"
         "\nPKT-SIZE: %d"
         "\nBytes sent: %ld"
         "\nBytes received: %ld"
         "\nDuration: %f"
         ,PKT_SIZE
         ,tx_throughput
         ,rx_throughput
         ,latency);
  printf("\nPacket Statistics ------------------------------"
         "\nPackets received: %d"
         "\nLatency: %ld"
         ,packets
         ,real_latency);
  printf("\n========================================================\n");
}

int main(){
    int sockfd, numbytes, new_fd;
    char recv_data[PKT_SIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    socklen_t sin_size;
    long int success = 0;
    static time_t start; //adding timer
    struct timespec tps, tpe;
    FILE * nic_file;
    char nic_str[100];

    tx_throughput = rx_throughput = 0;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    fcntl(sockfd, F_SETFL, O_NONBLOCK);


    // get information of the server
    if ((rv = getaddrinfo("172.24.30.31", PORT, &hints, &servinfo)) != 0) {
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


  nic_file = fopen("/sys/class/net/ib0/statistics/rx_packets" , "r");
  if (nic_file) {
      fscanf(nic_file, "%s", nic_str);
      packets = atoi(nic_str);
      fclose(nic_file);
  }


  time (&start);
  clock_gettime(CLOCK_REALTIME, &tps);
  for(int i=0; i<NUM_ROUNDS; i++){

                prev_latency = latency;
                char send_data[PKT_SIZE];
                memset( send_data, '*', PKT_SIZE * sizeof(char));
                success=send(sockfd, send_data, PKT_SIZE, 0);

                if(success && strlen(send_data)>0){
                    tx_throughput += strlen(send_data);
                }

                success=recv(sockfd, recv_data, PKT_SIZE-1, 0);

                if(success && strlen(recv_data)>0){
                    rx_throughput += strlen(recv_data);
                }

                latency = difftime(time(0), start);
                if((latency-prev_latency)>=1){
                  print_log();
                }
            }

    clock_gettime(CLOCK_REALTIME, &tpe);
    real_latency = tpe.tv_nsec - tps.tv_nsec;


    nic_file = fopen("/sys/class/net/ib0/statistics/rx_packets" , "r");
    if (nic_file) {
        fscanf(nic_file, "%s", nic_str);
        packets = atoi(nic_str) - packets;
        printf("%d\n",packets);
        fclose(nic_file);
    }

    print_log();


    close(sockfd);
    return 0;
}
