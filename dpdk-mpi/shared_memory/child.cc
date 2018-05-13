// the purpose is to let two different processes share the memory
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <string>
#include <cstdlib> //std::system
#include <sstream>
#include <iostream>

using namespace boost::interprocess;

typedef allocator<int, managed_shared_memory::segment_manager>  ShmemAllocator;
typedef vector<int, ShmemAllocator> MyVector;

int main (int argc, char *argv[]){

  //Open the managed segment
  managed_shared_memory segment(open_only, "MySharedMemory");
  //Find the vector using the c-string name
  MyVector *myvector = segment.find<MyVector>("myshmvector").first;
  //Use vector in reverse order
  std::sort(myvector->rbegin(), myvector->rend());

  int s=0;
  for (auto i = myvector->begin(); i != myvector->end(); ++i){
        std::cout << *i << ' ';
        s++;
  }
  myvector->erase(myvector->begin(), myvector->begin() + s);


  //When done, destroy the vector from the segment
  // segment.destroy<MyVector>("MyVector");

   return 0;
}
