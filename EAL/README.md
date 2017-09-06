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
