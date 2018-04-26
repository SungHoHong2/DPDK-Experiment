sudo modprobe uio
sudo insmod build/kmod/igb_uio.ko
sudo insmod build/kmod/rte_kni.ko

echo 1048576 | sudo tee /sys/kernel/mm/hugepages/hugepages-1048576kB/nr_hugepages
echo 512 > /proc/sys/vm/nr_hugepages

echo 1024 | sudo tee /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages

# sudo mkdir /mnt/huge
sudo mount -t hugetlbfs nodev /mnt/huge
sudo umount /mnt/huge


sudo ifconfig enp4s0f0 down
sudo ifconfig enp4s0f1 down

sudo ifconfig enp4s0f2 down
sudo ifconfig enp4s0f3 down
wait
sudo ./usertools/dpdk-devbind.py --bind=igb_uio enp4s0f0
sudo ./usertools/dpdk-devbind.py --bind=igb_uio enp4s0f1

sudo ./usertools/dpdk-devbind.py --bind=igb_uio enp4s0f2
sudo ./usertools/dpdk-devbind.py --bind=igb_uio enp4s0f3

# re-installing DPDK
rm -rf /usr/local/lib/rte_*
rm -rf /usr/local/include/dpdk


# ceph-dpdk - this part is highly stable in the workstation for visa
export RTE_SDK=/home/sungho/ceph-12.2.0/src/dpdk-17
export DESTDIR=/usr/local
export RTE_TARGET=x86_64-native-linuxapp-gcc

# local
export RTE_SDK=/home/sungho/dpdk-stable-17.05.2
export DESTDIR=/usr/local
export RTE_TARGET=x86_64-native-linuxapp-gcc



./app/x86_64-native-linuxapp-gcc/pktgen -l 0-4 -n 3 -- -P -m "[1:3].0, [2:4].1"
