FILENAME=10_memaslap_lite

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
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/libmemcached/io.cc      memaslap/io.cc
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/memaslap.c      memaslap/memaslap.c
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_thread.c     memaslap/ms_thread.c
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/libmemcached/io.cc      memaslap/io.cc
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_task.c       memaslap/ms_task.c
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/memcapable.cc   memaslap/memcapable.cc
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_conn.c       memaslap/ms_conn.c

cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/include.am      memaslap/include.am
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/configure               memaslap/configure
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/Makefile.in             memaslap/Makefile.in
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/Makefile.am             memaslap/Makefile.am
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/Makefile                memaslap/Makefile


cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/memaslap.cc     memaslap/memaslap.cc
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_conn.cc      memaslap/ms_conn.cc
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_setting.cc   memaslap/ms_setting.cc
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_sigsegv.cc   memaslap/ms_sigsegv.cc
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_stats.cc     memaslap/ms_stats.cc
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_task.cc      memaslap/ms_task.cc
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_thread.cc    memaslap/ms_thread.cc
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/memaslap.c      memaslap/memaslap.c
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_conn.c       memaslap/ms_conn.c
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_setting.c    memaslap/ms_setting.c
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_sigsegv.c    memaslap/ms_sigsegv.c
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_stats.c      memaslap/ms_stats.c
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_task.c       memaslap/ms_task.c
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_thread.c     memaslap/ms_thread.c
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/protocol_binary.h    memaslap/protocol_binary.h
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/vbucket.h       memaslap/vbucket.h
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients/ms_conn.h       memaslap/ms_conn.h


cp -a memaslap history/$FILENAME
git add .
git commit -m 'memaslap experiments'
git push origin master


# ./version.sh memaslap_lite_import
elif [ "$1" = "memaslap_lite_import" ]
then
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients_lite/make.sh        memaslap_lite/
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients_lite/memaslap.cc    memaslap_lite/
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients_lite/ms_conn.cc     memaslap_lite/
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients_lite/ms_setting.cc  memaslap_lite/
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients_lite/ms_sigsegv.cc  memaslap_lite/
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients_lite/ms_stats.cc    memaslap_lite/
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients_lite/ms_task.cc     memaslap_lite/
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients_lite/ms_thread.cc   memaslap_lite/
cp /Users/sunghohong/Documents/Projects/libmemcached-1.0.18/clients_lite/ms_memslap.h   memaslap_lite/

rm -rf history/$FILENAME && cp -a memaslap_lite history/$FILENAME
git add .
git commit -m 'memaslap_lite experiments'
git push origin master

fi
