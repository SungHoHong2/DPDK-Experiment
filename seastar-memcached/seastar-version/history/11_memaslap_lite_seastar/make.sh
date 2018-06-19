if [ "$1" = "memaslap_seastar" ]
then
depbase=`echo clients/memaslap.o | sed 's|[^/]*$|.deps/&|;s|\.o$||'`
g++-5 -std=gnu++1y -L/data1/sungho/seastar/build/release -L/data1/sungho/seastar/build/release/fmt/fmt -Wl,--whole-archive,-lseastar -lrte_pmd_mlx4 -libverbs -Wl,--no-whole-archive -lfmt -std=gnu++1y -g -fvisibility=hidden  -pthread -I/data1/sungho/seastar -U_FORTIFY_SOURCE  -DHAVE_DPDK -I/data1/sungho/seastar/build/dpdk/include -march=native -DRTE_MACHINE_CPUFLAG_SSE -DRTE_MACHINE_CPUFLAG_SSE2 -DRTE_MACHINE_CPUFLAG_SSE3 -DRTE_MACHINE_CPUFLAG_SSSE3 -DRTE_MACHINE_CPUFLAG_SSE4_1 -DRTE_MACHINE_CPUFLAG_SSE4_2 -DRTE_MACHINE_CPUFLAG_AES -DRTE_MACHINE_CPUFLAG_PCLMULQDQ -DRTE_MACHINE_CPUFLAG_AVX -DRTE_MACHINE_CPUFLAG_RDRAND -DRTE_MACHINE_CPUFLAG_FSGSBASE -DRTE_MACHINE_CPUFLAG_F16C -DRTE_MACHINE_CPUFLAG_AVX2 -Wno-error=literal-suffix -Wno-literal-suffix -Wno-invalid-offsetof -I/data1/sungho/seastar/fmt -DBOOST_TEST_DYN_LINK -Wno-overloaded-virtual -Wno-maybe-uninitialized -DHAVE_HWLOC -DHAVE_NUMA  -Wl,--no-as-needed -lboost_program_options -lboost_system -lboost_filesystem -lstdc++ -lm -lboost_thread -lcryptopp -lrt -lgnutls -lgnutlsxx -llz4 -lprotobuf -ldl -lgcc_s -lunwind  -lyaml-cpp -L/data1/sungho/seastar/build/dpdk/lib -Wl,--whole-archive -lrte_pmd_vmxnet3_uio -lrte_pmd_i40e -lrte_pmd_ixgbe -lrte_pmd_e1000 -lrte_pmd_ring -lrte_pmd_bnxt -lrte_pmd_cxgbe -lrte_pmd_ena -lrte_pmd_enic -lrte_pmd_fm10k -lrte_pmd_nfp -lrte_pmd_qede -lrte_pmd_sfc_efx -lrte_hash -lrte_kvargs -lrte_mbuf -lrte_ethdev -lrte_eal -lrte_mempool -lrte_mempool_ring -lrte_ring -lrte_cmdline -lrte_cfgfile -Wl,--no-whole-archive -lrt -lm -ldl -lhwloc -lnuma -lpciaccess -lxml2 -lz -lcares-seastar -lfmt -std=gnu++1y -g -fvisibility=hidden  -pthread -I/data1/sungho/seastar -U_FORTIFY_SOURCE  -DHAVE_DPDK -I/data1/sungho/seastar/build/dpdk/include -march=native -DRTE_MACHINE_CPUFLAG_SSE -DRTE_MACHINE_CPUFLAG_SSE2 -DRTE_MACHINE_CPUFLAG_SSE3 -DRTE_MACHINE_CPUFLAG_SSSE3 -DRTE_MACHINE_CPUFLAG_SSE4_1 -DRTE_MACHINE_CPUFLAG_SSE4_2 -DRTE_MACHINE_CPUFLAG_AES -DRTE_MACHINE_CPUFLAG_PCLMULQDQ -DRTE_MACHINE_CPUFLAG_AVX -DRTE_MACHINE_CPUFLAG_RDRAND -DRTE_MACHINE_CPUFLAG_FSGSBASE -DRTE_MACHINE_CPUFLAG_F16C -DRTE_MACHINE_CPUFLAG_AVX2 -Wno-error=literal-suffix -Wno-literal-suffix -Wno-invalid-offsetof -I/data1/sungho/seastar/fmt -DBOOST_TEST_DYN_LINK -Wno-overloaded-virtual -Wno-maybe-uninitialized -DHAVE_HWLOC -DHAVE_NUMA -O2  -I/data1/sungho/seastar/build/release/gen -I/data1/sungho/seastar/build/release/c-ares \
-DHAVE_CONFIG_H -I. -MT clients/memaslap.o -MD -MP -MF $depbase.Tpo -c -o clients/memaslap.o clients/memaslap.cc

elif [ "$1" = "memaslap_original" ]
then
depbase=`echo clients/memaslap.o | sed 's|[^/]*$|.deps/&|;s|\.o$||'`
echo $depbase
c++ -std=c++0x  -DHAVE_CONFIG_H -I. -fvisibility=hidden  -g -O2 -Wno-unknown-pragmas -Wno-pragmas -Wall -Wextra -Wno-attributes -Wvarargs -Waddress -Warray-bounds -Wchar-subscripts -Wcomment -Wctor-dtor-privacy -Wfloat-equal -Wformat=2 -Wformat-y2k -Wmaybe-uninitialized -Wmissing-field-initializers -Wlogical-op -Wnon-virtual-dtor -Wnormalized=id -Woverloaded-virtual -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-compare -Wstrict-overflow=1 -Wswitch-enum -Wtrampolines -Wundef -Wunsafe-loop-optimizations -funsafe-loop-optimizations -Wc++11-compat -Wclobbered -Wunused -Wunused-result -Wunused-variable -Wunused-parameter -Wunused-local-typedefs -Wwrite-strings -Wformat-security -fwrapv -pipe -fPIE -pie -Wsizeof-pointer-memaccess -Wpacked    -MT clients/memaslap.o -MD -MP -MF $depbase.Tpo -c -o clients/memaslap.o clients/memaslap.cc
mv -f $depbase.Tpo $depbase.Po

depbase=`echo clients/ms_conn.o | sed 's|[^/]*$|.deps/&|;s|\.o$||'`
c++ -std=c++0x   -DHAVE_CONFIG_H -I.  -fvisibility=hidden  -g -O2 -Wno-unknown-pragmas -Wno-pragmas -Wall -Wextra -Wno-attributes -Wvarargs -Waddress -Warray-bounds -Wchar-subscripts -Wcomment -Wctor-dtor-privacy -Wfloat-equal -Wformat=2 -Wformat-y2k -Wmaybe-uninitialized -Wmissing-field-initializers -Wlogical-op -Wnon-virtual-dtor -Wnormalized=id -Woverloaded-virtual -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-compare -Wstrict-overflow=1 -Wswitch-enum -Wtrampolines -Wundef -Wunsafe-loop-optimizations -funsafe-loop-optimizations -Wc++11-compat -Wclobbered -Wunused -Wunused-result -Wunused-variable -Wunused-parameter -Wunused-local-typedefs -Wwrite-strings -Wformat-security -fwrapv -pipe -fPIE -pie -Wsizeof-pointer-memaccess -Wpacked   -MT clients/ms_conn.o -MD -MP -MF $depbase.Tpo -c -o clients/ms_conn.o clients/ms_conn.cc
mv -f $depbase.Tpo $depbase.Po

depbase=`echo clients/ms_setting.o | sed 's|[^/]*$|.deps/&|;s|\.o$||'`
c++ -std=c++0x  -DHAVE_CONFIG_H -I.   -fvisibility=hidden  -g -O2 -Wno-unknown-pragmas -Wno-pragmas -Wall -Wextra -Wno-attributes -Wvarargs -Waddress -Warray-bounds -Wchar-subscripts -Wcomment -Wctor-dtor-privacy -Wfloat-equal -Wformat=2 -Wformat-y2k -Wmaybe-uninitialized -Wmissing-field-initializers -Wlogical-op -Wnon-virtual-dtor -Wnormalized=id -Woverloaded-virtual -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-compare -Wstrict-overflow=1 -Wswitch-enum -Wtrampolines -Wundef -Wunsafe-loop-optimizations -funsafe-loop-optimizations -Wc++11-compat -Wclobbered -Wunused -Wunused-result -Wunused-variable -Wunused-parameter -Wunused-local-typedefs -Wwrite-strings -Wformat-security -fwrapv -pipe -fPIE -pie -Wsizeof-pointer-memaccess -Wpacked  -MT clients/ms_setting.o -MD -MP -MF $depbase.Tpo -c -o clients/ms_setting.o clients/ms_setting.cc
mv -f $depbase.Tpo $depbase.Po

depbase=`echo clients/ms_sigsegv.o | sed 's|[^/]*$|.deps/&|;s|\.o$||'`
c++ -std=c++0x  -DHAVE_CONFIG_H -I.  -fvisibility=hidden  -g -O2 -Wno-unknown-pragmas -Wno-pragmas -Wall -Wextra -Wno-attributes -Wvarargs -Waddress -Warray-bounds -Wchar-subscripts -Wcomment -Wctor-dtor-privacy -Wfloat-equal -Wformat=2 -Wformat-y2k -Wmaybe-uninitialized -Wmissing-field-initializers -Wlogical-op -Wnon-virtual-dtor -Wnormalized=id -Woverloaded-virtual -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-compare -Wstrict-overflow=1 -Wswitch-enum -Wtrampolines -Wundef -Wunsafe-loop-optimizations -funsafe-loop-optimizations -Wc++11-compat -Wclobbered -Wunused -Wunused-result -Wunused-variable -Wunused-parameter -Wunused-local-typedefs -Wwrite-strings -Wformat-security -fwrapv -pipe -fPIE -pie -Wsizeof-pointer-memaccess -Wpacked -MT clients/ms_sigsegv.o -MD -MP -MF $depbase.Tpo -c -o clients/ms_sigsegv.o clients/ms_sigsegv.cc
mv -f $depbase.Tpo $depbase.Po

depbase=`echo clients/ms_stats.o | sed 's|[^/]*$|.deps/&|;s|\.o$||'`
c++ -std=c++0x  -DHAVE_CONFIG_H -I.   -fvisibility=hidden -fPIC -g -O2 -MT clients/ms_stats.o -MD -MP -MF $depbase.Tpo -c -o clients/ms_stats.o clients/ms_stats.cc
mv -f $depbase.Tpo $depbase.Po

depbase=`echo clients/ms_task.o | sed 's|[^/]*$|.deps/&|;s|\.o$||'`
c++ -std=c++0x  -DHAVE_CONFIG_H -I.  -fvisibility=hidden  -g -O2 -Wno-unknown-pragmas -Wno-pragmas -Wall -Wextra -Wno-attributes -Wvarargs -Waddress -Warray-bounds -Wchar-subscripts -Wcomment -Wctor-dtor-privacy -Wfloat-equal -Wformat=2 -Wformat-y2k -Wmaybe-uninitialized -Wmissing-field-initializers -Wlogical-op -Wnon-virtual-dtor -Wnormalized=id -Woverloaded-virtual -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-compare -Wstrict-overflow=1 -Wswitch-enum -Wtrampolines -Wundef -Wunsafe-loop-optimizations -funsafe-loop-optimizations -Wc++11-compat -Wclobbered -Wunused -Wunused-result -Wunused-variable -Wunused-parameter -Wunused-local-typedefs -Wwrite-strings -Wformat-security -fwrapv -pipe -fPIE -pie -Wsizeof-pointer-memaccess -Wpacked  -MT clients/ms_task.o -MD -MP -MF $depbase.Tpo -c -o clients/ms_task.o clients/ms_task.cc
mv -f $depbase.Tpo $depbase.Po

depbase=`echo clients/ms_thread.o | sed 's|[^/]*$|.deps/&|;s|\.o$||'`
c++ -std=c++0x  -DHAVE_CONFIG_H -I.   -fvisibility=hidden  -g -O2 -Wno-unknown-pragmas -Wno-pragmas -Wall -Wextra -Wno-attributes -Wvarargs -Waddress -Warray-bounds -Wchar-subscripts -Wcomment -Wctor-dtor-privacy -Wfloat-equal -Wformat=2 -Wformat-y2k -Wmaybe-uninitialized -Wmissing-field-initializers -Wlogical-op -Wnon-virtual-dtor -Wnormalized=id -Woverloaded-virtual -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-compare -Wstrict-overflow=1 -Wswitch-enum -Wtrampolines -Wundef -Wunsafe-loop-optimizations -funsafe-loop-optimizations -Wc++11-compat -Wclobbered -Wunused -Wunused-result -Wunused-variable -Wunused-parameter -Wunused-local-typedefs -Wwrite-strings -Wformat-security -fwrapv -pipe -fPIE -pie -Wsizeof-pointer-memaccess -Wpacked  -MT clients/ms_thread.o -MD -MP -MF $depbase.Tpo -c -o clients/ms_thread.o clients/ms_thread.cc
mv -f $depbase.Tpo $depbase.Po

depbase=`echo clients/generator.o | sed 's|[^/]*$|.deps/&|;s|\.o$||'`
c++ -std=c++0x -DHAVE_CONFIG_H -I.   -fvisibility=hidden  -g -O2 -Wno-unknown-pragmas -Wno-pragmas -Wall -Wextra -Wno-attributes -Wvarargs -Waddress -Warray-bounds -Wchar-subscripts -Wcomment -Wctor-dtor-privacy -Wfloat-equal -Wformat=2 -Wformat-y2k -Wmaybe-uninitialized -Wmissing-field-initializers -Wlogical-op -Wnon-virtual-dtor -Wnormalized=id -Woverloaded-virtual -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-compare -Wstrict-overflow=1 -Wswitch-enum -Wtrampolines -Wundef -Wunsafe-loop-optimizations -funsafe-loop-optimizations -Wc++11-compat -Wclobbered -Wunused -Wunused-result -Wunused-variable -Wunused-parameter -Wunused-local-typedefs -Wwrite-strings -Wformat-security -fwrapv -pipe -fPIE -pie -Wsizeof-pointer-memaccess -Wpacked -MT clients/generator.o -MD -MP -MF $depbase.Tpo -c -o clients/generator.o clients/generator.cc
mv -f $depbase.Tpo $depbase.Po

depbase=`echo clients/execute.o | sed 's|[^/]*$|.deps/&|;s|\.o$||'`
c++ -std=c++0x -DHAVE_CONFIG_H -I.   -fvisibility=hidden -fPIC -g -O2 -Wno-unknown-pragmas -Wno-pragmas -Wall -Wextra -Wno-attributes -Wvarargs -Waddress -Warray-bounds -Wchar-subscripts -Wcomment -Wctor-dtor-privacy -Wfloat-equal -Wformat=2 -Wformat-y2k -Wmaybe-uninitialized -Wmissing-field-initializers -Wlogical-op -Wnon-virtual-dtor -Wnormalized=id -Woverloaded-virtual -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-compare -Wstrict-overflow=1 -Wswitch-enum -Wtrampolines -Wundef -Wunsafe-loop-optimizations -funsafe-loop-optimizations -Wc++11-compat -Wclobbered -Wunused -Wunused-result -Wunused-variable -Wunused-parameter -Wunused-local-typedefs -Wwrite-strings -Wformat-security -fwrapv -pipe -fPIE -pie -Wsizeof-pointer-memaccess -Wpacked -MT clients/execute.o -MD -MP -MF $depbase.Tpo -c -o clients/execute.o clients/execute.cc
mv -f $depbase.Tpo $depbase.Po

rm -f clients/memaslap
libtool --silent --tag=CXX --mode=link c++ -std=c++0x -fPIC -g -O2 -Wno-unknown-pragmas -Wno-pragmas -Wall -Wextra -Wno-attributes -Wvarargs -Waddress -Warray-bounds -Wchar-subscripts -Wcomment -Wctor-dtor-privacy -Wfloat-equal -Wformat=2 -Wformat-y2k -Wmaybe-uninitialized -Wmissing-field-initializers -Wlogical-op -Wnon-virtual-dtor -Wnormalized=id -Woverloaded-virtual -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-compare -Wstrict-overflow=1 -Wswitch-enum -Wtrampolines -Wundef -Wunsafe-loop-optimizations -funsafe-loop-optimizations -Wc++11-compat -Wclobbered -Wunused -Wunused-result -Wunused-variable -Wunused-parameter -Wunused-local-typedefs -Wwrite-strings -Wformat-security -fwrapv -pipe -fPIE -pie -Wsizeof-pointer-memaccess -Wpacked  -lpthread -o clients/memaslap clients/memaslap.o clients/ms_conn.o clients/ms_setting.o clients/ms_sigsegv.o clients/ms_stats.o clients/ms_task.o clients/ms_thread.o clients/generator.o clients/execute.o -levent clients/libutilities.la libmemcached/libmemcached.la

fi