if [ "$1" = "memaslap_seastar" ]
then
echo "test"

if [ "$1" = "memaslap_original" ]
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