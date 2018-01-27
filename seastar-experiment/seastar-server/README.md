### RUNNING SEASTAR IN VISASU

```
# visasu

# dpdk enabled
sudo ./server --dpdk-pmd --dpdk-port-index 1 --network-stack native --dhcp 0 --host-ipv4-addr 10.107.30.40 --netmask-ipv4-addr 255.255.254.0 --gw-ipv4-addr 10.107.30.1 --collectd 0 --smp 2

# TCP seastar
./tcp_server --host-ipv4-addr 10.107.30.40 --netmask-ipv4-addr 255.255.254.0 --gw-ipv4-addr 10.107.30.1 --smp 2
```


```
# testing in visasu
wget -qO- http://10.107.30.40:10000 | sed -e 's/<[^>]*>//g'

# benchmark
./wrk -t2 -c2 -d10s http://10.107.30.40:10000
./wrk -t4 -c4 -d10s http://10.107.30.40:10000
./wrk -t8 -c8 -d10s http://10.107.30.40:10000
./wrk -t16 -c16 -d10s http://10.107.30.40:10000
./wrk -t32 -c32 -d10s http://10.107.30.40:10000
./wrk -t64 -c64 -d10s http://10.107.30.40:10000

wget -qO- http://10.107.30.40 | sed -e 's/<[^>]*>//g'

wget -qO- http://10.107.30.40 | sed -e 's/<[^>]*>//g'
./wrk -t2 -c2 -d10s http://10.107.30.40
./wrk -t4 -c4 -d10s http://10.107.30.40
./wrk -t8 -c8 -d10s http://10.107.30.40
./wrk -t16 -c16 -d10s http://10.107.30.40
./wrk -t32 -c32 -d10s http://10.107.30.40
./wrk -t64 -c64 -d10s http://10.107.30.40
```


```
# testing in FIU
wget -qO- http://172.24.30.31:10000 | sed -e 's/<[^>]*>//g'

# benchmark
./wrk -t2 -c2 -d10s http://172.24.30.31:10000
./wrk -t4 -c4 -d10s http://172.24.30.31:10000
./wrk -t8 -c8 -d10s http://172.24.30.31:10000
./wrk -t16 -c16 -d10s http://172.24.30.31:10000
./wrk -t32 -c32 -d10s http://172.24.30.31:10000
./wrk -t64 -c64 -d10s http://172.24.30.31:10000
```
