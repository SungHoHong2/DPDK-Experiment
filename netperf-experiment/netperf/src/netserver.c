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

struct listen_elt {
  SOCKET fd;
  struct listen_elt *next;
};

struct listen_elt *listen_list = NULL;

SOCKET   server_control;

int      child;   /* are we the child of inetd or a parent netserver?
		     */
int      netperf_daemon;
int      daemon_parent = 0;
int      not_inetd;
int      want_daemonize;
int      spawn_on_accept;
int      suppress_debug = 0;

extern	char	*optarg;
extern	int	optind, opterr;




int _cdecl
main(int argc, char *argv[]) {

// #ifdef WIN32
//   WSADATA	wsa_data ;
//
//   /* Initialize the winsock lib do we still want version 2.2? */
//   if ( WSAStartup(MAKEWORD(2,2), &wsa_data) == SOCKET_ERROR ){
//     printf("WSAStartup() failed : %lu\n", GetLastError()) ;
//     return -1 ;
//   }
// #endif /* WIN32 */
//
//   /* Save away the program name */
//   program = (char *)malloc(strlen(argv[0]) + 1);
//   if (program == NULL) {
//     printf("malloc for program name failed!\n");
//     return -1 ;
//   }
//   strcpy(program, argv[0]);
//
//   init_netserver_globals();
//
//   netlib_init();
//
//   strncpy(local_host_name,"",sizeof(local_host_name));
//   local_address_family = AF_UNSPEC;
//   strncpy(listen_port,TEST_PORT,sizeof(listen_port));
//
//   scan_netserver_args(argc, argv);
//
//   check_if_inetd();
//
//   if (child) {
//     /* we are the child of either an inetd or parent netserver via
//        spawning (Windows) rather than fork()ing. if we were fork()ed
//        we would not be coming through this way. set_server_sock() must
//        be called before open_debug_file() or there is a chance that
//        we'll toast the descriptor when we do not wish it. */
//     set_server_sock();
//     open_debug_file();
//     process_requests();
//   }
//   else if (daemon_parent) {
//     /* we are the parent daemonized netserver
//        process. accept_connections() will decide if we want to spawn a
//        child process */
//     accept_connections();
//   }
//   else {
//     /* we are the top netserver process, so we have to create the
//        listen endpoint(s) and decide if we want to daemonize */
//     setup_listens(local_host_name,listen_port,local_address_family);
//     if (want_daemonize) {
//       daemonize();
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
