if [ "$1" = "memaslap" ]
then
depbase=`echo clients/memaslap.o | sed 's|[^/]*$|.deps/&|;s|\.o$||'`;

echo $depbase
cc -DHAVE_CONFIG_H -I.   -fvisibility=hidden  -g -O2  -Wno-unknown-pragmas -Wno-pragmas -Wall -Wextra -Wunsuffixed-float-constants -Wjump-misses-init -Wno-attributes -Waddress -Wvarargs -Warray-bounds -Wbad-function-cast -Wchar-subscripts -Wcomment -Wfloat-equal -Wformat-security -Wformat=2 -Wformat-y2k -Wlogical-op -Wmaybe-uninitialized -Wmissing-field-initializers -Wmissing-noreturn -Wmissing-prototypes -Wnested-externs -Wnormalized=id -Woverride-init -Wpointer-arith -Wpointer-sign -Wredundant-decls -Wshadow -Wsign-compare -Wstrict-overflow=1 -Wswitch-enum -Wtrampolines -Wundef -Wunsafe-loop-optimizations -funsafe-loop-optimizations -Wclobbered -Wunused -Wunused-result -Wunused-variable -Wunused-parameter -Wunused-local-typedefs -Wwrite-strings -fwrapv -pipe -fPIE -pie -Wsizeof-pointer-memaccess -Wpacked -MT clients/memaslap.o -MD -MP -MF $depbase.Po -c -o clients/memaslap.o clients/memaslap.c &&\
# mv -f $depbase.Tpo $depbase.Po
elif [ "$1" = "ms_conn" ]
then
depbase=`echo clients/ms_conn.o | sed 's|[^/]*$|.deps/&|;s|\.o$||'`;

cc -DHAVE_CONFIG_H -I.   -fvisibility=hidden  -g -O2  -Wno-unknown-pragmas -Wno-pragmas -Wall -Wextra -Wunsuffixed-float-constants -Wjump-misses-init -Wno-attributes -Waddress -Wvarargs -Warray-bounds -Wbad-function-cast -Wchar-subscripts -Wcomment -Wfloat-equal -Wformat-security -Wformat=2 -Wformat-y2k -Wlogical-op -Wmaybe-uninitialized -Wmissing-field-initializers -Wmissing-noreturn -Wmissing-prototypes -Wnested-externs -Wnormalized=id -Woverride-init -Wpointer-arith -Wpointer-sign -Wredundant-decls -Wshadow -Wsign-compare -Wstrict-overflow=1 -Wswitch-enum -Wtrampolines -Wundef -Wunsafe-loop-optimizations -funsafe-loop-optimizations -Wclobbered -Wunused -Wunused-result -Wunused-variable -Wunused-parameter -Wunused-local-typedefs -Wwrite-strings -fwrapv -pipe -fPIE -pie -Wsizeof-pointer-memaccess -Wpacked -MT clients/ms_conn.o -MD -MP -MF $depbase.Tpo -c -o clients/ms_conn.o clients/ms_conn.c &&\
mv -f $depbase.Tpo $depbase.Po





fi