### Pingpong

- run the server from dkasu
- run the client from wenji-wrk

<br>

- running command
```
./build/l2fwd -l 0 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x1 -T 1
```
