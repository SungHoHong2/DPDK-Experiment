#include "netperf_version.h"

char	netserver_id[]="\
@(#)netserver.c (c) Copyright 1993-2012 Hewlett-Packard Co. Version 2.6.0";

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

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

#ifndef DEBUG_LOG_FILE_DIR
#if defined(WIN32)
#define DEBUG_LOG_FILE_DIR ""
#elif defined(ANDROID)
#define DEBUG_LOG_FILE_DIR "/data/local/tmp/"
#else
#define DEBUG_LOG_FILE_DIR "/tmp/"
#endif
#endif /* DEBUG_LOG_FILE_DIR */

#ifndef DEBUG_LOG_FILE
#define DEBUG_LOG_FILE DEBUG_LOG_FILE_DIR"netserver.debug"
#endif

#if !defined(PATH_MAX)
#define PATH_MAX MAX_PATH
#endif
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
int      suppress_debug = 0;

extern	char	*optarg;
extern	int	optind, opterr;

#define SERVER_ARGS "DdfhL:n:Np:v:VZ:46I:i:"
