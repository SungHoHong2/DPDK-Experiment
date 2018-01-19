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

<br>


**chekcing port info with test-pmd**

```
testpmd> show port info 1                  

********************* Infos for port 1  *********************   
MAC address: A0:36:9F:83:AB:BD             
Driver name: net_e1000_igb                 
Connect to socket: 0
memory allocation on the socket: 0         
Link status: up      
Link speed: 100 Mbps
Link duplex: full-duplex                   
MTU: 1500            
Promiscuous mode: enabled                  
Allmulticast mode: disabled                
Maximum number of MAC addresses: 32        
Maximum number of MAC addresses of hash filtering: 0            
VLAN offload:        
  strip on           
  filter on          
  qinq(extend) off   
Hash key size in bytes: 40                 
Redirection table size: 128                
Supported flow types:                      
  ipv4               
  ipv4-tcp           
  ipv4-udp           
  ipv6               
  ipv6-tcp           
  ipv6-udp           
  unknown            
  unknown            
  unknown            
Max possible RX queues: 8                  
Max possible number of RXDs per queue: 4096                     
Min possible number of RXDs per queue: 32  
RXDs number alignment: 8                   
Max possible TX queues: 8                  
Max possible number of TXDs per queue: 4096                     
Min possible number of TXDs per queue: 32  
TXDs number alignment: 8                   
testpmd>             

show port (port_id) rss reta



sudo ./testpmd -c 0xf -n 4 -- -i --portmask=0x03 --nb-cores=3 --rxq=2 --txq=2
testpmd> show port 1 rss-hash ipv4|ipv4-frag|ipv4-tcp|ipv4-udp|ipv4-sctp|ipv4-other|ipv6|ipv6-frag|ipv6-tcp|ipv6-udp|ipv6-sctp|ipv6-other|l2-payload|ipv6-ex|ipv6-tcp-ex|ipv6-udp-ex [key]

```
