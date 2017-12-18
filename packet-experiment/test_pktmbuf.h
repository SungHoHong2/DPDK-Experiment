static int test_pktmbuf_with_non_ascii_data(void){
  struct rte_mbuf *m = NULL;
	char *data;
  m = rte_pktmbuf_alloc(pktmbuf_pool); // allocate rte_mbuf in memory pool
  data = rte_pktmbuf_append(m, MBUF_TEST_DATA_LEN); // alllocate data offset in the packet
  memset(data, 0xff, rte_pktmbuf_pkt_len(m)); // update the data offset
  rte_pktmbuf_free(m);
}
