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
### Memaslap vs Memslap
- memslap uses set and get interface from MemcacheD library
- memaslap only compiles with MemcacheD library and the packet generation from MemcacheD library
  - however memaslap uses C.

### How the basic save and read is done in MemcachD
- I am figuring out the contents of the packet that are used in memcacheD
- the basic functions are `SET` and `GET`

### General features of sending the packet
- you have to choose whether the data has to be sent via binary or ascii
- the key has to by encryped with AES and ecrypted with AES
- I have converted the send data but doing this one by one will take too much time
- `memaslap implemented it's own transfer method, and it does not seem to use memcached library that much`

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
- you must solve this if you actually want to add Seastar in it. Because you have to know how to `compile IT!`


### Successfully build
- the main difference of memaslap is that it does not use generator and execute object file which creates packets in C++ library
- `generator` generate keys and the random value for memcacheD
- `execution` file use the SET and GET interface of memacacheD
- the memaslap files are built into binary files using C compiler
- and the library is compiled with C available compiler
- the execution and geneartor file is compiled with C++ compiler
- the final data is compiled with C++ using libtool combining the memcacheD library as shared-memory
- one threat is that programming style does not follow the standard procedure even in C
- (c) Copyright 2009, Schooner Information Technology, Inc.


**benefits of using memaslap**
- It is just compiled together without any connection at all.
- What is enticing about memaslap is that it does not entirely rely on MemcacheD library
- a bit more understanding about the source code is required


### Converting C file into C++
- unacceptable design for C++
- we need to first make change into a single makefile
- then move the global functions into somewhere else

### Memaslap Design
- global lock
  - global lock is comprised of mutexes
  - mutex lock works for init
  - configuration = warm up
  - running
  - generating keys
- global stats
  - stats contains of active connections
  - total bytes that have been read
  - total bytes that have been write
  - total number of get command
  - total number of set cmmand
  - total number of misses
  - total number of waiting gets that are not expired
  - total number of expired gets

  **in case of UDP**
  - total number of dropped packets

- global statistics
  - statistics contain mutex
  - statistics of get commands
  - statistics of set commands


### Source Code Design
- the distribution of key and the values
- there are keys with big size and keys with small size and the value is different according to the size of the keys
- All those keys and values are shared as a global value in the memcacheD
- In order to maximize the performance of Seastar, we need to divide the keys and values to each of the threads
- `First`  I will build Seastar-Memaslap
- `Second` I will build Seastar-Memaslap available for multi-threading
- `Third`  compare Seastar-Memaslap the performance with shared-library.
- `Fourth` re-design Seastar-Memalsap by dividing the key and value to each individual threads
- as far as I am aware of memaslap has no relationship with MemcacheD library
- everything is implemented by itself
- but for some reason, the compilation is done with the memcaheD library and includes it.
