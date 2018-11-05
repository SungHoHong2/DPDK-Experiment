#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>
#include <string.h>
#include <sys/queue.h>
#include <stdarg.h>
#include <errno.h>
#include <getopt.h>
#include <signal.h>
#include <stdbool.h>

#include <rte_common.h>
#include <rte_vect.h>
#include <rte_byteorder.h>
#include <rte_log.h>
#include <rte_memory.h>
#include <rte_memcpy.h>
#include <rte_eal.h>
#include <rte_launch.h>
#include <rte_atomic.h>
#include <rte_cycles.h>
#include <rte_prefetch.h>
#include <rte_lcore.h>
#include <rte_per_lcore.h>
#include <rte_branch_prediction.h>
#include <rte_interrupts.h>
#include <rte_random.h>
#include <rte_debug.h>
#include <rte_ether.h>
#include <rte_ethdev.h>
#include <rte_mempool.h>
#include <rte_mbuf.h>
#include <rte_malloc.h>
#include <rte_ip.h>
#include <rte_tcp.h>
#include <rte_udp.h>
#include <rte_string_fns.h>
#include <rte_cpuflags.h>
#include <rte_ip.h>
#include <rte_tcp.h>
#include <rte_udp.h>
#include <rte_lpm.h>
#include <rte_lpm6.h>
#include <rte_ip_frag.h>

#include <cmdline_parse.h>
#include <cmdline_parse_etheraddr.h>

#include "pkt_size.h"
#include "test_packet.h"
#include "l3fwd.h"
#include "dpdk_common.h"
#include "dpdk_init.h"
#include "dpdk_func.h"



int lpm_main_loop(__attribute__((unused)) void *dummy)
{
	unsigned lcore_id = rte_lcore_id();

	if(lcore_id<=tx_rte){
		 printf("lcore[%u] works for the tx_loop\n", lcore_id);
		 tx_loop(lcore_id+tx_rte);
	}else if(lcore_id<=rx_rte){
		printf("lcore[%u] works for the rx_loop\n", lcore_id);
		rx_loop();
	}
	return 0;
}


int main(int argc, char **argv)
{
	int ret;
	unsigned portid, nb_ports;
	unsigned lcore_id;

	tx_rte = 4;
	rx_rte = 8;

	pthread_mutex_init(&dpdk_mutex, NULL);

	dpdk_init();

	ret = 0;
	/* launch per-lcore init on every lcore */
	rte_eal_mp_remote_launch(lpm_main_loop, NULL, CALL_MASTER);
	RTE_LCORE_FOREACH_SLAVE(lcore_id) {
		if (rte_eal_wait_lcore(lcore_id) < 0) {
			ret = -1;
			break;
		}
	}

	nb_ports = rte_eth_dev_count();

	/* stop ports */
	for (portid = 0; portid < nb_ports; portid++) {
		if ((enabled_port_mask & (1 << portid)) == 0)
			continue;
		printf("Closing port %d...", portid);
		rte_eth_dev_stop(portid);
		rte_eth_dev_close(portid);
		printf(" Done\n");
	}
	printf("Bye...\n");

	return ret;
}
