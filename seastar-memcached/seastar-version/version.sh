FILENAME=2_memcached

if [ "$1" = "memcached_update" ]
then
cp memcached.cc history/$FILENAME.cc

elif [ "$1" = "memcached_recover" ]
then
cp history/$FILENAME.cc memcached.cc

elif [ "$1" = "memaslap_update" ]
then
# cp memaslap/io.cc /data1/sungho/libmemcached-1.0.18/libmemcached/io.cc
# cp memaslap/memaslap.c /data1/sungho/libmemcached-1.0.18/clients/memaslap.c




fi
