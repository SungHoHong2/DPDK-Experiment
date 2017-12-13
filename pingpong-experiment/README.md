### Pingpong

```
// receiver from dkasu
// sender from wenji-wrk
./build/l2fwd -l 0-3 -n 4 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -P -q 8 -p 0x3 -T 20
./build/l2fwd -l 0-3 -n 4 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x1 -T 20
```
