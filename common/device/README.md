### Device configuration


```c
// Another workaround: this time for a lack of number of RSS bits.
// ixgbe PF NICs support up to 16 RSS queues.
// ixgbe VF NICs support up to 4 RSS queues.
// i40e PF NICs support up to 64 RSS queues.
// i40e VF NICs support up to 16 RSS queues.

// default_ring_size


// get the number of queues
rte_eth_dev_info_get(_port_idx, &_dev_info);
_num_queues = std::min({_num_queues, _dev_info.max_rx_queues, _dev_info.max_tx_queues});

// device configuration
rte_eth_dev_configure(_port_idx, _num_queues, _num_queues, &port_conf);

rte_eth_rx_queue_setup(_dev_port_idx, _qid, default_ring_size,
                           rte_eth_dev_socket_id(_dev_port_idx),
                           _dev->def_rx_conf(), _pktmbuf_pool_rx);
rte_eth_tx_queue_setup(dev->port_idx(), qid, default_ring_size,
                          rte_eth_dev_socket_id(dev->port_idx()),
                          dev->def_tx_conf());
```

<br>

### ring size

```c
static constexpr uint16_t default_ring_size      = 512;
static constexpr uint16_t mbufs_per_queue_rx     = 2 * default_ring_size;
static constexpr uint16_t mbufs_per_queue_tx     = 2 * default_ring_size;
```
