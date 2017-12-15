#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/queue.h>
#include <netinet/in.h>
#include <setjmp.h>
#include <stdarg.h>
#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <signal.h>
#include <stdbool.h>
#include <rte_common.h>
#include <rte_log.h>
#include <rte_malloc.h>
#include <rte_memory.h>
#include <rte_memcpy.h>
#include <rte_memzone.h>
#include <rte_eal.h>
#include <rte_per_lcore.h>
#include <rte_launch.h>
#include <rte_atomic.h>
#include <rte_cycles.h>
#include <rte_prefetch.h>
#include <rte_lcore.h>
#include <rte_per_lcore.h>
#include <rte_branch_prediction.h>
#include <rte_interrupts.h>
#include <rte_pci.h>
#include <rte_random.h>
#include <rte_debug.h>
#include <rte_ether.h>
#include <rte_ethdev.h>
#include <rte_mempool.h>
#include <rte_mbuf.h>


#define GOTO_FAIL(str, ...) do {					\
		printf("mbuf test FAILED (l.%d): <" str ">\n",		\
		       __LINE__,  ##__VA_ARGS__);			\
		goto fail;						\
} while(0)

#define MBUF_TEST_DATA_LEN      1464
#define MBUF_DATA_SIZE          2048
#define NB_MBUF                 128


static struct rte_mempool *pktmbuf_pool = NULL;


int main(int argc, char **argv){

	struct lcore_queue_conf *qconf;
	struct rte_eth_dev_info dev_info;
	int ret;
	uint8_t nb_ports;
	uint8_t nb_ports_available;
	uint8_t portid, last_port;
	unsigned lcore_id, rx_lcore_id;
	unsigned nb_ports_in_mask = 0;

	/* init EAL */
	ret = rte_eal_init(argc, argv);
	if (ret < 0)
		rte_exit(EXIT_FAILURE, "Invalid EAL arguments\n");
	argc -= ret;
	argv += ret;

	/* create pktmbuf pool if it does not exist */
	if (pktmbuf_pool == NULL) {
		pktmbuf_pool = rte_pktmbuf_pool_create("test_pktmbuf_pool",
			NB_MBUF, 32, 0, MBUF_DATA_SIZE, SOCKET_ID_ANY);
	}

	if (pktmbuf_pool == NULL) {
		printf("cannot allocate mbuf pool\n");
		return -1;
	}



	unsigned i;
	struct rte_mbuf *m[NB_MBUF];
	int ret = 0;

	for (i=0; i<NB_MBUF; i++)
		m[i] = NULL;

	/* alloc NB_MBUF mbufs */
	for (i=0; i<NB_MBUF; i++) {
		m[i] = rte_pktmbuf_alloc(pktmbuf_pool);
		if (m[i] == NULL) {
			printf("rte_pktmbuf_alloc() failed (%u)\n", i);
			ret = -1;
			break;
		}
		m[i]->data_off += 64;
	}









	return 0;
}
