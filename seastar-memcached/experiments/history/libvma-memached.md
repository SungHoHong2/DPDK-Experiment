**libvma memcached**

```c++
// memached
LD_PRELOAD=libvma.so VMA_RING_ALLOCATION_LOGIC_TX=31 VMA_RING_ALLOCATION_LOGIC_RX=31 LD_LIBRARY_PATH=/usr/local/lib taskset -c 8-15 memcached -m 12000 -l 2.2.2.4 -u root -t 7 // threads

// memaslap
VMA_RING_ALLOCATION_LOGIC_TX=20 VMA_RING_ALLOCATION_LOGIC_RX=20 LD_PRELOAD=libvma.so taskset -c 8-15 memaslap -s 2.2.2.4:11211 -T 1 -c 1 -t 10s -X 64  -S 1s
```
