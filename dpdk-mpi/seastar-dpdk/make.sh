sudo git pull origin master
wait
sudo make

# sudo ./seastar-daemon  --dpdk-pmd  --dpdk-port-index 1  --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.253  --server "10.218.111.254:1234" --smp 1
# sudo ./seastar-daemon  --dpdk-pmd  --dpdk-port-index 1  --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.254  --server "10.218.111.253:1234" --smp 1


# sudo ./client --dpdk-pmd  --dpdk-port-index 1  --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.253  --server "10.218.111.254:1234"
# sudo ./server  --dpdk-pmd  --dpdk-port-index 1  --network-stack native --dhcp 0 --host-ipv4-addr 10.218.111.254  --smp 1
