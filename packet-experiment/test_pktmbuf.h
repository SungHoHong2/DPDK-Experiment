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
  // definitino of dump
  // The act of copying raw data from one place to another with little or no formatting for readability.

  data = rte_pktmbuf_append(m, MBUF_TEST_DATA_LEN);
  memset(data, '*', rte_pktmbuf_pkt_len(m));


  printf("append MBUF_TEST_DATA_LEN: %ld\n", strlen(data));

  rte_pktmbuf_dump(stdout, m, MBUF_TEST_DATA_LEN);
  rte_pktmbuf_dump(stdout, m, 2*MBUF_TEST_DATA_LEN);


  /* this append should fail */
  // data2 = rte_pktmbuf_append(m, (uint16_t)(rte_pktmbuf_tailroom(m) + 1));
  // if (data2 != NULL)
	// 	GOTO_FAIL("Append should not succeed");


  data2 = rte_pktmbuf_append(m, MBUF_TEST_DATA_LEN2);
  memset(data2, '*', MBUF_TEST_DATA_LEN2);
  printf("append MBUF_TEST_DATA_LEN2: %ld\n", strlen(data2));


  // trim the end file
  rte_pktmbuf_trim(m, MBUF_TEST_DATA_LEN2);
  printf("trim the end file: %ld\n", strlen(data2));


  // add header
  hdr = rte_pktmbuf_prepend(m, MBUF_TEST_HDR1_LEN);
  memset(hdr, '*', MBUF_TEST_HDR1_LEN);
  printf("prepend header: %ld\n", strlen(hdr));


  hdr = rte_pktmbuf_prepend(m, MBUF_TEST_HDR2_LEN);
  memset(hdr, '*', MBUF_TEST_HDR2_LEN);
  printf("prepend header: %ld\n", strlen(hdr));


  return 0;

}
