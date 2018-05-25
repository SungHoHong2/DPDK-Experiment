if [ "$2" = "traditional" ]
then
memcached -u sungho -m 12000 -p 11211 -t $3

elif [ "$2" = "seastar" ]
then
/data1/sungho/seastar/build/release/apps/memcached/memcached --dpdk-pmd --dpdk-port-index 1 --network-stack native --dhcp 0 --host-ipv4-addr 10.107.30.40 --netmask-ipv4-addr 255.255.254.0 --gw-ipv4-addr 10.107.30.1 --collectd 0 --smp $3
if
