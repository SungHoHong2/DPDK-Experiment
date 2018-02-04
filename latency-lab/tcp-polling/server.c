#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS     5

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{

/home/users/sungho/MLNX_OFED_SRC-4.2-1.2.0.0/
  // add argument smp with number
  // allocate the pthread by pointers

   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   for(t=0; t<NUM_THREADS; t++){
      printf("In main: creating thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
    if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }
   pthread_exit(NULL);

   return 0;
}



./configure --prefix=/home/users/sungho/libvma/usr 4 --includedir=/home/users/sungho/libvma/usr/include/mellanox --sysconfdir=/home/users/sungho/libvma/etc


============================================================================
== Configure project
============================================================================
checking for gcov support... no
checking for time measurement support... no
checking for valgrind support... no
checking for OFED path... /home/users/sungho/libvma/usr
checking infiniband/verbs.h usability... no
checking infiniband/verbs.h presence... yes
configure: WARNING: infiniband/verbs.h: present but cannot be compiled
configure: WARNING: infiniband/verbs.h:     check for missing prerequisite headers?
configure: WARNING: infiniband/verbs.h: see the Autoconf documentation
configure: WARNING: infiniband/verbs.h:     section "Present But Cannot Be Compiled"
configure: WARNING: infiniband/verbs.h: proceeding with the compiler's result
configure: WARNING:     ## ----------------------------------- ##
configure: WARNING:     ## Report this to support@mellanox.com ##
configure: WARNING:     ## ----------------------------------- ##
checking for infiniband/verbs.h... no
configure: error: Unable to find the libibverbs-devel header files
sungho@c1n14:~/libvma$ ./configure
checking for a BSD-compatible install... /usr/bin/install -c
checking whether build environment is sane... yes
checking for a thread-safe mkdir -p... /bin/mkdir -p
checking for gawk... gawk
checking whether make sets $(MAKE)... yes
checking whether make supports nested variables... yes
checking whether make supports nested variables... (cached) yes
============================================================================


============================================================================
== Configure project
============================================================================
checking for gcov support... no
checking for time measurement support... no
checking for valgrind support... no
checking for OFED path... /usr
checking infiniband/verbs.h usability... yes
checking infiniband/verbs.h presence... yes
checking for infiniband/verbs.h... yes
checking rdma/rdma_cma.h usability... yes
checking rdma/rdma_cma.h presence... yes
checking for rdma/rdma_cma.h... yes
checking for ibv_get_device_list in -libverbs... yes
checking for rdma_create_id in -lrdmacm... yes
checking for Mellanox OFED verbs (2.1 and older)... no
checking for infiniband/mlx5_hw.h... yes
checking for struct mlx5_qp.ctrl_seg... yes
checking for struct mlx5_qp.gen_data... yes
checking for attribute IBV_EXP_CQ_TIMESTAMP... yes
checking for attribute IBV_EXP_VALUES_CLOCK_INFO... yes
checking for attribute IBV_EXP_DEVICE_RX_CSUM_L4_PKT... no
checking for attribute IBV_EXP_DEVICE_RX_CSUM_TCP_UDP_PKT... yes
checking for attribute IBV_EXP_FLOW_SPEC_ACTION_TAG... yes
checking for attribute IBV_QPT_RAW_PACKET... yes
checking for attribute IBV_WC_WITH_VLAN... no
checking for attribute IBV_ACCESS_ALLOCATE_MR... no
checking for attribute IBV_FLOW_SPEC_IB... no
checking for attribute IBV_DEVICE_RAW_IP_CSUM... no
checking for attribute IBV_SEND_IP_CSUM... no
checking for attribute IBV_EXP_CQ_MODERATION... yes
checking for attribute IBV_EXP_WR_NOP... yes
checking for attribute IBV_EXP_ACCESS_ALLOCATE_MR... yes
checking for attribute IBV_EXP_QP_INIT_ATTR_ASSOCIATED_QPN... yes
