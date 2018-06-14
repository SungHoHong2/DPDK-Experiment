cd /data1/sungho/libmemcached-1.0.18/clients

# example
# sudocmd memcached_client traditional 1 avg
# sudocmd memcached_client traditional 1

if [ "$1" = "traditional" ]
then
    if [ "$3" = "avg" ]
    then
    ./memaslap -s 10.107.30.33:11211 -T $2 -S 1s -t 10s | grep "Run time: 10.0s\|   Avg:"
    else
    ./memaslap -s 10.107.30.33:11211 -T $2 -S 1s -t 10s
    fi

elif [ "$1" = "seastar" ]
then
    if [ "$3" = "avg" ]
    then
    ./memaslap -s 10.107.30.40:11211 -T $2 -S 1s -t 10s | grep "Run time: 10.0s\|   Avg:"
    else
    ./memaslap -s 10.107.30.40:11211 -T $2 -S 1s -t 10s
    fi
fi
