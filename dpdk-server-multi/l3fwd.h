

#ifndef __L3_FWD_H__
#define __L3_FWD_H__

#include <rte_common.h>
#include <rte_byteorder.h>
#include <rte_log.h>
#include <rte_memory.h>
#include <rte_memcpy.h>
#include <rte_eal.h>
#include <rte_launch.h>
#include <rte_atomic.h>
#include <rte_cycles.h>
#include <rte_prefetch.h>
#include <rte_lcore.h>
#include <rte_per_lcore.h>
#include <rte_branch_prediction.h>
#include <rte_interrupts.h>
#include <rte_random.h>
#include <rte_debug.h>
#include <rte_ether.h>
#include <rte_ethdev.h>
#include <rte_mempool.h>
#include <rte_mbuf.h>
#include <rte_malloc.h>
#include <rte_ip.h>
#include <rte_tcp.h>
#include <rte_udp.h>
#include <rte_string_fns.h>
#include <rte_lpm.h>
#include <rte_lpm6.h>
#include <rte_ip_frag.h>
#include <rte_vect.h>

#define DO_RFC_1812_CHECKS

#define RTE_LOGTYPE_L3FWD RTE_LOGTYPE_USER1

#if !defined(NO_HASH_MULTI_LOOKUP) && defined(RTE_MACHINE_CPUFLAG_NEON)
#define NO_HASH_MULTI_LOOKUP 1
#endif

#define MAX_PKT_BURST     32
#define BURST_TX_DRAIN_US 100 /* TX drain every ~100us */

#define MAX_RX_QUEUE_PER_LCORE 16

/*
 * Try to avoid TX buffering if we have at least MAX_TX_BURST packets to send.
 */
#define	MAX_TX_BURST	  (MAX_PKT_BURST / 2)

#define NB_SOCKETS        8

/* Configure how many packets ahead to prefetch, when reading packets */
#define PREFETCH_OFFSET	  3

/* Used to mark destination port as 'invalid'. */
#define	BAD_PORT ((uint16_t)-1)

#define FWDSTEP	4

/* replace first 12B of the ethernet header. */
#define	MASK_ETH 0x3f

/* Hash parameters. */
#ifdef RTE_ARCH_64
/* default to 4 million hash entries (approx) */
#define L3FWD_HASH_ENTRIES		(1024*1024*4)
#else
/* 32-bit has less address-space for hugepage memory, limit to 1M entries */
#define L3FWD_HASH_ENTRIES		(1024*1024*1)
#endif
#define HASH_ENTRY_NUMBER_DEFAULT	4

#define FRAG_PKT 1024
#define IPV4_MTU_DEFAULT 1024
#define MERGE_PACKETS 4

struct mbuf_table {
	uint16_t len;
	uint32_t head;
	uint32_t tail;
	struct rte_mbuf *m_table[0];
};

struct assembled_result {
	char packet[5][FRAG_PKT];
	int packet_length[5];
	char *assembled_pkt;
	int length;
};

struct lcore_rx_queue {
	uint16_t port_id;
	uint8_t queue_id;
	struct assembled_result *ar;
	struct rte_ip_frag_tbl *frag_tbl;
	struct rte_ip_frag_death_row death_row;
} __rte_cache_aligned;

struct lcore_conf {
	uint16_t n_rx_queue;
	struct lcore_rx_queue rx_queue_list[MAX_RX_QUEUE_PER_LCORE];
	uint16_t n_tx_port;
	uint16_t tx_port_id[RTE_MAX_ETHPORTS];
	uint16_t tx_queue_id[RTE_MAX_ETHPORTS];
	struct mbuf_table *tx_mbufs[RTE_MAX_ETHPORTS];
} __rte_cache_aligned;

extern volatile bool force_quit;

/* ethernet addresses of ports */
extern uint64_t dest_eth_addr[RTE_MAX_ETHPORTS];
extern struct ether_addr ports_eth_addr[RTE_MAX_ETHPORTS];

/* mask of enabled ports */
extern uint32_t enabled_port_mask;

/* Used only in exact match mode. */
extern int ipv6; /**< ipv6 is false by default. */
extern uint32_t hash_entry_number;

extern xmm_t val_eth[RTE_MAX_ETHPORTS];

extern struct lcore_conf lcore_conf[RTE_MAX_LCORE];

int lpm_check_ptype(int portid);

uint16_t
lpm_cb_parse_ptype(uint16_t port, uint16_t queue, struct rte_mbuf *pkts[],
		   uint16_t nb_pkts, uint16_t max_pkts, void *user_param);

int lpm_main_loop(__attribute__((unused)) void *dummy);

#define PREFETCH_OFFSET	3

#endif  /* __L3_FWD_H__ */


int chara_debug = 0;

int tx_rte;
int rx_rte;


pthread_mutex_t dpdk_mutex;


static struct rte_mempool * receive_pool[NB_SOCKETS];
static struct rte_mempool * transfer_pool[NB_SOCKETS];
static struct rte_mempool * direct_pool[NB_SOCKETS];
static struct rte_mempool * indirect_pool[NB_SOCKETS];

struct rte_ring *rx_ring[RTE_MAX_LCORE];
struct rte_ring *tx_ring[RTE_MAX_LCORE];

static int unique_id_s = 0;


static void ipv4_wrapper(int lcoreid, struct ipv4_hdr *in_hdr, int uniqueid){
	unique_id_s++;

	in_hdr->version_ihl = 69;
	in_hdr->type_of_service = 0;
	in_hdr->total_length= 51717;
	in_hdr->packet_id= 19446 + unique_id_s;
	in_hdr->fragment_offset = 0;
	in_hdr->time_to_live= 4;
	in_hdr->next_proto_id= unique_id_s*5;
	in_hdr->hdr_checksum= 36920;


	// mapped the destiantion queue
	switch(lcoreid+tx_rte){
		case 1:
		   	in_hdr->src_addr= 11111111;
		  	in_hdr->dst_addr= 11111111;
			break;
		case 2:
			in_hdr->src_addr= 00000001;
			in_hdr->dst_addr= 00000001;
			break;
		case 3:
			in_hdr->src_addr= 01111111;
			in_hdr->dst_addr= 01111111;
			break;
		case 4:
			in_hdr->src_addr= 00011111;
			in_hdr->dst_addr= 00011111;
			break;
		case 5:
			in_hdr->src_addr= 00111111;
			in_hdr->dst_addr= 00111111;
			break;
		case 6:
			in_hdr->src_addr= 01111111;
			in_hdr->dst_addr= 11111111;
			break;
		case 7:
			in_hdr->src_addr= 00000111;
			in_hdr->dst_addr= 00000111;
			break;
		case 8:
			in_hdr->src_addr= 11111111;
			in_hdr->dst_addr= 01111111;
			break;
	}

}


