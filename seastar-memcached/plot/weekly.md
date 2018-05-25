Experiments on Traditional MemCache[1], Seastar-Memcache[2] and libvma Memcache[3].

[1] https://memcached.org/
[2] https://github.com/scylladb/seastar/wiki/Memcached-Benchmark
[3] https://community.mellanox.com/docs/DOC-2168

However, I could not get the performance out of libvma Memache, because I could not access the FIU cluster.
Currently, FIU cluster responds that I have a wrong password that I have used for a long time.
I suspect that the password or the access configuration of FIU cluster has changed somehow because I was able to access FIU cluster in Korea.

I have checked the design, debugged the source code, and evaluated the basic performance in ASU cluster.
In ASU cluster,
I have used memaslap (Memcached benchmark) in c3n25 (act as a client host)
and run Memached and Seastar-Memecache in c3n24 (act as a server host)

First, the basic difference
1. traditional Memcached can run as both a daemon or a process
2. Seastar-Memcached can run as a process and it is independent from orignal memcached.
3. Libvma uses traditional memcached.

So basically, libvma simply overrides traditional socket-API interface used in MemCached, and use rdma for data transaction.
Seastar just implemeted the entire memcached by itself, and the overall logic is similar to the traditional Memcached.
It is known that memcached scales poorly to multicore processors because it was written for single core systems.
Seatar-Memcached claims that it has improve the performance when Memcached is running on multiple outstanding processes.
There are multiple alternative sources that also address this same issue such as Scaling Memcached at Facebook [4]
[4] https://www.usenix.org/system/files/conference/nsdi13/nsdi13-final170_update.pdf

The common logic that both Seatar-Memcached and traditional Memcached follows are these below
1. The servers maintain a key–value associative array
2. The clients populate this array and query it by key
3. The servers keep the values in RAM and if a server runs out of RAM, it discards the oldest values


Second, architecture of Seastar-Memcached
Memacached uses a client–server architecture. It means that the Memcached should be installed in both client and server in order to be utitlized. In case of Seastar-Memached, the server side is the only implemented side, which means that client still needs the client software that is compatiblie with Memcached.


Third, basic performance result from POSIX and DPDK.
The tests are done in ASU cluster c3n24 and c3n25.
The x axis represents the number of outstanding threads running on both client and server.
The y axis represents the average microseconds per response for latency and Mbytes per second for throughput






Seastar-Memcached is
