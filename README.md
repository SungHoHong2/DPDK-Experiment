# DPDK Experiment

### Prerequisites
- [Network Dictionary](https://docs.google.com/document/d/1ovVb2subuS-UQl161BGVeXlWYFnu6jngM4QcB81HNpw/edit?usp=sharing)
- [DPDK Dictionary](https://docs.google.com/document/d/1sOiMM1qw4DNYUfDTZYZ2L_ZUbv6R7lVD48AmClV51Mo/edit?usp=sharing)

<br>

### Common Features
- [`helloworld` - allocating the pthreads for each logical cores](common/helloworld)
- [`skeleton` - basic concpet of tranferring packets](common/skeleton)
- [`l2fwd` - basic concpet of l2 packet forwarding](common/l2fwd)
- [`crafting Packets` - experiment on creating packets](common/pkt-craft)
- [`dpdk packets` - experiment on packet components ](common/packet-experiment)
- [`ring` - experiment on ring ](common/ring-experiment)
- [`device reading` - getting device configuration data from ceph](common/device)
- [`MTU experiment`](common/MTU-experiment)
- [Factors influencing network performance](factor-performance)
- [Experiment on `RSS`](common/RSS)
  - finding out the reason why f-stack has trouble with distributing the packets
- [Official DPDK Performance results](common/performance/README.md)


### Related Papers
- [Removing Roadblocks from SDN: OpenFLow Software Switch Performance on Intel DPDK](papers/06680560.pdf)
- [Supporting Fine-Grained Network Functions through Intel DPDK](http://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=6984043)




<br>

### Performance Test
- [Implemented pingpong for DPDK](pingpong-experiment)
- [Implemented pingpong for TCP](tcp-experiment)
- [Implemented pingpong for PKTGEN](pktgen-experiment)
- [Comparing Official Performance Tests by Intel](Official_Performance_Test)
- [`Latency Performance Test` working in visasu](latency-experiment)
- [`Latency Performance Test` by using f-stack & IMB-benchmark](latency-lab)
    - testing fstack with wrk benchmark
    - testing tcp epolling with wrk benchmark
    - in depth interpretation on how epolling works
- [`Netperf Experiment` for integrating f-stack with the proper benchmark ](netperf-experiment)
- [`Seastar Experiment`](seastar-experiment)
