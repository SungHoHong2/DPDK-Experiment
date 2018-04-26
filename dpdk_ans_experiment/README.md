### DPDK ANS

**installation**
```
export RTE_ANS=/home/sungho/dpdk-ans
./install_deps.sh
cd ans
make
```

**installation for server**
```
# install dpdk
CONFIG_RTE_LIBRTE_KNI=y
CONFIG_RTE_LIBRTE_PMD_PCAP=y
CONFIG_RTE_LIBRTE_MLX4_PMD=y

git clone https://github.com/ansyun/dpdk-ans.git

make config T=x86_64-native-linuxapp-gcc
make
make install T=x86_64-native-linuxapp-gcc DESTDIR=/data1/sungho/usr/local

# correct install-dependency to run with gcc-5
export RTE_ANS=/data1/sungho/dpdk-ans
export RTE_SDK=/data1/sungho/dpdk-stable-17.05.1

sudo apt-get install gcc-5
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 100
sudo update-alternatives --config gcc

sudo apt-get install binutils-2.26
sudo update-alternatives --install /usr/bin/ld ld /usr/bin/ld-2.26 100

```


**run file**
```
config=(port, rx, core)
# core 1
sudo ./build/ans -c 0x4 -n 1 --base-virtaddr=0x2aaa2aa0000 -- -p 0x2 --config="(1,0,2)" --enable-kni --enable-ipsync                       


sudo ./build/ans -c 0x2 -n 1 --base-virtaddr=0x2aaa2aa0000 -- -p 0x2 --config="(1,0,1)" --enable-kni --enable-ipsync                       

# core 2
sudo ./build/ans -c 0x6 --base-virtaddr=0x2aaa2aa0000 -- -p 0x2 --config="(1,0,1),(1,1,2)" --enable-kni --enable-ipsync                       

# core 4
sudo ./build/ans -c 0x1E -n 8 --base-virtaddr=0x2aaa2aa0000 -- -p 0x2 --config="(1,0,1),(1,1,2),(1,2,3),(1,3,4)" --enable-kni --enable-ipsync            



sudo ip addr add 10.218.104.160 dev veth1
sudo ifconfig veth1 up
sudo ip addr add 10.218.104.161 dev veth1
sudo ifconfig veth1 up


mpirun -np 2 --hostfile hosts_posix ./IMB-MPI1 PingPong
mpirun -np 2 --hostfile hosts_dpdk ./IMB-MPI1 PingPong

mpirun -np 2 --hostfile hosts_posix ./IMB-MPI1 PingPong
mpirun -np 2 --hostfile hosts_dpdk ./IMB-MPI1 PingPong


10.218.111.252
10.218.104.170

```


**run file in server**
```
cp ans /data1/sungho/DPDK-Experiment/seastar-experiment/seastar-server/server
sudo ./server -c 0x2 -n 1 --base-virtaddr=0x2aaa2aa0000 -- -p 0x2 --config="(1,0,1)" --enable-kni --enable-ipsync                       


ip addr add 10.107.30.40 dev veth1
ip addr add 10.107.30.40/24 dev veth1

ip addr add 10.107.30.41 dev veth1

mpirun -np 2 --hostfile hosts_example ./IMB-MPI1 PingPong
mpirun -np 2 --hostfile dpdk_example ./IMB-MPI1 PingPong

```
