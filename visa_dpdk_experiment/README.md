### MAIN

```
./test -c 0x3 -n 3 --socket-mem=0,512 -d
./pktgen -c 0xB -n 3 --socket-mem 2048 --proc-type auto --file-prefix pg1 -b 01:00.1 -- -P -m "[1:3].0"
./build/l2fwd -l 0-3 -n 4 -d librte_pmd_e1000.so -d librte_mempool_ring.so  -- -q 8 -p 0x3 -T 1
```

<br>

### switching into shared and non-shared library

```
vi dpdk/config/common_base
SHARED = y or n

remove all the rte files in usr/local/lib
reinstall dpdk
sudo apt-get install libconfig++-dev


make config T=x86_64-native-linuxapp-gcc
make
make install T=x86_64-native-linuxapp-gcc DESTDIR=/usr/local
```

```
ifeq ($(RTE_SDK),)                                                   
$(error "Please define RTE_SDK environment variable")                
endif                                                                

# Default target, can be overriden by command line or environment    
RTE_TARGET ?= x86_64-native-linuxapp-gcc                             

include $(RTE_SDK)/mk/rte.vars.mk                                    

# binary name                                                        
APP = example                                                       

# all source are stored in SRCS-y                                    
SRCS-y := test.c vd_init.c vd_conn.c vd_rsmgr.c -lconfig -lpthread  

CFLAGS += -O3 -g                                                    

include $(RTE_SDK)/mk/rte.extapp.mk                                  
```
