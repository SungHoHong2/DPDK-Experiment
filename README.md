# DPDK Experiment
Collections of DPDK experiments focused on proper implementation and performance evaluations.


### Prerequisites
- [Network Dictionary](https://docs.google.com/document/d/1ovVb2subuS-UQl161BGVeXlWYFnu6jngM4QcB81HNpw/edit?usp=sharing)
- [DPDK Dictionary](https://docs.google.com/document/d/1sOiMM1qw4DNYUfDTZYZ2L_ZUbv6R7lVD48AmClV51Mo/edit?usp=sharing)
- [Related Papers](papers)


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
- [Official DPDK Performance results](common/performance/README.md)


### Performance Test
- [Implemented pingpong for DPDK](pingpong-experiment)
- [Implemented pingpong for TCP](tcp-experiment)
- [Implemented pingpong for PKTGEN](common/pktgen-experiment)
- [F-Stack Performance Test](f-stack-experiment)
- [Seastar Experiment](seastar-experiment)
- [DPDK-ANS Experiments](dpdk_ans_experiment)
- [Seastar-memcached Experiments](seastar-memcached)
