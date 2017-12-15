### Running the file

```
./build/pktcraft -l 0-1 -n 1 -d librte_pmd_e1000.so -d librte_mempool_ring.so -- -q 8 -p 0x1
gdb --args ./build/pktcraft -l 0-1 -n 1 -d librte_pmd_e1000.so -d librte_mempool_ring.so -- -q 8 -p 0x1
```

<br>


### READING PACKETS

```c

// read len data bytes in a mbuf at specified offset (internal)
const void *__rte_pktmbuf_read(const struct rte_mbuf *m, uint32_t off,uint32_t len, void *buf)
{
const struct rte_mbuf *seg = m;
uint32_t buf_off = 0, copy_len;

if (off + len > rte_pktmbuf_pkt_len(m))
		return NULL;

  while (off >= rte_pktmbuf_data_len(seg) &&
			rte_pktmbuf_data_len(seg) != 0) {
		off -= rte_pktmbuf_data_len(seg);
		seg = seg->next;
	}

	if (off + len <= rte_pktmbuf_data_len(seg))
		return rte_pktmbuf_mtod_offset(seg, char *, off);

	/* rare case: header is split among several segments */
	while (len > 0) {
		copy_len = rte_pktmbuf_data_len(seg) - off;
		if (copy_len > len)
			copy_len = len;
		rte_memcpy((char *)buf + buf_off,
			rte_pktmbuf_mtod_offset(seg, char *, off), copy_len);
		off = 0;
		buf_off += copy_len;
		len -= copy_len;
		seg = seg->next;
	}

	return buf;


```
