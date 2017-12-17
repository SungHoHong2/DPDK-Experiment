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

<br>

### Comparing the throughput with the TCP pingpong
- only comparing the offset of the data
```c
// example of counting the char length
char send_data[100];
printf("length of TCP offset %ld\n", strlen(send_data));
memset( send_data, '*', (50) * sizeof(char));
printf("length of TCP offset %ld\n", strlen(send_data));

```


```c

/*
 *  case of DPDK
 */
// creating the packet
char *data;
memset(data, '*', rte_pktmbuf_pkt_len(m));
printf("rte_pktmbuf_pkt_len(m): %d\n", rte_pktmbuf_pkt_len(m)); // count the packet length


// counting the offset of the packet
char *rtn;
rtn = rte_pktmbuf_mtod_offset(m, char *, sizeof(data));
printf("lenght of the offset: %ld\n", strlen(rtn));


/*
 *  case of TCP
 */




```
