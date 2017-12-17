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

  struct rte_mbuf *m = NULL;
  char *data;
  m = rte_pktmbuf_alloc(pktmbuf_pool);
  data = rte_pktmbuf_append(m, MBUF_TEST_DATA_LEN);
  memset(data, '*', rte_pktmbuf_pkt_len(m)-1000);
	printf("Length of DPDK packet: %d\n", rte_pktmbuf_pkt_len(m)); // rte_pktmbuf_pkt_len(m): 1464

	char *rtn;
	rtn = rte_pktmbuf_mtod_offset(m, char *, sizeof(data));
	printf("lenght of DPDK offset: %ld\n", strlen(rtn));  // lenght of the offset: 456
  rte_pktmbuf_free(m);


	// TCP PACKET EXAMPLE
	char send_data[MBUF_TEST_DATA_LEN];
	printf("length of TCP char_array: %ld\n", strlen(send_data));
	memset( send_data, '*', (sizeof(send_data)-1000) * sizeof(char));
	printf("length of TCP offset: %ld\n", strlen(send_data));
	return 0;
}
