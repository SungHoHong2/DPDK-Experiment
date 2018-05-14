#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/allocators/allocator.hpp>


int main ()
{
   using namespace boost::interprocess;
   //Typedefs
   typedef allocator<char, managed_shared_memory::segment_manager>
      CharAllocator;
   typedef basic_string<char, std::char_traits<char>, CharAllocator>
      MyShmString;
   typedef allocator<MyShmString, managed_shared_memory::segment_manager>
      StringAllocator;
   typedef vector<MyShmString, StringAllocator>
      MyShmStringVector;

   //Open shared memory
   //Remove shared memory on construction and destruction
   struct shm_remove
   {
      shm_remove() { shared_memory_object::remove("MySharedMemory"); }
      ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
   } remover;

   managed_shared_memory shm(create_only, "MySharedMemory", 10000);

   //Create allocators
   CharAllocator     charallocator  (shm.get_segment_manager());
   StringAllocator   stringallocator(shm.get_segment_manager());

   //This string is in only in this process (the pointer pointing to the
   //buffer that will hold the text is not in shared memory).
   //But the buffer that will hold "this is my text" is allocated from
   //shared memory
   MyShmString mystring(charallocator);
   mystring = "howdy";

   //This vector is only in this process (the pointer pointing to the
   //buffer that will hold the MyShmString-s is not in shared memory).
   //But the buffer that will hold 10 MyShmString-s is allocated from
   //shared memory using StringAllocator. Since strings use a shared
   //memory allocator (CharAllocator) the 10 buffers that hold
   //"this is my text" text are also in shared memory.
   MyShmStringVector myvector(stringallocator);
   myvector.insert(myvector.begin(), 6, mystring);

   //This vector is fully constructed in shared memory. All pointers
   //buffers are constructed in the same shared memory segment
   //This vector can be safely accessed from other processes.
   MyShmStringVector *myshmvector =
      shm.construct<MyShmStringVector>("myshmvector")(stringallocator);
   myshmvector->insert(myshmvector->begin(), 6, mystring);

   //Destroy vector. This will free all strings that the vector contains

   while(1){};

   shm.destroy_ptr(myshmvector);
   return 0;
}
