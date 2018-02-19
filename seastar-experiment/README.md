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
sudo ./configure.py --compiler g++-5

#in case there is an error related to boost
sudo apt-get install build-essential python-dev autotools-dev libicu-dev build-essential libbz2-dev
wget -O boost_1_66_0.tar.gz https://sourceforge.net/projects/boost/files/boost/1.66.0/boost_1_66_0.tar.gz/download
tar xzvf boost_1_66_0.tar.gz
cd boost_1_66_0.tar.gz/
./bootstrap.sh --prefix=/usr/

# if the compiled files still point to the old libraries
change the bootstrap.sh -> LIBDIR=/usr/lib/x86_64-linux-gnu

./b2
sudo ./b2 install
cat /usr/include/boost/version.hpp | grep "BOOST_LIB_VERSION"


# compile
sudo ninja

# lab 02
export SEASTAR=/home/sungho/seastar

# visasu
export SEASTAR=/data1/sungho/seastar

# fiu
export SEASTAR=/home/users/sungho/seastar

g++-5 `pkg-config --cflags --libs $SEASTAR/build/release/seastar.pc` server.cc -o server

g++ `pkg-config --cflags --libs $SEASTAR/build/release/seastar.pc` server.cc -o server


./a.out --dpdk-pmd 1
./a.out -c2 //running with two threads
```



<br>

**running dpdk**
```

export RTE_SDK=/data1/sungho/seastar/dpdk
export DESTDIR=/usr/local
export RTE_TARGET=x86_64-native-linuxapp-gcc

```

<br>

**seastar server application**
- [application running in workstation](seastar-server-lab)
- [application running in visasu](seastar-server)
