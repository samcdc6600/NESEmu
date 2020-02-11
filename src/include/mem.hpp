#include <cstddef>
#include <string>


namespace memory
{
  // That is bits :).

  typedef unsigned char minimumAddressableUnit;
  typedef unsigned short address;
  constexpr size_t minimumAddressableUnitSize
    {sizeof(minimumAddressableUnit) * 8};
  /* Note that we are adding the maximum amount of memory only temporarily as we
     are developing the CPU emulation code first and we think it is a good idea.
     Latter we will change it to 2K (or whatever the right amount is :) .) */
  constexpr size_t memSize {65536};
  extern minimumAddressableUnit mem [memSize];
}


#ifdef DEBUG
void printMemeory(std::string address);
#endif
