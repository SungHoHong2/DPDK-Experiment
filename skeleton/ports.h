
static const struct rte_eth_conf port_conf_default = {
	.rxmode = { .max_rx_pkt_len = ETHER_MAX_LEN }
};

/*
 * Initializes a given port using global settings and with the RX buffers
 * coming from the mbuf_pool passed as a parameter.
 */

static inline int
port_init(uint8_t port, struct rte_mempool *mbuf_pool){

  struct rte_eth_conf port_conf = port_conf_default;  //port configuration
	const uint16_t rx_rings = 1, tx_rings = 1;
	int retval;
	uint16_t q;

  // safe block for not allocating ports that does not exists
  if (port >= rte_eth_dev_count())
		return -1;

  /* Configure the Ethernet device. */
	retval = rte_eth_dev_configure(port, rx_rings, tx_rings, &port_conf);
	if (retval != 0)
		return retval;

  /* Allocate and set up 1 RX queue per Ethernet port. */
	for (q = 0; q < rx_rings; q++) {
		retval = rte_eth_rx_queue_setup(port, // The port identifier of the Ethernet device.
                                    q, // The index of the receive queue to set up. The value must be in the range [0, nb_rx_queue - 1]
                                    RX_RING_SIZE,
                                    rte_eth_dev_socket_id(port), // used for NUMA
                                    NULL, // rx configuration, in case of NULL - default
                                    mbuf_pool); // pointer to memory poll to allocate rte_mbuf

    // NUMA (non-uniform memory access) is a method of configuring a cluster of microprocessor
    // in a multiprocessing system so that they can share memory locally,
    // improving performance and the ability of the system to be expanded.
    // NUMA is used in a symmetric multiprocessing ( SMP ) system. An SMP system is a "tightly-coupled,"
    // "share everything" system in which multiple processors working under a single
    // operating system access each other's memory over a common bus or "interconnect"
    // path. Ordinarily, a limitation of SMP is that as microprocessors are added,
    // the shared bus or data path get overloaded and becomes a performance bottleneck.
    // NUMA adds an intermediate level of memory shared among a few microprocessors
    // so that all data accesses don't have to travel on the main bus.

		if (retval < 0)
			return retval;
	}


  /* Allocate and set up 1 TX queue per Ethernet port. */
  for (q = 0; q < tx_rings; q++) {
    retval = rte_eth_tx_queue_setup(port, // The port identifier of the Ethernet device.
                                    q, // The index of the transmit queue to set up. The value must be in the range [0, nb_tx_queue - 1
                                    TX_RING_SIZE,
                                    rte_eth_dev_socket_id(port),
                                    NULL);
    if (retval < 0)
      return retval;
  }


  /* Start the Ethernet port. */
	retval = rte_eth_dev_start(port);
	if (retval < 0)
		return retval;


  /* Display the port MAC address. */
	struct ether_addr addr;
	rte_eth_macaddr_get(port, &addr);


	printf("Port %u MAC: %02" PRIx8 " %02" PRIx8 " %02" PRIx8
			   " %02" PRIx8 " %02" PRIx8 " %02" PRIx8 "\n",
			(unsigned)port,
			addr.addr_bytes[0], addr.addr_bytes[1],
			addr.addr_bytes[2], addr.addr_bytes[3],
			addr.addr_bytes[4], addr.addr_bytes[5]);

  /* Enable RX in promiscuous mode for the Ethernet device. */
	rte_eth_promiscuous_enable(port);

  return 0;

}
