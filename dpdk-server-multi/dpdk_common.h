/*
 * Configurable number of RX/TX ring descriptors
 */
#define RTE_TEST_RX_DESC_DEFAULT 128
#define RTE_TEST_TX_DESC_DEFAULT 512

#define MAX_TX_QUEUE_PER_PORT RTE_MAX_ETHPORTS
#define MAX_RX_QUEUE_PER_PORT 128

#define MAX_LCORE_PARAMS 1024

/* Static global variables used within this file. */
static uint16_t nb_rxd = RTE_TEST_RX_DESC_DEFAULT;
static uint16_t nb_txd = RTE_TEST_TX_DESC_DEFAULT;

/**< Ports set in promiscuous mode off by default. */
static int promiscuous_on;

/* Select Longest-Prefix or Exact match. */
static int l3fwd_lpm_on;
static int l3fwd_em_on;

static int numa_on = 1; /**< NUMA is enabled by default. */
static int parse_ptype; /**< Parse packet type using rx callback, and */
/**< disabled by default */

/* Global variables. */

volatile bool force_quit;

/* ethernet addresses of ports */
uint64_t dest_eth_addr[RTE_MAX_ETHPORTS];
struct ether_addr ports_eth_addr[RTE_MAX_ETHPORTS];

xmm_t val_eth[RTE_MAX_ETHPORTS];

/* mask of enabled ports */
uint32_t enabled_port_mask;

/* Used only in exact match mode. */
int ipv6; /**< ipv6 is false by default. */
uint32_t hash_entry_number = HASH_ENTRY_NUMBER_DEFAULT;

struct lcore_conf lcore_conf[RTE_MAX_LCORE];

struct lcore_params {
    uint16_t port_id;
    uint8_t queue_id;
    uint8_t lcore_id;
} __rte_cache_aligned;

static struct lcore_params lcore_params_array[MAX_LCORE_PARAMS];
static struct lcore_params lcore_params_array_default[] = {
        {0, 0, 2},
        {0, 1, 2},
        {0, 2, 2},
        {1, 0, 2},
        {1, 1, 2},
        {1, 2, 2},
        {2, 0, 2},
        {3, 0, 3},
        {3, 1, 3},
};

static struct lcore_params * lcore_params = lcore_params_array_default;
static uint16_t nb_lcore_params = sizeof(lcore_params_array_default) /
                                  sizeof(lcore_params_array_default[0]);

static struct rte_eth_conf port_conf = {
        .rxmode = {
                .mq_mode = ETH_MQ_RX_RSS,
                .max_rx_pkt_len = ETHER_MAX_LEN,
                .split_hdr_size = 0,
                .header_split   = 0, /**< Header Split disabled */
                .hw_ip_checksum = 1, /**< IP checksum offload enabled */
                .hw_vlan_filter = 0, /**< VLAN filtering disabled */
                .jumbo_frame    = 0, /**< Jumbo Frame Support disabled */
                .hw_strip_crc   = 1, /**< CRC stripped by hardware */
        },
        .rx_adv_conf = {
                .rss_conf = {
                        .rss_key = NULL,
                        .rss_hf = ETH_RSS_IP,
                },
        },
        .txmode = {
                .mq_mode = ETH_MQ_TX_NONE,
        },
};



struct l3fwd_lkp_mode {
    void  (*setup)(int);
    int   (*check_ptype)(int);
    rte_rx_callback_fn cb_parse_ptype;
    int   (*main_loop)(void *);
    void* (*get_ipv4_lookup_struct)(int);
};

static struct l3fwd_lkp_mode l3fwd_lkp;

static struct l3fwd_lkp_mode l3fwd_lpm_lkp = {
        .check_ptype		= lpm_check_ptype,
        .cb_parse_ptype		= lpm_cb_parse_ptype,
        .main_loop          = lpm_main_loop,
};

/*
 * Setup lookup methods for forwarding.
 * Currently exact-match and longest-prefix-match
 * are supported ones.
 */
static void
setup_l3fwd_lookup_tables(void)
{
    l3fwd_lkp = l3fwd_lpm_lkp;
}

static int
check_lcore_params(void)
{
    uint8_t queue, lcore;
    uint16_t i;
    int socketid;

    for (i = 0; i < nb_lcore_params; ++i) {
        queue = lcore_params[i].queue_id;
        if (queue >= MAX_RX_QUEUE_PER_PORT) {
            printf("invalid queue number: %hhu\n", queue);
            return -1;
        }
        lcore = lcore_params[i].lcore_id;
        if (!rte_lcore_is_enabled(lcore)) {
            printf("error: lcore %hhu is not enabled in lcore mask\n", lcore);
            return -1;
        }
        if ((socketid = rte_lcore_to_socket_id(lcore) != 0) &&
            (numa_on == 0)) {
            printf("warning: lcore %hhu is on socket %d with numa off \n",
                   lcore, socketid);
        }
    }
    return 0;
}

static int
check_port_config(const unsigned nb_ports)
{
    uint16_t portid;
    uint16_t i;

    for (i = 0; i < nb_lcore_params; ++i) {
        portid = lcore_params[i].port_id;
        if ((enabled_port_mask & (1 << portid)) == 0) {
            printf("port %u is not enabled in port mask\n", portid);
            return -1;
        }
        if (portid >= nb_ports) {
            printf("port %u is not present on the board\n", portid);
            return -1;
        }
    }
    return 0;
}

static uint8_t
get_port_n_rx_queues(const uint16_t port)
{
    int queue = -1;
    uint16_t i;

    for (i = 0; i < nb_lcore_params; ++i) {
        if (lcore_params[i].port_id == port) {
            if (lcore_params[i].queue_id == queue+1)
                queue = lcore_params[i].queue_id;
            else
                rte_exit(EXIT_FAILURE, "queue ids of the port %d must be"
                                       " in sequence and must start with 0\n",
                         lcore_params[i].port_id);
        }
    }
    return (uint8_t)(++queue);
}

static int
init_lcore_rx_queues(void)
{
    uint16_t i, nb_rx_queue;
    uint8_t lcore;

    for (i = 0; i < nb_lcore_params; ++i) {
        lcore = lcore_params[i].lcore_id;
        nb_rx_queue = lcore_conf[lcore].n_rx_queue;
        if (nb_rx_queue >= MAX_RX_QUEUE_PER_LCORE) {
            printf("error: too many queues (%u) for lcore: %u\n",
                   (unsigned)nb_rx_queue + 1, (unsigned)lcore);
            return -1;
        } else {
            lcore_conf[lcore].rx_queue_list[nb_rx_queue].port_id =
                    lcore_params[i].port_id;
            lcore_conf[lcore].rx_queue_list[nb_rx_queue].queue_id =
                    lcore_params[i].queue_id;
            lcore_conf[lcore].n_rx_queue++;
        }
    }
    return 0;
}

static int parse_max_pkt_len(const char *pktlen)
{
    char *end = NULL;
    unsigned long len;

    /* parse decimal string */
    len = strtoul(pktlen, &end, 10);
    if ((pktlen[0] == '\0') || (end == NULL) || (*end != '\0'))
        return -1;

    if (len == 0)
        return -1;

    return len;
}

static int
parse_portmask(const char *portmask)
{
    char *end = NULL;
    unsigned long pm;

    /* parse hexadecimal string */
    pm = strtoul(portmask, &end, 16);
    if ((portmask[0] == '\0') || (end == NULL) || (*end != '\0'))
        return -1;

    if (pm == 0)
        return -1;

    return pm;
}

static int
parse_hash_entry_number(const char *hash_entry_num)
{
    char *end = NULL;
    unsigned long hash_en;
    /* parse hexadecimal string */
    hash_en = strtoul(hash_entry_num, &end, 16);
    if ((hash_entry_num[0] == '\0') || (end == NULL) || (*end != '\0'))
        return -1;

    if (hash_en == 0)
        return -1;

    return hash_en;
}

static int
parse_config(const char *q_arg)
{
    char s[256];
    const char *p, *p0 = q_arg;
    char *end;
    enum fieldnames {
        FLD_PORT = 0,
        FLD_QUEUE,
        FLD_LCORE,
        _NUM_FLD
    };
    unsigned long int_fld[_NUM_FLD];
    char *str_fld[_NUM_FLD];
    int i;
    unsigned size;

    nb_lcore_params = 0;

    while ((p = strchr(p0,'(')) != NULL) {
        ++p;
        if((p0 = strchr(p,')')) == NULL)
            return -1;

        size = p0 - p;
        if(size >= sizeof(s))
            return -1;

        snprintf(s, sizeof(s), "%.*s", size, p);
        if (rte_strsplit(s, sizeof(s), str_fld, _NUM_FLD, ',') != _NUM_FLD)
            return -1;
        for (i = 0; i < _NUM_FLD; i++){
            errno = 0;
            int_fld[i] = strtoul(str_fld[i], &end, 0);
            if (errno != 0 || end == str_fld[i] || int_fld[i] > 255)
                return -1;
        }
        if (nb_lcore_params >= MAX_LCORE_PARAMS) {
            printf("exceeded max number of lcore params: %hu\n",
                   nb_lcore_params);
            return -1;
        }
        lcore_params_array[nb_lcore_params].port_id =
                (uint8_t)int_fld[FLD_PORT];
        lcore_params_array[nb_lcore_params].queue_id =
                (uint8_t)int_fld[FLD_QUEUE];
        lcore_params_array[nb_lcore_params].lcore_id =
                (uint8_t)int_fld[FLD_LCORE];
        ++nb_lcore_params;
    }
    lcore_params = lcore_params_array;
    return 0;
}

static void
parse_eth_dest(const char *optarg)
{
    uint16_t portid;
    char *port_end;
    uint8_t c, *dest, peer_addr[6];

    errno = 0;
    portid = strtoul(optarg, &port_end, 10);
    if (errno != 0 || port_end == optarg || *port_end++ != ',')
        rte_exit(EXIT_FAILURE,
                 "Invalid eth-dest: %s", optarg);
    if (portid >= RTE_MAX_ETHPORTS)
        rte_exit(EXIT_FAILURE,
                 "eth-dest: port %d >= RTE_MAX_ETHPORTS(%d)\n",
                 portid, RTE_MAX_ETHPORTS);

    if (cmdline_parse_etheraddr(NULL, port_end,
                                &peer_addr, sizeof(peer_addr)) < 0)
        rte_exit(EXIT_FAILURE,
                 "Invalid ethernet address: %s\n",
                 port_end);
    dest = (uint8_t *)&dest_eth_addr[portid];
    for (c = 0; c < 6; c++)
        dest[c] = peer_addr[c];
    *(uint64_t *)(val_eth + portid) = dest_eth_addr[portid];
}

#define MAX_JUMBO_PKT_LEN  9600
#define MEMPOOL_CACHE_SIZE 256

static const char short_options[] =
        "p:"  /* portmask */
        "P"   /* promiscuous */
        "L"   /* enable long prefix match */
        "E"   /* enable exact match */
;

#define CMD_LINE_OPT_CONFIG "config"
#define CMD_LINE_OPT_ETH_DEST "eth-dest"
#define CMD_LINE_OPT_NO_NUMA "no-numa"
#define CMD_LINE_OPT_IPV6 "ipv6"
#define CMD_LINE_OPT_ENABLE_JUMBO "enable-jumbo"
#define CMD_LINE_OPT_HASH_ENTRY_NUM "hash-entry-num"
#define CMD_LINE_OPT_PARSE_PTYPE "parse-ptype"
enum {
    /* long options mapped to a short option */

    /* first long only option value must be >= 256, so that we won't
     * conflict with short options */
            CMD_LINE_OPT_MIN_NUM = 256,
    CMD_LINE_OPT_CONFIG_NUM,
    CMD_LINE_OPT_ETH_DEST_NUM,
    CMD_LINE_OPT_NO_NUMA_NUM,
    CMD_LINE_OPT_IPV6_NUM,
    CMD_LINE_OPT_ENABLE_JUMBO_NUM,
    CMD_LINE_OPT_HASH_ENTRY_NUM_NUM,
    CMD_LINE_OPT_PARSE_PTYPE_NUM,
};

static const struct option lgopts[] = {
        {CMD_LINE_OPT_CONFIG, 1, 0, CMD_LINE_OPT_CONFIG_NUM},
        {CMD_LINE_OPT_ETH_DEST, 1, 0, CMD_LINE_OPT_ETH_DEST_NUM},
        {CMD_LINE_OPT_NO_NUMA, 0, 0, CMD_LINE_OPT_NO_NUMA_NUM},
        {CMD_LINE_OPT_IPV6, 0, 0, CMD_LINE_OPT_IPV6_NUM},
        {CMD_LINE_OPT_ENABLE_JUMBO, 0, 0, CMD_LINE_OPT_ENABLE_JUMBO_NUM},
        {CMD_LINE_OPT_HASH_ENTRY_NUM, 1, 0, CMD_LINE_OPT_HASH_ENTRY_NUM_NUM},
        {CMD_LINE_OPT_PARSE_PTYPE, 0, 0, CMD_LINE_OPT_PARSE_PTYPE_NUM},
        {NULL, 0, 0, 0}
};

/*
 * This expression is used to calculate the number of mbufs needed
 * depending on user input, taking  into account memory for rx and
 * tx hardware rings, cache per lcore and mtable per port per lcore.
 * RTE_MAX is used to ensure that NB_MBUF never goes below a minimum
 * value of 8192
 */
#define NB_MBUF RTE_MAX(	\
	(nb_ports*nb_rx_queue*nb_rxd +		\
	nb_ports*nb_lcores*MAX_PKT_BURST +	\
	nb_ports*n_tx_queue*nb_txd +		\
	nb_lcores*MEMPOOL_CACHE_SIZE),		\
	(unsigned)8192)

/* Parse the argument given in the command line of the application */
static int
parse_args(int argc, char **argv)
{
    int opt, ret;
    char **argvopt;
    int option_index;
    char *prgname = argv[0];

    argvopt = argv;

    /* Error or normal output strings. */
    const char *str1 = "L3FWD: Invalid portmask";
    const char *str2 = "L3FWD: Promiscuous mode selected";
    const char *str3 = "L3FWD: Exact match selected";
    const char *str4 = "L3FWD: Longest-prefix match selected";
    const char *str5 = "L3FWD: Invalid config";
    const char *str6 = "L3FWD: NUMA is disabled";
    const char *str7 = "L3FWD: IPV6 is specified";
    const char *str8 =
            "L3FWD: Jumbo frame is enabled - disabling simple TX path";
    const char *str9 = "L3FWD: Invalid packet length";
    const char *str10 = "L3FWD: Set jumbo frame max packet len to ";
    const char *str11 = "L3FWD: Invalid hash entry number";
    const char *str12 =
            "L3FWD: LPM and EM are mutually exclusive, select only one";
    const char *str13 = "L3FWD: LPM or EM none selected, default LPM on";

    while ((opt = getopt_long(argc, argvopt, short_options,
                              lgopts, &option_index)) != EOF) {

        switch (opt) {
            /* portmask */
            case 'p':
                enabled_port_mask = parse_portmask(optarg);
                if (enabled_port_mask == 0) {
                    printf("%s\n", str1);
                    return -1;
                }
                break;

            case 'P':
                printf("%s\n", str2);
                promiscuous_on = 1;
                break;

            case 'E':
                printf("%s\n", str3);
                l3fwd_em_on = 1;
                break;

            case 'L':
                printf("%s\n", str4);
                l3fwd_lpm_on = 1;
                break;

                /* long options */
            case CMD_LINE_OPT_CONFIG_NUM:
                ret = parse_config(optarg);
                if (ret) {
                    printf("%s\n", str5);
                    return -1;
                }
                break;

            case CMD_LINE_OPT_ETH_DEST_NUM:
                parse_eth_dest(optarg);
                break;

            case CMD_LINE_OPT_NO_NUMA_NUM:
                printf("%s\n", str6);
                numa_on = 0;
                break;

            case CMD_LINE_OPT_IPV6_NUM:
                printf("%sn", str7);
                ipv6 = 1;
                break;

            case CMD_LINE_OPT_ENABLE_JUMBO_NUM: {
                struct option lenopts = {
                        "max-pkt-len", required_argument, 0, 0
                };

                printf("%s\n", str8);
                port_conf.rxmode.jumbo_frame = 1;

                /*
                 * if no max-pkt-len set, use the default
                 * value ETHER_MAX_LEN.
                 */
                if (getopt_long(argc, argvopt, "",
                                &lenopts, &option_index) == 0) {
                    ret = parse_max_pkt_len(optarg);
                    if ((ret < 64) ||
                        (ret > MAX_JUMBO_PKT_LEN)) {
                        printf("%s\n", str9);
                        return -1;
                    }
                    port_conf.rxmode.max_rx_pkt_len = ret;
                }
                printf("%s %u\n", str10,
                       (unsigned int)port_conf.rxmode.max_rx_pkt_len);
                break;
            }

            case CMD_LINE_OPT_HASH_ENTRY_NUM_NUM:
                ret = parse_hash_entry_number(optarg);
                if ((ret > 0) && (ret <= L3FWD_HASH_ENTRIES)) {
                    hash_entry_number = ret;
                } else {
                    printf("%s\n", str11);
                    return -1;
                }
                break;

            case CMD_LINE_OPT_PARSE_PTYPE_NUM:
                printf("soft parse-ptype is enabled\n");
                parse_ptype = 1;
                break;

            default:
                return -1;
        }
    }

    /* If both LPM and EM are selected, return error. */
    if (l3fwd_lpm_on && l3fwd_em_on) {
        printf("%s\n", str12);
        return -1;
    }

    /*
     * Nothing is selected, pick longest-prefix match
     * as default match.
     */
    if (!l3fwd_lpm_on && !l3fwd_em_on) {
        l3fwd_lpm_on = 1;
        printf("%s\n", str13);
    }

    /*
     * ipv6 and hash flags are valid only for
     * exact macth, reset them to default for
     * longest-prefix match.
     */
    if (l3fwd_lpm_on) {
        ipv6 = 0;
        hash_entry_number = HASH_ENTRY_NUMBER_DEFAULT;
    }

    if (optind >= 0)
        argv[optind-1] = prgname;

    ret = optind-1;
    optind = 1; /* reset getopt lib */
    return ret;
}

static void
print_ethaddr(const char *name, const struct ether_addr *eth_addr)
{
    char buf[ETHER_ADDR_FMT_SIZE];
    ether_format_addr(buf, ETHER_ADDR_FMT_SIZE, eth_addr);
    printf("%s%s", name, buf);
}

static int
init_mem(unsigned nb_mbuf)
{
    struct lcore_conf *qconf;
    int socketid;
    unsigned lcore_id;
    char s[64];

    for (lcore_id = 0; lcore_id < RTE_MAX_LCORE; lcore_id++) {
        if (rte_lcore_is_enabled(lcore_id) == 0)
            continue;

        if (numa_on)
            socketid = rte_lcore_to_socket_id(lcore_id);
        else
            socketid = 0;

        if (socketid >= NB_SOCKETS) {
            rte_exit(EXIT_FAILURE,
                     "Socket %d of lcore %u is out of range %d\n",
                     socketid, lcore_id, NB_SOCKETS);
        }

        qconf = &lcore_conf[lcore_id];
    }
    return 0;
}

/* Check the link status of all ports in up to 9s, and print them finally */
static void
check_all_ports_link_status(uint16_t port_num, uint32_t port_mask)
{
#define CHECK_INTERVAL 100 /* 100ms */
#define MAX_CHECK_TIME 90 /* 9s (90 * 100ms) in total */
    uint16_t portid;
    uint8_t count, all_ports_up, print_flag = 0;
    struct rte_eth_link link;

    printf("\nChecking link status");
    fflush(stdout);
    for (count = 0; count <= MAX_CHECK_TIME; count++) {
        if (force_quit)
            return;
        all_ports_up = 1;
        for (portid = 0; portid < port_num; portid++) {
            if (force_quit)
                return;
            if ((port_mask & (1 << portid)) == 0)
                continue;
            memset(&link, 0, sizeof(link));
            rte_eth_link_get_nowait(portid, &link);
            /* print link status if flag set */
            if (print_flag == 1) {
                if (link.link_status)
                    printf(
                            "Port%d Link Up. Speed %u Mbps -%s\n",
                            portid, link.link_speed,
                            (link.link_duplex == ETH_LINK_FULL_DUPLEX) ?
                            ("full-duplex") : ("half-duplex\n"));
                else
                    printf("Port %d Link Down\n", portid);
                continue;
            }
            /* clear all_ports_up flag if any link down */
            if (link.link_status == ETH_LINK_DOWN) {
                all_ports_up = 0;
                break;
            }
        }
        /* after finally printing all link status, get out */
        if (print_flag == 1)
            break;

        if (all_ports_up == 0) {
            printf(".");
            fflush(stdout);
            rte_delay_ms(CHECK_INTERVAL);
        }

        /* set the print_flag if all ports up or timeout */
        if (all_ports_up == 1 || count == (MAX_CHECK_TIME - 1)) {
            print_flag = 1;
            printf("done\n");
        }
    }
}

static void
signal_handler(int signum)
{
    if (signum == SIGINT || signum == SIGTERM) {
        printf("\n\nSignal %d received, preparing to exit...\n",
               signum);
        force_quit = true;
    }
}

static int
prepare_ptype_parser(uint16_t portid, uint16_t queueid)
{
    if (parse_ptype) {
        printf("Port %d: softly parse packet type info\n", portid);
        if (rte_eth_add_rx_callback(portid, queueid,
                                    l3fwd_lkp.cb_parse_ptype,
                                    NULL))
            return 1;

        printf("Failed to add rx callback: port=%d\n", portid);
        return 0;
    }

    if (l3fwd_lkp.check_ptype(portid))
        return 1;

    printf("port %d cannot parse packet type, please add --%s\n",
           portid, CMD_LINE_OPT_PARSE_PTYPE);
    return 0;
}