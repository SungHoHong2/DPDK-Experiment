### Running the file

```
./build/pktcraft -l 0-1 -n 1 -d librte_pmd_e1000.so -d librte_mempool_ring.so -- -q 8 -p 0x1
gdb --args ./build/pktcraft -l 0-1 -n 1 -d librte_pmd_e1000.so -d librte_mempool_ring.so -- -q 8 -p 0x1
```

<br>

### Crucial variables

```c
static __inline__ void
_send_burst_fast(port_info_t *info, uint16_t qid)
{
	struct mbuf_table   *mtab = &info->q[qid].tx_mbufs;
	struct rte_mbuf **pkts;
	uint32_t ret, cnt;

	cnt = mtab->len;
	mtab->len = 0;

	pkts    = mtab->m_table;

while (cnt > 0) {
    ret = rte_eth_tx_burst(info->pid, qid, pkts, cnt);
}
```
