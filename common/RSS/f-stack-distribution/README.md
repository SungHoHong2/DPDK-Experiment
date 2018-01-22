```
export FF_PATH=/data1/sungho/visa-fstack/
export FF_DPDK=/data1/sungho/visa-fstack/dpdk/x86_64-native-linuxapp-gcc
make
sudo ./start.sh -b ./fstack-server -c config_server.ini
./wrk -t2 -c2 -d1s http://10.107.30.40:10000
```

```


```
