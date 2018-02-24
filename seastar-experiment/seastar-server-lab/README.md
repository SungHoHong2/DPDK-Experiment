### DPDK

```
# DPDK seastar wenji-wrk
./server --dpdk-pmd --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.253 --netmask-ipv4-addr 255.255.248.0 --gw-ipv4-addr 10.218.111.1 --collectd 0 --smp 2

./client --dpdk-pmd --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.254 --netmask-ipv4-addr 255.255.248.0 --gw-ipv4-addr 10.218.111.1 --collectd 0 --smp 2


# DPDK seastar dkasu
wget -qO- http://10.218.111.253:10000 | sed -e 's/<[^>]*>//g'
./wrk -t12 -c12 -d1s http://10.218.111.253:10000

./wrk -t2 -c2 -d10s http://10.218.111.253:10000
./wrk -t4 -c4 -d10s http://10.218.111.253:10000
./wrk -t8 -c8 -d10s http://10.218.111.253:10000
./wrk -t16 -c16 -d10s http://10.218.111.253:10000
./wrk -t32 -c32 -d10s http://10.218.111.253:10000

```

<br>

### TCP
```
# TCP seastar wenji-wrk
./server --host-ipv4-addr 10.218.111.252 --netmask-ipv4-addr 255.255.248.0 --gw-ipv4-addr 10.218.111.1 --collectd 0 --smp 2

./httpd --host-ipv4-addr 10.218.111.252 --netmask-ipv4-addr 255.255.248.0 --gw-ipv4-addr 10.218.111.1 --collectd 0 --smp 2


# TCP seastar dkasu
wget -qO- http://10.218.111.252:10000 | sed -e 's/<[^>]*>//g'
```


# The primary network interface  
auto p5p1                        
iface p5p1 inet static           
address 10.107.30.34             
netmask 255.255.254.0            
network 10.107.30.0              
broadcast 10.107.31.255          
gateway 10.107.30.1              
dns-nameservers 129.219.17.200   
