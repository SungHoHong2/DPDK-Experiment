# SEASTAR ="/home/sungho/seastar"
SEASTAR ="/data1/sungho/seastar"
TARGET ="server"

all:
	g++-5  `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc`
		${TARGET}.cc
		${SEASTAR}/build/release/net/proxy.cc
		${SEASTAR}/build/release/net/virtio.cc
		${SEASTAR}/build/release/net/dpdk.cc
		${SEASTAR}/build/release/net/ip.cc
		${SEASTAR}/build/release/net/ethernet.cc
		${SEASTAR}/build/release/net/arp.cc
		${SEASTAR}/build/release/net/native-stack.cc
		${SEASTAR}/build/release/net/ip_checksum.cc
		${SEASTAR}/build/release/net/udp.cc
		${SEASTAR}/build/release/net/tcp.cc
		${SEASTAR}/build/release/net/dhcp.cc
		${SEASTAR}/build/release/net/tls.cc
		${SEASTAR}/build/release/net/dns.cc
		${SEASTAR}/build/release/net/config.cc
		 -o ${TARGET}

#
#
# core/reactor.cc',
# core/systemwide_memory_barrier.cc',
# core/fstream.cc',
# core/posix.cc',
# core/memory.cc',
# core/resource.cc',
# core/scollectd.cc',
# core/metrics.cc',
# core/app-template.cc',
# core/thread.cc',
# core/dpdk_rte.cc',
# core/fsqual.cc',
# core/linux-aio.cc',
# util/conversions.cc',
# util/program-options.cc',
# util/log.cc',
# util/backtrace.cc',
# util/alloc_failure_injector.cc',
# net/packet.cc',
# net/posix-stack.cc',
# net/net.cc',
# net/stack.cc',
# net/inet_address.cc',
# rpc/rpc.cc',
# rpc/lz4_compressor.cc',
# core/exception_hacks.cc',
# core/future-util.cc',
#
#
# http = ['http/transformers.cc',
#         'http/json_path.cc',
#         'http/file_handler.cc',
#         'http/common.cc',
#         'http/routes.cc',
#         'json/json_elements.cc',
#         'json/formatter.cc',
#         'http/matcher.cc',
#         'http/mime_types.cc',
#         'http/httpd.cc',
#         'http/reply.cc',
#         'http/request_parser.rl',
#         'http/api_docs.cc'


.PHONY: clean
clean:
	rm -f *.o ${TARGET}
