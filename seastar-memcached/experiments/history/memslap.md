### memslap

**description**
- memaslap is a load generation and benchmark tool for memcached servers.
- It generates configurable workload such as threads, concurrencies, connections, run time, overwrite, miss rate, key size, value size, get/set proportion, expected throughput
- it also testss data verification, expire-time verification, UDP, binary protocol, facebook test, replication test, multi-get and reconnection, etc.
- Memaslap manages network connections like memcached with libevent.
- Each thread of memaslap is bound with a CPU core,
- all the threads don’t communicate with each other,
- there are several socket connections in each thread
- Each connection keeps key size distribution, value size distribution, and command distribution by itself


```c++
cd /data1/sungho/libmemcached-1.0.18/clients
./memaslap -s 10.107.30.33:11211 -S 1s -t 10s
memaslap -s 10.107.30.33:11211 -t 2m -v 0.2 -e 0.05 -b
memaslap -s 10.107.30.33:11211 -F config -t 2m -w 40k -S 20s -o 0.2
memaslap -s 10.107.30.33:11211 -F config -t 2m -T 4 -c 128 -d 20 -P 40k
memaslap -s 10.107.30.33:11211 -F config -t 2m -d 50 -a -n 40

// server
memcached -d -m 24 -p 11211

// client
cd /data1/sungho/libmemcached-1.0.18/clients
./memaslap -s 10.107.30.33:11211 -S 10s –facebook –division=50 –conn_sock=200


// checking for memory usage for memached
ps -u root -o rss,command | grep 'memcached -d'  | awk '{print $0}{sum+=$1} END {print "\nMemory usage for memcached:", sum/1024, "MB\n"}'

```



**results from memaslap**

```
Get Statistics
Type  Time(s)  Ops   TPS(ops/s)  Net(M/s)  Get_miss  Min(us)  Max(us)
Avg(us)  Std_dev    Geo_dist
Period   5   345826  69165     65.3      0         27      2198     203
95.43      177.29
Global  20  1257935  62896     71.8      0         26      3791     224
117.79     192.60

Set Statistics
Type  Time(s)  Ops   TPS(ops/s)  Net(M/s)  Get_miss  Min(us)  Max(us)
Avg(us)  Std_dev    Geo_dist
Period   5    38425   7685      7.3       0         42      628     240
88.05      220.21
Global   20   139780  6989      8.0       0         37      3790    253
117.93     224.83

Total Statistics
Type  Time(s)  Ops   TPS(ops/s)  Net(M/s)  Get_miss  Min(us)  Max(us)
Avg(us)  Std_dev    Geo_dist
Period   5   384252   76850     72.5      0        27      2198     207
94.72      181.18
Global  20  1397720   69886     79.7      0        26      3791     227
117.93     195.60


Get Statistics
   Statistics information of get command

Set Statistics
   Statistics information of set command

Total Statistics
   Statistics information of both get and set command

The average response time
```

**how memcached is calculated**
-
