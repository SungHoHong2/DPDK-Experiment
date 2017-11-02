### Netperf with DPDK

- **PREFACE**
    - currently testing on dpdk-child
    - it is certain that the dpdk has been tested with iperf uperf and netperf
    - and iperf uperf netperf denfinitedly can be tested on RDMA

<br>

- **[failed] using iperf as a dpdk benchmark**
    - [using dpdk-iperf](https://github.com/ansyun/dpdk-iperf)
    - Iperf already saturated the line speed of the card so there was no improvement to be made.
    - Using this will also not be fair because the dpdk uses a special stack while Infiniband does not use it
    - The benchmark area should have same Implementation for all RDMA and DPDK

<br>

- **Implementing DPDK with OPEN V SWITCH**
    - [Offical website for OpenVSwitch for INFINIBAND](https://wiki.openstack.org/wiki/Mellanox-Neutron-Juno-Redhat-InfiniBand)
    - netperf definitedly works for RDMA
    - netperf Iperf all works for OPEN V SWITCH
    - netperf and netserver should both be on the traffic generator.
    - On the DPDK host, traffic coming in one interface is simply routed out the other interface by OVS, and back to your generator
    - netserver running on the DPDK host
    - create a virtual interface, attach it to OVS
    - give it an IP, and direct your netperf traffic

    <br>

- **comments of IFNINIBAND working with OpenVSwitch**

```
It would probably not be too hard to modify OVS to support 20-byte MAC
addresses exclusively.  Beyond changing ETH_ADDR_LEN, you would have to
audit some of the code to make sure that it does not have some kind of
hidden dependency on 6-byte addresses.  You would probably have to drop
OpenFlow support, since OpenFlow assumes that MAC addresses are 6 bytes
long.  Flow data structures would grow by 32 bytes, approximately
doubling their size, which would be a shame.

To support both sizes of MAC addresses would be more work.  I think that
it would amount to a more careful audit of each place a MAC address is
used.  It would probably require adding address-length fields some
places.  I'm not sure how it would interact with OpenFlow.  You could
drop OpenFlow support, or you could only expose the 6-byte MAC flows
through OpenFlow, or you could add OpenFlow extensions.

I have a question, though: do you really want to actually *switch*
IPoIB?  If you just want to use it on your host, without doing
switching, then why not skip going through the bridge or OVS entirely?
Just configure the network device directly.
```

```
OVS forwards Ethernet packets, which contain 6-byte MAC addresses.
OVS has some support for forwarding IPv4 and IPv6 as well, which don't
contain any MAC addresses at all.  I don't know how OVS would even
encounter Infiniband frames.
```

<br>

- **Connecting PKTGEN - DPDK**
    - [Stackoverflow explaining the topology ](https://stackoverflow.com/questions/45473475/understanding-dpdk-pktgens-destination-addressing)
    - [examples of running pktgen](https://github.com/danieltt/pktgen/tree/master/examples)
    - [official documentation](http://pktgen-dpdk.readthedocs.io/en/latest/getting_started.html)
    - [in depth understanding of packet-gen](https://people.kth.se/~danieltt/pktgen/docs/DanielTurull-thesis.pdf)

<br>


- **Connecting PKTGEN with IFNIBAND & DPDK**
    - [official documentation](https://community.mellanox.com/docs/DOC-2506)
