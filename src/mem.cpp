#include <sstream>
#include <iostream>
#include "include/mem.hpp"


namespace memory
{
  unsigned char mem [memSize] {};
}


#ifdef DEBUG
void printMemeory(std::string address)
{
  std::stringstream {address};
  std::cout<<"address = "<<address<<'\n';
}
#endif
