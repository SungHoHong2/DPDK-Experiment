### Pingpong

- run the server from dkasu
- run the client from wenji-wrk

<br>

### running command
```
./build/l2fwd -l 0 -- -q 8 -p 0x2 -T 1
sudo ./dpdk-pdump -- --pdump 'port=1,queue=*,tx-dev=/tmp/chara2.pcap'
tcpdump -ttttt -qns 0 -A -r /tmp/chara2.pcap >> chara_output
tcpdump -ttttt -qns 0 -A -r /tmp/chara0.pcap >> chara_output



./build/l2fwd -l 0 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x2 -T 1
./build/l2fwd -l 0 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x2 -T 1



```
