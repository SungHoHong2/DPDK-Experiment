### Core components of EAL

| name            | description  |
| -------------   |------------- |
| rte_timer       | Time facilities |
| rte_malloc      | Allocation of name memory zones |
| rte_mempool     | Handle a pool of objects using a ring to store them, Allow bulk enqueue/dequeue and CPU cache |
| rte_eal + libc  | Environment abstraction layer: RTE loading, memory allocation, time reference, PCI access logging |
| rte_mbuf        | Manipulation of packet buffers carrying network data |
| rte_ring        | Fixed size lockeless FIFO for storing objects in a table |
| rte_debug       | Provide debug helpers |


#### Ring Manager (Librte_ring)
- provide lockless multi-producer, multi-consumer FIFO
- used by memory pool manager

#### Memory Pool Manager (Librte_mempool)
- allocate pools of objects in memory

#### Network Packet Buffer Management (Librte_mbuf)
- create and destroy buffers that may be used by the DPDK application to store message buffers

#### Librte_net
- collection of IP protocol definitions



#### Features of EAL
- responsible for gaining access to low-level resource like hardware and memory space
- DPDK loading and launching
- Core Affinity and Assignment
- Memory reservation
  - using hugepages
- PCI Address Abstraction
  - using igb_uio EAL accesses to PCI information
- Utility functions such as spinlocks and atomic counters
- Interrupt handling
  - EAL polls the UIO device file descriptors to detect interrupts
- Alarm functions to set/remove callbacks to be run at a specific time
