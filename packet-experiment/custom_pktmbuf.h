static int custom_pktmbuf(void){

  struct rte_mbuf *m = NULL;
  char *data;

  m = rte_pktmbuf_alloc(pktmbuf_pool);

  // create packet with size 50
  data = rte_pktmbuf_append(m, 50);
  printf("length: %d\n", rte_pktmbuf_pkt_len(m));


  // increase packet size to 300
  if(!rte_pktmbuf_prepend(m, 200)){
      printf("prepend failed\n");
  }else{
      printf("length: %d\n", rte_pktmbuf_pkt_len(m));
  }

  // increase packet size to 150
  if(!rte_pktmbuf_prepend(m, 100)){
      printf("prepend failed\n");
  }else{
      printf("length: %d\n", rte_pktmbuf_pkt_len(m));
  }

  // decrease packet size to 100
  if(!rte_pktmbuf_adj(m, 50)){
      printf("adjacent failed\n");
  }else{
      printf("length: %d\n", rte_pktmbuf_pkt_len(m));
  }

  // increase packet size to 150
  if(!rte_pktmbuf_prepend(m, 50)){
      printf("prepend failed\n");
  }else{
      printf("length: %d\n", rte_pktmbuf_pkt_len(m));
  }

  // increase packet size to 500
  if(!rte_pktmbuf_append(m, 350)){
      printf("append failed\n");
  }else{
      printf("length: %d\n", rte_pktmbuf_pkt_len(m));
  }



  // increase packet size to 1000
  if(!rte_pktmbuf_append(m, 500)){
      printf("append failed\n");
  }else{
      printf("length: %d\n", rte_pktmbuf_pkt_len(m));
  }


  // increase packet size to 1500
  if(!rte_pktmbuf_append(m, 500)){
      printf("append failed\n");
  }else{
      printf("length: %d\n", rte_pktmbuf_pkt_len(m));
  }


  // increase packet size to 2000
  if(!rte_pktmbuf_append(m, 500)){
      printf("append failed\n");
  }else{
      printf("length: %d\n", rte_pktmbuf_pkt_len(m));
  }


for(int i =0; i<10; i++){
  // increase packet size to 2010
  if(!rte_pktmbuf_append(m, 10)){
      printf("append failed\n");
  }else{
      printf("length: %d\n", rte_pktmbuf_pkt_len(m));
  }
}


for(int i =0; i<10; i++){
  // increase packet size to 2010
  if(!rte_pktmbuf_append(m, 1)){
      printf("append failed\n");
  }else{
      printf("length: %d\n", rte_pktmbuf_pkt_len(m));
  }
}


for(int i =0; i<29; i++){
  // increase packet size to 2010
  if(!rte_pktmbuf_prepend(m, 1)){
      printf("prepend failed\n");
  }else{
      printf("length: %d\n", rte_pktmbuf_pkt_len(m));
  }
}

  return 0;

}


static int one_packet(){
  struct rte_mbuf *m = NULL;
  m = rte_pktmbuf_alloc(pktmbuf_pool);

  if(!rte_pktmbuf_prepend(m, 2048)){
      printf("prepend failed\n");
  }else{
      printf("length: %d\n", rte_pktmbuf_pkt_len(m));
  }

  if(!rte_pktmbuf_append(m, 2000)){
      printf("append failed\n");
  }else{
      printf("length: %d\n", rte_pktmbuf_pkt_len(m));
  }


  if(!rte_pktmbuf_append(m, 1500)){
      printf("append failed\n");
  }else{
      printf("length: %d\n", rte_pktmbuf_pkt_len(m));
  }

  for(int i =0; i<10; i++){
    if(!rte_pktmbuf_append(m, 100)){
        printf("append failed\n");
    }else{
        printf("length: %d\n", rte_pktmbuf_pkt_len(m));
    }

  }



  return 0;
}
