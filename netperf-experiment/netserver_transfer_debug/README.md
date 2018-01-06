### RECV REQUEST

```c
void
recv_request()
{

  return recv_request_n(-1);

}
```

```c
int
recv_request_n(int n)
{

  return recv_request_timed_n(n,0);

}
```

```c

int
recv_request_timed_n(int n, int seconds)
{
  int     tot_bytes_recvd,
    bytes_recvd,
    bytes_left;
  char    * buf = (char * )&netperf_request;
  int     buflen = sizeof(netperf_request);
  int     counter,count;

  fd_set  readfds;
  struct timeval timeout;

  if (n < 0) count = sizeof(netperf_request)/4;
  else count = 2 + n;

  if (count > sizeof(netperf_request)/4) {
    count = sizeof(netperf_request)/4;
  }

  // for the time being, we rather rely on select decrementing timeout
  //   each time to preclude someone with nefarious intent from just
  //   dribbling data to us piecemeal.  of course, who knows what
  //   someone with nefarious intent might come-up with. raj 2012-01-23
  tot_bytes_recvd = 0;
  bytes_recvd = 0;     // nt_lint; bytes_recvd uninitialized if buflen == 0

  bytes_left      = buflen;
  timeout.tv_sec = seconds;
  timeout.tv_usec = 0;
  do {
    FD_ZERO(&readfds);
    FD_SET(server_sock,&readfds);
    if (select(FD_SETSIZE,
	       &readfds,
	       0,
	       0,
	       (seconds > 0) ? &timeout : NULL) != 1) {
      fprintf(where,
	      "Issue receiving request on control connection. Errno %d (%s)\n",
	      errno,
	      strerror(errno));
      fflush(where);
      close(server_sock);
      return -1;
    }

    if ((bytes_recvd = recv(server_sock, buf, bytes_left, 0)) > 0) {
      tot_bytes_recvd += bytes_recvd;
      buf             += bytes_recvd;
      bytes_left      -= bytes_recvd;
    }
  }  while ((tot_bytes_recvd != buflen) &&
	    (bytes_recvd > 0 ));

  // put the request into host order

  for (counter = 0; counter < count; counter++) {
    request_array[counter] = ntohl(request_array[counter]);
  }


  if (bytes_recvd == SOCKET_ERROR) {
    Print_errno(where,
		"recv_request: error on recv");
    fflush(where);
    close(server_sock);
    return -1;
  }

  if (bytes_recvd == 0) {
    // the remote has shutdown the control connection, we should shut
    //   it down as well and return
    close(server_sock);
    return 0;
  }

  if (tot_bytes_recvd < buflen) {
    fprintf(where,
	    "recv_request: partial request received of %d bytes\n",
	    tot_bytes_recvd);
    fflush(where);
    close(server_sock);
    return -1;
  }

  // get the processor affinity request value from netperf this is a
  //   kludge and I know it.  sgb 8/11/04

  local_proc_affinity = netperf_request.content.dummy;

  if (local_proc_affinity != -1) {
    bind_to_specific_processor(local_proc_affinity,0);
  }
  return buflen;
}
```


<br>

### SEND DATA

```c

/* the name is something of a misnomer since this test could send, or
   receive, or both, but it matches the historical netperf routine
   naming convention for what runs in the netserver context. */
void
recv_omni()
{

  struct addrinfo * local_res;
  char local_name[BUFSIZ];
  char port_buffer[PORTBUFSIZE];

  struct sockaddr_storage myaddr_in, peeraddr_in;
  int peeraddr_set = 0;
  SOCKET s_listen, data_socket;
  netperf_socklen_t 	addrlen;

  struct ring_elt * send_ring;
  struct ring_elt * recv_ring;

  int	timed_out = 0;
  int   pad_time = 0;
  int   need_to_connect = 0;
  int   need_to_accept;
  int   connected;
  int   first_receive = 1;
  int   ret;
  uint32_t   temp_recvs;

  struct	omni_request_struct	* omni_request;
  struct	omni_response_struct	* omni_response;
  struct	omni_results_struct	* omni_results;

  omni_request =
    (struct omni_request_struct * )netperf_request.content.test_specific_data;
  omni_response =
    (struct omni_response_struct * )netperf_response.content.test_specific_data;
  omni_results =
    (struct omni_results_struct * )netperf_response.content.test_specific_data;


  fixup_request_n(OMNI_REQUEST_CONV_CUTOFF);

  strncpy(local_cong_control_req,
	  omni_request->cong_control,
	  sizeof(local_cong_control_req));

  netperf_response.content.response_type = OMNI_RESPONSE;

  lss_size_req    = omni_request->send_buf_size;
  lsr_size_req    = omni_request->recv_buf_size;
  loc_nodelay     = (omni_request->flags) & OMNI_NO_DELAY;
  loc_rcvavoid    = omni_request->so_rcvavoid;
  loc_sndavoid    = omni_request->so_sndavoid;
  routing_allowed = (omni_request->flags) & OMNI_ROUTING_ALLOWED;
  want_keepalive  = (omni_request->flags) & OMNI_WANT_KEEPALIVE;
  local_connected = (omni_request->flags) & OMNI_USE_CONNECTED;
  local_socket_prio = omni_request->socket_prio;
  local_socket_tos  = omni_request->socket_tos;
  want_defer_accept = omni_request->flags & OMNI_WANT_DEFER_ACCEPT;

#ifdef WANT_INTERVALS
  interval_usecs = omni_request->interval_usecs;
  interval_wate  = interval_usecs / 1000;
  interval_burst = omni_request->interval_burst;
#else
  interval_usecs = 0;
  interval_wate  = 1;
  interval_burst = 0;
#endif

  connection_test = omni_request->flags & OMNI_CONNECT_TEST;
#ifdef TCP_FASTOPEN
  use_fastopen = omni_request->flags & OMNI_FASTOPEN;
#endif

#ifdef IP_MTU_DISCOVER
  use_mtu_discover = omni_request->flags & OMNI_USE_MTU_DISCOVER;
#endif

  direction       = omni_request->direction;
  use_pktinfo = (omni_request->flags) & OMNI_USE_PKTINFO;

  // let's be quite certain the fill file string is null terminated
  omni_request->fill_file[sizeof(omni_request->fill_file) - 1] = '\0';
  strncpy(local_fill_file,
	  omni_request->fill_file,
	  sizeof(local_fill_file));

 // kludgy, because I have no way at present to say how many bytes
 //     needed to be swapped around for the request from which this is
 //     pulled, and it is probably all wrong for IPv6 :(
  switch (nf_to_af(omni_request->ipfamily)) {

  case AF_INET:
  default:
    for (ret=0; ret < 4; ret++) {
      omni_request->netserver_ip[ret] = htonl(omni_request->netserver_ip[ret]);
      omni_request->netperf_ip[ret] = htonl(omni_request->netperf_ip[ret]);
    }
    break;
  }

  set_hostname_and_port_2(omni_request->netserver_ip,
			  local_name,
			  port_buffer,
			  nf_to_af(omni_request->ipfamily),
			  omni_request->data_port);

  local_res = complete_addrinfo(local_name,
				local_name,
				port_buffer,
				nf_to_af(omni_request->ipfamily),
				nst_to_hst(omni_request->socket_type),
				omni_request->protocol,
				0);

  s_listen = omni_create_data_socket(local_res);

  if (s_listen == INVALID_SOCKET) {
    netperf_response.content.serv_errno = errno;
    send_response();
    exit(-1);
  }


  omni_response->send_size = omni_request->send_size;
  omni_response->send_width = omni_request->send_width;
  omni_response->socket_prio = local_socket_prio;
  omni_response->socket_tos = local_socket_tos;

  if (omni_request->direction & NETPERF_XMIT) {
#ifdef fo
    // do we need to set multicast ttl?
    if (is_multicast_addr(remote_res)) {
      // yes, s_listen - for a UDP test we will be copying it to
	    // data_socket but that hasn't happened yet. raj 20100315
      // set_multicast_ttl(s_listen);
    }
#endif

    if (omni_request->response_size > 0) {
      // request/response_test
      bytes_to_send = omni_request->response_size;
      if (omni_request->send_width == 0) send_width = 1;
      else send_width = omni_request->send_width;
    }
    else {
      if (omni_request->send_size == -1) {
	bytes_to_send = choose_send_size(lss_size,omni_request->protocol);
      }
      else bytes_to_send = omni_request->send_size;
      // set the send_width
      if (omni_request->send_width == 0) {
	send_width = (lss_size/bytes_to_send) + 1;
	if (send_width == 1) send_width++;
      }
      else
	send_width = omni_request->send_width;
    }
    send_ring = allocate_buffer_ring(send_width,
				     bytes_to_send,
				     omni_request->send_alignment,
				     omni_request->send_offset);

    omni_response->send_width = send_width;
    omni_response->send_size = bytes_to_send;
  }

  omni_response->receive_size = omni_request->receive_size;
  omni_response->recv_width = omni_request->recv_width;
  if (omni_request->direction & NETPERF_RECV) {

    // do we need to join a multicast group?
    if (is_multicast_addr(local_res)) {
      join_multicast_addr(s_listen, local_res);
    }

    if (omni_request->request_size > 0) {
      /* request/response test */
      bytes_to_recv = omni_request->request_size;
      if (omni_request->recv_width == 0) recv_width = 1;
      else recv_width = omni_request->recv_width;
    }
    else {
      if (omni_request->receive_size == -1) {
	if (lsr_size > 0) bytes_to_recv = lsr_size;
	else  bytes_to_recv = 4096;
      }
      else {
	bytes_to_recv = omni_request->receive_size;
      }
      /* set the recv_width */
      if (omni_request->recv_width == 0) {
	recv_width = (lsr_size/bytes_to_recv) + 1;
	if (recv_width == 1) recv_width++;
      }
      else
	recv_width = omni_request->recv_width;
    }
    recv_ring = allocate_buffer_ring(recv_width,
				     bytes_to_recv,
				     omni_request->recv_alignment,
				     omni_request->recv_offset);

    omni_response->receive_size = bytes_to_recv;
    omni_response->recv_width = recv_width;
  }


  need_to_accept = (omni_request->protocol != IPPROTO_UDP);

  /* we need to hang a listen for everything that needs at least one
     accept. the age-old constant of 5 is probably OK for our purposes
     but does not necessarily represent best practice */
  if (need_to_accept) {
    int backlog = 5;
#ifdef TCP_FASTOPEN
    /* one of these days I will have to go find-out what the backlog
       is supposed to be here.  until then, I'll just set it to five
       like the listen() call does - it is classic, and was what was
       used in the online example I found */
    if (use_fastopen &&
	(setsockopt(s_listen,IPPROTO_TCP, TCP_FASTOPEN, &backlog, sizeof(backlog)) ==
	 SOCKET_ERROR)) {
      netperf_response.content.serv_errno = errno;
      close(s_listen);
      send_response();
      if (debug) {
	fprintf(where,"netperfserver: %s could not fastopen\n",__FUNCTION__);
	fflush(where);
      }
      exit(1);
    }
#endif /* TCP_FASTOPEN */
#ifdef TCP_DEFER_ACCEPT
    if (want_defer_accept &&
	(setsockopt(s_listen, IPPROTO_TCP, TCP_DEFER_ACCEPT, &backlog, sizeof(backlog)) == SOCKET_ERROR)) {
      netperf_response.content.serv_errno = errno;
      close(s_listen);
      send_response();
      if (debug) {
	fprintf(where,
		"netperfserver: %s could not defer accept\n",__FUNCTION__);
	fflush(where);
      }
      exit(1);
    }
#endif /* TCP_DEFER_ACCEPT */
    if (listen(s_listen, backlog) == SOCKET_ERROR) {
      netperf_response.content.serv_errno = errno;
      close(s_listen);
      send_response();
      if (debug) {
	fprintf(where,"netperfserver: %s could not listen\n",__FUNCTION__);
	fflush(where);
      }
      exit(1);
    }
  }

  /* now get the port number assigned by the system  */
  addrlen = sizeof(myaddr_in);
  if (getsockname(s_listen,
		  (struct sockaddr *)&myaddr_in,
		  &addrlen) == SOCKET_ERROR){
    netperf_response.content.serv_errno = errno;
    close(s_listen);
    send_response();
    if (debug) {
      fprintf(where,"could not getsockname\n");
      fflush(where);
    }
    exit(-1);
  }

  /* Now myaddr_in contains the port and the internet address this is
     returned to the sender also implicitly telling the sender that
     the socket buffer sizing has been done. likely as not, the IP
     address will be the wildcard - so we only really need to extract
     the port number. since send_response is going to call htonl on
     all the fields, we want to initially put the port number in there
     in host order. */

  omni_response->data_port =
    (int) ntohs(((struct sockaddr_in *)&myaddr_in)->sin_port);
  if (debug) {
    fprintf(where,"telling the remote to call me at %d\n",
	    omni_response->data_port);
    fflush(where);
  }
  netperf_response.content.serv_errno   = 0;

  /* But wait, there's more. If the initiator wanted cpu measurements, */
  /* then we must call the calibrate routine, which will return the max */
  /* rate back to the initiator. If the CPU was not to be measured, or */
  /* something went wrong with the calibration, we will return a 0.0 to */
  /* the initiator. */

  omni_response->cpu_rate = (float)0.0; 	/* assume no cpu */
  omni_response->flags &= ~OMNI_MEASURE_CPU;
  if (omni_request->flags & OMNI_MEASURE_CPU) {
    omni_response->flags |= OMNI_MEASURE_CPU;
    omni_response->cpu_rate =
      calibrate_local_cpu(omni_request->cpu_rate);
  }

  /* before we send the response back to the initiator, pull some of */
  /* the socket parms from the globals */
  omni_response->send_buf_size = lss_size;
  omni_response->recv_buf_size = lsr_size;
  if (loc_nodelay)
    omni_response->flags |= OMNI_NO_DELAY;
  else
    omni_response->flags &= ~OMNI_NO_DELAY;

  omni_response->so_rcvavoid = loc_rcvavoid;
  omni_response->so_sndavoid = loc_sndavoid;
  omni_response->interval_usecs = interval_usecs;
  omni_response->interval_burst = interval_burst;

  send_response_n(OMNI_RESPONSE_CONV_CUTOFF); /* brittle, but functional */

  local_send_calls = 0;
  local_receive_calls = 0;

  addrlen = sizeof(peeraddr_in);
  memset(&peeraddr_in,0,sizeof(peeraddr_in));

  /* Now it's time to start receiving data on the connection. We will */
  /* first grab the apropriate counters and then start grabbing. */

  cpu_start(omni_request->flags & OMNI_MEASURE_CPU);

  /* if the test is timed, set a timer of suitable length.  if the
     test is by byte/transaction count, we don't need a timer - or
     rather we rely on the netperf to only ask us to do transaction
     counts over "reliable" protocols.  perhaps at some point we
     should add a check herebouts to verify that... */

  if (omni_request->test_length >= 0) {
    times_up = 0;
    units_remaining = 0;
	test_time=omni_request->test_length;
    /* if we are the sender and only sending, then we don't need/want
       the padding, otherwise, we need the padding */
    if (!(NETPERF_XMIT_ONLY(omni_request->direction)) &&
	(omni_request->test_length > 0))
      pad_time = PAD_TIME;
    start_timer(omni_request->test_length + pad_time);
  }
  else {
    times_up = 1;
    units_remaining = omni_request->test_length * -1;
  }

#if defined(WANT_INTERVALS)
  INTERVALS_INIT();
#endif /* WANT_INTERVALS */


  trans_completed = 0;
  bytes_sent = 0;
  bytes_received = 0;
  connected = 0;

  while ((!times_up) || (units_remaining > 0)) {

    if (need_to_accept) {
      /* accept a connection from the remote */
#ifdef WIN32
      /* The test timer will probably fire during this accept,
	 so to make the start_timer above work we have to move
	 it to close s_listen while we are blocked on accept. */
      win_kludge_socket = s_listen;
#endif
      if ((data_socket=accept(s_listen,
			      (struct sockaddr *)&peeraddr_in,
			      &addrlen)) == INVALID_SOCKET) {
	if (errno == EINTR) {
	  /* the timer popped */
	  times_up = 1; /* ostensibly the signal hander dealt with this?*/
	  timed_out = 1;
	  break;
	}
	netperf_response.content.serv_errno = errno;
	send_response();
	fprintf(where,"%s: accept: errno = %d\n",__FUNCTION__,errno);
	fflush(where);
	close(s_listen);

	exit(-1);
      }

      if (debug) {
	fprintf(where,"%s: accepted data connection.\n",__FUNCTION__);
	fflush(where);
      }
      need_to_accept = 0;
      connected = 1;

#ifdef KLUDGE_SOCKET_OPTIONS
      /* this is for those systems which *INCORRECTLY* fail to pass
	 attributes across an accept() call. Including this goes
	 against my better judgement :( raj 11/95 */

      kludge_socket_options(data_socket);

#endif /* KLUDGE_SOCKET_OPTIONS */

    }
    else {
      /* I wonder if duping would be better here? we also need to set
	 peeraddr_in so we can send to netperf if this isn't a
	 request/response test or if we are going to connect() the
	 socket, but we only need to do it once. */
      if ((omni_request->protocol == IPPROTO_UDP) &&
	  (!peeraddr_set)) {
	peeraddr_set = 1;
	data_socket = s_listen;
	set_sockaddr_family_addr_port(&peeraddr_in,
				      nf_to_af(omni_request->ipfamily),
				      omni_request->netperf_ip,
				      omni_request->netperf_port);
      }
    }

#ifdef WIN32
  /* this is used so the timer thread can close the socket out from
     under us, which to date is the easiest/cleanest/least
     Windows-specific way I can find to force the winsock calls to
     return WSAEINTR with the test is over. anything that will run on
     95 and NT and is closer to what netperf expects from Unix signals
     and such would be appreciated raj 1/96 */
  win_kludge_socket = data_socket;
#endif /* WIN32 */

    /* in recv_omni, we check recv first, and _then_ send, otherwise,
       a request/response test will be all messed-up :) and that then
       is why there are two routines to rule them all rather than just
       one :) */
    if ((omni_request->direction & NETPERF_RECV) &&
	((!times_up) || (units_remaining > 0))) {
      ret = recv_data(data_socket,
		      recv_ring,
		      bytes_to_recv,
		      (connected) ? NULL : (struct sockaddr *)&peeraddr_in,
		      &addrlen,
		      /* if XMIT also, then this is RR test so waitall */
		      (direction & NETPERF_XMIT) ? NETPERF_WAITALL: 0,
		      &temp_recvs);
      if (ret > 0) {
	/* if this is a recv-only test controlled by byte count we
	   decrement the units_remaining by the bytes received */
	if (!(direction & NETPERF_XMIT) && (units_remaining > 0)) {
	  units_remaining -= ret;
	}
	bytes_received += ret;
	local_receive_calls += temp_recvs;
	if (first_receive && local_connected) {
	  connect(data_socket,
		  (struct sockaddr *)&peeraddr_in,
		  addrlen);
	  first_receive = 0;
	}
      }
      else if (ret == 0) {
	/* is this the end of a test, just a zero-byte recv, or
	   something else? that is an exceedingly good question and
	   one for which I don't presently have a good answer, but
	   that won't stop me from guessing :) raj 2008-01-09 */
	if (!((connection_test) || (null_message_ok))) {
	  /* if it is neither a connection_test nor null_message_ok it
	     must be the end of the test */
	  times_up = 1;
	  break;
	}
	local_receive_calls += temp_recvs;
      }
      else if (ret == -1) {
	/* test timed-out */
	times_up = 1;
	timed_out = 1;
	break;
      }
      else {
	/* presently at least, -2 and -3 are equally bad on recv */
	/* we need a response message here for the control connection
	   before we exit! */
	netperf_response.content.serv_errno = errno;
	send_response();
	exit(-1);
      }
      recv_ring = recv_ring->next;
    }

    /* if we should try to send something, then by all means, let us
       try to send something. */
    if ((omni_request->direction & NETPERF_XMIT) &&
	((!times_up) || (units_remaining > 0))) {

      /* there used to be some code here looking sched_yield() until
	 there was no more queued, unsent data on the socket but
	 frankly, I've no idea what that was all about so I have
	 removed it. It may have been part of a kludge to try to avoid
	 coalescing requests and responses */

      if (omni_request->protocol == IPPROTO_UDP && need_to_connect &&
          !connected) {
        if (connect(data_socket,
                    (struct sockaddr*)&peeraddr_in,
                    addrlen) == INVALID_SOCKET) {
	  netperf_response.content.serv_errno = errno;
	  send_response();
	  close(data_socket);
	  exit(-1);
        }
        connected = 1;
      }

      ret = send_data(data_socket,
		      send_ring,
		      bytes_to_send,
		      (connected) ? NULL : (struct sockaddr *)&peeraddr_in,
		      addrlen,
		      omni_request->protocol);

      /* the order of these if's will seem a triffle strange, but they
	 are my best guess as to order of probabilty and/or importance
	 to the overhead raj 2008-01-09*/
      if (ret == bytes_to_send) {
	/* if this is a send-only test controlled by byte count we
	   decrement units_remaining by the bytes sent */
	if (!(direction & NETPERF_RECV) && (units_remaining > 0)) {
	  units_remaining -= ret;
	}
	bytes_sent += ret;
	send_ring = send_ring->next;
	local_send_calls++;
      }
      else if (ret == -2) {
	/* what to do here -2 means a non-fatal error - probably
	   ENOBUFS and so our send didn't happen.  in the old code for
	   UDP_STREAM we would just continue in the while loop.  it
	   isn't clear that is what to do here, so we will simply
	   increment the failed_sends stat and fall-through. If this
	   is a UDP_STREAM style of test, the net effect should be the
	   same. if this is a UDP_RR with a really-big burst count, I
	   don't think we were checking for ENOBUFS there anyway and
	   so would have failed.  Here we can just let things
	   slide. */
	failed_sends++;
      }
      else if (ret == 0) {
	/* was this a zero-byte send? if it was, then ostensibly we
	   would hit the ret == bytes_to_send case which means we'd
	   never get here as we are using blocking semantics */
      }
      else if (ret == -1) {
	times_up = 1;
	timed_out = 1;
	break;
      }
      else {
	/* we need a response message back to netperf here before we
	   exit */
	/* NEED RESPONSE; */
	netperf_response.content.serv_errno = errno;
	send_response();
	exit(-1);
      }

    }

    if (connection_test) {
#ifdef __linux
      /* so, "Linux" with autotuning likes to alter the socket buffer
	 sizes over the life of the connection, but only does so when
	 one takes the defaults at time of socket creation.  if we
	 took those defaults, we should inquire as to what the values
	 ultimately became. raj 2008-01-15 */
      /* but as annoying as it is to have to make these calls, don't
	 penalize linux by calling them over and over again. instead
	 we will simply ass-u-me that it will become the same value
	 over and over again. raj 20100917 */
      if ((lsr_size_req < 0) && (-1 == lsr_size_end))
	get_sock_buffer(data_socket, RECV_BUFFER, &lsr_size_end);
      else
	lsr_size_end = lsr_size;
      if ((lss_size_req < 0) && (-1 == lss_size_end))
	get_sock_buffer(data_socket, SEND_BUFFER, &lss_size_end);
      else
	lss_size_end = lss_size;
#else
      lsr_size_end = lsr_size;
      lss_size_end = lss_size;
#endif
      ret = close_data_socket(data_socket,NULL,0,omni_request->protocol);
      if (ret == -1) {
	times_up = 1;
	timed_out = 1;
	break;
      }
      else if (ret < 0) {
	netperf_response.content.serv_errno = errno;
	send_response();
	perror("netperf: recv_omni: close_data_socket failed");
	fflush(where);
	exit(-1);
      }
      /* we will need a new connection to be established */
      need_to_accept = 1;
      connected = 0;
    }

#if defined(WANT_INTERVALS)
    INTERVALS_WAIT();
#endif /* WANT_INTERVALS */

    /* was this a "transaction" test? don't for get that a TCP_CC
       style test will have no xmit or recv :) so, we check for either
       both XMIT and RECV set, or neither XMIT nor RECV set */
    if (NETPERF_IS_RR(omni_request->direction)) {
      trans_completed++;
      if (units_remaining) {
	units_remaining--;
      }
    }
  }

  /* The current iteration loop now exits due to timeout or unit count
     being  reached */
  stop_timer();
  cpu_stop(omni_request->flags & OMNI_MEASURE_CPU,&elapsed_time);
  close(s_listen);

#if defined(WANT_INTERVALS)
#ifdef WIN32
  stop_itimer();
#endif
#endif /* WANT_INTERVALS */

 if (timed_out) {
    /* we ended the test by time, which may have been PAD_TIME seconds
       longer than we wanted to run. so, we want to subtract pad_time
       from the elapsed_time. if we didn't pad the timer pad_time will
       be 0 so we can just subtract it anyway :) */
    if (debug) {
      fprintf(where,"Adjusting elapsed time by %d seconds\n",pad_time);
      fflush(where);
    }
    elapsed_time -= pad_time;
  }

  remote_transport_retrans = get_transport_retrans(data_socket,
						   omni_request->protocol);

  if (connected) {
#ifdef __linux
    /* so, "Linux" with autotuning likes to alter the socket buffer
       sizes over the life of the connection, but only does so when
       one takes the defaults at time of socket creation.  if we took
       those defaults, we should inquire as to what the values
       ultimately became. raj 2008-01-15 */
    if (lsr_size_req < 0)
      get_sock_buffer(data_socket, RECV_BUFFER, &lsr_size_end);
    else
      lsr_size_end = lsr_size;
    if (lss_size_req < 0)
      get_sock_buffer(data_socket, SEND_BUFFER, &lss_size_end);
    else
      lss_size_end = lss_size;
#else
    lsr_size_end = lsr_size;
    lss_size_end = lss_size;
#endif
    if (omni_request->flags & OMNI_WANT_REM_CONG) {
      get_transport_cong_control(data_socket,
				 local_res->ai_protocol,
				 omni_results->cong_control,
				 sizeof(omni_results->cong_control));
    }
    else {
      strncpy(omni_results->cong_control,"",sizeof(omni_results->cong_control));
    }


    close_data_socket(data_socket,NULL,0,omni_request->protocol);
  }
  else {
    close_data_socket(data_socket,(struct sockaddr *)&peeraddr_in,addrlen,omni_request->protocol);
    lsr_size_end = lsr_size;
    lss_size_end = lss_size;
  }

  /* send the results to the sender  */

  omni_results->send_calls      = (uint32_t) local_send_calls;
  omni_results->bytes_received_lo = bytes_received & 0x00000000FFFFFFFFULL;
  omni_results->bytes_received_hi = (bytes_received & 0xFFFFFFFF00000000ULL) >> 32;
  omni_results->recv_buf_size   = lsr_size_end;
  omni_results->recv_calls      = (uint32_t) local_receive_calls;
  omni_results->bytes_sent_lo   = bytes_sent & 0x00000000FFFFFFFFULL;
  omni_results->bytes_sent_hi   = (bytes_sent & 0xFFFFFFFF00000000ULL) >> 32;
  omni_results->send_buf_size   = lss_size_end;
  omni_results->trans_received	= (uint32_t) trans_completed;
  omni_results->elapsed_time	= elapsed_time;
  omni_results->transport_retrans = remote_transport_retrans;
  omni_results->cpu_method      = cpu_method;
  omni_results->num_cpus        = lib_num_loc_cpus;
  if (omni_request->flags & OMNI_MEASURE_CPU) {
    omni_results->cpu_util            = calc_cpu_util(elapsed_time);
    omni_results->cpu_percent_user    = lib_local_cpu_stats.cpu_user;
    omni_results->cpu_percent_system  = lib_local_cpu_stats.cpu_system;
    omni_results->cpu_percent_iowait  = lib_local_cpu_stats.cpu_iowait;
    omni_results->cpu_percent_irq     = lib_local_cpu_stats.cpu_irq;
    omni_results->cpu_percent_swintr  = lib_local_cpu_stats.cpu_swintr;
    omni_results->peak_cpu_util       = lib_local_cpu_stats.peak_cpu_util;
    omni_results->peak_cpu_id         = lib_local_cpu_stats.peak_cpu_id;
  }

#if defined(WANT_INTERVALS)
#ifdef WIN32
  stop_itimer();
#endif
#endif /* WANT_INTERVALS */

  if (debug) {
    fprintf(where,
	    "%s: test complete, sending results.\n",
	    __FUNCTION__);
    fflush(where);
  }

  send_response_n(OMNI_RESULTS_CONV_CUTOFF);

}
```
