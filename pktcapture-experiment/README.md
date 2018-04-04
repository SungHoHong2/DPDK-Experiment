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
sudo ./dpdk-pdump -- --pdump 'port=1,queue=*,tx-dev=/tmp/dpdk_tx5.pcap,rx-dev=/tmp/dpdk_rx5.pcap'
tcpdump -ttttt -qns 0 -A -r /tmp/dpdk_tx5.pcap >> chara_send
tcpdump -ttttt -qns 0 -A -r /tmp/dpdk_rx5.pcap >> chara_recv

cp chara_send /home/sungho/DPDK-Experiment/pktcapture-experiment/sender_tx
cp chara_recv /home/sungho/DPDK-Experiment/pktcapture-experiment/sender_rx

cp chara_send /home/sungho/DPDK-Experiment/pktcapture-experiment/receiver_tx
cp chara_recv /home/sungho/DPDK-Experiment/pktcapture-experiment/receiver_rx
```

### capture packets from tcp
```
./server
./client --server <ip address>

sudo tshark -n -i eno1 -T fields -e frame.time_relative -e ip.src -Y "ip.src == 10.218.111.252 || ip.src == 10.218.104.170" -e data.data

sudo tshark -n -i enp0s31f6 -T fields -e frame.time_relative -e ip.src -Y "ip.src == 10.218.104.170 || ip.src == 10.218.111.252" -e data.data
```
