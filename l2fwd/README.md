### L2FWD

```
./build/l2fwd -l 0-3 -n 4 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x3 -T 1
gdb --args ./build/l2fwd -l 0-3 -n 4 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x3 -T 1

```

<br>

```c
/* init EAL */
ret = rte_eal_init(argc, argv);

/* arguments of port, queue and time */
ret = l2fwd_parse_args(argc, argv);

/* create the mbuf pool */
l2fwd_pktmbuf_pool = rte_pktmbuf_pool_create("mbuf_pool", NB_MBUF,
  MEMPOOL_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE,
  rte_socket_id());

```

> the basic initialization for packet forwarding


<br>


```c
/* reset l2fwd_dst_ports */
for (portid = 0; portid < RTE_MAX_ETHPORTS; portid++)
  l2fwd_dst_ports[portid] = 0;
last_port = 0;


/*
 * Each logical core is assigned a dedicated TX queue on each port.
 */
 for (portid = 0; portid < nb_ports; portid++) {
   if ((l2fwd_enabled_port_mask & (1 << portid)) == 0)
      continue;

   if (nb_ports_in_mask % 2) {
      l2fwd_dst_ports[portid] = last_port;
      l2fwd_dst_ports[last_port] = portid;
    } else
    last_port = portid;

  nb_ports_in_mask++;
  rte_eth_dev_info_get(portid, &dev_info);
}



/*
 * save the list of port id in the global configuration struct
 */

 struct lcore_queue_conf *qconf;
 for (portid = 0; portid < nb_ports; portid++) {

   // skip ports that are not enabled
   if ((l2fwd_enabled_port_mask & (1 << portid)) == 0)
     continue;

   // get the lcore_id for this port
     while (rte_lcore_is_enabled(rx_lcore_id) == 0 || lcore_queue_conf[rx_lcore_id].n_rx_port == l2fwd_rx_queue_per_lcore) {
           rx_lcore_id++;

       if (rx_lcore_id >= RTE_MAX_LCORE)
           rte_exit(EXIT_FAILURE, "Not enough cores\n");
     }

   if (qconf != &lcore_queue_conf[rx_lcore_id])
       // Assigned a new logical core in the loop above.
       qconf = &lcore_queue_conf[rx_lcore_id];

     qconf->rx_port_list[qconf->n_rx_port] = portid;
     qconf->n_rx_port++;
     printf("Lcore %u: RX port %u\n", rx_lcore_id, (unsigned) portid);
 }
 nb_ports_available = nb_ports;


```

> overall configuration of ports <br>
> this configuration file is used in the thread loop


<br>


```c
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

```

<br>


- running the main thread loops
```c
ret = 0;
/* launch per-lcore init on every lcore */
rte_eal_mp_remote_launch(l2fwd_launch_one_lcore, NULL, CALL_MASTER);
RTE_LCORE_FOREACH_SLAVE(lcore_id) {
  if (rte_eal_wait_lcore(lcore_id) < 0) {
    ret = -1;
    break;
  }
}
```

```c
prev_tsc = 0;
timer_tsc = 0;

lcore_id = rte_lcore_id();
qconf = &lcore_queue_conf[lcore_id];


if (qconf->n_rx_port == 0) {
	RTE_LOG(INFO, L2FWD, "lcore %u has nothing to do\n", lcore_id);
	return;
}

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
  						print_stats();
  						/* reset the timer */
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
        m = pkts_burst[j];
        rte_prefetch0(rte_pktmbuf_mtod(m, void *));
        l2fwd_simple_forward(m, portid);
      }
    }
  }
```


```c
static void
l2fwd_simple_forward(struct rte_mbuf *m, unsigned portid){
	unsigned dst_port;
	int sent;
	struct rte_eth_dev_tx_buffer *buffer;

	dst_port = l2fwd_dst_ports[portid];

	if (mac_updating)
		l2fwd_mac_updating(m, dst_port);

  buffer = tx_buffer[dst_port];
	sent = rte_eth_tx_buffer(dst_port, 0, buffer, m);
	if (sent)
		port_statistics[dst_port].tx += sent;
}
```
