// the purpose is to let two different processes share the memory
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>

#include <cstdlib> //std::system
#include <sstream>
#include <iostream>

using namespace boost::interprocess;

//Typedefs
typedef allocator<char, managed_shared_memory::segment_manager> CharAllocator;
typedef basic_string<char, std::char_traits<char>, CharAllocator> MyShmString;

typedef allocator<MyShmString, managed_shared_memory::segment_manager>  ShmemAllocator;
typedef vector<MyShmString, ShmemAllocator> MyVector;


int main (int argc, char *argv[]){

    struct shm_remove
    {
       shm_remove() { shared_memory_object::remove("MySharedMemory"); }
       ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
    } remover;

    managed_shared_memory segment(create_only, "MySharedMemory", 65536);
    const ShmemAllocator alloc_inst (segment.get_segment_manager());
    MyVector *myvector = segment.construct<MyVector>("MyVector")(alloc_inst);


    MyShmString mystring(charallocator);
      mystring = "howdy\t";


    for(int i = 0; i < 100; ++i)  //Insert data in the vector
       myvector->push_back(mystring);

     while(1){};


   return 0;
}
