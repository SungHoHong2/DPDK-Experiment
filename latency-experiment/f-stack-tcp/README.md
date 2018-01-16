### RUNNING F-STACK in VISASU

```
export FF_PATH=/data1/sungho/visa-fstack/
export FF_DPDK=/data1/sungho/visa-fstack/dpdk/x86_64-native-linuxapp-gcc
make

// change the core numbers in fstack (binary to hexadecimal)
./start.sh -b ./fstack-server -c config_server.ini
./start.sh -b ./tcp-server -c config_server.ini
```

```
./wrk -t2 -c2 -d10s http://10.218.111.252
```
