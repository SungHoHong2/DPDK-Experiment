### HW Setup
- A single or dual processor and PCH chip, except for System on Chip (SoC) cases
- DRAM memory size and frequency (normally single DIMM per channel)
- Specific Intel Network Interface Cards (NICs)
- BIOS settings noting those that updated from the basic settings
- DPDK build configuration settings, and commands used for tests

- **test pmd**

```
/home/sungho/dpdk-17/app/test-pmd
./testpmd -l 0-3 -n 4 -d librte_pmd_e1000.so -d librte_mempool_ring.so -- -i --portmask=0x1 --nb-cores=2

```

<br>

### Checking the Maximum Transfer Unit

```
ip link show enp3s0f2 // you can see the default MTU
enp3s0f2: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc mq state DOWN
ip link set eth0 mtu 9000 // changing the MTU size
```




<br>

### L3 original test by INTEL









### L2 customized test

| item | description |
| -- | -- |
| test case | Single core performance test for i40e DPDK PMD |
