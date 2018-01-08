### app_lcore_main_loop


```c
int
app_lcore_main_loop(__attribute__((unused)) void *arg)
{
     struct app_lcore_params * lp;
	   unsigned lcore;

     lcore = rte_lcore_id();
   	 lp = &app.lcore_params[lcore];

     if (lp->type == e_APP_LCORE_IO) {
          app_lcore_main_loop_io();
     }   

     if (lp->type == e_APP_LCORE_WORKER) {
          app_lcore_main_loop_worker();
     }
}
```

<br>

```c
static void app_lcore_main_loop_io(void){
    uint32_t lcore = rte_lcore_id();
    struct app_lcore_params_io * lp = &app.lcore_params[lcore].io;
    uint32_t n_workers = app_get_lcores_worker();
    uint64_t i = 0;

    uint32_t bsz_rx_rd = app.burst_size_io_rx_read;
  	uint32_t bsz_rx_wr = app.burst_size_io_rx_write;
  	uint32_t bsz_tx_rd = app.burst_size_io_tx_read;
  	uint32_t bsz_tx_wr = app.burst_size_io_tx_write;

    uint8_t pos_lb = app.pos_lb;


    for(; ;){
          if (APP_LCORE_IO_FLUSH && (unlikely(i == APP_LCORE_IO_FLUSH))) {
                app_lcore_io_rx_flush(lp, n_workers);
                app_lcore_io_tx_flush(lp);
          }

          i = 0;

          app_lcore_io_rx(lp, n_workers, bsz_rx_rd, bsz_rx_wr, pos_lb);
```

> [app_lcore_io_rx](app_lcore_io_rx.md)

```c          
          app_lcore_io_tx(lp, n_workers, bsz_tx_rd, bsz_tx_wr);

          i ++;
    }
}

}

```
