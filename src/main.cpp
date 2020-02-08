#include <iostream>
#include "include/cpu.hpp"
//#include "include/mem.hpp"


int main()
{
  cpu();
  #ifdef DEBUG
  std::cout<<"In Debug mode\n";
  #endif
}
