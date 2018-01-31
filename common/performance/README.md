### Official Configuration settings
- How to get best performance with NICs on Intel platforms
  - [each memory channel has at least one memory DIMM inserted](http://dpdk.org/doc/guides-16.04/linux_gsg/nic_perf_intel_platform.html)
  - Make sure each NIC has been flashed the latest version of NVM/firmware.
  - Check for BIOS settings
    - Disable all power saving options such as: Power performance tuning, CPU P-State, CPU C3 Report and CPU C6 Report.
    - Select Performance as the CPU Power and Performance policy.
    - Disable Turbo Boost to ensure the performance scaling increases with the number of cores.
    - Set memory frequency to the highest available number, NOT auto.
  - Grub settings
    - reserve hugepages
    - you must isolate the CPU cores which will be used for DPDK
    - **To get the best performance, ensure that the core and NICs are in the same socket**
      - `0x:00.x` is on socket 0
      - `8x:00.x` is on socket 1
      - run `lscpu` or `tools/cpu_layout.py` to check the the cores on each socket.
      - run `lspci -nn | grep Eth` to check your NIC id and related socket id
      - **In the example above `85:00.0` is on socket 1 and should be used by cores on socket 1 for the best performance.**

<br>

### [DPDK Performance](https://www.slideshare.net/shemminger/dpdk-performance)
- Time budget from network stack challenges at increasing speeds - LCA 2015 Jesper Dangaard Brouer
    - `Packet` 67.2 ns
    - `L3` 8ns
    - `L2` 4.3 nx
    - `atomic Lock` 8.25 ns
    - `lock / unlock` 16.1 ns
- Checking the assembly language and count the time for checking the performance
  - DPDK can be used to build fast router (General Idea)
- single core test case
  - PMD test



<br>


### Official DPDK base-line
- A single or dual processor and PCH chip, except for System on Chip (SoC) cases
- DRAM memory size and frequency (normally single DIMM per channel)
- Specific Intel Network Interface Cards (NICs)
- BIOS settings noting those that updated from the basic settings
- DPDK build configuration settings, and commands used for tests


<br>

### Test results visible to the web
- [Chelsio Communications](https://www.chelsio.com/wp-content/uploads/resources/T5-40Gb-Linux-DPDK.pdf)
- they usually count for Mpps (Mega packet per second)


### Conclusion for performacne Optimizing
- the is a reason for using hexadecimals to assign cores is that the cores and NICs that are in the same socket should be assigned together.
- The general idea of using DPDK is creating application for Router




<br>

### RDMA experiments

- VMA
VMA is an Open Source library project that exposes standard socket APIs with kernel-bypass architecture, enabling user-space networking for Multicast, UDP unicast and TCP streaming. VMA also features ease of use out-of-the-box, with built in preconfigured profiles such as for latency or streaming.
