```
# DPDK seastar wenji-wrk
./server --dpdk-pmd --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.253 --netmask-ipv4-addr 255.255.248.0 --gw-ipv4-addr 10.218.111.1 --collectd 0 --smp 2

# DPDK seastar dkasu
wget -qO- http://10.218.111.253:10000 | sed -e 's/<[^>]*>//g'
```
