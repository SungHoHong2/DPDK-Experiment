sudo git pull origin master
wait
sudo make
wait
sudo gcc daemon-interface.c -o daemon-interface

echo ./seastar-daemon --server "10.218.111.252:1234" --smp 1
echo ./seastar-daemon --server "10.218.104.170:1234" --smp 1
echo "\n"
echo ./seastar-daemon  --dpdk-pmd --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.253 --netmask-ipv4-addr 255.255.248.0 --gw-ipv4-addr 10.218.111.1 --collectd 0 --server "10.218.111.254:1234" --smp 1
echo ./seastar-daemon  --dpdk-pmd --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.254 --netmask-ipv4-addr 255.255.248.0 --gw-ipv4-addr 10.218.111.1 --collectd 0 --server "10.218.111.253:1234" --smp 1
