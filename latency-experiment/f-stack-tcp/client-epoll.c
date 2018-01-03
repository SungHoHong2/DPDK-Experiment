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

#include "ff_config.h"
#include "ff_api.h"



int main(int argc,char* argv[]){

  int sock;
  struct hostent *hent;
  struct sockaddr_in server;
  char *host = "10.218.111.254";
  unsigned short port = 80;


  if ((hent = gethostbyname(host)) == NULL)
    printf("gethostbyname failed.\n");
  if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    printf("create socket failed: %s\n", strerror(errno));


  bzero(&server, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr = *((struct in_addr*)hent->h_addr);
  printf("[CLIENT] server addr: %s, port: %u\n", inet_ntoa(server.sin_addr), ntohs(server.sin_port));



  if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
      printf("connect to server failed: %s\n", strerror(errno));

  printf("[CLIENT] connected to server %s\n", inet_ntoa(server.sin_addr));




return 0;
}
