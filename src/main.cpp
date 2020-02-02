#include <iostream>


int main()
{
  std::cout<<"Hello world\n";

  #ifdef DEBUG
  std::cout<<"In Debug mode\n";
  #endif
}
