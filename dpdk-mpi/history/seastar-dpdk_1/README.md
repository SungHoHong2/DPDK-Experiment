```

tcp

./client --server "10.218.111.252:10000"
./server


sudo ./client --dpdk-pmd  --dpdk-port-index 1  --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.253  --server "10.218.111.254:10000" --smp 4

sudo ./server  --dpdk-pmd  --dpdk-port-index 1  --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.254 --smp 4


```
