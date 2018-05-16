sudo git pull origin master
wait
sudo make
wait
sudo gcc daemon-interface.c -o daemon-interface

echo ./seastar-daemon --server "10.218.111.252:1234" --smp 1
echo ./seastar-daemon --server "10.218.104.170:1234" --smp 1
echo "\n"
# sudo ./seastar-daemon  --dpdk-pmd  --dpdk-port-index 1  --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.253  --server "10.218.111.254:1234" --smp 1
# sudo ./seastar-daemon  --dpdk-pmd  --dpdk-port-index 1  --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.254  --server "10.218.111.253:1234" --smp 1

# sudo ./tcp_test --dpdk-pmd  --dpdk-port-index 1  --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.253  --server "10.218.111.254:1234" --smp 1
# sudo ./tcp_test  --dpdk-pmd  --dpdk-port-index 1  --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.254  --server "10.218.111.253:1234" --smp 1
