#include <stdint.h>
#include <inttypes.h>
#include <rte_eal.h>
#include <rte_ethdev.h>
#include <rte_cycles.h>
#include <rte_lcore.h>
#include <rte_mbuf.h>

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
	if (nb_ports < 2 || (nb_ports & 1))
		rte_exit(EXIT_FAILURE, "Error: number of ports must be even\n");


  /* Creates a new mempool in memory to hold the mbufs. */
	mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL", NUM_MBUFS * nb_ports,
		MBUF_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());

  // rte_socket_id
  // the ID of current lcoreid's physical socket
  printf("current lcore's id %u\n", rte_socket_id());
  printf("current lcore's id %u\n", rte_socket_id());
  printf("current lcore's id %u\n", rte_socket_id());






  return 0;

}
