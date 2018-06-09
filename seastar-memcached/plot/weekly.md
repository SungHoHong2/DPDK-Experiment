Experiments on Traditional MemCache[1], Seastar-Memcache[2] and libvma Memcache[3].

[1] https://memcached.org/
[2] https://github.com/scylladb/seastar/wiki/Memcached-Benchmark
[3] https://community.mellanox.com/docs/DOC-2168

However, I could not get the performance out of libvma Memache, because I could not access the FIU cluster.
Currently, FIU cluster responds that I have a wrong password that I have used for a long time.
I suspect that the password or the access configuration of FIU cluster has changed somehow because I was able to access FIU cluster in Korea.
Basic information about the memcacheD are collected in the link [5]
All the plot data related to the Seastar-Memcached cal be viwed here [6]

[5] https://github.com/SungHoHong2/DPDK-Experiment/blob/master/seastar-memcached/experiments/memcached.md
[6] https://github.com/SungHoHong2/DPDK-Experiment/tree/master/seastar-memcached

I have checked the design, debugged the source code, and evaluated the basic performance in ASU cluster.
In ASU cluster,
I have used memaslap (Memcached benchmark) in c3n25 (act as a client host)
and run Memached and Seastar-Memecache in c3n24 (act as a server host)

First, the basic difference
1. traditional Memcached can run as both a daemon or a process and is dependent on libevent library [7]
2. Seastar-Memcached can run as a process and it is independent from orignal memcached.
3. Libvma uses traditional memcached.

[7] http://libevent.org/

So basically, libvma simply overrides traditional socket-API interface used in MemCached, and use rdma for data transaction.
Seastar just implemeted the entire memcached by itself, and the overall logic is similar to the traditional Memcached.
It is known that memcached scales poorly to multicore processors because it was written for single core systems.
Seatar-Memcached claims that it has improve the performance when Memcached is running on multiple outstanding processes.
There are multiple alternative sources that also address this same issue such as Scaling Memcached at Facebook [4]
[4] https://www.usenix.org/system/files/conference/nsdi13/nsdi13-final170_update.pdf

The common logic that both Seatar-Memcached and traditional Memcached follows are these below
1. The servers maintain a key–value associative array
2. The clients populate this array and query it by key
3. The servers keep the values in RAM and if a server runs out of RAM, it discards the oldest values


Second, architecture of Seastar-Memcached
Memacached uses a client–server architecture. It means that the Memcached should be installed in both client and server in order to be utitlized. In case of Seastar-Memached, the server side is the only implemented side, which means that client still needs the client software that is compatiblie with Memcached.


Third, basic performance result from POSIX and DPDK.
The tests are done in ASU cluster c3n24 and c3n25.
The x axis represents the number of outstanding threads running on both client and server.
The y axis represents the average microseconds per response for latency and Mbytes per second for throughput

[images are provided]


Current shared-memory design of DPDK-MPI library
Since you have mentioned that you are not comfortable with the current shared-memory design.
I searched for all the possible options for changing my design.

The current version I am using is called MPICH, which is referred as
MPICH is a high-performance and widely portable implementation of the Message Passing Interface (MPI)
standard (MPI-1, MPI-2 and MPI-3).
(1) to provide an MPI implementation that efficiently supports different computation
(2) communication platforms including commodity clusters (desktop systems, shared-memory systems, multicore architectures), high-speed networks (10 Gigabit Ethernet, InfiniBand, Myrinet, Quadrics)

The major reason why I'am sharing library is the compilation between C and C++
Seastar is built with C++ and MPI is built with C. This alone is okay, but Seastar is heavily dependent on boost library [8]
Since C cannot compile boost, I cannot even compile Seastar and MPI together.
[8] https://en.wikipedia.org/wiki/Boost_(C%2B%2B_libraries)

Second, MPI uses shared memory between working processes.
In case of MPICH, MPI needs process manager which run and controls the entire scheduling of working processes.
The working processes are not aware of each other processes and use shared-memory only when they have to send and recv data in the same node.

Third, my limited understanding of the schduling logic of MPICH.
some process higher than the process manager is preventing to create more than one process at a time.
This is very troublesome to me because, process manager is the execution file, that first thing that MPI runs.
Once this issue is solved I may be able to compile and run global f-stack with MPICH and hopefully refrain from using shared memory.



Possible alternatives for not using sharing memory

First, combine MVAPICH or Open-MPI and f-stack
I have checked how Infiniband is used instead of POSIX, and MPICH run libvma when Mellanox products are detected. I have searched about the possible options that completely opens how Infiniband can be used in MPI. I have found that Ohio state university and Tokyo University and other institutions have built alternative process managers that support Infiniband in MPICH. However I am very very skeptical about the availablity of theses alternatives because there are no references of these solutions to be found.

I believe I have to switch from MPICH to MVAPICH or Open-MPI, and see how Infiniband is properly used for MPI library.
Hopefully, MVAPICH or Open-MPI will have a friendly design for typical DMA interface, since RDMA also uses polling mode when retrieving the messages from complete queue.
Based on this design, I will have to use f-stack which is built with C, to compile with MPI library.
However, IMB-benchmark might not work for open-mpi or MVAPICH, because it was a known issue that IMB-benchmark only works for MPICH.

Second, follow logic of libvma.
I will have to find a way to override native socket API interface, and replace them with f-stack.
In this case, I can still use the MPICH and the IMB library.
In theory, F-stack will be compiled together with the MPI-application (IMB-benchmark) and override the traditional socket API interface.

Third, combine MPICH and f-stack
My implementation of shared-memory between MPI and Seastar will not be a waste, because after I figure out the way to compile f-stack with MPI, I can swap the shared memory with a global pointer that leads to f-stack.


In conclusion,
Either way I don't think I can avoid using shared-memory when using Seastar, because Seastar cannot be compiled with MPI library.
