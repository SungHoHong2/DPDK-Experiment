### Errors
Network errors can generally be categorized into problems with queuing, latency, and jitter. The data queue can affect network performance in several ways. For example, larger queues increase the wait time, while smaller queues increase the probability of dropped data.

### [Speed](speed.md)
`Pipe size` is the amount of data the network can send simultaneously on a single connection. It's often confused with connection speed, although pipe size doesn't actually affect the speed at which data travels between nodes. While hardware capabilities determine the maximum bandwidth that is theoretically available, software mechanisms typically allocate a lower bandwidth for each network service.

### [Memory](memory.md)
`Memory` is a computing resource that has requirements in both the data and control planes. The performance of the entire network can degrade when control plane processes fail, as is the case when routing convergence requires additional memory.

### Distance
Distance can have a dramatic impact on network performance, especially when the applications haven't been optimized. The maximum speed at which data can be forwarded is the speed of light, which is 186,000 miles per second or 186 miles per millisecond. This packet forwarding delay becomes significant when an enterprise is running an international client/server application.


### [Central Processing Unit (CPU)](cpu.md)
A node's central processing unit `(CPU)` is typically used by both the control and data planes. Capacity and performance management requires a network and its nodes to have insufficient processing capability at all times. A single node with an inadequate CPU can impact the entire network due to the high degree of interdependence between the nodes in the modern network. Insufficient processing can also increase latency if a node's CPU is unable to keep up with network traffic.


### Applications
Applications can also affect a network's capacity and performance, with issues such as the amount of data the application is able to transmit compared to what it needs to transmit. This factor is especially critical for the performance of Wide Area Networks (WANs). Additional application characteristics that affect capacity and performance include application keep-alives and window sizes.

### Input/Output (I/O)
Input/Output (I/O) capability on a network is also known as the network’s back plane and is usually measured in terms of `bus size`. An inadequate back plane can cause the network to drop packets, thus increasing the network traffic due to retransmitted data.
