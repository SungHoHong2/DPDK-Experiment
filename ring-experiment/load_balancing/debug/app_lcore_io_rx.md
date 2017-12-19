### app_lcore_io_rx

```c

static inline void
app_lcore_io_rx(
	struct app_lcore_params_io *lp,
	uint32_t n_workers,
	uint32_t bsz_rd,
	uint32_t bsz_wr,
	uint8_t pos_lb)
{
    struct rte_mbuf * mbuf_1_0, * mbuf_1_1, * mbuf_2_0, * mbuf_2_1;
    uint8_t * data_1_0, * data_1_1 = NULL;
    uint32_t i;

    for (i = 0; i < lp->rx.n_nic_queues; i ++) {
          uint8_t port = lp->rx.nic_queues[i].port;
      		uint8_t queue = lp->rx.nic_queues[i].queue;
      		uint32_t n_mbufs, j;

          n_mbufs = rte_eth_rx_burst(
                        port,
                        queue,
                        lp->rx.mbuf_in.array,
                        (uint16_t) bsz_rd);

          for (j = 0; j + 3 < n_mbufs; j += 2) {
                    app_lcore_io_rx_buffer_to_send(lp, worker_0, mbuf_0_0, bsz_wr);
      			        app_lcore_io_rx_buffer_to_send(lp, worker_1, mbuf_0_1, bsz_wr);
          }  
    }
}

```

<br>

```c




```
