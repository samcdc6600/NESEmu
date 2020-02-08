#include <cstddef>


namespace memory
{
  constexpr size_t minimumAddressableUnit {8}; // That is bits :).
  /* Note that we are adding the maximum amount of memory only temporarily as we
     are developing the CPU emulation code first and we think it is a good idea.
     Latter we will change it to 2K (or whatever the right amount is :) .) */
  constexpr size_t memSize {65536};
  extern unsigned char mem [memSize];
}
