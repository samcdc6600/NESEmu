#ifndef ERROR_HPP_
#define ERROR_HPP_


#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "mem.hpp"


namespace error
{
  enum _error
    {
     CMD_ARGS,			// Invalid command line arguments
     FILE_LOAD,			// Error loading file
     CPU_DECODE			// Error decoding opcode
    };
  
  template <typename T>
  void genError(const T & eNum)
  {
    exit(eNum);
  }
  
  template <typename T, typename... Args>
  void genError(const int eNum, const T& value, const Args&... args)
  {                             // A general error has occured.
    std::cerr<<value;
    genError(eNum, args...);
  }
}


namespace masks
{
  constexpr unsigned char bit0 {0b00000001};
  constexpr unsigned char bit1 {0b00000010};
  constexpr unsigned char bit2 {0b00000100};
  constexpr unsigned char bit3 {0b00001000};
  constexpr unsigned char bit4 {0b00010000};
  constexpr unsigned char bit5 {0b00100000};
  constexpr unsigned char bit6 {0b01000000};
  constexpr unsigned char bit7 {0b10000000};
}


namespace command
{
  constexpr char argDelim {' '};	// Command argument delimiter
  // This is assuming we are using "std::getline()"
  constexpr char endDelim {'\0'};
  // We expect to see 2 and only 2 characters before command arguments.
  constexpr char argumentsPrefixLen {2};
}


// Used when we want to decide what to do if we cannot open path.
// Where s is the size of buff in bytes.
bool loadFile(const std::string & path, unsigned char buff [], const size_t s);
// Used when we want to exit if we cannot open path.
// Where s is the size of buff in bytes.
void loadFile(const std::string & path, unsigned char buff [], const size_t s,
	      const std::string & errorContext);

#ifdef DEBUG // ================ DEBUG FUNCTIONS ===============================
// Used to print values in buff in hex with address indexes starting at 0.
// Where s is the size of the buffer in bytes.
void printBufferAsMemory(const memory::minimumAddressableUnit buff [], const size_t s);
// Print minimumAddressableUnitSize bit of memory starting at addressStr.
void printMemeory(const std::string addressStr);
// Set memory at addressStr equal to x.
void alterMemory(const std::string argsStr);
/* Return true if addressStr is valid. Print error message and return false
   otherwise. */
template <typename T1, typename T2, typename T3>
bool checkStrNumber(const std::string numStr, T1 & number, const T2 min,
 			    const T3 max, size_t * pPos);
// template <typename T1, typename T2, typename T3>
// bool checkStrUnsignedNumber(const std::string numStr, T1 & number, const T2 min,
// 			    const T3 max, size_t * pPos);
  // requires std::is_unsigned<T1>::value && std::is_unsigned<T2>::value &&
  // std::is_unsigned<T3>::value;
/* ^^^ Seems to cause segmentation fault. We don't know if there is a flag to
   enable this on clang currently anyway (and we wish to be able to build and test
   with clang and g++ without warning) */
#endif


#endif
