#include "netserver_h.h"
#include "create_listens.h"
#include "daemonize_h.h"

int _cdecl main(int argc, char *argv[]) {

  /* Save away the program name */
  program = (char *)malloc(strlen(argv[0]) + 1);
  strcpy(program, argv[0]);

  child = 0; // active
  not_inetd = 0; // active
  netperf_daemon = 0; // active

  netlib_init();

  strncpy(local_host_name,"",sizeof(local_host_name));
  local_address_family = AF_UNSPEC;
  strncpy(listen_port,TEST_PORT,sizeof(listen_port));

  struct sockaddr_storage name;
  netperf_socklen_t namelen;

  namelen = sizeof(name);
  if (getsockname(0,(struct sockaddr *)&name, &namelen) == SOCKET_ERROR) {
      not_inetd = 1;
  }

    /* we are the top netserver process, so we have to create the
       listen endpoint(s) and decide if we want to daemonize */
    // setup_listens(local_host_name,listen_port,local_address_family);
    int no_name = 1;  //active
    create_listens("::0",listen_port,AF_INET6);  // active
    create_listens("0.0.0.0",listen_port,AF_INET);  // active

    if (listen_list) {
      fprintf(stdout,
  	    "Starting netserver with host '%s' port '%s' and family %s\n",
  	    (no_name) ? "IN(6)ADDR_ANY" : local_host_name,
  	    listen_port,
  	    inet_ftos(af));
      fflush(stdout);
    }
    else {
      fprintf(stderr,
  	    "Unable to start netserver with  '%s' port '%s' and family %s\n",
  	    (no_name) ? "IN(6)ADDR_ANY" : local_host_name,
  	    listen_port,
  	    inet_ftos(af));
      fflush(stderr);
      exit(1);
    }

    daemonize();
  return 0;

}
