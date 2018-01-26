```
export FF_PATH=/data1/sungho/visa-fstack/
export FF_DPDK=/data1/sungho/visa-fstack/dpdk/x86_64-native-linuxapp-gcc
make
sudo ./start.sh -b ./fstack-server -c config_server.ini
./wrk -t2 -c2 -d1s http://10.107.30.40:10000


sudo ./fstack-server --conf=config_server.ini --proc-type=primary --proc-id=0
sudo ./fstack-server --conf=config_server.ini --proc-type=secondary --proc-id=1

```

```
vi /etc/network/interfaces
```
