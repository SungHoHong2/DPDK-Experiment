### Experiments on Seastar Memcached
- currently, I'am  able to transfer data through DPDK with shared memory.
- but hopefully Seastar-Memcached experiment will bring me better ideas that does not have to use shared memory in MPICH.
- for starters `since MPI-library is built with C, f-stack we be more compatible for MPI-library`.


**what is memcached**
- Free & open source, high-performance, distributed memory object caching system, generic in nature, but intended for use in speeding up dynamic web applications by alleviating database load."
- [architecture](experiments/memcached.md)

```c++
1) Download libevent from  http://libevent.org/
git clone https://github.com/libevent/libevent.git

2) Go inside extracted directory and type following things
./autogen.sh
./configure --prefix=/data1/sungho/usr/local
make && make install

3) Download source code of memcached from http://www.memcached.org/
wget http://www.memcached.org/files/memcached-1.5.7.tar.gz
tar -xvf memcached-1.5.7.tar.gz
cd /data1/sungho/memcached-1.5.7
./configure --with-libevent=/data1/sungho/usr/local
make && make install

4) You can check whether memcached is working by giving following command
// After that you can do
memcached -u nobody &
// to see if memcached is started.
ps -el | grep memcached


5) install memslap
wget https://launchpad.net/libmemcached/1.0/1.0.18/+download/libmemcached-1.0.18.tar.gz
tar -xvf libmemcached-1.0.18.tar.gz
cd libmemcached-1.0.18/
./configure --enable-memaslap LDFLAGS=-lpthread --prefix=/data1/sungho/usr/local
make && sudo make install

6) Now go inside clients directory present inside libmemcached and give following command
cd /data1/sungho/libmemcached-1.0.18/clients
./memslap -s localhost
```


**How to run Seastar Memcahced**
```c++
sudo /data1/sungho/seastar/build/release/apps/memcached/memcached --dpdk-pmd --dpdk-port-index 1 --network-stack native --dhcp 0 --host-ipv4-addr 10.107.30.40 --netmask-ipv4-addr 255.255.254.0 --gw-ipv4-addr 10.107.30.1 --collectd 0 --smp $2
```


**Run traditional Memcached**
```c++
memcached -m 12000 -p 11211
cd /data1/sungho/libmemcached-1.0.18/clients
./memslap -s 10.107.30.33:11211 –facebook –division=50 –conn_sock=200
./memslap -s 10.107.30.33:11211 -t 60s -T 1
```
