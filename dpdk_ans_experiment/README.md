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

sudo modprobe uio
sudo insmod /data1/sungho/dpdk-stable-17.05.1/build/kmod/rte_kni.ko

cp ans /data1/sungho/DPDK-Experiment/seastar-experiment/seastar-server/server
sudo ./server -c 0x2 -n 1 --base-virtaddr=0x2aaa2aa0000 -- -p 0x2 --config="(1,0,1)" --enable-kni --enable-ipsync                       


ip addr add 10.107.30.40 dev veth1
ip addr add 10.107.30.41 dev veth1

cd /data1/sungho/dpdk-stable-17.05.1
```




**run file**
```
sudo ./build/ans -c 0x2 -n 1 --base-virtaddr=0x2aaa2aa0000 -- -p 0x2 --config="(1,0,1)" --enable-kni --enable-ipsync                       

ip addr add 10.218.104.171 dev veth1
ip addr add 10.218.104.172 dev veth0


export PATH=/home/sungho/mpich/bin:$PATH
mpirun -np 2 --hostfile hosts_example ./IMB-MPI1 PingPong
```
