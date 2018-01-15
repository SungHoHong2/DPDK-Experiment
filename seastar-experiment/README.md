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
./b2
sudo ./b2 install
cat /usr/include/boost/version.hpp | grep "BOOST_LIB_VERSION"


# compile
sudo ninja

# lab 02
export SEASTAR=/home/sungho/seastar

# visasu
export SEASTAR=/data1/sungho/seastar
g++-5 `pkg-config --cflags --libs $SEASTAR/build/release/seastar.pc` getting-started.cc

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




```
comerr-dev cython cython3 dh-exec dh-systemd docutils-common git git-man    
gperf javahelper jq krb5-multidev libbabeltrace-ctf-dev libbabeltrace-dev   
libblkid-dev libboost-atomic-dev libboost-atomic1.54-dev                    
libboost-atomic1.54.0 libboost-chrono-dev libboost-chrono1.54-dev           
libboost-chrono1.54.0 libboost-context-dev libboost-context1.54-dev         
libboost-context1.54.0 libboost-coroutine-dev libboost-coroutine1.54-dev    
libboost-date-time-dev libboost-date-time1.54-dev libboost-date-time1.54.0  
libboost-dev libboost-exception-dev libboost-exception1.54-dev              
libboost-filesystem-dev libboost-filesystem1.54-dev                         
libboost-filesystem1.54.0 libboost-graph-dev libboost-graph-parallel-dev    
libboost-graph-parallel1.54-dev libboost-graph-parallel1.54.0               
libboost-graph1.54-dev libboost-graph1.54.0 libboost-iostreams-dev          
libboost-iostreams1.54-dev libboost-locale-dev libboost-locale1.54-dev      
libboost-locale1.54.0 libboost-log-dev libboost-log1.54-dev                 
libboost-log1.54.0 libboost-math-dev libboost-math1.54-dev                  
libboost-math1.54.0 libboost-mpi-dev libboost-mpi-python-dev                
libboost-mpi-python1.54-dev libboost-mpi-python1.54.0 libboost-mpi1.54-dev  
libboost-mpi1.54.0 libboost-program-options-dev                             
libboost-program-options1.54-dev libboost-program-options1.54.0             
libboost-python-dev libboost-python1.54-dev libboost-python1.54.0           
libboost-random-dev libboost-random1.54-dev libboost-random1.54.0           
libboost-regex-dev libboost-regex1.54-dev libboost-regex1.54.0              
libboost-serialization-dev libboost-serialization1.54-dev                   
libboost-serialization1.54.0 libboost-signals-dev libboost-signals1.54-dev  
libboost-signals1.54.0 libboost-system-dev libboost-system1.54-dev          
libboost-system1.54.0 libboost-test-dev libboost-test1.54-dev               
libboost-test1.54.0 libboost-thread-dev libboost-thread1.54-dev             
libboost-thread1.54.0 libboost-timer-dev libboost-timer1.54-dev             
libboost-timer1.54.0 libboost-tools-dev libboost-wave-dev                   
libboost-wave1.54-dev libboost-wave1.54.0 libboost1.54-dev                  
libboost1.54-tools-dev libc6-dbg libcephfs1 libcr0 libfcgi0ldbl libfuse-dev
```
