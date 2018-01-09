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

```
