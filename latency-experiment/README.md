### Latency Experiment

- TCP need to count latency by packets which is done by DPDK
- unlike TCP which can guarantee send and receive per attempt DPDK continuously receive packets
    - DPDK receive packets even if there is no communication

```
Using the SO_TIMESTAMP option to setsockopt(), we can measure the amount of time it takes the Linux kernel to hand a received network packet off to user space. With the option set, the kernel returns an extra struct timeval to the recvmsg() packet reception function
```
