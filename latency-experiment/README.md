### INSTALLING F-SHARK
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


### running IMB-benchmark
```
mpirun -np 2 --hostfile hosts_example ./IMB-MPI1 pingpong
```

eno1: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500                     
        inet 10.218.111.252  netmask 255.255.248.0  broadcast 10.218.111.255   
        inet6 fe80::b30a:eb7d:2e84:8f6d  prefixlen 64  scopeid 0x20<link>      
        ether 64:00:6a:5a:21:5b  txqueuelen 1000  (Ethernet)                   
        RX packets 1560592  bytes 280894156 (280.8 MB)                         
        RX errors 0  dropped 0  overruns 0  frame 0                            
        TX packets 9647  bytes 1627556 (1.6 MB)                                
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0             
        device interrupt 20  memory 0xf7d00000-f7d20000                        
