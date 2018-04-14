### Pingpong
- run the server from dkasu
- run the client from wenji-wrk


<br>

### install dpdk pdump
```
#1
add the pdump initialization code in dpdk.cc

#2
update build.ninja -> add lrte_pdump

#
update build/release/seastar.pc
```

<br>

### capture packets from dpdk pdump
```
./build/l2fwd -l 0 -- -q 8 -p 0x2 -T 1
sudo ./dpdk-pdump -- --pdump 'port=1,queue=*,tx-dev=/tmp/dpdk_tx0.pcap,rx-dev=/tmp/dpdk_rx0.pcap'
tcpdump -ttttt -qns 0 -A -r /tmp/dpdk_tx0.pcap >> /home/sungho/DPDK-Experiment/pktcapture-experiment/dpdk_test/result/sender0_tx
tcpdump -ttttt -qns 0 -A -r /tmp/dpdk_rx0.pcap >> /home/sungho/DPDK-Experiment/pktcapture-experiment/dpdk_test/result/sender0_rx

tcpdump -ttttt -qns 0 -A -r /tmp/dpdk_tx0.pcap >> /home/sungho/DPDK-Experiment/pktcapture-experiment/dpdk_test/result/receiver0_tx
tcpdump -ttttt -qns 0 -A -r /tmp/dpdk_rx0.pcap >> /home/sungho/DPDK-Experiment/pktcapture-experiment/dpdk_test/result/receiver0_rx


tcpdump -ttttt -qns 0 -A -r /tmp/dpdk_rx9.pcap >> receiver_rx

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
