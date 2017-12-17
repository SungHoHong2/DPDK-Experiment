### Pingpong

- run the server from dkasu
- run the client from wenji-wrk

<br>

### running command
```
./build/l2fwd -l 0 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x1 -T 1
```

<br>

### Comparing the throughput with the TCP pingpong
- only comparing the offset of the data
- it is proven that `strlen()` only counts the length of the ASCII char `*` and not the allocated memory

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
memset(data, '*', rte_pktmbuf_pkt_len(m)); // deciding the length of the offset
printf("rte_pktmbuf_pkt_len(m): %d\n", rte_pktmbuf_pkt_len(m)); // count the packet length


// counting the offset of the packet
char *rtn;
rtn = rte_pktmbuf_mtod_offset(m, char *, sizeof(data));
printf("length of the offset: %ld\n", strlen(rtn));


/*
 *  case of TCP
 */

 // sending the packet
 char send_data[100]; // even though the char array is fixed the strlen will only count the valid values
 memset( send_data, '*', PKT_SIZE * sizeof(char));


 // receiving the packet
 success=send(sockfd, send_data, PKT_SIZE, 0);
```


<br>


### Example

```c
char *data; // packet length 1464
memset(data, '*', rte_pktmbuf_pkt_len(m)-1000);
printf("rte_pktmbuf_pkt_len(m): %d\n", rte_pktmbuf_pkt_len(m)); // rte_pktmbuf_pkt_len(m): 1464

char *rtn;
rtn = rte_pktmbuf_mtod_offset(m, char *, sizeof(data));
printf("lenght of the offset: %ld\n", strlen(rtn));  // lenght of the offset: 456

char send_data[100];
printf("length of TCP offset %ld\n", strlen(send_data));
memset( send_data, '*', (50) * sizeof(char)); // decide the offset data
printf("length of TCP offset %ld\n", strlen(send_data));

// rte_pktmbuf_pkt_len(m): 1464
// lenght of the offset: 456   
// length of TCP offset 0      
// length of TCP offset 50     

```
