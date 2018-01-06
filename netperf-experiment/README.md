### Netperf Experiments

- **install**

```
git clone https://github.com/HewlettPackard/netperf.git
./autogen.sh
apt install texinfo
./configure
make
```

<br>


- **running**

```
// server wenji-wrk
// Starting netserver with host 'IN(6)ADDR_ANY' port '12865' and family AF_UNSPEC
cd src
./netserver

// client dkasu
cd src

./netperf -P 12865 -t TCP_RR -H 10.218.111.252 -- -r 1,1 -o P50_LATENCY,P90_LATENCY,P99_LATENCY
```

<br>

| commands | description |
| -- | -- |
| -H | server ip address |
| -m | size of the packet |
| -l | elapsed time |
| -o | used for creating latency features [optional]|


<br>


- **building netserver**
```
./netperf -H 10.218.111.252 -l 5 -- -m 2048 -o P99_LATENCY

./netserver --conf config_server.ini --proc-type=primary --proc-id=0


gcc -DHAVE_CONFIG_H -I. -I.. -g -MT netserver.o -MD -MP -MF .deps/netserver.Tpo -c -o netserver.o netserver.c                

```

<br>

- **netperf makefile modification**

```
TOPDIR=..

ifeq ($(FF_PATH),)
        FF_PATH=${TOPDIR}
endif

ifeq ($(FF_DPDK),)
        FF_DPDK=${TOPDIR}/dpdk/x86_64-native-linuxapp-gcc
endif


CFLAGS = -g -O -gdwarf-2  -I /data/f-stack/lib
LIBS+= -L${FF_PATH}/lib -L${FF_DPDK}/lib -Wl,--whole-archive,-lfstack,--no-whole-archive
LIBS+= -Wl,--whole-archive -lrte_pmd_vmxnet3_uio -lrte_pmd_i40e -lrte_pmd_ixgbe -lrte_pmd_e1000 -lrte_pmd_ring
LIBS+= -Wl,--whole-archive -lrte_hash -lrte_kvargs -Wl,-lrte_mbuf -lethdev -lrte_eal -Wl,-lrte_mempool
LIBS+= -lrte_ring -lrte_cmdline -lrte_cfgfile -lrte_kni -lrte_timer -Wl,-lrte_pmd_virtio
LIBS+= -Wl,--no-whole-archive -lrt -lm -ldl -lcrypto -pthread

```

<br>

- **debugging netserver**
    - [netserver overall debug](netserver_debug)
    - [netserver data transfer debug](netserver_transfer_debug)
