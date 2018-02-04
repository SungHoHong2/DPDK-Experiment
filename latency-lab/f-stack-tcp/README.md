### RUNNING F-STACK in WORKSTATION LAB

```
export FF_PATH=/data/f-stack/
export FF_DPDK=/data/f-stack/dpdk/x86_64-native-linuxapp-gcc
make

// change the core numbers in fstack (binary to hexadecimal)
sudo ./start.sh -b ./fstack-server -c config_server.ini
sudo ./start.sh -b ./tcp-server -c config_server.ini
```

```
# prove
wget -qO- http://10.218.111.254 | sed -e 's/<[^>]*>//g'
wget -qO- http://10.218.111.252 | sed -e 's/<[^>]*>//g'



# benchmark
./wrk -t2 -c2 -d10s http://10.218.111.252:8888
./wrk -t4 -c4 -d10s http://10.218.111.252:8888
./wrk -t8 -c8 -d10s http://10.218.111.252:8888
./wrk -t16 -c16 -d10s http://10.218.111.252:8888
./wrk -t32 -c32 -d10s http://10.218.111.252:8888
./wrk -t64 -c64 -d10s http://10.218.111.252:8888

# check for NIC brand
sudo apt-get install lshw
sudo lshw -class network
```

<br>

### HW description

```
sudo lshw
grep MemTotal /proc/meminfo
cat /proc/cpuinfo   

--- client dkasu

1. Server board
Motherboard description: Motherboard product: 0XHGV1 vendor: Dell Inc.       

2. CPU
Intel(R) Core(TM) i7-7700 CPU @ 3.60GHz

3. Memory
16307104kb

4. NIC
Ethernet Connection (5) I219-LM,  capacity: 1Gbit/s

5. Operating Systems
16.04.1-Ubuntu

6. Linux Kernel version
4.13.0-32-generic

7.DPDK version
dpdk-17.01

8.HugePages
2048


--- server wenji-wrk

1. Server board
Motherboard description: Motherboard product: 0XHGV1 vendor: Dell Inc.       

2. CPU
Intel(R) Core(TM) i7-7700 CPU @ 3.60GHz

3. Memory
20457968kb

4. NIC
I350 Gigabit Network Connection  capacity: 1Gbit/s   

5. Operating Systems
17.10-Ubuntu

6. Linux Kernel version
4.13.0-32-generic

7.DPDK version
dpdk-17.01

8.HugePages
2048
---

```
