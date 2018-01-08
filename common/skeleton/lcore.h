
/*
 * The lcore main. This is the main thread that does the work, reading from
 * an input port and writing to an output port.
 */
static __attribute__((noreturn)) void lcore_main(void){

  const uint8_t nb_ports = rte_eth_dev_count();
  uint8_t port;

  /* Run until the application is quit or killed. */
  for (;;) {

     /*
      * Receive packets on a port and forward them on the paired
      * port. The mapping is 0 -> 1, 1 -> 0, 2 -> 3, 3 -> 2, etc.
      */

      for (port = 0; port < nb_ports; port++) {

  			/* Get burst of RX packets, from first port of pair. */
  			struct rte_mbuf *bufs[BURST_SIZE];
  			const uint16_t nb_rx = rte_eth_rx_burst(port, // port identifier
                                                0,    // queue id
                                                bufs, //rte_buff
                                                BURST_SIZE); // number of packets to retrieve

  			if (unlikely(nb_rx == 0))
  				continue;

  			/* Send burst of TX packets, to second port of pair. */
  			const uint16_t nb_tx = rte_eth_tx_burst(port ^ 1, 0, bufs, nb_rx);

  			/* Free any unsent packets. */
  			if (unlikely(nb_tx < nb_rx)) {
  				uint16_t buf;
  				for (buf = nb_tx; buf < nb_rx; buf++)
  					rte_pktmbuf_free(bufs[buf]);
  			}

  		}
  }

}
