### DPDK ANS

**installation**

```
export RTE_ANS=/home/sungho/dpdk-ans
./install_deps.sh
cd ans
make

```


**run file**

```
sudo ./build/ans -c 0x2 -n 1 --base-virtaddr=0x2aaa2aa0000 -- -p 0x1 --config="(0,0,1)" --enable-kni --enable-ipsync                       

ip addr add 10.218.104.171 dev veth0
ip addr add 10.218.104.172 dev veth0

export PATH=/home/sungho/mpich/bin:$PATH
mpirun -np 2 --hostfile hosts_example ./IMB-MPI1 PingPong
```
