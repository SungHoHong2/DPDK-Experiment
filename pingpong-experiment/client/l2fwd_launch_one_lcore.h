#include <time.h>
const int LATENCY = 0, LIMIT = 100000;
const int THROUGHPUT = 1, TIMER = 10;
static time_t start, end; //adding timer

/* Print out statistics on packets dropped */
static void print_stats(void){
	uint64_t total_packets_dropped, total_packets_tx, total_packets_rx;
  uint64_t curr_time, duration;
	unsigned portid;


	total_packets_dropped = 0;
	total_packets_tx = 0;
	total_packets_rx = 0;

	const char clr[] = { 27, '[', '2', 'J', '\0' };
	const char topLeft[] = { 27, '[', '1', ';', '1', 'H','\0' };

		/* Clear screen and move to top left */
	printf("%s%s", clr, topLeft);

	printf("\nDPDK Pingpong Client ====================================");

	for (portid = 0; portid < RTE_MAX_ETHPORTS; portid++) {
		/* skip disabled ports */
		if ((l2fwd_enabled_port_mask & (1 << portid)) == 0)
			continue;


		printf("\nByte statistics for port %u ------------------------------"
				 "\nPKT-SIZE: %d"
			   "\nByte received: %24"PRIu64,
			   portid,
				 PKT_SIZE,
			   port_statistics[portid].rx_bytes);

		printf("\nPacket statistics for port %u ------------------------------"
			   "\nPacket sent: %24"PRIu64
			   "\nPacket received: %20"PRIu64
			   "\nPacket dropped: %21"PRIu64,
			   portid,
			   port_statistics[portid].tx,
			   port_statistics[portid].rx,
			   port_statistics[portid].dropped);
	}
	printf("\n====================================================\n");
}


static void
l2fwd_mac_updating(struct rte_mbuf *m, unsigned dest_portid){
	struct ether_hdr *eth;
	void *tmp;

	eth = rte_pktmbuf_mtod(m, struct ether_hdr *);

	/* 02:00:00:00:00:xx */
	// A0:36:9F:83:AB:BD
	// 0x00 00 00 00 00 02
	tmp = &eth->d_addr.addr_bytes[0];

	// 0x 00 00 00 00 00 02
  //    A0:36:9F:83:AB:BD
	// 0x 00 00 00 00 00 02

  // 0x bd ab 83 9f 36 a0
  // 0x000000000002
  // 0x0000000002
	// 00 bd ab 83 9f 36 a0
	// A0:36:9F:83:AB:BD
	*((uint64_t *)tmp) = 0x00ab839f36a0  + ((uint64_t)dest_portid << 40);
	// *((uint64_t *)tmp) = 0xbdab839f36a0 + ((uint64_t)dest_portid << 40);

	/* src addr */
	ether_addr_copy(&l2fwd_ports_eth_addr[dest_portid], &eth->s_addr);

}



/* main processing loop */
static void l2fwd_main_loop(void){
    struct rte_mbuf *pkts_burst[MAX_PKT_BURST];
		struct rte_mbuf *rm[1];
  	struct rte_mbuf *m;
  	int sent;
  	unsigned lcore_id;
  	uint64_t prev_tsc, diff_tsc, cur_tsc, timer_tsc;
  	unsigned i, j, portid, nb_rx;
  	struct lcore_queue_conf *qconf;
  	const uint64_t drain_tsc = (rte_get_tsc_hz() + US_PER_S - 1) / US_PER_S * BURST_TX_DRAIN_US;
  	struct rte_eth_dev_tx_buffer *buffer;

    prev_tsc = 0;
  	timer_tsc = 0;

    lcore_id = rte_lcore_id();
  	qconf = &lcore_queue_conf[lcore_id];

  	if (qconf->n_rx_port == 0) {
  		RTE_LOG(INFO, L2FWD, "lcore %u has nothing to do\n", lcore_id);
  		return;
  	}

		time (&start); //useful call
		char *data, *rtn;

    while (!force_quit) {
        cur_tsc = rte_rdtsc();
        /*
         * TX burst queue drain
         */
        diff_tsc = cur_tsc - prev_tsc;
        if (unlikely(diff_tsc > drain_tsc)) {

            for (i = 0; i < qconf->n_rx_port; i++) {
                portid = l2fwd_dst_ports[qconf->rx_port_list[i]];
                buffer = tx_buffer[portid];
                sent = rte_eth_tx_buffer_flush(portid, 0, buffer);
                if (sent)
                  port_statistics[portid].tx += sent;
            }

            /* if timer is enabled */
      			if (timer_period > 0) {
      				/* advance the timer */
      				timer_tsc += diff_tsc;
      				/* if timer has reached its timeout */
      				if (unlikely(timer_tsc >= timer_period)) {
      					/* do this only on master core */
      					if (lcore_id == rte_get_master_lcore()) {
      						// print_stats();
      						// /* reset the timer */
									if(difftime( time(0), start)>=TIMER){
										 	print_stats();
											force_quit=1;
									}
									timer_tsc = 0;
      					}
      				}
      			}
      			prev_tsc = cur_tsc;
        }

        /*
         * Read packet from RX queues
         */
        for (i = 0; i < qconf->n_rx_port; i++) {
          	portid = qconf->rx_port_list[i];
          	nb_rx = rte_eth_rx_burst((uint8_t) portid, 0,
                 		pkts_burst, MAX_PKT_BURST);

          	port_statistics[portid].rx += nb_rx;

						for (j = 0; j < nb_rx; j++) {
								rtn = rte_pktmbuf_mtod_offset(pkts_burst[j], char *, sizeof(data));

								for(int s=0; s<strlen(rtn); s++){
										if(rtn[s]=='*') port_statistics[portid].rx_bytes += 1 //rte_pktmbuf_pkt_len(pkts_burst[j]);
								}
								rte_pktmbuf_free(pkts_burst[j]);
						}

						rm[0] = rte_pktmbuf_alloc(test_pktmbuf_pool);
						data = rte_pktmbuf_append(rm[0], PKT_SIZE);
						memset(data, '*', rte_pktmbuf_pkt_len(rm[0]));
						rte_prefetch0(rte_pktmbuf_mtod(rm[0], void *));
						l2fwd_mac_updating(rm[0], portid);

						sent = rte_eth_tx_burst(portid, 0, rm, 1);

						if (sent){
							port_statistics[portid].tx += sent;
						}
						rte_pktmbuf_free(rm[0]);
        }
      }

}


static int
l2fwd_launch_one_lcore(__attribute__((unused)) void *dummy){
	if (THROUGHPUT) time(&start);
	l2fwd_main_loop();
	return 0;
}
