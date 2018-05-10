
```
# pktgen
./app/x86_64-native-linuxapp-gcc/pktgen -l 0-4 -n 3 -- -P -m "[2:4].1"
set 0 dst mac 00:1B:21:A6:D4:D5

./build/l2fwd -l 0-3 -n 4 -- -q 8 -p 0x2 -T 1
```
