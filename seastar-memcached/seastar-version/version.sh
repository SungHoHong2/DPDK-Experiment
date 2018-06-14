FILENAME=1_memcached

if [ "$1" = "update" ]
then
cp memcached.cc history/$FILENAME.cc

elif [ "$1" = "recover" ]
then
cp history/$FILENAME.cc memcached.cc

fi
