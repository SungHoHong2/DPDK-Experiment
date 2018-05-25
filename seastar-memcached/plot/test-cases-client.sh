cd /data1/sungho/libmemcached-1.0.18/clients

if [ "$1" = "traditional" ]
then
./memaslap -s 10.107.30.33:11211 -T $2 -S 1s -t 10s | grep "Run time: 10.0s\|   Avg:"

elif [ "$1" = "seastar" ]
then
./memaslap -s 10.107.30.40:11211 -T $2 -S 1s -t 10s | grep "Run time: 10.0s\|   Avg:"
fi
