### Load balancer
- concept of isolating the packet I/O task from the application-specific workload.
- a number of logical cores (lcores) are dedicated to handle the interaction with the NIC ports (I/O lcores)
- the rest of the lcores are dedicated to performing the application processing (worker lcores)
- use the NIC-agnostic interface provided by software rings to exchange packets with the I/O cores.
- `in this case I think you should concentrate on getting two queue pairs working on DPDK first`


### Overview
-  two I/O RX and two I/O TX lcores off loading the packet I/O overhead
-  incurred by four NIC ports from four worker cores,
-  with each I/O lcore handling RX/TX for two NIC ports.


### IO
