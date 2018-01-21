### problem for finding why multi cores is not working

```
    if (_num_queues > 1) {
        if (_dev_info.reta_size) {
            // RETA size should be a power of 2
            assert((_dev_info.reta_size & (_dev_info.reta_size - 1)) == 0);

            // Set the RSS table to the correct size
            _redir_table.resize(_dev_info.reta_size);
            _rss_table_bits = std::lround(std::log2(_dev_info.reta_size));
            printf("Port %d: RSS table size is %d\n",
                   _port_idx, _dev_info.reta_size);
        } else {

            // this part is initiated
            _rss_table_bits = std::lround(std::log2(_dev_info.max_rx_queues));
        }
```

<br>


```
static void
set_rss_table(uint8_t port_id, uint16_t reta_size, uint16_t nb_queues)
{
    if (reta_size == 0) {
        return;
    }

    int reta_conf_size = RTE_MAX(1, reta_size / RTE_RETA_GROUP_SIZE);
    struct rte_eth_rss_reta_entry64 reta_conf[reta_conf_size];

    /* config HW indirection table */
    unsigned i, j, hash=0;
    for (i = 0; i < reta_conf_size; i++) {
        reta_conf[i].mask = ~0ULL;
        for (j = 0; j < RTE_RETA_GROUP_SIZE; j++) {
            reta_conf[i].reta[j] = hash++ % nb_queues;
        }
    }

    if (rte_eth_dev_rss_reta_update(port_id, reta_conf, reta_size)) {
        rte_exit(EXIT_FAILURE, "port[%d], failed to update rss table\n",
                 port_id);
    }

    printf("CHARA: set rss table done successfully and it is not zero\n");
}
```

> it is one hundred percent confirmed that this part has the problem

```
// visasu
CHARA: set_rss_table: 128, 2, 64

// wrk
CHARA: set_rss_table: 128, 2, 64


```
