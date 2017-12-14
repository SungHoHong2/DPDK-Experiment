### Pingpong

```
// receiver from dkasu
// sender from wenji-wrk
gdb --args ./build/l2fwd -l 0 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x3
break /home/sungho/DPDK-Experiment/pingpong-experiment/sender/l2fwd_launch_one_lcore.h:127

./build/l2fwd -l 0 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x1
./build/l2fwd -l 0 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x1 -T 1
```
