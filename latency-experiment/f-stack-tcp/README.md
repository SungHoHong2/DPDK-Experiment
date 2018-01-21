### RUNNING F-STACK in VISASU

```
export FF_PATH=/data1/sungho/visa-fstack/
export FF_DPDK=/data1/sungho/visa-fstack/dpdk/x86_64-native-linuxapp-gcc
make

// change the core numbers in fstack (binary to hexadecimal)
sudo ./start.sh -b ./fstack-server -c config_server.ini
sudo ./start.sh -b ./tcp-server -c config_server.ini
```

```
# prove
wget -qO- http://10.107.30.40:10000 | sed -e 's/<[^>]*>//g'

# benchmark
./wrk -t2 -c2 -d10s http://10.107.30.40:10000
./wrk -t8 -c8 -d10s http://10.107.30.40:10000
./wrk -t2 -c2 -d10s http://10.218.111.253


```
