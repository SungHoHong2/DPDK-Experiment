git pull origin master
cd /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap_c
SOURCE_FILES="memaslap.c "


export PATH=~/data1/sungho/usr/bin:$PATH
g++ -std=gnu++11 $SOURCE_FILES -o client -lmemcached -lmemcachedutil
