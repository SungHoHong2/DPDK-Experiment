### F-STACK

**installing F-stack**
```
# Install from github
git clone https://github.com/F-Stack/f-stack.git /data/f-stack

# Compile F-Stack
export FF_PATH=/home/sungho/f-stack
export FF_DPDK=/home/sungho/f-stack/dpdk/x86_64-native-linuxapp-gcc

export RTE_SDK=/data/f-stack/dpdk
export DESTDIR=/usr/local
export RTE_TARGET=x86_64-native-linuxapp-gcc


# Compile F-Stack [visasu]
export FF_PATH=/data1/sungho/visa-fstack/
export FF_DPDK=/data1/sungho/visa-fstack/dpdk/x86_64-native-linuxapp-gcc

export RTE_SDK=/data1/sungho/visa-fstack/dpdk
export DESTDIR=/usr/local
export RTE_TARGET=x86_64-native-linuxapp-gcc


# install gwak
sudo apt-get install gawk

# Running the F-Stack
./start.sh -b example/helloworld -c config.ini
./start.sh -b example/helloworld_epoll -c config.ini

# running in [visasu]
./example. ./helloworld  --conf config.ini --proc-type=primary --proc-id=0

# the ip address needs to be within the broadcast []
wget -qO- http://10.218.111.253 | sed -e 's/<[^>]*>//g'
wget -qO- http://10.107.30.33:8888 | sed -e 's/<[^>]*>//g'
wget -qO- http://10.107.30.102 | sed -e 's/<[^>]*>//g'
```

<br>

**[implementing f-stack-tcp](f-stack-tcp)**
```
cd f-stack-tcp
sudo ./fstack-server --conf config_server.ini --proc-type=primary --proc-id=0
sudo ./fstack-client --conf config_client.ini --proc-type=primary --proc-id=0

./tcp-server
./tcp-client
```


<br>

**testing f-stack with wrk benchmark**
- [test results from visasu](results/visasu-result.md)
- [test results from fiu](results/fiu-result.md)

```
./wrk -t12 -c400 -d30s http://10.218.111.252
./wrk -t12 -c400 -d1s http://10.218.111.252

./wrk -t12 -c400 -d1s http://10.107.30.102
./wrk -t12 -c400 -d1s http://10.107.30.33:8888

wget -qO- http://10.107.30.102 | sed -e 's/<[^>]*>//g'
```


<br>


- **CPU affinity**
```
1 = Processor 1 (CPU-0)
10 = Processor 2 (CPU-1)
100 = Processor 3
100000000000 = Processor 12
110 = 2 and 3 only
101010101010 = 12, 10, 8, 6, 4, 2 only
```
