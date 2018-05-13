// the purpose is to let two different processes share the memory
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <string>
#include <cstdlib> //std::system
#include <sstream>
#include <iostream>

using namespace boost::interprocess;


int main (int argc, char *argv[]){

    struct shm_remove
    {
       shm_remove() { shared_memory_object::remove("MySharedMemory"); }
       ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
    } remover;

    managed_shared_memory segment(create_only, "MySharedMemory", 65536);
    const ShmemAllocator alloc_inst (segment.get_segment_manager());
    MyVector *myvector = segment.construct<MyVector>("MyVector")(alloc_inst);

    for(int i = 0; i < 100; ++i)  //Insert data in the vector
       myvector->push_back(i);

     while(1){};


   return 0;
}
