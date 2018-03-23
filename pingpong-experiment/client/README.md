### L2FWD

- the ports are working only for port 1
- this is due to the server reason

```
./build/l2fwd -l 0 -n 4 -- -q 8 -p 0x2 -T 1
./build/l2fwd -l 0 -n 4 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x2 -T 1
gdb --args ./build/l2fwd -l 0-3 -n 4 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x2 -T 1
```

00:1B:21:A6:D4:D5
