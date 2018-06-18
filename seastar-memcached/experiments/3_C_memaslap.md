### Memaslap
- researching about the possiblility of swapping the memaslap transfer location into Seastar version
- One problem is that Memaslap is built based on global lock which is not good for multi processing

### Located the send and recv section
- the logic is similar to the Seastar version
- memaslap benchmark provides comprehensive test for memcacheD
- however it is built in C, fortunately, it is not complicated as MPI library.
- only the protocols have to be equal, so I am trying to convert memaslap into C++ version
- I need to check whether it is possilbe to `wait` `Seastar` to send data when there is none. in MPI library they just send dummy - data with dummy packets. and MPI library ignores it. However, I believe this is the right way.

### BEGIN
### How the basic save and read is done in MemcachD
- I am figuring out the contents of the packet that are used in memcacheD
- the basic functions are `SET` and `GET`

### General features of sending the packet
- you have to choose whether the data has to be sent via binary or ascii
- the key has to by encryped with AES and ecrypted with AES
- I have converted the send data but doing this one by one will take too much time
- `memaslap implemented it's own transfer method, and it does not seem to use memcached library that much`
- we nneed to convert this into C++

### the main focus
- I have compared both libmemcached library and memaslap benchmark.
- although memaslpa is built with C files
- This is more straight forward and less coupled compared to libmemcacheD library.
- I believe it is better to convert memaslap into C++ object and then use Seastar.
- Because Memaslap contains diverse tests
- The transfer section does not rely on MemcacheD library.
- Memaslap only uses hashmap and server list provided by MemcacheD library


### problem with makefile of memaslap
- It seems that I am not familiar with Makefiles
- First it creates binary files out of from the clients utiltiy directory
- The first it creates an binary file of memalsap
- Second it combines the binary file with C++ file
- Third it creates the executive file


dist-gzip dist-lzip dist-shar dist-tarZ dist-xz dist-zip \

```
running CONFIG_SHELL=/bin/bash /bin/bash /data1/sungho/libmemcached-1.0.18/configure --enable-memaslap LD
FLAGS=-lpthread --prefix=/data1/sungho/usr/local --no-create --no-recursion
checking for cc... cc

echo "  CXX     " clients/utilities.lo;depbase=`echo clients/utilities.lo | sed 's|[^/]*$|.deps/&|;s|\.lo│$||'`;\


echo "  CC      " clients/memaslap.o;depbase=`echo clients/memaslap.o | sed 's|[^/]*$|.deps/&|;s|\.o$||'`
;\
        cc -DHAVE_CONFIG_H -I.   -fvisibility=hidden  -g -O2  -Wno-unknown-pragmas -Wno-pragmas -Wall -We
xtra -Wunsuffixed-float-constants -Wjump-misses-init -Wno-attributes -Waddress -Wvarargs -Warray-bounds -
Wbad-function-cast -Wchar-subscripts -Wcomment -Wfloat-equal -Wformat-security -Wformat=2 -Wformat-y2k -W
logical-op -Wmaybe-uninitialized -Wmissing-field-initializers -Wmissing-noreturn -Wmissing-prototypes -Wn
ested-externs -Wnormalized=id -Woverride-init -Wpointer-arith -Wpointer-sign -Wredundant-decls -Wshadow -
Wsign-compare -Wstrict-overflow=1 -Wswitch-enum -Wtrampolines -Wundef -Wunsafe-loop-optimizations -funsaf
e-loop-optimizations -Wclobbered -Wunused -Wunused-result -Wunused-variable -Wunused-parameter -Wunused-l
ocal-typedefs -Wwrite-strings -fwrapv -pipe -fPIE -pie -Wsizeof-pointer-memaccess -Wpacked -MT clients/me
maslap.o -MD -MP -MF $depbase.Tpo -c -o clients/memaslap.o clients/memaslap.c &&\
        mv -f $depbase.Tpo $depbase.Po


rm -f clients/memaslap
echo "  CXXLD   " clients/memaslap;/bin/bash ./libtool --silent --tag=CXX   --mode=link c++ -std=c++0x  -
g -O2 -Wno-unknown-pragmas -Wno-pragmas -Wall -Wextra -Wno-attributes -Wvarargs -Waddress -Warray-bounds
-Wchar-subscripts -Wcomment -Wctor-dtor-privacy -Wfloat-equal -Wformat=2 -Wformat-y2k -Wmaybe-uninitializ
ed -Wmissing-field-initializers -Wlogical-op -Wnon-virtual-dtor -Wnormalized=id -Woverloaded-virtual -Wpo
inter-arith -Wredundant-decls -Wshadow -Wsign-compare -Wstrict-overflow=1 -Wswitch-enum -Wtrampolines -Wu
ndef -Wunsafe-loop-optimizations -funsafe-loop-optimizations -Wc++11-compat -Wclobbered -Wunused -Wunused
-result -Wunused-variable -Wunused-parameter -Wunused-local-typedefs -Wwrite-strings -Wformat-security -f
wrapv -pipe -fPIE -pie -Wsizeof-pointer-memaccess -Wpacked  -lpthread -o clients/memaslap clients/memasla
p.o clients/ms_conn.o clients/ms_setting.o clients/ms_sigsegv.o clients/ms_stats.o clients/ms_task.o clie
nts/ms_thread.o clients/generator.o clients/execute.o -levent clients/libutilities.la libmemcached/libmem
cached.la

/bin/mkdir -p '/data1/sungho/usr/local/bin'
libtool: install: /usr/bin/install -c clients/.libs/memslap /data1/sungho/usr/local/bin/memslap


```



* C Compiler:                cc (Ubuntu 5.4.1-2ubuntu1~14.04) 5.4.1 20160904
* C Flags:                   -g -O2  -Wno-unknown-pragmas -Wno-pragmas -Wall -Wextra -Wunsuffixed-floa
t-constants -Wjump-misses-init -Wno-attributes -Waddress -Wvarargs -Warray-bounds -Wbad-function-cast -Wc
har-subscripts -Wcomment -Wfloat-equal -Wformat-security -Wformat=2 -Wformat-y2k -Wlogical-op -Wmaybe-uni
nitialized -Wmissing-field-initializers -Wmissing-noreturn -Wmissing-prototypes -Wnested-externs -Wnormal
ized=id -Woverride-init -Wpointer-arith -Wpointer-sign -Wredundant-decls -Wshadow -Wsign-compare -Wstrict
-overflow=1 -Wswitch-enum -Wtrampolines -Wundef -Wunsafe-loop-optimizations -funsafe-loop-optimizations -
Wclobbered -Wunused -Wunused-result -Wunused-variable -Wunused-parameter -Wunused-local-typedefs -Wwrite-
strings -fwrapv -pipe -fPIE -pie -Wsizeof-pointer-memaccess -Wpacked
* C++ Compiler:              c++ (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4
* C++ Flags:                 -g -O2 -Wno-unknown-pragmas -Wno-pragmas -Wall -Wextra -Wno-attributes -W
varargs -Waddress -Warray-bounds -Wchar-subscripts -Wcomment -Wctor-dtor-privacy -Wfloat-equal -Wformat=2
-Wformat-y2k -Wmaybe-uninitialized -Wmissing-field-initializers -Wlogical-op -Wnon-virtual-dtor -Wnormal
ized=id -Woverloaded-virtual -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-compare -Wstrict-overflow=
1 -Wswitch-enum -Wtrampolines -Wundef -Wunsafe-loop-optimizations -funsafe-loop-optimizations -Wc++11-com
pat -Wclobbered -Wunused -Wunused-result -Wunused-variable -Wunused-parameter -Wunused-local-typedefs -Ww
rite-strings -Wformat-security -fwrapv -pipe -fPIE -pie -Wsizeof-pointer-memaccess -Wpacked
* CPP Flags:                  -fvisibility=hidden
