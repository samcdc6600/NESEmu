#ifndef UTILS_HPP_
#define UTILS_HPP_


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

#ifdef DEBUG //================= DEBUG FUNCTIONS ===============================
// Used to print values in buff in hex with address indexes starting at 0.
// Where s is the size of the buffer in bytes.
void printBufferAsMemory(const memory::minimumAddressableUnit buff [], const size_t s);
// Print minimumAddressableUnitSize bit of memory starting at addressStr.
void printMemeory(const std::string addressStr);
// Set memory at addressStr equal to x.
void alterMemory(std::stringstream argsSS);


//================= Functions To Extract Numbers From A String =================
// Return true if number is of type "char" or "unsigned char".
template <typename T> bool isNumChar(T)
{
    if(typeid(T) == typeid(unsigned char) || typeid(T) == typeid(char))
      return true;
    return false;
}


/* Throws exception if number is greater then
   "std::numeric_limits<unsigned char>::max()" or
   "std::numeric_limits<char>::max()", depending on whether T is an unsigned
   char or a char, respectively. */
template <typename T> void checkForCharNumRange(size_t number,
						const size_t callCount)
//  requires (typeid(T) == typeid(unsigned char) || typeid(T) == typeid(char))
{
  std::stringstream e {};
  // Replace with constrint in the future?
  assert(typeid(T) == typeid(unsigned char) || typeid(T) == typeid(char)
	 && "Error T != unsigned char or T != char!\n");

  if(typeid(T) == typeid(unsigned char))
    {
      if(number > std::numeric_limits<unsigned char>::max())
	{
	  e<<"argument #"<<callCount<<" invalid";
	  throw std::invalid_argument(e.str().c_str());
	}
    }
  else
    {
      if(typeid(T) == typeid(char))
	{
	  if(number > std::numeric_limits<char>::max())
	    {
	      e<<"argument #"<<callCount<<" invalid";
	      throw std::invalid_argument(e.str().c_str());
	    }
	}
    }
}


inline void getNumbersFromStr(std::stringstream & str, size_t callCount)
{
  callCount++;
  std::stringstream e {};
  std::string s {};
  str>>s;
  if(!s.empty())
    {
      e<<"too many ("<<callCount<<" or more) arguments detected";
      throw std::invalid_argument(e.str().c_str());
    }
}


/* Extracts numbers of type T for str and stores in retNumber, throws exception
   if there number cannot be read from str or if there are too few (a case where
   the number cannot be read) or too many numbers in str. Note that the argument
   callCount should generally be 0 unless you are doing something wired. */
template <typename T, typename ... Args>
void getNumbersFromStr(std::stringstream & str, size_t callCount, T & retNumber,
		       Args & ... args) // requires std::is_integral<T>::value
{
  std::stringstream e {};

  callCount++;
  /* We have to make sure that number isn't of type "char" or "unsigned char"
     beacuse it will only read in one character from the stream instead of the
     desired two. */
  if(isNumChar(retNumber))
    {
      size_t nonCharNum {};
      str>>std::hex>>nonCharNum;
      checkForCharNumRange<T>(nonCharNum, callCount);
      retNumber = nonCharNum;
    }
  else
    {
      str>>std::hex>>retNumber;
    }
  
  if(str.fail())
    {
      if(str.eof())
	{
	  e<<"too few arguments read "<<(callCount -1)<<" arguments";
	  throw std::invalid_argument(e.str().c_str());
	}
      else
	{
	  e<<"argument #"<<callCount<<" invalid";
	  throw std::invalid_argument(e.str().c_str());
	}
    }
  else
    {
      getNumbersFromStr(str, callCount, args...);
    }
}


//====================== Functions to check integer ranges =====================


template <typename T> struct numRange
{
  numRange(const T number, const size_t minimum, const size_t maximum) :
    num(number), min(minimum), max(maximum) {}
  const T num;
  const size_t min;
  const size_t max;
};


// For the range check the number must be in the range [min, max).
template <typename T>
void checkIntRangesProper(size_t callCount, numRange<T> range)
{
  std::stringstream e {};
  if(!(range.min <= range.num && range.num < range.max))
    {
      e<<"argument (\""<<size_t(range.num)<<"\") #"<<callCount<<" out of range";
      throw std::invalid_argument(e.str().c_str());
    }
}


template <typename T>
inline void checkIntRanges(size_t callCount, numRange<T> range)
{
  checkIntRangesProper(++callCount, range);
}


// "checkIntRanges()" should always be called with callCount set to 0
template <typename T, typename ... Args>
void checkIntRanges(size_t callCount, numRange<T> range, Args ... args)
{
  checkIntRangesProper(++callCount, range);
  checkIntRanges(callCount, args ...);
}

  
#endif

  
#endif
