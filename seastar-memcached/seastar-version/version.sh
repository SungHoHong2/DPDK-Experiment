FILENAME=3_memaslap

if [ "$1" = "memcached_update" ]
then
cp memcached.cc history/$FILENAME.cc

elif [ "$1" = "memcached_recover" ]
then
cp history/$FILENAME.cc memcached.cc

elif [ "$1" = "memaslap_recover" ]
then
cp history/$FILENAME/io.cc memaslap/io.cc
cp history/$FILENAME/memaslap.c memaslap/memaslap.c

elif [ "$1" = "memaslap_import" ]
then
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/libmemcached/io.cc memaslap/io.cc
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/memaslap.c memaslap/memaslap.c
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_thread.c memaslap/ms_thread.c
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/libmemcached/io.cc memaslap/io.cc
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_task.c memaslap/ms_task.c
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/memcapable.cc  memaslap/memcapable.cc


cp -a memaslap history/$FILENAME

git add .
git commit -m 'memaslap experiments'
git push origin master

fi
