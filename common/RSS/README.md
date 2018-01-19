### RSS

Receive side scaling (RSS) is a network driver technology that enables the efficient distribution of network receive processing across multiple CPUs in multiprocessor systems


This means a multi process application can use the hardware to distribute and split the traffic between the CPU’s. The use of the indirection table in the process is very use full for implementing dynamic load balancing as the indirection table can be reprogrammed by the driver/application.

sungho@c3n24:~$ lspci | grep Mellanox                                         
81:00.0 Ethernet controller: Mellanox Technologies MT27500 Family [ConnectX-3]

```
static struct rte_eth_conf default_port_conf = {
    .rxmode = {
        .mq_mode = ETH_MQ_RX_RSS,
        .max_rx_pkt_len = ETHER_MAX_LEN,
        .split_hdr_size = 0, /**< hdr buf size */
        .header_split   = 0, /**< Header Split disabled */
        .hw_ip_checksum = 0, /**< IP checksum offload disabled */
        .hw_vlan_filter = 0, /**< VLAN filtering disabled */
        .hw_vlan_strip  = 0, /**< VLAN strip disabled. */
        .hw_vlan_extend = 0, /**< Extended VLAN disabled. */
        .jumbo_frame    = 0, /**< Jumbo Frame Support disabled */
        .hw_strip_crc   = 0, /**< CRC stripped by hardware */
        .enable_lro     = 0, /**< LRO disabled */
    },
    .rx_adv_conf = {
        .rss_conf = {
            .rss_key = default_rsskey_40bytes,
            .rss_key_len = 40,
            .rss_hf = ETH_RSS_PROTO_MASK,
        },
    },
    .txmode = {
        .mq_mode = ETH_MQ_TX_NONE,
    },
};
```
