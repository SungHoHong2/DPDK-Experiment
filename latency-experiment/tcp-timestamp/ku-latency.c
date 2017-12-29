/*
Copyright (c) 2008, Max Vilimpoc, http://vilimpoc.org/

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

    * Redistributions of source code must retain the above
      copyright notice, this list of conditions and the following
      disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials
      provided with the distribution.
    * Neither the name of the author nor the names of its
      contributors may be used to endorse or promote products
      derived from this software without specific prior written
      permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#define _XOPEN_SOURCE 600

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/time.h>

#include <sys/ioctl.h>
#include <linux/if.h>

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>

#include <getopt.h>

typedef enum
{
    STRERROR_LEN           = 80,
    NUM_LATENCIES          = 32,
    DEFAULT_PORT           = 1025,
} CONSTS;

static int                 inSocket;
static struct sockaddr_in  inInAddr;

static int                 totalUsec;
static int                 totalPackets;

static int                 latencies[NUM_LATENCIES];
static int                 index;
static int                 rollingAverage;

static bool                keepRunning;



void Usage(const char * const progName)
{
    printf("\n");
    printf("Usage: %s [-i IP address] [-e ethx] [-p port]\n", progName);
    printf("\n");
    printf("       -h          Help.\n");
    printf("       -i          Specifies IP address of interface you want to listen to.\n");
    printf("       -e          Specifies the ethernet interface name you want to listen to.\n");
    printf("       -p          Specifies port number of packets you want to see.\n");
    printf("\n");
    printf("If no option is specified (they are all optional), then the program\n");
    printf("will listen on IPADDR_ANY (all interfaces), port 1025.");
    printf("\n");
    printf("\n");
}


static void printError(int errorCode, const char * const lastFunction)
{
    static char strError[STRERROR_LEN];
    memset(strError, 0, STRERROR_LEN);

    /* Old school. */
    perror(lastFunction);

    /* New school. */
    strerror_r(errorCode, strError, STRERROR_LEN);

    printf(strError);
    printf("\n");
}


void catchIntr(int signalNumber)
{
    /* Exit the main loop. */
    keepRunning = false;
}

int main(int argc, char **argv)
{
    int rc = 0;


    /* Defaults */
    inInAddr.sin_addr.s_addr    = INADDR_ANY;
    inInAddr.sin_port           = htons(DEFAULT_PORT);
    inInAddr.sin_family         = AF_INET;


    inSocket = socket(PF_INET, SOCK_DGRAM, 0);
    if (0 > inSocket)
    {
        printf("socket() call failed.\n");
        printError(inSocket, "socket");
        rc = -1;
        goto socket_failed;
    }

    /* Process cmdline opts. */
    char *shortOpts = "hi:e:p:";
    int   getoptRet;

    while(-1 != (getoptRet = getopt(argc, argv, shortOpts)))
    {
        switch(getoptRet)
        {
            case 'i':
                inInAddr.sin_addr.s_addr = inet_addr(optarg);
                break;
            case 'e':
                {
                struct ifreq fetchIfInfo;
                memset(&fetchIfInfo, 0, sizeof(struct ifreq));
                memcpy(fetchIfInfo.ifr_name, optarg, IFNAMSIZ - 1);

                /* Fetch the IP address to listen to based on interface name. */
                ioctl(inSocket, SIOCGIFADDR, &fetchIfInfo);

                struct sockaddr_in * const sockInfo = (struct sockaddr_in * const) &fetchIfInfo.ifr_addr;
                inInAddr.sin_addr.s_addr   = sockInfo->sin_addr.s_addr;
                }
                break;
            case 'p':
                inInAddr.sin_port        = htons(atoi(optarg));
                break;
            case 'h':
            case '?':
            default:
                Usage(argv[0]);
                goto normal_exit;
                break;
        }
    }


    printf("Listening to: %s:%d\n", inet_ntoa(inInAddr.sin_addr),
                                    ntohs(inInAddr.sin_port));

    int timestampOn = 1;
    rc = setsockopt(inSocket, SOL_SOCKET, SO_TIMESTAMP, (int *) &timestampOn, sizeof(timestampOn));
    if (0 > rc)
    {
        printf("setsockopt(SO_TIMESTAMP) failed.\n");
        printError(rc, "setsockopt");
        goto setsockopt_failed;
    }

    rc = bind(inSocket, (struct sockaddr *) &inInAddr, sizeof(struct sockaddr_in));
    if (0 > rc)
    {
        printf("UDP bind() failed.\n");
        printError(rc, "bind");
        goto bind_failed;
    }

    struct msghdr   msg;
    struct iovec    iov;
    char            pktbuf[2048];

    char            ctrl[CMSG_SPACE(sizeof(struct timeval))];
    struct cmsghdr *cmsg = (struct cmsghdr *) &ctrl;

    msg.msg_control      = (char *) ctrl;
    msg.msg_controllen   = sizeof(ctrl);

    msg.msg_name         = &inInAddr;
    msg.msg_namelen      = sizeof(inInAddr);
    msg.msg_iov          = &iov;
    msg.msg_iovlen       = 1;
    iov.iov_base         = pktbuf;
    iov.iov_len          = sizeof(pktbuf);


    struct timeval  time_kernel, time_user;
    int             timediff;


    printf("Starting main loop.\n");

    for(keepRunning = true; keepRunning;)
    {
        rc = recvmsg(inSocket, &msg, 0);

        gettimeofday(&time_user, NULL);

        if (cmsg->cmsg_level == SOL_SOCKET &&
            cmsg->cmsg_type  == SCM_TIMESTAMP &&
            cmsg->cmsg_len   == CMSG_LEN(sizeof(time_kernel)))
        {
            memcpy(&time_kernel, CMSG_DATA(cmsg), sizeof(time_kernel));
        }

        printf("\n");
        printf("time_kernel                  : %d.%06d\n", (int) time_kernel.tv_sec,
                                                           (int) time_kernel.tv_usec);
        printf("time_user                    : %d.%06d\n", (int) time_user.tv_sec,
                                                           (int) time_user.tv_usec);

        timediff      = (time_user.tv_sec - time_kernel.tv_sec) * 1000000 +
                        (time_user.tv_usec - time_kernel.tv_usec);
        totalUsec    += timediff;
        ++totalPackets;

        rollingAverage  += timediff;
        rollingAverage  -= latencies[index];
        latencies[index] = timediff;
        index = (index + 1) % NUM_LATENCIES;

        printf("Total Average                : %d/%d = %.2f us\n", totalUsec,
                                                                   totalPackets,
                                                                   (float) totalUsec / totalPackets);
        printf("Rolling Average (%d samples) : %.2f us\n", NUM_LATENCIES,
                                                           (float) rollingAverage / NUM_LATENCIES);
    }

bind_failed:
setsockopt_failed:
    close(inSocket);
socket_failed:
normal_exit:
    return rc;
}
