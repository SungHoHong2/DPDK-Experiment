git add .
git commit -m 'updated for DPDK-Experiments'
git push origin master
wait

ip addr add 10.10.10.10/24 dev veth1 
