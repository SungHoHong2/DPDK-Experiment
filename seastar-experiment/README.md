### SEASTAR

**prerequisite**
- [lambda experiment](lambda)

<br>

**install**
```
sudo apt-get install libaio-dev ninja-build ragel libhwloc-dev libnuma-dev libpciaccess-dev libcrypto++-dev libboost-all-dev
git clone https://github.com/scylladb/seastar.git
./install-dependencies.sh
sudo ./configure.py --enable-dpdk --compiler g++-5

#in case there is an error related to boost

sudo apt-get install build-essential python-dev autotools-dev libicu-dev build-essential libbz2-dev
wget -O boost_1_66_0.tar.gz https://sourceforge.net/projects/boost/files/boost/1.66.0/boost_1_66_0.tar.gz/download
tar xzvf boost_1_66_0.tar.gz
cd boost_1_66_0.tar.gz/
./bootstrap.sh --prefix=/usr/
./b2
sudo ./b2 install

/data1/sungho/boost_1_66_0

# compile
ninja

# lab 02
export SEASTAR=/home/sungho/seastar

# visasu
export SEASTAR=/data1/sungho/seastar
c++ `pkg-config --cflags --libs $SEASTAR/build/release/seastar.pc` getting-started.cc
./a.out --dpdk-pmd 1
./a.out -c2 //running with two threads
```



build/release/apps/httpd/httpd
sungho@c3n24:/data1/sungho/DPDK-Experiment/seastar-experiment/seastar-server$ c++ `pkg
-config --cflags --libs $SEASTAR/build/release/seastar.pc` server.cc                  
In file included from /data1/sungho/seastar/core/ragel.hh:25:0,                       
                 from http/request_parser.rl:24,                                      
                 from /data1/sungho/seastar/http/httpd.hh:25,                         
                 from server.cc:22:                                                   
/data1/sungho/seastar/core/sstring.hh:37:36: fatal error: experimental/string_view: No
 such file or directory                                                               
 #include <experimental/string_view>                                                  

<br>

**running dpdk**
```
./configure.py --dpdk-target /home/sungho/seastar/dpdk/x86_64-native-linuxapp-gcc
./a.out --dpdk-pmd --network-stack native --dhcp 0


./configure.py --enable-dpdk

```

<br>

**seastar server application**
```
# wenji-wrk
# DPDK seastar wenji-wrk
./server --dpdk-pmd --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.253 --netmask-ipv4-addr 255.255.248.0 --gw-ipv4-addr 10.218.111.1 --collectd 0 --smp 2
wget -qO- http://10.218.111.253:10000 | sed -e 's/<[^>]*>//g'

# visasu
./server --dpdk-pmd --network-stack native --dhcp 0 --host-ipv4-addr 10.107.30.34 --netmask-ipv4-addr 255.255.254.0 --gw-ipv4-addr 10.107.30.1 --collectd 0 --smp 2
wget -qO- http://10.218.111.253:10000 | sed -e 's/<[^>]*>//g'

# TCP seastar
./server --host-ipv4-addr 10.218.111.252 --netmask-ipv4-addr 255.255.248.0 --gw-ipv4-addr 10.218.111.1 --collectd 0 --smp 2
wget -qO- http://10.218.111.252:10000 | sed -e 's/<[^>]*>//g'
```
