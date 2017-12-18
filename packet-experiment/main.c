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


#define MBUF_DATA_SIZE          2048
#define NB_MBUF                 128
#define MBUF_TEST_DATA_LEN      1464
#define MBUF_TEST_DATA_LEN2     50
#define MBUF_TEST_HDR1_LEN      20
#define MBUF_TEST_HDR2_LEN      30
#define MBUF_TEST_ALL_HDRS_LEN  (MBUF_TEST_HDR1_LEN+MBUF_TEST_HDR2_LEN)



/* size of private data for mbuf in pktmbuf_pool2 */
#define MBUF2_PRIV_SIZE         128

#define REFCNT_MAX_ITER         64
#define REFCNT_MAX_TIMEOUT      10
#define REFCNT_MAX_REF          (RTE_MAX_LCORE)
#define REFCNT_MBUF_NUM         64
#define REFCNT_RING_SIZE        (REFCNT_MBUF_NUM * REFCNT_MAX_REF)

#define MAGIC_DATA              0x42424242

#define MAKE_STRING(x)          # x

static struct rte_mempool *pktmbuf_pool = NULL;
static struct rte_mempool *pktmbuf_pool2 = NULL;
static struct rte_mempool *refcnt_pool = NULL;
static struct rte_ring *refcnt_mbuf_ring = NULL;
static volatile uint32_t refcnt_stop_slaves;
static unsigned refcnt_lcore[RTE_MAX_LCORE];


#include "test_pktmbuf.h"
#include "custom_pktmbuf.h"


/*
# allocate mbuf pool
	the pool contains NB_MBUF elements, where each mbuf is MBUF_SIZE byes long

# test multiple allocations of mbufs for this pool
	alocate NB_MBUF and store pointers in the table
	if an allocation ails return an error
	free all these mbufs
	Repeat the same test to check that mbufs are freed correctly


# data manipulation
 	alloc mbuf
	append data
	test error if length is too large
	trim data
	prepend header
	test for error if prepend is too large
	remove beginning of mbuf using adjacent
	test for error when adjacent length is too large
	check appended data is not corrupt


# packet cloning
		clone mbuf and verify the data
		clone the cloned data and verify the data
		attach mbuf to another that does not have the private size
*/




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


	// test data manipulation with no ascii data
	// test_pktmbuf_with_non_ascii_data();


	// manipulating packet
	// test_one_pktmbuf();

	// customized action
	// custom_pktmbuf();
	// one_packet();

	checking_head_room_size();




	return 0;
}
