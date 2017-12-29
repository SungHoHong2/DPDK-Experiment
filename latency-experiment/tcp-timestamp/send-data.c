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

#include <getopt.h>

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <signal.h>

typedef enum
{
    DESTINATION = 0x0001,
    DEF_PORT    = 1025,
    MIN_REPEAT  = 20,
    PACKET_SIZE = 32,
} CONSTS;

static bool keepRunning = true;

static void Usage(const char * const progName)
{
    /* Here are the valid commands. */
    printf("\n");
    printf("%s accepts the following parameters: \n\n", progName);
    printf("\t* --destination or -d [ip address]\n");
    printf("\t  --port        or -p [port number]          (default: 1025)\n");
    printf("\t  --repeat      or -r [repeat every x msec.] (default: 20)\n");
    printf("\n");
}

void sigintHandler(int signal)
{
    keepRunning = false;
}

int main(int argc, char **argv)
{
    int theOption, theOptionIndex;
    const char *short_options = "d:p:r:";
    static struct option long_options[] =
    {
        { "destination", required_argument, NULL, 'd' },
        { "port",        required_argument, NULL, 'p' },
        { "repeat",      required_argument, NULL, 'r' },
        { 0, 0, 0, 0 }
    };

    int requiredParameters = DESTINATION;

    struct in_addr destAddr;
    memset(&destAddr, 0, sizeof(struct in_addr));

    uint16_t destPort = DEF_PORT;
    uint32_t repeatMs = MIN_REPEAT;

    while (-1 != (theOption = getopt_long(argc, argv, short_options, long_options,
                                          &theOptionIndex)))
    {
        switch(theOption)
        {
            case 'd':
                inet_pton(AF_INET, optarg, &destAddr);
                requiredParameters &= ~DESTINATION;
                break;
            case 'p':
                destPort = (uint16_t) atoi(optarg);
                break;
            case 'r':
                {
                int tempMs = atoi(optarg);
                repeatMs = (tempMs < MIN_REPEAT) ? MIN_REPEAT : tempMs;
                }
                break;
            case 'h':
            case '?':
            default:
                Usage(argv[0]);
                return -1;
                break;
        }
    }

    /* If not all required parameters were entered, then we need to exit. */
    if (0 != requiredParameters)
    {
        printf("Not all * required parameters were entered.\n");
        Usage(argv[0]);
        return -1;
    }

    /* Setup signal handler. */
    signal(SIGINT, sigintHandler);

    /* Print up the options in use: */
    printf("Destination address is %s\n",       inet_ntoa(destAddr));
    printf("Destination port    is %d\n",       destPort);
    printf("Packet interval     is %d ms.\n",   repeatMs);

    /* Data packet to send. */
    uint8_t dataPacket[PACKET_SIZE];

    /* Initialize the random number generator. */
    srand(clock());

    /* Destination ok. */
    int destSocket = socket(PF_INET, SOCK_DGRAM, 0);
    if (destSocket < 0)
    {
        printf("destSocket not opened.\n");
        return -1;
    }

    struct sockaddr_in destSocketAddr;
    destSocketAddr.sin_family   = AF_INET;
    destSocketAddr.sin_addr     = destAddr;
    destSocketAddr.sin_port     = htons(destPort);

    /* This thing's only any good under 2.6 w/realtime or High Res Timers active. */
    /*
    struct timespec sleepSpec;
    sleepSpec.tv_sec  = 0;
    sleepSpec.tv_nsec = repeatMs * 1000 * 1000;
    */

    unsigned char randByte;
    struct timeval theStart, afterTx, nextTx, afterSleep;

    gettimeofday(&theStart, NULL);
    nextTx    = theStart;
    repeatMs *= 1000;

    for(;keepRunning;)
    {
        /* busyfrickinwaiting: linux, and its low res timers, are awful. */
        /* Busy-waiting, the only reliable way to sleep less than 1/HZ.  */
        for(;keepRunning;)
        {
            gettimeofday(&afterSleep, NULL);
            if (afterSleep.tv_sec  >= nextTx.tv_sec &&
                afterSleep.tv_usec >= nextTx.tv_usec)
            {
                if (0 > sendto(destSocket,
                               &dataPacket,
                               sizeof(dataPacket),
                               0,
                               (struct sockaddr *) &destSocketAddr,
                               sizeof(destSocketAddr)))
                {
                    perror("sendto");
                }
                break;
            }
        }

        /* Prepare next payload. */
        randByte = (unsigned char) (rand() % 255);
        memset(&dataPacket, randByte, sizeof(dataPacket));

        /* Setup next TX time. */
        nextTx.tv_usec += repeatMs;
        nextTx.tv_sec  += nextTx.tv_usec / 1000000;
        nextTx.tv_usec %= 1000000;

        gettimeofday(&afterTx, NULL);

        printf("aftersleep: %d.%06d, aftersend: %d.%06d, nextTx: %d.%06d\n",
               (int) afterSleep.tv_sec,
               (int) afterSleep.tv_usec,
               (int) afterTx.tv_sec,
               (int) afterTx.tv_usec,
               (int) nextTx.tv_sec,
               (int) nextTx.tv_usec);
    }

    /* Cleanup. */
    printf("Shutting %s down.\n", argv[0]);
    close(destSocket);

    return 0;
}
