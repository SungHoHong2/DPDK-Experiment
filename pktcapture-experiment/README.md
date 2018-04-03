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
sudo ./server --dpdk-pmd --dpdk-port-index 1 --network-stack native --dhcp 0 --host-ipv4-addr 10.107.30.40 --netmask-ipv4-addr 255.255.254.0 --gw-ipv4-addr 10.107.30.1 --collectd 0

sudo ./client --dpdk-pmd --dpdk-port-index 1 --network-stack native --dhcp 0 --host-ipv4-addr 10.107.30.41 --netmask-ipv4-addr 255.255.254.0 --gw-ipv4-addr 10.107.30.1 --collectd 0 --server "10.107.30.40:1234"


./build/l2fwd -l 0 -- -q 8 -p 0x2 -T 1
sudo ./dpdk-pdump -- --pdump 'port=1,queue=*,tx-dev=/tmp/dpdk_tx0.pcap,rx-dev=/tmp/dpdk_rx0.pcap'
tcpdump -ttttt -qns 0 -A -r /tmp/dpdk_tx0.pcap >> chara_output
```

### capture packets from tcp
```
sudo tshark -n -i eno1 -T fields -e frame.time_relative -e ip.src -Y "ip.src == 10.218.111.252 || ip.src == 10.218.104.170" -e data.data

sudo tshark -n -i enp0s31f6 -T fields -e frame.time_relative -e ip.src -Y "ip.src == 10.218.104.170 || ip.src == 10.218.111.252" -e data.data

```
