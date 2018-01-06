
SOCKET set_fdset(struct listen_elt *list, fd_set *fdset) {

  struct listen_elt *temp;
  SOCKET max = INVALID_SOCKET;
  FD_ZERO(fdset);
  temp = list;

  while (temp) {
    if (temp->fd > max)
      max = temp->fd;

    FD_SET(temp->fd,fdset);
    temp = temp->next;
  }
  return max;
}


void close_listens(struct listen_elt *list) {
  struct listen_elt *temp;
  temp = list;

  while (temp) {
    close(temp->fd);
    temp = temp->next;
  }
}


/* This routine implements the "main event loop" of the netperf server
   code. Code above it will have set-up the control connection so it
   can just merrily go about its business, which is to "schedule"
   performance tests on the server.  */

void
process_requests()
{

  printf("%s\n",__FUNCTION__);


  while (1) {

    if (recv_request() <= 0) {  //finsihing receive
      printf("chara: recv_request\n");
      close(server_sock);
      return;
    }

    switch (netperf_request.content.request_type) {
        case DO_OMNI:
        printf("DO_OMNI\n");
          recv_omni();
          break;
    }
  }
}



void
spawn_child() {

#if defined(HAVE_FORK)
  /* flush the usual suspects */
  fflush(stdin);
  fflush(stdout);
  fflush(stderr);
  fflush(where);

  signal(SIGCLD,SIG_IGN);

  switch (fork()) {
  case 0:
    /* we are the child, but not of inetd.  we don't know if we are
       the child of a daemonized parent or not, so we still need to
       worry about the standard file descriptors. raj 2011-07-11 */

    close_listens(listen_list);
    // open_debug_file();

    child = 1;
    netperf_daemon = 0;
    process_requests();
    exit(0);
    break;
  }

#endif /* HAVE_FORK */
}


void accept_connections() {

  fd_set read_fds, write_fds, except_fds;
  SOCKET high_fd, candidate;
  int num_ready;

  printf("accept_connections....\n");

  while (1) {
    FD_ZERO(&write_fds);
    FD_ZERO(&except_fds);
    high_fd = set_fdset(listen_list,&read_fds);

    num_ready = select(high_fd + 1,
		            &read_fds,
		            &write_fds,
		            &except_fds,
		            NULL);

    /* try to keep things simple */
    candidate = 0;
    // this place runs when it recevied the data.
    while ((num_ready) && (candidate <= high_fd)) {
      printf("number of candidates %d....\n", candidate);

        if (FD_ISSET(candidate,&read_fds)) {
	           // accept_connection(candidate);

             struct sockaddr_storage peeraddr;
             netperf_socklen_t peeraddrlen;
             peeraddrlen = sizeof(peeraddr);

             server_control = candidate;
             server_sock = accept(candidate,(struct sockaddr *)&peeraddr,&peeraddrlen);

             spawn_child();
             /* spawn_child() only returns when we are the parent */
             close(server_sock);

             FD_CLR(candidate,&read_fds);
	            num_ready--;
      }
      else {
	            candidate++;
      }
    }
  }
}



void daemonize() {

  /* flush the usual suspects */
  fflush(stdin);
  fflush(stdout);
  fflush(stderr);

  switch (fork()) {
  case 0:

    /* we are the child. we should get a new "where" to match our new
       pid */
      signal(SIGCLD, SIG_IGN);
      /* ok, we can start accepting control connections now */
      accept_connections();

  default:
    printf("running\n");
    /* we are the parent, nothing to do but exit? */
    exit(0);
  }

}
