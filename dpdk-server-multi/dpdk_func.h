

static int tx_loop(int rx_lcoreid){

    unsigned lcore_id;
    unsigned portid, nb_rx;
    struct lcore_conf *qconf;
    struct lcore_rx_queue *rxq;
    struct rte_eth_dev_tx_buffer *buffer;
    char* data;
    char *msg;
    void *_msg;
    int rte_index, frag_num, ret;
    int socketid, unique_id;
    struct rte_mbuf *m_table[MAX_FRAG_NUM];
    struct rte_mbuf *rmbuf;
    char server_full_txt[PKT_SIZE];
    uint8_t queueid;

    generate_4096_packet(server_full_txt);

    lcore_id = rte_lcore_id();
    qconf = &lcore_conf[lcore_id];
    socketid = rte_lcore_to_socket_id(lcore_id);

    if (qconf->n_rx_queue == 0) {
        RTE_LOG(INFO, L3FWD, "lcore %u has nothing to do\n", lcore_id);
        return 0;
    }

    RTE_LOG(INFO, L3FWD, "entering main loop on lcore %u\n", lcore_id);

    for (int i = 0; i < qconf->n_rx_queue; i++) {
        portid = qconf->rx_queue_list[i].port_id;
        queueid = qconf->rx_queue_list[i].queue_id;
        RTE_LOG(INFO, L3FWD, " -- lcoreid=%u portid=%u rxqueueid=%hhu\n", lcore_id, portid, queueid);
    }

    while (1) {
        // intialized packet num
        rte_index = frag_num = 0;

        while(rte_ring_dequeue(rx_ring[rx_lcoreid], &_msg) < 0){
            rte_delay_us(5);
            // printf("Failed to send message in DPDK - message discarded\n");
        }

        msg = _msg;
        rmbuf = rte_pktmbuf_alloc(transfer_pool[socketid]);
        data = rte_pktmbuf_append(rmbuf, PKT_SIZE*sizeof(char));

        struct ipv4_hdr *in_hdr;
        in_hdr = rte_pktmbuf_mtod(rmbuf, struct ipv4_hdr *);
        data += sizeof(struct ipv4_hdr) - 2;
        ipv4_wrapper(lcore_id, in_hdr, unique_id++);

        rte_memcpy(data, server_full_txt, PKT_SIZE*sizeof(char));

        frag_num = rte_ipv4_fragment_packet(rmbuf, m_table, MERGE_PACKETS*2,
                                            IPV4_MTU_DEFAULT,
                                            direct_pool[socketid], indirect_pool[socketid]);

        rte_pktmbuf_free(rmbuf);

        for (int i = rte_index; i < rte_index + frag_num; i ++) {
            void *d_addr_bytes;
            rmbuf = m_table[i];
            struct ether_hdr *eth_hdr = (struct ether_hdr *)
                    rte_pktmbuf_prepend(rmbuf, (uint16_t)sizeof(struct ether_hdr));
            if (eth_hdr == NULL) {
                rte_panic("No headroom in mbuf.\n");
            }

            rmbuf->l2_len = sizeof(struct ether_hdr);
            d_addr_bytes = &eth_hdr->d_addr.addr_bytes[0];

            // E4:1D:2D:D9:B6:41
            // E4:1D:2D:D9:CB:81
            *((uint64_t *)d_addr_bytes) = 0x80cbd92d1de4 + ((uint64_t)portid << 40);

            /* src addr */
            ether_addr_copy(&ports_eth_addr[portid], &eth_hdr->s_addr);

            // add the type of the header as IPv4
            eth_hdr->ether_type = rte_be_to_cpu_16(ETHER_TYPE_IPv4);
            // rte_pktmbuf_dump(stdout, rmbuf, 60);
        }

        if(chara_debug)
        printf("[%d]::txburst\n", lcore_id);

        ret = rte_eth_tx_burst(portid, 0, m_table, frag_num);
        if (unlikely(ret < frag_num)) {
            do {
                rte_pktmbuf_free(m_table[ret]);
            } while (++ret < frag_num);
        }
    }
}


int total_received = 0;
static inline void
reassemble(uint16_t lcoreid,
           struct rte_mbuf *m, uint16_t portid, uint32_t queue,
           struct lcore_conf *qconf, uint64_t tms)
{
    struct ether_hdr *eth_hdr;
    struct rte_ip_frag_tbl *tbl;
    struct rte_ip_frag_death_row *dr;
    struct lcore_rx_queue *rxq;
    void *d_addr_bytes;
    char *pkt_data;
    int proof_of_return;
    int recv_length;
    rxq = &qconf->rx_queue_list[queue];
    eth_hdr = rte_pktmbuf_mtod(m, struct ether_hdr *);


    if (RTE_ETH_IS_IPV4_HDR(m->packet_type)) {
        struct ipv4_hdr *ip_hdr;
        ip_hdr = (struct ipv4_hdr *)(eth_hdr + 1);

        /* if it is a fragmented packet, then try to reassemble. */
        if (rte_ipv4_frag_pkt_is_fragmented(ip_hdr)) {

            struct rte_mbuf *mo;

            tbl = rxq->frag_tbl;
            dr = &rxq->death_row;

            /* prepare mbuf: setup l2_len/l3_len. */
            m->l2_len = sizeof(*eth_hdr);
            m->l3_len = sizeof(*ip_hdr);

            /* process this fragment. */
            pthread_mutex_lock(&dpdk_mutex);
            mo = rte_ipv4_frag_reassemble_packet(tbl, dr, m, tms, ip_hdr);
            pthread_mutex_unlock(&dpdk_mutex);


            if (mo == NULL) {
                /* no packet to send out. */
                return;
            } else {
                if(chara_debug==3)
                    printf("<<packet processed!>>\n");
            }

            /* we have our packet reassembled. */
            if (mo != m) {

                proof_of_return = 0;
                m = mo;

                recv_length = rte_pktmbuf_pkt_len(m);
                if(recv_length!=4110)
                    return;


                pkt_data = rte_pktmbuf_mtod(m, char * );
                pkt_data += sizeof(struct ether_hdr) + sizeof(struct ipv4_hdr) - 2;


//                 if(chara_debug)
                    printf("[%d]::First data::[%.24s...]__length::[%ld]\n", lcoreid, pkt_data, strlen(pkt_data));
                proof_of_return+=strlen(pkt_data);


                while(m->next){
                    m = m->next;
                    pkt_data = rte_pktmbuf_mtod(m, char * );
                     if(chara_debug)
                        printf("[%d]::Following data::[%.24s...]__length::[%ld]\n", lcoreid, pkt_data, strlen(pkt_data));
                    proof_of_return+= strlen(pkt_data);
                }

                rte_pktmbuf_free(mo);

                // successfuly received!
//                if(chara_debug)
                printf("[%d, ]assembled_result: %d\n", total_received++, proof_of_return);
                if(proof_of_return>=4078){
                    // move the packet pointer back to the front
                    while(rte_ring_enqueue(rx_ring[lcoreid], "received all packets") < 0){
                        rte_delay_us(5);
                        if (chara_debug) printf("[dpdk] forward message - message discarded\n");
                    }

                    if(chara_debug) printf("message added to ring\n");
                }
            }
        }
    }
};


/* main processing loop */
int rx_loop()
{
    struct rte_mbuf *pkts_burst[MAX_PKT_BURST];
    unsigned lcore_id;
    int i, j, nb_rx;
    uint64_t cur_tsc;
    uint16_t portid;
    uint8_t queueid;
    struct lcore_conf *qconf;

    lcore_id = rte_lcore_id();
    qconf = &lcore_conf[lcore_id];

    if (qconf->n_rx_queue == 0) {
        RTE_LOG(INFO, L3FWD, "lcore %u has nothing to do\n", lcore_id);
        return 0;
    }

    RTE_LOG(INFO, L3FWD, "entering main loop on lcore %u\n", lcore_id);

    for (i = 0; i < qconf->n_rx_queue; i++) {
        portid = qconf->rx_queue_list[i].port_id;
        queueid = qconf->rx_queue_list[i].queue_id;
        RTE_LOG(INFO, L3FWD, " -- lcoreid=%u portid=%u rxqueueid=%hhu\n", lcore_id, portid, queueid);
    }

    while (!force_quit) {

        /*
         * Read packet from RX queues
         */
        for (i = 0; i < qconf->n_rx_queue; ++i) {
            portid = qconf->rx_queue_list[i].port_id;
            queueid = qconf->rx_queue_list[i].queue_id;
            nb_rx = rte_eth_rx_burst(portid, queueid, pkts_burst, MAX_PKT_BURST);
            if (nb_rx == 0)
                continue;

            /* Prefetch first packets */
            for (j = 0; j < PREFETCH_OFFSET && j < nb_rx; j++) {
                rte_prefetch0(rte_pktmbuf_mtod(pkts_burst[j], void *));
            }

            /* Prefetch and forward already prefetched packets */
            for (j = 0; j < (nb_rx - PREFETCH_OFFSET); j++) {
                rte_prefetch0(rte_pktmbuf_mtod(pkts_burst[j + PREFETCH_OFFSET], void *));
                reassemble(lcore_id, pkts_burst[j], portid, i, qconf, cur_tsc);
            }

            /* Forward remaining prefetched packets */
            for (; j < nb_rx; j++) {
                reassemble(lcore_id, pkts_burst[j], portid, i, qconf, cur_tsc);
            }

            rte_ip_frag_free_death_row(&qconf->rx_queue_list[i].death_row, PREFETCH_OFFSET);
        }
    }

    return 0;
}


int
lpm_check_ptype(int portid)
{
    int i, ret;
    int ptype_l3_ipv4 = 0, ptype_l3_ipv6 = 0;
    uint32_t ptype_mask = RTE_PTYPE_L3_MASK;

    ret = rte_eth_dev_get_supported_ptypes(portid, ptype_mask, NULL, 0);
    if (ret <= 0)
        return 0;

    uint32_t ptypes[ret];

    ret = rte_eth_dev_get_supported_ptypes(portid, ptype_mask, ptypes, ret);
    for (i = 0; i < ret; ++i) {
        if (ptypes[i] & RTE_PTYPE_L3_IPV4)
            ptype_l3_ipv4 = 1;
        if (ptypes[i] & RTE_PTYPE_L3_IPV6)
            ptype_l3_ipv6 = 1;
    }

    if (ptype_l3_ipv4 == 0)
        printf("port %d cannot parse RTE_PTYPE_L3_IPV4\n", portid);

    if (ptype_l3_ipv6 == 0)
        printf("port %d cannot parse RTE_PTYPE_L3_IPV6\n", portid);

    if (ptype_l3_ipv4 && ptype_l3_ipv6)
        return 1;

    return 0;

}

static inline void
lpm_parse_ptype(struct rte_mbuf *m)
{
    struct ether_hdr *eth_hdr;
    uint32_t packet_type = RTE_PTYPE_UNKNOWN;
    uint16_t ether_type;

    eth_hdr = rte_pktmbuf_mtod(m, struct ether_hdr *);
    ether_type = eth_hdr->ether_type;
    if (ether_type == rte_cpu_to_be_16(ETHER_TYPE_IPv4))
        packet_type |= RTE_PTYPE_L3_IPV4_EXT_UNKNOWN;
    else if (ether_type == rte_cpu_to_be_16(ETHER_TYPE_IPv6))
        packet_type |= RTE_PTYPE_L3_IPV6_EXT_UNKNOWN;

    m->packet_type = packet_type;
}

uint16_t
lpm_cb_parse_ptype(uint16_t port __rte_unused, uint16_t queue __rte_unused,
                   struct rte_mbuf *pkts[], uint16_t nb_pkts,
                   uint16_t max_pkts __rte_unused,
                   void *user_param __rte_unused)
{
    unsigned i;

    for (i = 0; i < nb_pkts; ++i)
        lpm_parse_ptype(pkts[i]);

    return nb_pkts;
}

