cd /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/tcp-client
SOURCE_FILES=client.cc dpdk_memcached.cpp
export PATH=~/data1/sungho/usr/bin:$PATH

g++ -std=gnu++11 client.cc dpdk_memcached.cc -o client -lmemcached -lmemcachedutil
