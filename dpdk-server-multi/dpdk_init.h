


#define	DEF_FLOW_NUM	0x1000
static uint32_t max_flow_num = DEF_FLOW_NUM;

static int
setup_port_tbl(struct lcore_conf *qconf, uint32_t lcore, int socket,
               uint32_t port)
{
    struct mbuf_table *mtb;
    uint32_t n;
    size_t sz;

    n = RTE_MAX(max_flow_num, 2UL * MAX_PKT_BURST);
    sz = sizeof (*mtb) + sizeof (mtb->m_table[0]) *  n;

    if ((mtb = rte_zmalloc_socket(__func__, sz, RTE_CACHE_LINE_SIZE,
                                  socket)) == NULL) {
        return -1;
    }

    mtb->len = n;
    qconf->tx_mbufs[port] = mtb;

    return 0;
}


/* TTL numbers are in ms. */
#define	MAX_FLOW_TTL	(3600 * MS_PER_S)
#define	MIN_FLOW_TTL	1
#define	DEF_FLOW_TTL	MS_PER_S
static uint32_t max_flow_ttl = DEF_FLOW_TTL;

/* Should be power of two. */
#define	IP_FRAG_TBL_BUCKET_ENTRIES	16
#define MAX_FRAG_NUM RTE_LIBRTE_IP_FRAG_MAX_FRAG
#define	BUF_SIZE	RTE_MBUF_DEFAULT_DATAROOM

static int
setup_queue_tbl(struct lcore_rx_queue *rxq, uint32_t lcore, uint32_t queue)
{
    int socket;
    uint32_t nb_mbuf;
    uint64_t frag_cycles;
    char buf[RTE_MEMPOOL_NAMESIZE];

    socket = rte_lcore_to_socket_id(lcore);
    if (socket == SOCKET_ID_ANY)
        socket = 0;

    frag_cycles = (rte_get_tsc_hz() + MS_PER_S - 1) / MS_PER_S * max_flow_ttl;
    if ((rxq->frag_tbl = rte_ip_frag_table_create(max_flow_num,
                                                  IP_FRAG_TBL_BUCKET_ENTRIES, max_flow_num, frag_cycles,
                                                  socket)) == NULL) {
        printf("rte_ip_frag_table_create failed!!!!\n");
        return -1;
    }

    nb_mbuf = RTE_MAX(max_flow_num, 2UL * MAX_PKT_BURST) * MAX_FRAG_NUM;
    nb_mbuf *= (port_conf.rxmode.max_rx_pkt_len + BUF_SIZE - 1) / BUF_SIZE;
    nb_mbuf *= 1;
    nb_mbuf += nb_rxd + nb_txd;

    if (transfer_pool[lcore] == NULL) {

        snprintf(buf, sizeof(buf), "pool_recieve_%d", socket);
        receive_pool[lcore] = rte_pktmbuf_pool_create(buf, nb_mbuf, MEMPOOL_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket);

        snprintf(buf, sizeof(buf), "pool_transfer_%d", socket);
        transfer_pool[lcore] = rte_pktmbuf_pool_create(buf, nb_mbuf, MEMPOOL_CACHE_SIZE, 0, PKT_SIZE + 128, socket);

        snprintf(buf, sizeof(buf), "pool_direct_%d", socket);
        direct_pool[lcore] = rte_pktmbuf_pool_create(buf, nb_mbuf, MEMPOOL_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE, socket);

        snprintf(buf, sizeof(buf), "pool_indirect_%d", socket);
        indirect_pool[lcore] = rte_pktmbuf_pool_create(buf, nb_mbuf, MEMPOOL_CACHE_SIZE, 0, 0, socket);
    }

    snprintf(buf, sizeof(buf), "mbuf_rx_ring_%d", lcore);
    rx_ring[lcore] = rte_ring_create(buf, 512, socket, 0);
    snprintf(buf, sizeof(buf), "mbuf_tx_ring_%d", lcore);
    tx_ring[lcore] = rte_ring_create(buf, 512, socket, 0);

    // for packet assemble
    rxq->ar = (struct assembled_result *)malloc(sizeof(struct assembled_result));
    rxq->ar->length = 0;
    rxq->ar->assembled_pkt = (char *)malloc(sizeof(char)*PKT_SIZE);
    return 0;
}



int dpdk_init(){

    struct lcore_conf *qconf;
    struct rte_eth_dev_info dev_info;
    struct rte_eth_txconf *txconf;
    int ret;
    unsigned nb_ports;
    uint16_t queueid, portid;
    unsigned lcore_id;
    uint32_t n_tx_queue, nb_lcores;
    uint8_t nb_rx_queue, queue, socketid;


    int count = 9;
    char** dpdk_argv;
    dpdk_argv = malloc(count * sizeof(char*));      // allocate the array to hold the pointer
    for (size_t i = 0; i < count; i += 1)
        dpdk_argv[i] = malloc(255 * sizeof(char));  // allocate each array to hold the strings

    dpdk_argv[0]="./build/dpdk_server";
    dpdk_argv[1]="-l";
    dpdk_argv[2]="1-8";
    dpdk_argv[3]="-n";
    dpdk_argv[4]="4";
    dpdk_argv[5]="--";
    dpdk_argv[6]="-p";
    dpdk_argv[7]="0x2";
    dpdk_argv[8]="--config=(1,0,1),(1,1,2),(1,2,3),(1,3,4),(1,4,5),(1,5,6),(1,6,7),(1,7,8)";



    /* init EAL */
    ret = rte_eal_init(count, dpdk_argv);
    if (ret < 0)
        rte_exit(EXIT_FAILURE, "Invalid EAL parameters\n");
    count -= ret;
    dpdk_argv += ret;

    force_quit = false;
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    /* pre-init dst MACs for all ports to 02:00:00:00:00:xx */
    for (portid = 0; portid < RTE_MAX_ETHPORTS; portid++) {
        dest_eth_addr[portid] =
                ETHER_LOCAL_ADMIN_ADDR + ((uint64_t)portid << 40);
        *(uint64_t *)(val_eth + portid) = dest_eth_addr[portid];
    }

    /* parse application arguments (after the EAL ones) */
    ret = parse_args(count, dpdk_argv);
    if (ret < 0)
        rte_exit(EXIT_FAILURE, "Invalid L3FWD parameters\n");

    if (check_lcore_params() < 0)
        rte_exit(EXIT_FAILURE, "check_lcore_params failed\n");

    ret = init_lcore_rx_queues();
    if (ret < 0)
        rte_exit(EXIT_FAILURE, "init_lcore_rx_queues failed\n");

    nb_ports = rte_eth_dev_count();

    if (check_port_config(nb_ports) < 0)
        rte_exit(EXIT_FAILURE, "check_port_config failed\n");

    nb_lcores = rte_lcore_count();

    /* Setup function pointers for lookup method. */
    setup_l3fwd_lookup_tables();

    /* initialize all ports */
    for (portid = 0; portid < nb_ports; portid++) {
        /* skip ports that are not enabled */
        if ((enabled_port_mask & (1 << portid)) == 0) {
            printf("\nSkipping disabled port %d\n", portid);
            continue;
        }

        /* init port */
        printf("Initializing port %d ... ", portid );
        fflush(stdout);

        nb_rx_queue = get_port_n_rx_queues(portid);
        n_tx_queue = nb_lcores;
        if (n_tx_queue > MAX_TX_QUEUE_PER_PORT)
            n_tx_queue = MAX_TX_QUEUE_PER_PORT;
        printf("Creating queues: nb_rxq=%d nb_txq=%u... ",
               nb_rx_queue, (unsigned)n_tx_queue );
        ret = rte_eth_dev_configure(portid, nb_rx_queue,
                                    (uint16_t)n_tx_queue, &port_conf);
        if (ret < 0)
            rte_exit(EXIT_FAILURE,
                     "Cannot configure device: err=%d, port=%d\n",
                     ret, portid);

        ret = rte_eth_dev_adjust_nb_rx_tx_desc(portid, &nb_rxd, &nb_txd);
        if (ret < 0)
            rte_exit(EXIT_FAILURE,
                     "Cannot adjust number of descriptors: err=%d, "
                     "port=%d\n", ret, portid);

        rte_eth_macaddr_get(portid, &ports_eth_addr[portid]);
        print_ethaddr(" Address:", &ports_eth_addr[portid]);
        printf(", ");
        print_ethaddr("Destination:",
                      (const struct ether_addr *)&dest_eth_addr[portid]);
        printf(", ");

        /*
         * prepare src MACs for each port.
         */
        ether_addr_copy(&ports_eth_addr[portid],
                        (struct ether_addr *)(val_eth + portid) + 1);

        /* init memory */
        ret = init_mem(NB_MBUF);
        if (ret < 0)
            rte_exit(EXIT_FAILURE, "init_mem failed\n");



        // FIXME: allocate 1/2 cores to tx
        /* init one TX queue per couple (lcore,port) */
        queueid = 0;

        for (lcore_id = 0; lcore_id < RTE_MAX_LCORE; lcore_id++) {
            if (rte_lcore_is_enabled(lcore_id) == 0)
                continue;

            if (numa_on)
                socketid = (uint8_t)rte_lcore_to_socket_id(lcore_id);
            else
                socketid = 0;

            printf("txq=%u,%d,%d ", lcore_id, queueid, socketid);
            fflush(stdout);

            rte_eth_dev_info_get(portid, &dev_info);
            txconf = &dev_info.default_txconf;
            if (port_conf.rxmode.jumbo_frame)
                txconf->txq_flags = 0;
            ret = rte_eth_tx_queue_setup(portid, queueid, nb_txd,
                                         socketid, txconf);
            if (ret < 0)
                rte_exit(EXIT_FAILURE,
                         "rte_eth_tx_queue_setup: err=%d, "
                         "port=%d\n", ret, portid);

            qconf = &lcore_conf[lcore_id];
            qconf->tx_queue_id[portid] = queueid;
            queueid++;
            setup_port_tbl(qconf, lcore_id, socketid, portid);
            qconf->tx_port_id[qconf->n_tx_port] = portid;
            qconf->n_tx_port++;
        }
        printf("\n");
    }

    struct lcore_rx_queue *rxq;
    // FIXME: allocate 1/2 cores to rx
    for (lcore_id = 0; lcore_id < RTE_MAX_LCORE; lcore_id++) {
        if (rte_lcore_is_enabled(lcore_id) == 0)
            continue;
        qconf = &lcore_conf[lcore_id];
        printf("\nInitializing rx queues on lcore %u ... ", lcore_id );
        fflush(stdout);
        /* init RX queues */
        for(queue = 0; queue < qconf->n_rx_queue; ++queue) {
            portid = qconf->rx_queue_list[queue].port_id;
            queueid = qconf->rx_queue_list[queue].queue_id;
            rxq = &qconf->rx_queue_list[queue];

            if (setup_queue_tbl(rxq, lcore_id, queueid) < 0)
                rte_exit(EXIT_FAILURE, "Failed to set up queue table\n");

            if (numa_on)
                socketid = (uint8_t)rte_lcore_to_socket_id(lcore_id);
            else
                socketid = 0;

            printf("rxq=%d,%d,%d ", portid, queueid, socketid);
            fflush(stdout);

            ret = rte_eth_rx_queue_setup(portid, queueid, nb_rxd, socketid, NULL, receive_pool[socketid]);
            if (ret < 0)
                rte_exit(EXIT_FAILURE,
                         "rte_eth_rx_queue_setup: err=%d, port=%d\n",
                         ret, portid);
        }
    }

    printf("\n");

    /* start ports */
    for (portid = 0; portid < nb_ports; portid++) {
        if ((enabled_port_mask & (1 << portid)) == 0) {
            continue;
        }
        /* Start device */
        ret = rte_eth_dev_start(portid);
        if (ret < 0)
            rte_exit(EXIT_FAILURE,
                     "rte_eth_dev_start: err=%d, port=%d\n",
                     ret, portid);

        rte_eth_promiscuous_disable(portid);
    }

    printf("\n");

    for (lcore_id = 0; lcore_id < RTE_MAX_LCORE; lcore_id++) {
        if (rte_lcore_is_enabled(lcore_id) == 0)
            continue;
        qconf = &lcore_conf[lcore_id];
        for (queue = 0; queue < qconf->n_rx_queue; ++queue) {
            portid = qconf->rx_queue_list[queue].port_id;
            queueid = qconf->rx_queue_list[queue].queue_id;
            if (prepare_ptype_parser(portid, queueid) == 0)
                rte_exit(EXIT_FAILURE, "ptype check fails\n");
        }
    }
    check_all_ports_link_status(nb_ports, enabled_port_mask);
}
