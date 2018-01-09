### SEASTAR

**prerequisite**
- [lambda experiment](lambda)

**install**
```
sudo apt-get install libaio-dev ninja-build ragel libhwloc-dev libnuma-dev libpciaccess-dev libcrypto++-dev libboost-all-dev
git clone https://github.com/scylladb/seastar.git
./configure.py
ninja


export SEASTAR=/home/sungho/seastar
c++ `pkg-config --cflags --libs $SEASTAR/build/release/seastar.pc` getting-started.cc
./a.out
./a.out -c2 //running with two threads


c++ `pkg-config --cflags --libs $SEASTAR/build/release/seastar.pc` server-example.cc



```
