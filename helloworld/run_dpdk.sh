echo 1024 | tee /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages
mount -t hugetlbfs nodev /mnt/huge
export RTE_SDK=/home/sungho/dpdk
