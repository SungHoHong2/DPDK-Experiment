### Netperf with DPDK

- **PREFACE**
    - currently testing on dpdk-child
    - it is certain that the dpdk has been tested with iperf uperf and netperf
    - and iperf uperf netperf denfinitedly can be tested on RDMA

<br>
    
- **[failed]** [using dpdk-iperf](https://github.com/ansyun/dpdk-iperf)
    - Iperf already saturated the line speed of the card so there was no improvement to be made.
    - Using this will also not be fair because the dpdk uses a special stack while Infiniband does not use it
    - **The benchmark area should have same Implementation for all RDMA and DPDK**

<br>

- **Implementing DPDK with OPEN V SWITCH**
    - netperf definitedly works for RDMA
    - netperf Iperf all works for OPEN V SWITCH
    - netperf and netserver should both be on the traffic generator.
    - On the DPDK host, traffic coming in one interface is simply routed out the other interface by OVS, and back to your generator
    - netserver running on the DPDK host
    - create a virtual interface, attach it to OVS
    - give it an IP, and direct your netperf traffic

<br>
