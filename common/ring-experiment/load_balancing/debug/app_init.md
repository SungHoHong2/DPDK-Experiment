### app init

```c
void
app_init(void)
{
	app_assign_worker_ids();
	app_init_mbuf_pools();
	app_init_lpm_tables();
	app_init_rings_rx();
	app_init_rings_tx();
	app_init_nics();

	printf("Initialization completed.\n");
}
```

<br>

```c
static void app_init_rings_rx(void){
  unsigned lcore;

  // Initialize the rings for the RX side

  for (lcore = 0; lcore < APP_MAX_LCORES; lcore ++) {

        struct app_lcore_params_io * lp_io = &app.lcore_params[lcore].io;
        unsigned socket_io, lcore_worker;

        if ((app.lcore_params[lcore].type != e_APP_LCORE_IO) ||
        (lp_io->rx.n_nic_queues == 0)) {
          continue;
        }

        socket_io = rte_lcore_to_socket_id(lcore);

        for (lcore_worker = 0; lcore_worker < APP_MAX_LCORES; lcore_worker ++) {
              char name[32];
              struct app_lcore_params_worker * lp_worker = &app.lcore_params[lcore_worker].worker;
              struct rte_ring * ring = NULL;

              if (app.lcore_params[lcore_worker].type != e_APP_LCORE_WORKER) {
                    continue;
              }

              ring = rte_ring_create( name,
                                      app.ring_rx_size, // 1024
                                      socket_io, // rte_lcore_to_socket_id
                                      RING_F_SP_ENQ | RING_F_SC_DEQ);
              lp_io->rx.rings[lp_io->rx.n_rings] = ring;
              lp_io->rx.n_rings ++;
              lp_worker->rings_in[lp_worker->n_rings_in] = ring;
        			lp_worker->n_rings_in ++;
        }
    }
}

```

<br>


```c
static void app_init_rings_tx(void) {
    unsigned lcore;
    // Initialize the rings for the TX side
    for (lcore = 0; lcore < APP_MAX_LCORES; lcore ++) {
          struct app_lcore_params_worker * lp_worker = &app.lcore_params[lcore].worker;
          unsigned port;

          if (app.lcore_params[lcore].type != e_APP_LCORE_WORKER) {
              continue;
          }

          for (port = 0; port < APP_MAX_NIC_PORTS; port ++) {
                char name[32];
                struct app_lcore_params_io * lp_io = NULL;
                struct rte_ring * ring;
                uint32_t socket_io, lcore_io;

                if (app.nic_tx_port_mask[port] == 0) {
          				continue;
          			}

                lp_io = &app.lcore_params[lcore_io].io;
                socket_io = rte_lcore_to_socket_id(lcore_io);
                ring = rte_ring_create(
          				name,
          				app.ring_tx_size, //1024
          				socket_io,
          				RING_F_SP_ENQ | RING_F_SC_DEQ);

                lp_worker->rings_out[port] = ring;
                lp_io->tx.rings[port][lp_worker->worker_id] = ring;
          }
     }
}

```


<br>


```c

static void app_init_nics(void) {
  unsigned socket;
  uint32_t lcore;
  uint8_t port, queue;
  int ret;
  uint32_t n_rx_queues, n_tx_queues;


  // Init NIC ports and queues, then start the ports
  for (port = 0; port < APP_MAX_NIC_PORTS; port ++) {
      struct rte_mempool * pool;
      n_rx_queues = app_get_nic_rx_queues_per_port(port);
      n_tx_queues = app.nic_tx_port_mask[port];

      if ((n_rx_queues == 0) && (n_tx_queues == 0)) {
          continue;
      }

      ret = rte_eth_dev_configure(
              port,
              (uint8_t) n_rx_queues,
              (uint8_t) n_tx_queues,
              &port_conf);

              for (queue = 0; queue < APP_MAX_RX_QUEUES_PER_NIC_PORT; queue ++) {
                    app_get_lcore_for_nic_rx(port, queue, &lcore);
                    socket = rte_lcore_to_socket_id(lcore);
                    pool = app.lcore_params[lcore].pool
                    ret = rte_eth_rx_queue_setup(
                             port,
                             queue,
                             (uint16_t) app.nic_rx_ring_size,
                             socket,
                             NULL,
                             pool);
              }  

              // Init TX queues
              if (app.nic_tx_port_mask[port] == 1) {
                  app_get_lcore_for_nic_tx(port, &lcore);
                  socket = rte_lcore_to_socket_id(lcore);
                  ret = rte_eth_tx_queue_setup(
                              port,
                              0,
                              (uint16_t) app.nic_tx_ring_size,
                              socket,
                              NULL);

              ret = rte_eth_dev_start(port);
    }
}

```
