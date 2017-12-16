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


./build/app/testpmd -cffffff -n 3 -d librte_pmd_e1000.so -d librte_mempool_ring.so -- -i --rxd=1024 --txd=1024 --burst=144 --txpt=32 --txht=0 --txfreet=0 --rxfreet=64 --mbcache=200 --portmask=0x3 --mbuf-size=2048 --max-pkt-len=9600
```

<br>

### informatoin of the Maximum Transfer Unit

- **turning on the MTU**

```
ip link show enp3s0f2 // you can see the default MTU
enp3s0f2: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc mq state DOWN
ip link set eth0 mtu 9000 // changing the MTU size
```

- The jumbo frame is considered to be bigger than 1500 packet length and it can increase up to 9000
- However if the ethernet speed is 100mbps the jumbo frame won't have positive effect even though the ethernet supports it
- **the reason that why VISA workstation cannot support JUMBO frame**
    - [reference link about the limitation of jumbo link](https://www.intel.com/content/www/us/en/support/articles/000005593/network-and-i-o/ethernet-products.html)

```
Port 0: LSC event                                                               
PMD: eth_igb_interrupt_action():  Port 1: Link Up - speed 100 Mbps - full-duplex
```

<br>

### L3 original test by INTEL









### L2 customized test

| item | description |
| -- | -- |
| test case | Single core performance test for i40e DPDK PMD |
