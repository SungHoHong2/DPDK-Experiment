FILENAME=1_memaslap

if [ "$1" = "memcached_update" ]
then
cp memcached.cc history/$FILENAME.cc

elif [ "$1" = "memcached_recover" ]
then
cp history/$FILENAME.cc memcached.cc

elif [ "$1" = "memaslap_update" ]
then
mkdir history/$FILENAME
cp memaslap/io.cc history/$FILENAME/io.cc
cp memaslap/memaslap.c history/$FILENAME/memaslap.c

elif [ "$1" = "memaslap_recover" ]
then
cp history/$FILENAME/io.cc io.cc
cp history/$FILENAME/memaslap.c memaslap.c

fi
