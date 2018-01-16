### RUNNING F-STACK in VISASU

```
export FF_PATH=/data1/sungho/visa-fstack/
export FF_DPDK=/data1/sungho/visa-fstack/dpdk/x86_64-native-linuxapp-gcc
make

sudo ./fstack-server --conf config_server.ini --proc-type=primary --proc-id=0

./start.sh -b ./fstack-server -c config_server.ini

./tcp-server
```


```
./wrk -t2 -c2 -d10s http://10.218.111.252
```
