### F-SHARK

- **installing F-SHARK**
```
# Install from github
git clone https://github.com/F-Stack/f-stack.git /data/f-stack

# Compile F-Stack
export FF_PATH=/data/f-stack
export FF_DPDK=/data/f-stack/dpdk/x86_64-native-linuxapp-gcc

# Running the F-Stack
./start.sh -b example/helloworld -c config.ini
./start.sh -b example/helloworld_epoll -c config.ini


# the ip address needs to be within the broadcast []
wget -qO- http://10.218.111.253 | sed -e 's/<[^>]*>//g'
```

<br>

- [implementing f-stack-tcp](f-stack-tcp)
```
cd f-stack-tcp
./server --conf config_server.ini --proc-type=primary --proc-id=0
./client --conf config_client.ini --proc-type=primary --proc-id=1

```
