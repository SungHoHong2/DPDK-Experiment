SOURCE_FILES=client.cc dpdk_memcached.hh dpdk_memcached.cpp
export PATH=~/data1/sungho/usr/bin:$PATH

g++ -std=gnu++11 $SOURCE_FILES -o client -lmemcached -lmemcachedutil
