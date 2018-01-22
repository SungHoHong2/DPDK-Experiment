```
export FF_PATH=/data1/sungho/visa-fstack/
export FF_DPDK=/data1/sungho/visa-fstack/dpdk/x86_64-native-linuxapp-gcc
make
sudo gdb --args ./fstack-server --conf config_server.ini --proc-type=primary --proc-id=0
break 112

```
