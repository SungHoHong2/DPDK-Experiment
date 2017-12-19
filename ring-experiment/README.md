### RING EXPERIMENT

- **load balancing example running code**

```
./build/load_balancer -l 3-7 -n 4 -d librte_pmd_e1000.so -d librte_mempool_ring.so -- --rx "(0,0,3),(1,0,3)" --tx "(0,3),(1,3)" --w "4,5,6,7" --lpm "1.0.0.0/24=>0; 1.0.1.0/24=>1;" --pos-lb 29
```


<br>


- **the files related ring**

```c
#define APP_DEFAULT_NIC_RX_RING_SIZE 1024
#define APP_DEFAULT_NIC_TX_RING_SIZE 1024


struct rte_ring *rings[APP_MAX_NIC_PORTS][APP_MAX_WORKER_LCORES];

struct rte_ring *rings_in[APP_MAX_IO_LCORES];
struct rte_ring *rings_out[APP_MAX_NIC_PORTS];



```
