#include <iostream>
#include "include/cpu.hpp"
//#include "include/mem.hpp"


int main()
{
  std::cout<<"Hello world\n";

  #ifdef DEBUG
  std::cout<<"In Debug mode\n";
  #endif
}
