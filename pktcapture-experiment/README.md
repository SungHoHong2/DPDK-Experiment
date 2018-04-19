### Pingpong
- run the client from dkasu
- run the server from wenji-wrk


### capture packets from dpdk pdump
```
sudo ./build/l2fwd -l 0 -- -q 8 -p 0x2 -T 1
sudo ./dpdk-pdump -- --pdump 'port=1,queue=*,tx-dev=/tmp/dpdk_tx0.pcap,rx-dev=/tmp/dpdk_rx0.pcap'
tcpdump -ttttt -qns 0 -A -r /tmp/dpdk_tx0.pcap >> /home/sungho/DPDK-Experiment/pktcapture-experiment/dpdk_test/result/sender0_tx
tcpdump -ttttt -qns 0 -A -r /tmp/dpdk_rx0.pcap >> /home/sungho/DPDK-Experiment/pktcapture-experiment/dpdk_test/result/sender0_rx

tcpdump -ttttt -qns 0 -A -r /tmp/dpdk_tx0.pcap >> /home/sungho/DPDK-Experiment/pktcapture-experiment/dpdk_test/result/receiver0_tx
tcpdump -ttttt -qns 0 -A -r /tmp/dpdk_rx0.pcap >> /home/sungho/DPDK-Experiment/pktcapture-experiment/dpdk_test/result/receiver0_rx
tcpdump -ttttt -qns 0 -A -r /tmp/dpdk_rx0.pcap >> receiver_rx

```

### capture packets from tcp
```
./server
./client --server <ip address>

sudo tshark -n -i eno1 -T fields -e frame.time_relative -e ip.src -Y "ip.src == 10.218.111.252 || ip.src == 10.218.104.170" -e data.data >> receiver_tcp

sudo tshark -n -i enp0s31f6 -T fields -e frame.time_relative -e ip.src -Y "ip.src == 10.218.104.170 || ip.src == 10.218.111.252" -e data.data >> sender_tcp

cp sender_tcp /home/sungho/DPDK-Experiment/pktcapture-experiment/sender_tcp
cp receiver_tcp /home/sungho/DPDK-Experiment/pktcapture-experiment/receiver_tcp
```



### server

```
sudo ./build/l2fwd -l 0 -- -q 8 -p 0x2 -T 1
sudo ./server -- --pdump 'port=1,queue=*,tx-dev=/tmp/dpdk_tx0.pcap,rx-dev=/tmp/dpdk_rx0.pcap'


sudo ./dpdk-pdump -- --pdump 'port=1,queue=*,tx-dev=/tmp/dpdk_tx0.pcap,rx-dev=/tmp/dpdk_rx0.pcap'


erver -- --pdump 'port=1,queue=*,tx-dev=/tmp/dpdk_tx0.pcap,rx-dev=/tmp/dpdk_rx[3/1

EAL: Detected 32 lcore(s)                                                         
EAL: Probing VFIO support...                                                      
EAL: WARNING: Address Space Layout Randomization (ASLR) is enabled in the kernel.
EAL:    This may cause issues with mapping memory into secondary processes        
EAL: PCI device 0000:04:00.0 on NUMA socket 0                                     
EAL:   probe driver: 8086:1521 net_e1000_igb                                      
EAL: PCI device 0000:04:00.1 on NUMA socket 0                                     
EAL:   probe driver: 8086:1521 net_e1000_igb                                      
EAL: PCI device 0000:81:00.0 on NUMA socket 1                                     
EAL:   probe driver: 15b3:1003 net_mlx4    
PMD: net_mlx4: PCI information matches, using device "mlx4_0" (VF: false)         
PMD: net_mlx4: 2 port(s) detected          
PMD: net_mlx4: port 1 MAC address is e4:1d:2d:d9:bf:b0                            
PMD: net_mlx4: no private data for port 0  
EAL: Requested device 0000:81:00.0 cannot be used                                 
PMD: Initializing pmd_pcap for net_pcap_rx_0                                      
PMD: Creating pcap-backed ethdev on numa socket 4294967295                        
Port 0 MAC: 00 00 00 01 02 03              
PMD: Initializing pmd_pcap for net_pcap_tx_0                                      
PMD: Creating pcap-backed ethdev on numa socket 4294967295                        
Port 1 MAC: 00 00 00 01 02 03              
```
