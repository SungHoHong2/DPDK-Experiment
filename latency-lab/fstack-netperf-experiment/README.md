```
export FF_PATH=/data/f-stack
export FF_DPDK=/data/f-stack/dpdk/x86_64-native-linuxapp-gcc

export RTE_SDK=/data/f-stack/dpdk
export DESTDIR=/usr/local
export RTE_TARGET=x86_64-native-linuxapp-gcc



./server --conf config_server.ini --proc-type=primary --proc-id=0

```
