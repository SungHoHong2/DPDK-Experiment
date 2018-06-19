#  sudocmd seastar_memcached_exp
cd /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version
HOST_NAME=$(cat /etc/hostname)
TARGET=memcached

echo "github update check"
git pull origin master


echo "compiling memcached in" $HOST_NAME

if [ "$HOST_NAME" = "c3n24" ]
then
   if [ "$1" = "make" ]
   then
 g++-5 -std=gnu++1y -g -Wall -Werror -Wno-error=deprecated-declarations -fvisibility=hidden -pthread -U_FORTIFY_SOURCE -DHAVE_DPDK -march=native -DRTE_MACHINE_CPUFLAG_SSE -DRTE_MACHINE_CPUFLAG_SSE2 -DRTE_MACHINE_CPUFLAG_SSE3 -DRTE_MACHINE_CPUFLAG_SSSE3 -DRTE_MACHINE_CPUFLAG_SSE4_1 -DRTE_MACHINE_CPUFLAG_SSE4_2 -DRTE_MACHINE_CPUFLAG_AES -DRTE_MACHINE_CPUFLAG_PCLMULQDQ -DRTE_MACHINE_CPUFLAG_AVX -DRTE_MACHINE_CPUFLAG_RDRAND -DRTE_MACHINE_CPUFLAG_FSGSBASE -DRTE_MACHINE_CPUFLAG_F16C -DRTE_MACHINE_CPUFLAG_AVX2 -Wno-error=literal-suffix -Wno-literal-suffix -Wno-invalid-offsetof -DBOOST_TEST_DYN_LINK -Wno-overloaded-virtual -Wno-maybe-uninitialized -Wno-sign-compare -Wno-error=cpp -DFMT_HEADER_ONLY -DHAVE_HWLOC -DHAVE_NUMA -O2 -I/data1/sungho/seastar -I/data1/sungho/seastar/build/dpdk/include -I/data1/sungho/seastar/fmt -I/data1/sungho/seastar/build/release/gen -I/data1/sungho/seastar/build/release/c-ares  -Wl,--whole-archive,-lseastar -lrte_pmd_mlx4 -libverbs -Wl,--no-whole-archive -std=gnu++1y -g -Wall -Werror -Wno-error=deprecated-declarations -fvisibility=hidden -pthread -I/data1/sungho/seastar -U_FORTIFY_SOURCE -DHAVE_DPDK -I/data1/sungho/seastar/build/dpdk/include -march=native -DRTE_MACHINE_CPUFLAG_SSE -DRTE_MACHINE_CPUFLAG_SSE2 -DRTE_MACHINE_CPUFLAG_SSE3 -DRTE_MACHINE_CPUFLAG_SSSE3 -DRTE_MACHINE_CPUFLAG_SSE4_1 -DRTE_MACHINE_CPUFLAG_SSE4_2 -DRTE_MACHINE_CPUFLAG_AES -DRTE_MACHINE_CPUFLAG_PCLMULQDQ -DRTE_MACHINE_CPUFLAG_AVX -DRTE_MACHINE_CPUFLAG_RDRAND -DRTE_MACHINE_CPUFLAG_FSGSBASE -DRTE_MACHINE_CPUFLAG_F16C -DRTE_MACHINE_CPUFLAG_AVX2 -Wno-error=literal-suffix -Wno-literal-suffix -Wno-invalid-offsetof -I/data1/sungho/seastar/fmt -DBOOST_TEST_DYN_LINK -Wno-overloaded-virtual -Wno-maybe-uninitialized -Wno-sign-compare -Wno-error=cpp -DFMT_HEADER_ONLY -DHAVE_HWLOC -DHAVE_NUMA -Wl,--no-as-needed -Wl,--whole-archive  -Wl,--no-whole-archive -L/data1/sungho/seastar/build/release -L/data1/sungho/seastar/build/dpdk/lib -lboost_program_options -lboost_system -lboost_filesystem -lstdc++ -lboost_thread -lcryptopp -lgnutls -lgnutlsxx -llz4 -lprotobuf -lgcc_s -lunwind -lyaml-cpp -Wl,--whole-archive -lrte_pmd_vmxnet3_uio -lrte_pmd_i40e -lrte_pmd_ixgbe -lrte_pmd_e1000  -lrte_pmd_ring -lrte_pmd_bnxt -lrte_pmd_cxgbe -lrte_pmd_ena -lrte_pmd_enic -lrte_pmd_fm10k -lrte_pmd_nfp -lrte_pmd_qede -lrte_pmd_sfc_efx -lrte_hash -lrte_kvargs -lrte_mbuf -lrte_ethdev -lrte_eal -lrte_mempool -lrte_mempool_ring -lrte_ring -lrte_cmdline -lrte_cfgfile -Wl,--no-whole-archive -lrt -lm -ldl -lhwloc -lnuma -lpciaccess -lxml2 -lz -lcares-seastar $TARGET.cc -o $TARGET
rm -f *.o
   fi

/data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memcached --dpdk-pmd --dpdk-port-index 1 --network-stack native --dhcp 0 --host-ipv4-addr 10.107.30.40 --netmask-ipv4-addr 255.255.254.0 --gw-ipv4-addr 10.107.30.1 --collectd 0 --smp 1


# cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ /data1/sungho/libmemcached-1.0.18/
elif [ "$HOST_NAME" = "c3n25" ]
then
  if [ "$1" = "memaslap_make" ]
  then
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/io.cc /data1/sungho/libmemcached-1.0.18/libmemcached/io.cc
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/memaslap.c /data1/sungho/libmemcached-1.0.18/clients/memaslap.c
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ms_thread.c /data1/sungho/libmemcached-1.0.18/clients/ms_thread.c
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/io.cc /data1/sungho/libmemcached-1.0.18/libmemcached/io.cc
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ms_task.c /data1/sungho/libmemcached-1.0.18/clients/ms_task.c
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/memcapable.cc /data1/sungho/libmemcached-1.0.18/clients/memcapable.cc
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ms_conn.c /data1/sungho/libmemcached-1.0.18/clients/ms_conn.c
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/include.am /data1/sungho/libmemcached-1.0.18/clients/include.am
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/configure /data1/sungho/libmemcached-1.0.18/configure
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/Makefile.in /data1/sungho/libmemcached-1.0.18/Makefile.in
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/Makefile.am /data1/sungho/libmemcached-1.0.18/Makefile.am
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/Makefile /data1/sungho/libmemcached-1.0.18/Makefile
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/make.sh /data1/sungho/libmemcached-1.0.18/clients/make.sh
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/make.sh /data1/sungho/libmemcached-1.0.18/clients/make.sh
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/protocol_binary.h /data1/sungho/libmemcached-1.0.18/clients/protocol_binary.h
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/vbucket.h /data1/sungho/libmemcached-1.0.18/clients/vbucket.h


cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/memaslap.cc   /data1/sungho/libmemcached-1.0.18/clients/
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ms_conn.cc    /data1/sungho/libmemcached-1.0.18/clients/
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ms_setting.cc /data1/sungho/libmemcached-1.0.18/clients/
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ms_sigsegv.cc /data1/sungho/libmemcached-1.0.18/clients/
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ms_stats.cc   /data1/sungho/libmemcached-1.0.18/clients/
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ms_task.cc    /data1/sungho/libmemcached-1.0.18/clients/
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ms_thread.cc  /data1/sungho/libmemcached-1.0.18/clients/
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/memaslap.c   /data1/sungho/libmemcached-1.0.18/clients/
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ms_conn.c    /data1/sungho/libmemcached-1.0.18/clients/
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ms_setting.c /data1/sungho/libmemcached-1.0.18/clients/
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ms_sigsegv.c /data1/sungho/libmemcached-1.0.18/clients/
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ms_stats.c   /data1/sungho/libmemcached-1.0.18/clients/
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ms_task.c    /data1/sungho/libmemcached-1.0.18/clients/
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ms_thread.c  /data1/sungho/libmemcached-1.0.18/clients/
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap/ms_conn.h  /data1/sungho/libmemcached-1.0.18/clients/


cd /data1/sungho/libmemcached-1.0.18/
/data1/sungho/libmemcached-1.0.18/configure --enable-memaslap LDFLAGS=-lpthread --prefix=/data1/sungho/usr/local
# make -j 16 -n && sudo make install -j 16
rm -rf clients/*.o
make -j 16 -n && sudo make install -j 16


# sudocmd seastar_memcached_exp memaslap_lite_make
elif [ "$1" = "memaslap_lite_make" ]
then
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap_lite/make.sh          /data1/sungho/libmemcached-1.0.18/make.sh
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap_lite/memaslap.cc      /data1/sungho/libmemcached-1.0.18/clients/memaslap.cc
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap_lite/ms_conn.cc       /data1/sungho/libmemcached-1.0.18/clients/ms_conn.cc
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap_lite/ms_setting.cc    /data1/sungho/libmemcached-1.0.18/clients/ms_setting.cc
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap_lite/ms_sigsegv.cc    /data1/sungho/libmemcached-1.0.18/clients/ms_sigsegv.cc
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap_lite/ms_stats.cc      /data1/sungho/libmemcached-1.0.18/clients/ms_stats.cc
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap_lite/ms_task.cc       /data1/sungho/libmemcached-1.0.18/clients/ms_task.cc
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap_lite/ms_thread.cc     /data1/sungho/libmemcached-1.0.18/clients/ms_thread.cc
cp /data1/sungho/DPDK-Experiment/seastar-memcached/seastar-version/memaslap_lite/ms_memslap.h     /data1/sungho/libmemcached-1.0.18/clients/ms_memslap.h
fi

fi
