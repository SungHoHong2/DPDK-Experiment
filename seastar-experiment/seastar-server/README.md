### RUNNING SEASTAR

```
# dpdk enabled
sudo ./server --dpdk-pmd --dpdk-port-index 1 --network-stack native --dhcp 0 --host-ipv4-addr 10.107.30.40 --netmask-ipv4-addr 255.255.254.0 --gw-ipv4-addr 10.107.30.1 --collectd 0 --smp 2


# TCP seastar
./tcp_server --smp 2
```

```
for running server c3n25 shipreck
cp seawreck into server
export SEASTAR=/data1/sungho/seastar
g++-5  `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` --whole-archive,-lseastar -lrte_pmd_mlx4 -libverbs server.cc -Wl, -o server

sudo ./server --dpdk-pmd --dpdk-port-index 1 --network-stack native --dhcp 0 --host-ipv4-addr 10.107.30.40 --netmask-ipv4-addr 255.255.254.0 --gw-ipv4-addr 10.107.30.1 --collectd 0 --smp 1

sudo ./server --dpdk-pmd --dpdk-port-index 1 --network-stack native --dhcp 0 --host-ipv4-addr 10.107.30.41 --netmask-ipv4-addr 255.255.254.0 --gw-ipv4-addr 10.107.30.1 --collectd 0 --server "10.107.30.40:10000"

VMA_SPEC=latency LD_PRELOAD=libvma.so numactl --cpunodebind=1 taskset -c 0-2  ./tcp_server --smp 2
```


```
# testing in visasu in dpdk
wget -qO- http://10.107.30.40:10000 | sed -e 's/<[^>]*>//g'

# benchmark
./wrk -t2 -c2 -d10s http://10.107.30.40:10000
./wrk -t4 -c4 -d10s http://10.107.30.40:10000
./wrk -t8 -c8 -d10s http://10.107.30.40:10000
./wrk -t16 -c16 -d10s http://10.107.30.40:10000
./wrk -t32 -c32 -d10s http://10.107.30.40:10000
./wrk -t64 -c64 -d10s http://10.107.30.40:10000

# testing in visasu in tcp
wget -qO- http://10.107.30.33:10000 | sed -e 's/<[^>]*>//g'
./wrk -t2 -c2 -d10s http://10.107.30.33:10000
./wrk -t4 -c4 -d10s http://10.107.30.33:10000
./wrk -t8 -c8 -d10s http://10.107.30.33:10000
./wrk -t16 -c16 -d10s http://10.107.30.33:10000
./wrk -t32 -c32 -d10s http://10.107.30.33:10000
./wrk -t64 -c64 -d10s http://10.107.30.33:10000
```


```
# testing in FIU with rdma
wget -qO- http://172.24.30.30:10000 | sed -e 's/<[^>]*>//g'

# benchmark
./wrk -t2 -c2 -d10s http://172.24.30.30:10000
./wrk -t4 -c4 -d10s http://172.24.30.30:10000
./wrk -t8 -c8 -d10s http://172.24.30.30:10000
./wrk -t16 -c16 -d10s http://172.24.30.30:10000
./wrk -t32 -c32 -d10s http://172.24.30.30:10000
./wrk -t64 -c64 -d10s http://172.24.30.30:10000
```
