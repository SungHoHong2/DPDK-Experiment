#include <stdint.h>
#include <inttypes.h>
#include <rte_eal.h>
#include <rte_ethdev.h>
#include <rte_cycles.h>
#include <rte_lcore.h>
#include <rte_mbuf.h>
#include "ports.h"


#define RX_RING_SIZE 128
#define TX_RING_SIZE 512

#define NUM_MBUFS 8191
#define MBUF_CACHE_SIZE 250
#define BURST_SIZE 32


int main(int argc, char *argv[]){

  struct rte_mempool *mbuf_pool; //memory pool is introduced because of the ports
	unsigned nb_ports; // number of ports
	uint8_t portid; // port id


  /* Initialize the Environment Abstraction Layer (EAL). */
	int ret = rte_eal_init(argc, argv);
	if (ret < 0)
		rte_exit(EXIT_FAILURE, "Error with EAL initialization\n");

	argc -= ret;
	argv += ret;


  /* Check that there is an even number of ports to send/receive on. */
	nb_ports = rte_eth_dev_count(); // counting the number of available ports
	if (nb_ports < 2 || (nb_ports & 1)){
  	rte_exit(EXIT_FAILURE, "Error: number of ports must be even\n");
  }

  printf("number of ports: %u\n", rte_eth_dev_count()); // got two ports


  /* Creates a new mempool in memory to hold the mbufs. */

	mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL", // name of the packet pool
                                       NUM_MBUFS * nb_ports, // number of elements in mbuf pool
		                                   MBUF_CACHE_SIZE, // per core cache size
                                       0, // private data size
                                       RTE_MBUF_DEFAULT_BUF_SIZE, // size of the data buffer in each mbuf
                                       rte_socket_id()); // this is the master core

  // rte_socket_id -> invoking here will get the master core
  // the ID of current lcoreid's physical socket
  // printf("current lcore's id %u\n", rte_socket_id());

  if (mbuf_pool == NULL)
		rte_exit(EXIT_FAILURE, "Cannot create mbuf pool\n");

  /* Initialize all ports. */
  // each ports will be allocated in the single pool
	for (portid = 0; portid < nb_ports; portid++)
		if (port_init(portid, mbuf_pool) != 0)
			rte_exit(EXIT_FAILURE, "Cannot init port %"PRIu8 "\n",portid);


  /* Call lcore_main on the master core only. */
	// lcore_main();

  return 0;

}
