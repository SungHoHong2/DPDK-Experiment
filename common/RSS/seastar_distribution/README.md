```
sudo ./configure.py --enable-dpdk --compiler g++-5
sudo ninja

sudo ./server --dpdk-pmd --dpdk-port-index 1 --network-stack native --dhcp 0 --host-ipv4-addr 10.107.30.40 --netmask-ipv4-addr 255.255.254.0 --gw-ipv4-addr 10.107.30.1 --collectd 0 --smp 2


sudo ./server --dpdk-pmd --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.253 --netmask-ipv4-addr 255.255.248.0 --gw-ipv4-addr 10.218.111.1 --collectd 0 --smp 2


./wrk -t2 -c2 -d1s http://10.107.30.40:10000
```


```c
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
        _rss_table_bits = std::lround(std::log2(_dev_info.max_rx_queues));
    }
```

> CHARA: _rss_table_bits: 16  _dev_info.max_rx_queues: 65408

```c
future<> interface::dispatch_packet(packet p) {
    auto eh = p.get_header<eth_hdr>(); // get the header
    if (eh) {
        auto i = _proto_map.find(ntoh(eh->eth_proto)) ;
        if (i != _proto_map.end()) { // two
            l3_rx_stream& l3 = i->second;
            auto fw = _dev->forward_dst(engine().cpu_id(), [&p, &l3, this] () {
                auto hwrss = p.rss_hash();
                if (hwrss) {
                    return hwrss.value();
                } else {
                    forward_hash data;
                    if (l3.forward(data, p, sizeof(eth_hdr))) {
                        return toeplitz_hash(rss_key(), data);
                    }
                    return 0u;
                }
            });
            if (fw != engine().cpu_id()) {
                forward(fw, std::move(p));

```
> The part that only runs when using Mellanox

```c
            } else {  // when using mellanox it only goes to this part
                auto h = ntoh(*eh);
                auto from = h.src_mac;
                p.trim_front(sizeof(*eh));
                // avoid chaining, since queue lenth is unlimited
                // drop instead.
                if (l3.ready.available()) {
                    l3.ready = l3.packet_stream.produce(std::move(p), from); // packet send
                }
            }
        }
    }
    return make_ready_future<>();
}
```
