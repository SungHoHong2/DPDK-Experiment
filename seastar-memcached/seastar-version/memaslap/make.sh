# git pull origin master
# cd /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/tcp-client
SOURCE_FILES="memaslap.c ms_conn.c ms_setting.c ms_sigsegv.c ms_stats.c ms_task.c ms_thread.c "


# export PATH=~/data1/sungho/usr/bin:$PATH

gcc -g -O2 -lm -ldl $SOURCE_FILES -o client -lpthread  -levent -lmemcached -lmemcachedutil
