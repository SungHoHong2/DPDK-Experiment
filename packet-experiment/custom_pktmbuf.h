static int custom_pktmbuf(void){

  struct rte_mbuf *m = NULL;
  char *data;

  m = rte_pktmbuf_alloc(pktmbuf_pool);

  // create packet with size 50
  data = rte_pktmbuf_append(m, 50);
  printf("length: %d\n", rte_pktmbuf_pkt_len(m));


  // increase packet size to 300
  rte_pktmbuf_prepend(m, 200);
  printf("length: %d\n", rte_pktmbuf_pkt_len(m));


  // decrease packet size to 250
  rte_pktmbuf_adj(m, 50);
  printf("length: %d\n", rte_pktmbuf_pkt_len(m));


  // increase packet size to 300
  rte_pktmbuf_append(m, 50);
  printf("length: %d\n", rte_pktmbuf_pkt_len(m));


  return 0;

}
