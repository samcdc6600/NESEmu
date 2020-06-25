#ifndef UTILS_HPP_
#define UTILS_HPP_


#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
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
  constexpr unsigned char bit0	{0b00000001};
  constexpr unsigned char bit1	{0b00000010};
  constexpr unsigned char bit2	{0b00000100};
  constexpr unsigned char bit3	{0b00001000};
  constexpr unsigned char bit4	{0b00010000};
  constexpr unsigned char bit5	{0b00100000};
  constexpr unsigned char bit6	{0b01000000};
  constexpr unsigned char bit7	{0b10000000};
  constexpr unsigned bit8	{0b0000000100000000};
  constexpr unsigned bit9	{0b0000001000000000};
  constexpr unsigned bit10	{0b0000010000000000};
  constexpr unsigned bit11	{0b0000100000000000};
  constexpr unsigned bit12	{0b0001000000000000};
  constexpr unsigned bit13	{0b0010000000000000};
  constexpr unsigned bit14	{0b0100000000000000};
  constexpr unsigned bit15	{0b1000000000000000};
}


#ifdef DEBUG
namespace command
{	     // For "command" in "handleDebugCommand()" and callee's.
  constexpr char argDelim {' '};	// Command argument delimiter
  // This is assuming we are using "std::getline()"
  constexpr char endDelim {'\0'};
  // We expect to see 2 and only 2 characters before command arguments.
  constexpr size_t argumentsPrefixLen {2};
  constexpr size_t cmdSizeNoArgs {1};
  // Index of command code.
  constexpr size_t cmdIndex {0};
  /* Index of first argument after the command has been stripped on the command
     code and it's deliminator */
  constexpr size_t argsStrippedOfCmdIndex {0};
  // Index of character after command code.
  constexpr size_t postCmdIndex {1};
  constexpr char printCmd		{'p'};
  constexpr char printCmdUpper		{'P'};
  constexpr char alterCmd		{'a'};
  constexpr char alterCmdUpper		{'A'};
  constexpr char nextCmd		{'n'};
  constexpr char nextCmdUpper		{'N'};
  constexpr char nextAlt		{'\n'};
  constexpr char breakpointCmd		{'b'};
  constexpr char breakpointCmdUpper	{'B'};
  constexpr char listCmd		{'l'};
  constexpr char listCmdUpper		{'L'};
  namespace listArgs
  {
    constexpr char breakpoint			{'b'};
  }
  constexpr char runCmd			{'r'};
  constexpr char runCmdUpper		{'R'};
  constexpr char fiddleCmd		{'f'};
  constexpr char fiddleCmdUpper		{'F'};
  namespace fiddleArgs
  {
    constexpr char accumulator			{'a'};
    constexpr char X				{'x'};
    constexpr char Y				{'y'};
    constexpr char PC				{'p'};
    constexpr char stack			{'s'};
    constexpr char status			{'f'}; // aka flags
    constexpr char cycles			{'c'};
  }
  constexpr char quitCmd		{'q'};
  constexpr char quitCmdUpper		{'Q'};
  constexpr char helpCmd		{'h'};
  constexpr char helpCmdUpper		{'H'};
}
#endif


class SuperString: public std::string
{   // String class but we can initialize the class with a single char.
public:
  SuperString(const char c): std::string(std::string{c})
  {}
};


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
/* Print minimumAddressableUnitSize bit of memory starting at addressStr. That
   is if ssArgs is well-formed, otherwise print error message.*/
void printMemeory(std::stringstream ssArgs);
/* Set memory at addressStr equal to x. That is if ssArgs is well-formed,
   otherwise print error message. */
void alterMemory(std::stringstream ssArgs);
/* Add breakpoint at address in ssArgs to breakpoints. That is if ssArgs is
   well-formed, otherwise print error message. */
void setBreakpoint(std::stringstream ssArgs,
	      std::vector<memory::address> & breakpoints);
void listBreakpoints(std::vector<memory::address> & breakpoints);
/* List memory in the range [X, Z], where X and Z come from ssArgs. That is if
ssArgs is well-formed, otherwise print error message. */
void listMemory(std::stringstream ssArgs);
void fiddleWithArchitecturalState(std::stringstream ssArgs);


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
	  throw std::invalid_argument(e.str());
	}
    }
  else
    {
      if(typeid(T) == typeid(char))
	{
	  if(number > std::numeric_limits<char>::max())
	    {
	      e<<"argument #"<<callCount<<" invalid";
	      throw std::invalid_argument(e.str());
	    }
	}
    }
}


inline void getNumbersFromStrInHex(std::stringstream & str, size_t callCount)
{
  callCount++;
  std::stringstream e {};
  std::string s {};
  str>>s;
  if(!s.empty())
    {
      e<<"too many ("<<callCount<<" or more) arguments detected, or arguments "
	"malformed";
      throw std::invalid_argument(e.str());
    }
}


/* Extracts numbers of type T for str and stores in retNumber, throws exception
   if the number cannot be read from str or if there are too few (a case where
   the number cannot be read) or too many numbers in str. Note that the argument
   callCount should generally be 0 unless you are doing something wired. */
template <typename T, typename ... Args>
void getNumbersFromStrInHex(std::stringstream & str, size_t callCount, T & retNumber,
		       Args & ... args) // requires std::is_integral<T>::value
{
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
      std::stringstream e {};
      if(str.eof())
	{
	  e<<"too few arguments read "<<(callCount -1)<<" arguments, or "
	    "arguments too long";
	  throw std::invalid_argument(e.str());
	}
      else
	{
	  e<<"argument #"<<callCount<<" invalid";
	  throw std::invalid_argument(e.str());
	}
    }
  else
    {
      getNumbersFromStrInHex(str, callCount, args...);
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
inline void checkIntRangesProper(size_t callCount, numRange<T> range)
{
  if(!(range.min <= range.num && range.num < range.max))
    {
      std::stringstream e {};
      e<<"argument (\""<<size_t(range.num)<<"\") #"<<callCount<<" out of range";
      throw std::invalid_argument(e.str());
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


//========== Functions to check pairs of integers against one another  =========
// Throw exception if first argument is not less then or equal to second.
template <typename T1, typename T2>
inline void enforce1stLessThenOrEqTo2ndProper(size_t & callCount,
					      const T1 first, const T2 second)
{
  callCount += 2;
    if(!(first <= second))
      {
	std::stringstream e {};
	e<<std::hex<<"argument (\""<<first<<"\") #"<<(callCount -1)<<" greater "
	  "then argument (\""<<second<<"\") #"<<callCount;
	throw std::invalid_argument(e.str());
      }
}

template <typename T1, typename T2>
inline void enforce1stLessThenOrEqTo2nd(size_t callCount, const T1 first,
				 const T2 second)
{
  enforce1stLessThenOrEqTo2ndProper(callCount, first, second);
}

template <typename T1, typename T2, typename ... Args>
void enforce1stLessThenOrEqTo2nd(size_t callCount, const T1 first,
				 const T2 second, Args ... args)
{
  enforce1stLessThenOrEqTo2ndProper(callCount, first, second);
  enforce1stLessThenOrEqTo2nd(callCount, args ...);
}


#endif
#endif
