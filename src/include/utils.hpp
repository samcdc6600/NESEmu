#ifndef ERROR_HPP_
#define ERROR_HPP_
#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


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


// Used when we want to decide what to do if we cannot open path.
// Where s is the size of buff in bytes.
bool loadFile(const std::string & path, char buff [], const size_t s);
// Used when we want to exit if we cannot open path.
// Where s is the size of buff in bytes.
void loadFile(const std::string & path, const std::string & errorContext,
	      char buff [], const size_t s);
// Used to print values in buff in hex with address indexes starting at 0.
// Where s is the size of the buffer in bytes.
void printBufferAsMemory(const char buff [], const size_t s);


#endif
