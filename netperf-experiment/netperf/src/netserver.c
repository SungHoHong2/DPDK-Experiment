#include "netperf_version.h"

char	netserver_id[]="\
@(#)netserver.c (c) Copyright 1993-2012 Hewlett-Packard Co. Version 2.6.0";
#include "config.h"

#if HAVE_STRING_H
# if !STDC_HEADERS && HAVE_MEMORY_H
#  include <memory.h>
# endif
# include <string.h>
#endif

#if HAVE_STRINGS_H
# include <strings.h>
#endif

#if HAVE_LIMITS_H
# include <limits.h>
#endif

#if HAVE_SYS_IPC_H
#include <sys/ipc.h>
#endif

#if HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

#if HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif

#if HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif

#if HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif

#if HAVE_NETDB_H
#include <netdb.h>
#endif

#if HAVE_UNISTD_H
#include <unistd.h>
#endif

#if HAVE_STDLIB_H
#include <stdlib.h>
#endif

#if HAVE_ERRNO_H
#include <errno.h>
#endif

#if HAVE_SIGNAL_H
#include <signal.h>
/* some OS's have SIGCLD defined as SIGCHLD */
#ifndef SIGCLD
#define SIGCLD SIGCHLD
#endif /* SIGCLD */

#endif

#if !defined(HAVE_SETSID)
#if HAVE_SYS_WAIT_H
#include <sys/wait.h>
#endif
#endif

#ifdef WIN32
#include <time.h>
#include <winsock2.h>

#if HAVE_WS2TCPIP_H
#include <ws2tcpip.h>
#endif

#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

#include "missing\stdint.h"

#define strdup _strdup
#define sleep(x) Sleep((x)*1000)
#define netperf_socklen_t socklen_t
#endif /* WIN32 */

/* unconditional system includes */

#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>

/* netperf includes */
#include "netlib.h"
#include "nettest_bsd.h"

#ifdef WANT_UNIX
#include "nettest_unix.h"
#endif /* WANT_UNIX */

#ifdef WANT_DLPI
#include "nettest_dlpi.h"
#endif /* WANT_DLPI */

#ifdef WANT_SCTP
#include "nettest_sctp.h"
#endif
#include "netsh.h"

char     FileName[PATH_MAX];
char     listen_port[10];

char *netperf_version;
int     *request_array;
int     *response_array;


struct listen_elt {
  SOCKET fd;
  struct listen_elt *next;
};

struct listen_elt *listen_list = NULL;
SOCKET   server_control;

int      child;
int      netperf_daemon;
int      daemon_parent = 0;
int      not_inetd;
int      want_daemonize;
int      spawn_on_accept;
int      suppress_debug = 0;

extern	char	*optarg;
extern	int	optind, opterr;

void
netlib_init_cpu_map__ex() {

  int i;
#ifdef HAVE_MPCTL
  int num;
  i = 0;
  /* I go back and forth on whether this should be the system-wide set
     of calls, or if the processor set versions (sans the _SYS) should
     be used.  at the moment I believe that the system-wide version
     should be used. raj 2006-04-03 */
  num = mpctl(MPC_GETNUMSPUS_SYS,0,0);
  lib_cpu_map[i] = mpctl(MPC_GETFIRSTSPU_SYS,0,0);
  for (i = 1;((i < num) && (i < MAXCPUS)); i++) {
    lib_cpu_map[i] = mpctl(MPC_GETNEXTSPU_SYS,lib_cpu_map[i-1],0);
  }
  /* from here, we set them all to -1 because if we launch more
     loopers than actual CPUs, well, I'm not sure why :) */
  for (; i < MAXCPUS; i++) {
    lib_cpu_map[i] = -1;
  }

#else
  /* we assume that there is indeed a contiguous mapping */
  for (i = 0; i < MAXCPUS; i++) {
    lib_cpu_map[i] = i;
  }
#endif
}


void
create_listens(char hostname[], char port[], int af) {

  struct addrinfo hints;
  struct addrinfo *local_res;
  struct addrinfo *local_res_temp;
  int count, error;
  int on = 1;
  SOCKET temp_socket;
  struct listen_elt *temp_elt;

  if (debug) {
    fprintf(stderr,
	    "%s: called with host '%s' port '%s' family %s(%d)\n",
	    __FUNCTION__,
            hostname,
	    port,
	    inet_ftos(af),
            af);
    fflush(stderr);
  }
 memset(&hints,0,sizeof(hints));
  hints.ai_family = af;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;

  count = 0;
  do {
    error = getaddrinfo((char *)hostname,
                        (char *)port,
                        &hints,
                        &local_res);
    count += 1;
    if (error == EAI_AGAIN) {
      if (debug) {
        fprintf(stderr,
		"%s: Sleeping on getaddrinfo EAI_AGAIN\n",
		__FUNCTION__);
        fflush(stderr);
      }
      sleep(1);
    }
  } while ((error == EAI_AGAIN) && (count <= 5));

  if (error) {
    if (debug) {

      fprintf(stderr,
	      "%s: could not resolve remote '%s' port '%s' af %d\n"
	      "\tgetaddrinfo returned %s (%d)\n",
	      __FUNCTION__,
	      hostname,
	      port,
	      af,
	      gai_strerror(error),
	      error);

    }
    return;
  }

  if (debug) {
    dump_addrinfo(stderr, local_res, hostname, port, af);
  }

  local_res_temp = local_res;

  while (local_res_temp != NULL) {

    temp_socket = socket(local_res_temp->ai_family,SOCK_STREAM,0);

    if (temp_socket == INVALID_SOCKET) {
      if (debug) {
	fprintf(stderr,
		"%s could not allocate a socket: %s (errno %d)\n",
		__FUNCTION__,
		strerror(errno),
		errno);
	fflush(stderr);
      }
      local_res_temp = local_res_temp->ai_next;
      continue;
    }

    /* happiness and joy, keep going */
    if (setsockopt(temp_socket,
		   SOL_SOCKET,
		   SO_REUSEADDR,
		   (char *)&on ,
		   sizeof(on)) == SOCKET_ERROR) {
      if (debug) {
	fprintf(stderr,
		"%s: warning: could not set SO_REUSEADDR: %s (errno %d)\n",
		__FUNCTION__,
		strerror(errno),
		errno);
	fflush(stderr);
      }
    }
    /* still happy and joyful */

    if ((bind(temp_socket,
	      local_res_temp->ai_addr,
	      local_res_temp->ai_addrlen) != SOCKET_ERROR) &&
	(listen(temp_socket,1024) != SOCKET_ERROR))  {

      /* OK, now add to the list */
      temp_elt = (struct listen_elt *)malloc(sizeof(struct listen_elt));
      if (temp_elt) {
	temp_elt->fd = temp_socket;
	if (listen_list) {
	  temp_elt->next = listen_list;
	}
	else {
	  temp_elt->next = NULL;
	}
	listen_list = temp_elt;
      }
      else {
	fprintf(stderr,
		"%s: could not malloc a listen_elt\n",
		__FUNCTION__);
	fflush(stderr);
	exit(1);
      }
    }
    else {
      /* we consider a bind() or listen() failure a transient and try
	 the next address */
      if (debug) {
	fprintf(stderr,
		"%s: warning: bind or listen call failure: %s (errno %d)\n",
		__FUNCTION__,
		strerror(errno),
		errno);
	fflush(stderr);
      }
      close(temp_socket);
    }
    local_res_temp = local_res_temp->ai_next;
  }
}


void
process_requests()
{

  float	temp_rate;

  if (debug) {
    fprintf(where,
	    "%s: enter\n",
	    __FUNCTION__);
    fflush(where);
  }

  /* if the netserver was started with a passphrase, look for it in
     the first request to arrive.  if there is no passphrase in the
     first request we will end-up dumping the control connection. raj
     2012-01-23 */

  if ((passphrase != NULL)  && (recv_passphrase()))
      return;

  while (1) {

    if (recv_request() <= 0) {
      close(server_sock);
      return;
    }

    switch (netperf_request.content.request_type) {

    case DEBUG_ON:
      netperf_response.content.response_type = DEBUG_OK;
      if (!suppress_debug) {
	debug++;

	if (debug == 1) {
	  /* we just flipped-on debugging, dump the request because
	     recv_request/recv_request_n will not have dumped it as its
	     dump_request() call is conditional on debug being set. raj
	     2011-07-08 */
	  dump_request();
	}
      }

      send_response();
      break;

    case DEBUG_OFF:
      if (debug)
	debug--;
      netperf_response.content.response_type = DEBUG_OK;
      send_response();
      /* we used to take the trouble to close the debug file, but SAF
	 asked a good question when he asked "Why?" and since I cannot
	 think of a good reason, I have removed the code. raj
	 2011-07-08 */
      break;

    case DO_SYSINFO:
      {
	netperf_response.content.response_type = SYSINFO_RESPONSE;

	snprintf((char *)netperf_response.content.test_specific_data,
		 sizeof(netperf_response.content.test_specific_data),
		 "%c%s%c%s%c%s%c%s",
		 ',',
		 "Deprecated",
		 ','
,		 "Deprecated",
		 ',',
		 "Deprecated",
		 ',',
		 "Deprecated");

	send_response_n(0);
	break;
      }

    case CPU_CALIBRATE:
      netperf_response.content.response_type = CPU_CALIBRATE;
      temp_rate = calibrate_local_cpu(0.0);
      bcopy((char *)&temp_rate,
	    (char *)netperf_response.content.test_specific_data,
	    sizeof(temp_rate));
      bcopy((char *)&lib_num_loc_cpus,
	    (char *)netperf_response.content.test_specific_data +
	            sizeof(temp_rate),
	    sizeof(lib_num_loc_cpus));
      if (debug) {
	fprintf(where,
		"netserver: sending CPU information: rate is %g num cpu %d\n",
		temp_rate,
		lib_num_loc_cpus);
	fflush(where);
      }

      /* we need the cpu_start, cpu_stop in the looper case to kill
         the child proceses raj 7/95 */

#ifdef USE_LOOPER
      cpu_start(1);
      cpu_stop(1,&temp_rate);
#endif /* USE_LOOPER */

      send_response();
      break;

    case DO_TCP_STREAM:
      recv_tcp_stream();
      break;

    case DO_TCP_MAERTS:
      recv_tcp_maerts();
      break;

    case DO_TCP_RR:
      recv_tcp_rr();
      break;

    case DO_TCP_CRR:
      recv_tcp_conn_rr();
      break;

    case DO_TCP_CC:
      recv_tcp_cc();
      break;

#ifdef DO_1644
    case DO_TCP_TRR:
      recv_tcp_tran_rr();
      break;
#endif /* DO_1644 */

#ifdef DO_NBRR
    case DO_TCP_NBRR:
      recv_tcp_nbrr();
      break;
#endif /* DO_NBRR */

    case DO_UDP_STREAM:
      recv_udp_stream();
      break;

    case DO_UDP_RR:
      recv_udp_rr();
      break;

#ifdef WANT_DLPI

    case DO_DLPI_CO_RR:
      recv_dlpi_co_rr();
      break;

    case DO_DLPI_CL_RR:
      recv_dlpi_cl_rr();
      break;

    case DO_DLPI_CO_STREAM:
      recv_dlpi_co_stream();
      break;

    case DO_DLPI_CL_STREAM:
      recv_dlpi_cl_stream();
      break;

#endif /* WANT_DLPI */

#ifdef WANT_UNIX

    case DO_STREAM_STREAM:
      recv_stream_stream();
      break;

    case DO_STREAM_RR:
      recv_stream_rr();
      break;

    case DO_DG_STREAM:
      recv_dg_stream();
      break;

    case DO_DG_RR:
      recv_dg_rr();
      break;

#endif /* WANT_UNIX */

#ifdef WANT_XTI
    case DO_XTI_TCP_STREAM:
      recv_xti_tcp_stream();
      break;

    case DO_XTI_TCP_RR:
      recv_xti_tcp_rr();
      break;

    case DO_XTI_UDP_STREAM:
      recv_xti_udp_stream();
      break;

    case DO_XTI_UDP_RR:
      recv_xti_udp_rr();
      break;

#endif /* WANT_XTI */

#ifdef WANT_SCTP
    case DO_SCTP_STREAM:
      recv_sctp_stream();
      break;

    case DO_SCTP_STREAM_MANY:
      recv_sctp_stream_1toMany();
      break;

    case DO_SCTP_RR:
      recv_sctp_rr();
      break;

    case DO_SCTP_RR_MANY:
      recv_sctp_rr_1toMany();
      break;
#endif

#ifdef WANT_SDP
    case DO_SDP_STREAM:
      recv_sdp_stream();
      break;

    case DO_SDP_MAERTS:
      recv_sdp_maerts();
      break;

    case DO_SDP_RR:
      recv_sdp_rr();
      break;
#endif

#ifdef WANT_OMNI
    case DO_OMNI:
      recv_omni();
      break;
#endif

    case PASSPHRASE:
      if (debug) {
	fprintf(where,"Ignoring an unexpected passphrase control message\n");
	fflush(where);
      }
      break;

    default:
      fprintf(where,"unknown test number %d\n",
	      netperf_request.content.request_type);
      fflush(where);
      netperf_response.content.serv_errno=998;
      send_response();
      break;

    }
  }
}


void
accept_connection(SOCKET listen_fd) {

  struct sockaddr_storage peeraddr;
  netperf_socklen_t peeraddrlen;
#if defined(SO_KEEPALIVE)
  int on = 1;
#endif

  if (debug) {
    fprintf(where,
	    "%s: enter\n",
	    __FUNCTION__);
    fflush(where);
  }

  peeraddrlen = sizeof(peeraddr);

  /* while server_control is only used by the WIN32 path, but why
     bother ifdef'ing it?  and besides, do we *really* need knowledge
     of server_control in the WIN32 case? do we have to tell the
     child about *all* the listen endpoints? raj 2011-07-08 */
  server_control = listen_fd;

  if ((server_sock = accept(listen_fd,
			   (struct sockaddr *)&peeraddr,
			    &peeraddrlen)) == INVALID_SOCKET) {
    fprintf(where,
	    "%s: accept failure: %s (errno %d)\n",
	    __FUNCTION__,
	    strerror(errno),
	    errno);
    fflush(where);
    exit(1);
  }

#if defined(SO_KEEPALIVE)
  /* we are not terribly concerned if this does not work, it is merely
     duct tape added to belts and suspenders. raj 2011-07-08 */
  setsockopt(server_sock,
	     SOL_SOCKET,
	     SO_KEEPALIVE,
	     (const char *)&on,
	     sizeof(on));
#endif

  if (spawn_on_accept) {
    // spawn_child();
    /* spawn_child() only returns when we are the parent */
    close(server_sock);
  }
  else {
    process_requests();
  }
}


void
accept_connections() {

  fd_set read_fds, write_fds, except_fds;
  SOCKET high_fd, candidate;
  int num_ready;

  if (debug) {
    fprintf(where,
	    "%s: enter\n",
	    __FUNCTION__);
    fflush(where);
  }

  while (1) {

    FD_ZERO(&write_fds);
    FD_ZERO(&except_fds);
    high_fd = set_fdset(listen_list,&read_fds);

    num_ready = select(1,
		       &read_fds,
		       &write_fds,
		       &except_fds,
		       NULL);

    if (num_ready < 0) {
      fprintf(where,
	      "%s: select failure: %s (errno %d)\n",
	      __FUNCTION__,
	      strerror(errno),
	      errno);
      fflush(where);
      exit(1);
    }

    /* try to keep things simple */
    candidate = 0;
    while ((num_ready) && (candidate <= high_fd)) {
      if (FD_ISSET(candidate,&read_fds)) {
	accept_connection(candidate);
	FD_CLR(candidate,&read_fds);
	num_ready--;
      }
      else {
	candidate++;
      }
    }
  }
}




int _cdecl
main(int argc, char *argv[]) {

/* Save away the program name */
program = (char *)malloc(strlen(argv[0]) + 1);
  if (program == NULL) {
    printf("malloc for program name failed!\n");
    return -1 ;
  }

  strcpy(program, argv[0]);

//   init_netserver_globals();
spawn_on_accept = 1;
want_daemonize = 1;

child = 0;
not_inetd = 0;
netperf_daemon = 0;

//   netlib_init();
where = stdout;
request_array = (int *)(&netperf_request);
response_array = (int *)(&netperf_response);

for (int i = 0; i < MAXCPUS; i++) {
  lib_local_per_cpu_util[i] = -1.0;
}

lib_local_cpu_stats.peak_cpu_id = -1;
lib_local_cpu_stats.peak_cpu_util = -1.0;
lib_remote_cpu_stats.peak_cpu_id = -1;
lib_remote_cpu_stats.peak_cpu_util = -1.0;

netperf_version = strdup(NETPERF_VERSION);

netlib_init_cpu_map__ex(); // active
srand(getpid()); // active

strncpy(local_host_name,"",sizeof(local_host_name));
local_address_family = AF_UNSPEC;
strncpy(listen_port,TEST_PORT,sizeof(listen_port));

//   scan_netserver_args(argc, argv);

//   check_if_inetd();
struct sockaddr_storage name;
netperf_socklen_t namelen;

namelen = sizeof(name);
if (getsockname(0,
    (struct sockaddr *)&name,
    &namelen) == SOCKET_ERROR)
  not_inetd = 1;



    /* we are the top netserver process, so we have to create the
       listen endpoint(s) and decide if we want to daemonize */
//    setup_listens(local_host_name,listen_port,local_address_family);

int do_inet; // active
int do_inet6;
int no_name = 0;  //active

// if (strcmp(name,"") == 0) { //active

  no_name = 1; // active
  do_inet = 1;  // active
  do_inet6 = 1;  // active
// }

if (do_inet6)  // active
create_listens("::0",listen_port,AF_INET6);  // active

if (do_inet)  // active
create_listens("0.0.0.0",listen_port,AF_INET);  // active

if (listen_list) {  // active
  fprintf(stdout,
    "Starting netserver with host '%s' port '%s' and family %s\n",
    (no_name) ? "IN(6)ADDR_ANY" : local_host_name,
    listen_port,
    inet_ftos(af));  // active
  fflush(stdout);  // active
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

if (want_daemonize) {
//       daemonize();
/* flush the usual suspects */


/* ok, we can start accepting control connections now */
  accept_connections();

  fflush(stdin); // active
  fflush(stdout); // active
  fflush(stderr); // active

  exit(1);

}

//     }
//     accept_connections();
//   }
//
//   unlink_empty_debug_file();
//
// #ifdef WIN32
//   WSACleanup();
// #endif

  return 0;

}
