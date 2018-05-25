cd /data1/sungho/libmemcached-1.0.18/clients
for i in 1 2 4 8
do
   ./memaslap -s 10.107.30.33:11211 -T 1 -S 1s -t 10s | grep "Run time: 10.0s\|   Avg:"
   wait
done
