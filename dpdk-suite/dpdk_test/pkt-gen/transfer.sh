git pull origin master
wait
cp throughput.lua /home/sungho/pktgen-3.4.2/throughput.lua
cd /home/sungho/pktgen-3.4.2
/app/x86_64-native-linuxapp-gcc/pktgen -l 0-4 -n 3 -- -P -m "[2:2].1" -f throughput.lua
