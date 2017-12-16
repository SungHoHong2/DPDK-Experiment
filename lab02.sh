sudo modprobe uio
sudo insmod build/kmod/igb_uio.ko
sudo insmod build/kmod/rte_kni.ko

echo 1048576 | sudo tee /sys/kernel/mm/hugepages/hugepages-1048576kB/nr_hugepages
echo 512 > /proc/sys/vm/nr_hugepages

# sudo mkdir /mnt/huge
sudo mount -t hugetlbfs nodev /mnt/huge
sudo umount /mnt/huge

ip link show enp4s0f0
ip link show enp4s0f1
ip link set enp4s0f0 mtu 9000
ip link set enp4s0f1 mtu 9000

sudo ifconfig enp4s0f0 down
sudo ifconfig enp4s0f1 down
wait
sudo ./usertools/dpdk-devbind.py --bind=igb_uio enp4s0f0
sudo ./usertools/dpdk-devbind.py --bind=igb_uio enp4s0f1


# ceph-dpdk
export RTE_SDK=/home/sungho/ceph-12.2.0/src/dpdk-17
export DESTDIR=/usr/local
export RTE_TARGET=x86_64-native-linuxapp-gcc

export RTE_SDK=/home/sungho/dpdk-stable-17.05.2
export DESTDIR=/usr/local
export RTE_TARGET=x86_64-native-linuxapp-gcc


./app/x86_64-native-linuxapp-gcc/pktgen -l 0-4 -n 3 -- -P -m "[1:3].0, [2:4].1"
