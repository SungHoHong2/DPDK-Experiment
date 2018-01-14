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

<br>

**boost version compare**

```
sungho@wenji-wrk:~$
dpkg -s libboost-dev | grep 'Version'
Version: 1.61.0.2

sungho@c3n24
Version: 1.54.0.1ubuntu1




```


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
./httpd --dpdk-pmd --network-stack native --dhcp 0 --host-ipv4-addr 10.107.30.34 --netmask-ipv4-addr 255.255.254.0 --gw-ipv4-addr 10.107.30.1 --collectd 0 --smp 2
wget -qO- http://10.218.111.253:10000 | sed -e 's/<[^>]*>//g'


# TCP seastar
./server --host-ipv4-addr 10.218.111.252 --netmask-ipv4-addr 255.255.248.0 --gw-ipv4-addr 10.218.111.1 --collectd 0 --smp 2
wget -qO- http://10.218.111.252:10000 | sed -e 's/<[^>]*>//g'
```
