### Pingpong
- run the server from dkasu
- run the client from wenji-wrk

<br>

### running command
```
./build/l2fwd -l 0 -- -q 8 -p 0x2 -T 1
sudo ./dpdk-pdump -- --pdump 'port=1,queue=*,tx-dev=/tmp/dpdk_tx0.pcap,rx-dev=/tmp/dpdk_rx0.pcap'
tcpdump -ttttt -qns 0 -A -r /tmp/dpdk_tx0.pcap >> chara_output

./build/l2fwd -l 0 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x2 -T 1
./build/l2fwd -l 0 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x2 -T 1

sudo tshark -n -i eno1 -T fields -e frame.time_relative -e ip.src -Y "ip.src == 10.218.111.252 || ip.dst == 10.218.111.252" -e data.data
```

<br>

### capture packets from dpdk pdump
```
#1
add the pdump initialization code in dpdk.cc

#2
update build.ninja -> add lrte_pdump

#
update build/release/seastar.pc
```


### capture packets from tcp
```

```
