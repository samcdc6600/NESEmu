#include <iostream>
#include "include/cpu.hpp"
//#include "include/mem.hpp"


int main()
{
#ifdef DEBUG

  std::cout<<"============================= Running debug build ==============="
    "===============\n";
#endif
  
  cpu();
}
