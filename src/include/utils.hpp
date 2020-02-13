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
  
  template<typename T>
  void genError(const T & eNum)
  {
    exit(eNum);
  }
  
  template<typename T, typename... Args>
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


// Used when we want to decide what to do if we cannot open path.
// Where s is the size of buff in bytes.
bool loadFile(const std::string & path, unsigned char buff [], const size_t s);
// Used when we want to exit if we cannot open path.
// Where s is the size of buff in bytes.
void loadFile(const std::string & path, unsigned char buff [], const size_t s,
	      const std::string & errorContext);
#ifdef DEBUG
// Used to print values in buff in hex with address indexes starting at 0.
// Where s is the size of the buffer in bytes.
void printBufferAsMemory(const memory::minimumAddressableUnit buff [], const size_t s);
#endif


#endif
