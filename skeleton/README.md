### FWD

```
./build/basicfwd -l 0-3 -n 4 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x3
```


<br>


```c
struct rte_mempool *mbuf_pool; //memory pool is introduced because of the ports
unsigned nb_ports; // number of ports
uint8_t portid; // port id


/* Initialize the Environment Abstraction Layer (EAL). */
int ret = rte_eal_init(argc, argv);


nb_ports = rte_eth_dev_count(); // counting the number of available ports



/* Creates a new mempool in memory to hold the mbufs. */
mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL", // name of the packet pool
                                     NUM_MBUFS * nb_ports, // number of elements in mbuf pool
                                     MBUF_CACHE_SIZE, // per core cache size
                                     0, // private data size
                                     RTE_MBUF_DEFAULT_BUF_SIZE, // size of the data buffer in each mbuf
                                     rte_socket_id()); // this is the master core

/* Initialize all ports. */
for (portid = 0; portid < nb_ports; portid++)
      port_init(portid, mbuf_pool);

```

<br>


- step into port_init

```c

  struct rte_eth_conf port_conf = port_conf_default;  //port configuration
	const uint16_t rx_rings = 1, tx_rings = 1;
	int retval;
	uint16_t q;


  /* Configure the Ethernet device. */
  retval = rte_eth_dev_configure(port, rx_rings, tx_rings, &port_conf);


  /* Allocate and set up 1 RX queue per Ethernet port. */
  for (q = 0; q < rx_rings; q++)
        rte_eth_rx_queue_setup(port, // The port identifier of the Ethernet device.
                               q, // The index of the receive queue to set up. The value must be in the range [0, nb_rx_queue - 1]
                               RX_RING_SIZE,
                               rte_eth_dev_socket_id(port), // used for NUMA
                               NULL, // rx configuration, in case of NULL - default
                               mbuf_pool); // pointer to memory poll to allocate rte_mbuf


  for (q = 0; q < tx_rings; q++) {
        rte_eth_tx_queue_setup(port, // The port identifier of the Ethernet device.
                               q, // The index of the transmit queue to set up. The value must be in the range [0, nb_tx_queue - 1
                               TX_RING_SIZE,
                               rte_eth_dev_socket_id(port),
                               NULL);

  /* Start the Ethernet port. */
 	retval = rte_eth_dev_start(port);

  /* Enable RX in promiscuous mode for the Ethernet device. */
	rte_eth_promiscuous_enable(port);

```

<br>


```c
/* Call lcore_main on the master core only. */
lcore_main();
```

- step into lcore_main()


```c
/* Run until the application is quit or killed. */
for (;;) {
  for (port = 0; port < nb_ports; port++) {

        /* Get burst of RX packets, from first port of pair. */
        struct rte_mbuf *bufs[BURST_SIZE];

        const uint16_t nb_rx = rte_eth_rx_burst(port, // port identifier
                                                0,    // queue id
                                                bufs, //rte_buff
                                                BURST_SIZE); // number of packets to retrieve

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

```
