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
  char *host = "127.0.0.1";
  unsigned short port = 80;


  if ((hent = gethostbyname(host)) == NULL)
    printf("gethostbyname failed.\n");
  if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    printf("create socket failed: %s\n", strerror(errno));









return 0;
}
