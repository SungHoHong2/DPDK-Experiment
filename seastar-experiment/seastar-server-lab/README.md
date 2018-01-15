### DPDK

```
# DPDK seastar wenji-wrk
./server -c4 --dpdk-pmd --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.253 --netmask-ipv4-addr 255.255.248.0 --gw-ipv4-addr 10.218.111.1 --collectd 0 --smp 2

# DPDK seastar dkasu
wget -qO- http://10.218.111.253:10000 | sed -e 's/<[^>]*>//g'

./wrk -t12 -c12 -d1s http://10.218.111.253:10000


# DPDK f-stack

sudo ./fstack-server --conf config_server.ini --proc-type=primary --proc-id=0
sudo ./fstack-server --conf config_server.ini --proc-type=secondary --proc-id=1
sudo ./fstack-server --conf config_server.ini --proc-type=secondary --proc-id=2
sudo ./fstack-server --conf config_server.ini --proc-type=secondary --proc-id=4
sudo ./fstack-server --conf config_server.ini --proc-type=secondary --proc-id=5
sudo ./fstack-server --conf config_server.ini --proc-type=secondary --proc-id=6
sudo ./fstack-server --conf config_server.ini --proc-type=secondary --proc-id=7
sudo ./fstack-server --conf config_server.ini --proc-type=secondary --proc-id=8



```

<br>

### TCP
```
# TCP seastar wenji-wrk
./server --host-ipv4-addr 10.218.111.252 --netmask-ipv4-addr 255.255.248.0 --gw-ipv4-addr 10.218.111.1 --collectd 0 --smp 2

# TCP seastar dkasu
wget -qO- http://10.218.111.252:10000 | sed -e 's/<[^>]*>//g'
```
