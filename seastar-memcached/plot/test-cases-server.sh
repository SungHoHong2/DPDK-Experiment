
if [ "$1" = "traditional" ]
then
memcached -u sungho -m 12000 -p 11211 -t $2

elif [ "$1" = "seastar" ]
then
/data1/sungho/seastar/build/release/apps/memcached/memcached --dpdk-pmd --dpdk-port-index 1 --network-stack native --dhcp 0 --host-ipv4-addr 10.107.30.40 --netmask-ipv4-addr 255.255.254.0 --gw-ipv4-addr 10.107.30.1 --collectd 0 --smp $2
fi
