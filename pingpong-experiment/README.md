### Pingpong

- run the server from dkasu
- run the client from wenji-wrk

<br>

### running command
```
./build/l2fwd -l 0 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x1 -T 1
```

<br>


### modifying the size of packets

```c

int sent;
char *data;
rm[0] = rte_pktmbuf_alloc(test_pktmbuf_pool);

data = rte_pktmbuf_append(rm[0], 1464); //append length bytes to an buff
memset(data, 0xff, rte_pktmbuf_pkt_len(rm[0])); //update the value of data
sent = rte_eth_tx_burst(portid, 0, rm, 1); // returns the number of sent packets

if (sent){
  port_statistics[portid].tx += sent; //aggregate the results
}

```
