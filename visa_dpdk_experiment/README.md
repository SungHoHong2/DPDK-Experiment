### MAIN

```
./test -c 0x3 -n 3 --socket-mem=0,512 -d
./pktgen -c 0xB -n 3 --socket-mem 2048 --proc-type auto --file-prefix pg1 -b 01:00.1 -- -P -m "[1:3].0"
./build/l2fwd -l 0-3 -n 4 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x3 -T 1
```
