### RUNNING F-STACK in WORKSTATION LAB

```
export FF_PATH=/data/visa-fstack/
export FF_DPDK=/data/visa-fstack/dpdk/x86_64-native-linuxapp-gcc
make

// change the core numbers in fstack (binary to hexadecimal)
sudo ./start.sh -b ./fstack-server -c config_server.ini
sudo ./start.sh -b ./tcp-server -c config_server.ini
```

```
# prove
wget -qO- http://10.218.111.254 | sed -e 's/<[^>]*>//g'

# benchmark
./wrk -t2 -c2 -d10s 10.218.111.254
./wrk -t4 -c4 -d10s 10.218.111.254
./wrk -t8 -c8 -d10s 10.218.111.254
./wrk -t16 -c16 -d10s 10.218.111.254
./wrk -t32 -c32 -d10s 10.218.111.254
./wrk -t64 -c64 -d10s 10.218.111.254

```
