### SEASTAR

**prerequisite**
- [lambda experiment](lambda)

<br>

**install**
```
sudo apt-get install libaio-dev ninja-build ragel libhwloc-dev libnuma-dev libpciaccess-dev libcrypto++-dev libboost-all-dev
git clone https://github.com/scylladb/seastar.git
./install-dependencies.sh
./configure.py --enable-dpdk
ninja

export SEASTAR=/home/sungho/seastar
c++ `pkg-config --cflags --libs $SEASTAR/build/release/seastar.pc` getting-started.cc
./a.out --dpdk-pmd 1
./a.out -c2 //running with two threads
```

<br>
**running dpdk**
```
./configure.py --dpdk-target /home/sungho/seastar/dpdk/x86_64-native-linuxapp-gcc
./a.out --dpdk-pmd --network-stack native --dhcp 0

```

<br>

**seastar server application**
```
./seastar-server --dpdk-pmd --network-stack native --dhcp 0
```
