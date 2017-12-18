static int test_pktmbuf_with_non_ascii_data(void){
  struct rte_mbuf *m = NULL;
	char *data;
  m = rte_pktmbuf_alloc(pktmbuf_pool); // allocate rte_mbuf in memory pool
  data = rte_pktmbuf_append(m, MBUF_TEST_DATA_LEN); // alllocate data offset in the packet
  memset(data, 0xff, rte_pktmbuf_pkt_len(m)); // update the data offset
  rte_pktmbuf_free(m);
}


static int test_one_pktmbuf(void){

  struct rte_mbuf *m = NULL;
	char *data, *data2, *hdr;
	unsigned i;

  m = rte_pktmbuf_alloc(pktmbuf_pool);

  rte_pktmbuf_dump(stdout, m, 0);
  // dump mbuf at 0x7f9a7fe0c700, phys=3ffe0c780, buf_len=2048
  // pkt_len=0, ol_flags=0, nb_segs=1, in_port=255
  // segment at 0x7f9a7fe0c700, data=0x7f9a7fe0c800, data_len=0


  data = rte_pktmbuf_append(m, MBUF_TEST_DATA_LEN);
  memset(data, '*', rte_pktmbuf_pkt_len(m));

  printf("\nappend MBUF_TEST_DATA_LEN: %ld\n", strlen(data));
  // append MBUF_TEST_DATA_LEN: 1464


  rte_pktmbuf_dump(stdout, m, MBUF_TEST_DATA_LEN);
  // dump mbuf at 0x7f9a7fe0c700, phys=3ffe0c780, buf_len=2048
  // pkt_len=1464, ol_flags=0, nb_segs=1, in_port=255
  // segment at 0x7f9a7fe0c700, data=0x7f9a7fe0c800, data_len=1464
  // Dump data at [0x7f9a7fe0c800], len=1464

  // ol_flags = PKT_TX_IPV4 | PKT_TX_IP_CSUM | PKT_TX_UDP_CKSUM -> supported by hardware
  // nb_segs = number of connected packets
  // in_port = from which port
  // segment at = beginning location
  // data = data offset location
  // buf_len = total packet length
  // data_len = data offset length


  data2 = rte_pktmbuf_append(m, MBUF_TEST_DATA_LEN2);
  memset(data2, '*', MBUF_TEST_DATA_LEN2);
  printf("append MBUF_TEST_DATA_LEN2: %ld\n", strlen(data2));
  // append MBUF_TEST_DATA_LEN2: 50


  // trim the end file
  rte_pktmbuf_trim(m, MBUF_TEST_DATA_LEN2);
  printf("trim the end file: %ld\n", strlen(data2));
  // trim the end file: 50


  // add header
  hdr = rte_pktmbuf_prepend(m, MBUF_TEST_HDR1_LEN);
  memset(hdr, '*', MBUF_TEST_HDR1_LEN);
  printf("prepend header: %ld\n", strlen(hdr));
  // prepend header: 1534


  hdr = rte_pktmbuf_prepend(m, MBUF_TEST_HDR2_LEN);
  memset(hdr, '*', MBUF_TEST_HDR2_LEN);
  printf("prepend header: %ld\n", strlen(hdr));
  // prepend header: 1564


  printf("trying to prepend data length %ld\n", (uint16_t)(rte_pktmbuf_headroom(m) + 1);
  if (hdr != NULL)
		GOTO_FAIL("prepend should not succeed");


  rte_pktmbuf_adj(m, MBUF_TEST_ALL_HDRS_LEN);
  printf("rte_pktmbuf_adj header: %ld\n", strlen(hdr));

  

  rte_pktmbuf_free(m);
  return 0;

}
