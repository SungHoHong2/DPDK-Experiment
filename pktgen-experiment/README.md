### PACKETGEN Experiment

```
running the pktgen from dkasu
running the l2fwd and TCP fwd from wenji-wrk
```

<br>


### DPDK-PKTGEN and Forwarding

```
// pktgen
./app/x86_64-native-linuxapp-gcc/pktgen -l 0-4 -n 3 -- -P -m "[1:3].0"
set 0 dst mac A0:36:9F:83:AB:BC

//l2fwd
./build/l2fwd -l 0 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x1 -T 1
```

<br>

### PKTGEN and TCP-Forwarding

```

```
