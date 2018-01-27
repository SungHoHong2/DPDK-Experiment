# SEASTAR ="/home/sungho/seastar"
# SEASTAR ="/data1/sungho/seastar"
SEASTAR ="/home/users/sungho/seastar"
TARGET ="dpdk_server"
# TARGET = "tcp_server"

all:
	# tcp server
	g++-5 -std=gnu++17 -g -Wall -Werror -Wno-error=deprecated-declarations -fvisibility=hidden -pthread -U_FORTIFY_SOURCE -DBOOST_TEST_DYN_LINK -Wno-overloaded-virtual -Wno-maybe-uninitialized -Wno-sign-compare -Wno-error=cpp -DFMT_HEADER_ONLY -DHAVE_HWLOC -DHAVE_NUMA -DHAVE_LZ4_COMPRESS_DEFAULT -O2 -I/home/users/sungho/seastar -I/home/users/sungho/seastar/fmt -I/home/users/sungho/seastar/build/release/gen -I/home/users/sungho/seastar/build/release/c-ares -L/home/users/sungho/seastar/build/release -Wl,--whole-archive,-lseastar,--no-whole-archive -std=gnu++17 -g -Wall -Werror -Wno-error=deprecated-declarations -fvisibility=hidden -pthread -I/home/users/sungho/seastar -U_FORTIFY_SOURCE -I/home/users/sungho/seastar/fmt -DBOOST_TEST_DYN_LINK -Wno-overloaded-virtual -Wno-maybe-uninitialized -Wno-sign-compare -Wno-error=cpp -DFMT_HEADER_ONLY -DHAVE_HWLOC -DHAVE_NUMA -DHAVE_LZ4_COMPRESS_DEFAULT -Wl,--no-as-needed -lboost_program_options -lboost_system -lboost_filesystem -lstdc++ -lm -lboost_thread -lcryptopp -lrt -lgnutls -lgnutlsxx -llz4 -lprotobuf -ldl -lgcc_s -lunwind -lyaml-cpp -lhwloc -lnuma -lpciaccess -lxml2 -lz -lcares-seastar ${TARGET}.cc -o ${TARGET}

	# dpdk server

.PHONY: clean
clean:
	rm -f *.o ${TARGET}
