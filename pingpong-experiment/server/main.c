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

#define RTE_LOGTYPE_L2FWD RTE_LOGTYPE_USER1
#define NB_MBUF   8192
// #define MAX_PKT_BURST 32
#define MAX_PKT_BURST 32
#define RTE_MBUF_SIZE 384 // RTE_MBUF_DEFAULT_BUF_SIZE
#define PKT_SIZE 64 // sending packet size

#define BURST_TX_DRAIN_US 100 /* TX drain every ~100us */
#define MEMPOOL_CACHE_SIZE 256
#define MAX_RX_QUEUE_PER_LCORE 16
#define MAX_TX_QUEUE_PER_PORT 16
#define MAX_TIMER_PERIOD 86400 /* 1 day max */

/*
 * Configurable number of RX/TX ring descriptors
 */
#define RTE_TEST_RX_DESC_DEFAULT 128
#define RTE_TEST_TX_DESC_DEFAULT 512
static uint16_t nb_rxd = RTE_TEST_RX_DESC_DEFAULT;
static uint16_t nb_txd = RTE_TEST_TX_DESC_DEFAULT;


/* list of enabled ports */
static uint32_t l2fwd_dst_ports[RTE_MAX_ETHPORTS];

/* mask of enabled ports */
static uint32_t l2fwd_enabled_port_mask = 0;
static unsigned int l2fwd_rx_queue_per_lcore = 1;

struct rte_mempool *l2fwd_pktmbuf_pool = NULL;
struct rte_mempool *test_pktmbuf_pool = NULL;


/* MAC updating enabled by default */
static int mac_updating = 1;
static uint64_t timer_period = 10; /* default period is 10 seconds */

static volatile bool first_start = 0;
static volatile bool force_quit;

#include "signal_handler.h"
#include "l2fwd_parse_args.h"

struct lcore_queue_conf {
	unsigned n_rx_port;
	unsigned rx_port_list[MAX_RX_QUEUE_PER_LCORE];
} __rte_cache_aligned;

struct lcore_queue_conf lcore_queue_conf[RTE_MAX_LCORE];

static struct rte_eth_dev_tx_buffer *tx_buffer[RTE_MAX_ETHPORTS];

static const struct rte_eth_conf port_conf = {
	.rxmode = {
		.split_hdr_size = 0,
		.header_split   = 0, /**< Header Split disabled */
		.hw_ip_checksum = 0, /**< IP checksum offload disabled */
		.hw_vlan_filter = 0, /**< VLAN filtering disabled */
		.jumbo_frame    = 0, /**< Jumbo Frame Support disabled */
		.hw_strip_crc   = 1, /**< CRC stripped by hardware */
	},
	.txmode = {
		.mq_mode = ETH_MQ_TX_NONE,
	},
};

/* ethernet addresses of ports */
static struct ether_addr l2fwd_ports_eth_addr[RTE_MAX_ETHPORTS];


/* Per-port statistics struct */
struct l2fwd_port_statistics {
	uint64_t tx;
	uint64_t rx;
	uint64_t dropped;
} __rte_cache_aligned;
struct l2fwd_port_statistics port_statistics[RTE_MAX_ETHPORTS];
#include "l2fwd_launch_one_lcore.h"
#include "port.h"

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

	force_quit = false;
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);

  /* parse application arguments (after the EAL ones) */
	ret = l2fwd_parse_args(argc, argv);
	if (ret < 0)
		rte_exit(EXIT_FAILURE, "Invalid L2FWD arguments\n");

  printf("MAC updating %s\n", mac_updating ? "enabled" : "disabled");

  /* convert to number of cycles */
	timer_period *= rte_get_timer_hz();


  /* create the mbuf pool */
	l2fwd_pktmbuf_pool = rte_pktmbuf_pool_create("mbuf_pool", NB_MBUF,
		MEMPOOL_CACHE_SIZE, 0, RTE_MBUF_SIZE,
		rte_socket_id());

  nb_ports = rte_eth_dev_count();

	/* create memory pool for send data */
	if (test_pktmbuf_pool == NULL) {
		test_pktmbuf_pool = rte_pktmbuf_pool_create("test_pktmbuf_pool",
			NB_MBUF, MEMPOOL_CACHE_SIZE, 0, RTE_MBUF_SIZE, rte_socket_id());
	}


  // setting destination port for each ports BEGIN

  /* reset l2fwd_dst_ports */
	for (portid = 0; portid < RTE_MAX_ETHPORTS; portid++)
		l2fwd_dst_ports[portid] = 0;
	last_port = 0;


  /*
	 * Each logical core is assigned a dedicated TX queue on each port.
     allocate destination port id array
	 */
   for (portid = 0; portid < nb_ports; portid++) {
 		/* skip ports that are not enabled */
 		if ((l2fwd_enabled_port_mask & (1 << portid)) == 0)
 			continue;

 		if (nb_ports_in_mask % 2) {
 			l2fwd_dst_ports[portid] = last_port;
 			l2fwd_dst_ports[last_port] = portid;
 		}
 		else
 			last_port = portid;

 		nb_ports_in_mask++;
 		// rte_eth_dev_info_get(portid, &dev_info);
 	}

  if (nb_ports_in_mask % 2) {
		printf("Notice: odd number of ports in portmask.\n");
		l2fwd_dst_ports[last_port] = last_port;
	}

  // setting destination port for each ports EBD


  	rx_lcore_id = 0;
  	qconf = NULL;

    /* Initialize the port/queue configuration of each logical core */
    for (portid = 0; portid < nb_ports; portid++) {

      /* skip ports that are not enabled */
  		if ((l2fwd_enabled_port_mask & (1 << portid)) == 0)
  			continue;

      /* get the lcore_id for this port */
    		while (rte_lcore_is_enabled(rx_lcore_id) == 0 || lcore_queue_conf[rx_lcore_id].n_rx_port == l2fwd_rx_queue_per_lcore) {
    			    rx_lcore_id++;

    			if (rx_lcore_id >= RTE_MAX_LCORE)
    				  rte_exit(EXIT_FAILURE, "Not enough cores\n");
    		}

      if (qconf != &lcore_queue_conf[rx_lcore_id])
    			/* Assigned a new logical core in the loop above. */
    			qconf = &lcore_queue_conf[rx_lcore_id];

        qconf->rx_port_list[qconf->n_rx_port] = portid;
    		qconf->n_rx_port++;
    		printf("Lcore %u: RX port %u\n", rx_lcore_id, (unsigned) portid);
    }
    nb_ports_available = nb_ports;



  	/* Initialise each port */
  	for (portid = 0; portid < nb_ports; portid++) {
      /* skip ports that are not enabled */
  		if ((l2fwd_enabled_port_mask & (1 << portid)) == 0) {
  			printf("Skipping disabled port %u\n", (unsigned) portid);
  			nb_ports_available--;
  			continue;
  		}

      /* init port */
      printf("Initializing port %u... ", (unsigned) portid);
      fflush(stdout);

      ret = rte_eth_dev_configure(portid, 1, 1, &port_conf);
      rte_eth_macaddr_get(portid,&l2fwd_ports_eth_addr[portid]);


      /* init one RX queue */
  		fflush(stdout);
  		ret = rte_eth_rx_queue_setup(portid, 0, nb_rxd, rte_eth_dev_socket_id(portid), NULL, l2fwd_pktmbuf_pool);
      /* init one TX queue on each port */
  		fflush(stdout);
  		ret = rte_eth_tx_queue_setup(portid, 0, nb_txd, rte_eth_dev_socket_id(portid), NULL);

      /* Initialize TX buffers */
  		tx_buffer[portid] = rte_zmalloc_socket("tx_buffer", RTE_ETH_TX_BUFFER_SIZE(MAX_PKT_BURST), 0, rte_eth_dev_socket_id(portid));
      rte_eth_tx_buffer_init(tx_buffer[portid], MAX_PKT_BURST);

      /* read the packet loss */
      ret = rte_eth_tx_buffer_set_err_callback(tx_buffer[portid], rte_eth_tx_buffer_count_callback, &port_statistics[portid].dropped);

      /* Start device */
  		ret = rte_eth_dev_start(portid);

      rte_eth_promiscuous_enable(portid);
      printf("Port %u, MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n\n",
  				(unsigned) portid,
  				l2fwd_ports_eth_addr[portid].addr_bytes[0],
  				l2fwd_ports_eth_addr[portid].addr_bytes[1],
  				l2fwd_ports_eth_addr[portid].addr_bytes[2],
  				l2fwd_ports_eth_addr[portid].addr_bytes[3],
  				l2fwd_ports_eth_addr[portid].addr_bytes[4],
  				l2fwd_ports_eth_addr[portid].addr_bytes[5]);

      /* initialize port stats */
  		memset(&port_statistics, 0, sizeof(port_statistics));
    }

    check_all_ports_link_status(nb_ports, l2fwd_enabled_port_mask);

    ret = 0;
  	/* launch per-lcore init on every lcore */
  	rte_eal_mp_remote_launch(l2fwd_launch_one_lcore, NULL, CALL_MASTER);
  	RTE_LCORE_FOREACH_SLAVE(lcore_id) {
  		if (rte_eal_wait_lcore(lcore_id) < 0) {
  			ret = -1;
  			break;
  		}
  	}

	// chara
	print_stats();

  for (portid = 0; portid < nb_ports; portid++) {
		if ((l2fwd_enabled_port_mask & (1 << portid)) == 0)
			continue;
		printf("Closing port %d...", portid);
		rte_eth_dev_stop(portid);
		rte_eth_dev_close(portid);
		printf(" Done\n");
	}


  return ret;
}
