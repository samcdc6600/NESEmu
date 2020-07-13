#ifndef MEM_HPP_
#define MEM_HPP_


#include <cstddef>
#include <string>


namespace memory
{
  typedef unsigned char minimumAddressableUnit;
  
  constexpr size_t minimumAddressableUnitSize
    {sizeof(minimumAddressableUnit) * 8};
  constexpr size_t minimumAddressableUnitMax
    {std::numeric_limits<minimumAddressableUnit>::max()};
  
  typedef unsigned short address;
  constexpr address maskAddressLow {0x00ff};
  constexpr address maskAddressHigh {0xff00};
  constexpr address pageSize {256};
  constexpr address zeroPageBase {0x0000}; // Bas address of the zero page.
  constexpr address stackBase {0x0100}; // Base address of stack
  constexpr address brkPCLoadVector {0xfffe};  // Brk loads the new PC from this address.
  /* Note that we are adding the maximum amount of memory only temporarily as we
     are developing the CPU emulation code first and we think it is a good idea.
     Latter we will change it to 2K (or whatever the right amount is :) .) */
  constexpr size_t memSize {65536};
  extern minimumAddressableUnit mem [memSize];
}





#endif
