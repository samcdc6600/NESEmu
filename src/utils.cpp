#include <cassert>
#include <limits>
#include "include/utils.hpp"


bool loadFileProper(const std::string & path, unsigned char buff [],
		    const size_t s);


bool loadFile(const std::string & path, unsigned char buff [], const size_t s)
{
  return loadFileProper(path, buff, s);
}


void loadFile(const std::string & path, unsigned char buff [], const size_t s,
	      const std::string & errorContext)
{
  try
    {
      if(!loadFileProper(path, buff, s))
	{
	  std::stringstream e {};
	  e<<std::hex<<"Error (fatal): ("<<errorContext<<") couldn't load file "
	    "\""<<path<<"\"\n";
	  throw std::invalid_argument(e.str().c_str());
	}
    }
  catch(const std::exception & e)
    {
      genError(error::FILE_LOAD, e.what());
    }
}


bool loadFileProper(const std::string & path, unsigned char buff [],
		    const size_t s)
{
  std::ifstream f {path};
  if(f.is_open())
    {
      for(size_t i {} ; i < s; ++i)
	{
	  buff[i] = f.get();
	  if(f.eof())
	    {
	      buff[i] = 0x0;	// We don't want the EOF value!
	      break;
	    }
	}
      return true;
    }
  
  return false;
}


#ifdef DEBUG // ================ DEBUG FUNCTIONS ===============================
constexpr size_t defaultCallCount {0};


void printBufferAsMemory(const memory::minimumAddressableUnit buff [],
			 const size_t s)
{
  for(size_t i {}; i < s; ++i)
    {
      std::cerr<<std::hex<<i<<":"<<"\t\t"
	       <<memory::address(buff[i])<<'\n';
    }
}


void printMemeory(std::stringstream argsSS)
{		     // We expect addressStr to be in base addressBase
  memory::address address {};
  std::stringstream e {};

  try
    {
      getNumbersFromStrInHex(argsSS, defaultCallCount, address);
      checkIntRanges(defaultCallCount, numRange(address, 0, memory::memSize));
      std::cout<<std::hex<<memory::address(memory::mem[address])<<'\n';
    }
  catch(const std::exception & e)
    {
      std::cerr<<"Error: converting print command argument (\""
	       <<argsSS.str()<<"\") to integer of type (\""
	       <<typeid(memory::address).name()<<"\"), recived exception \""
	       <<e.what()<<".\"\n";
    }
}


void alterMemory(std::stringstream argsSS)
{
  memory::address address {};
  memory::minimumAddressableUnit value {};
  std::stringstream e {};
  
  try
    {
      getNumbersFromStrInHex(argsSS, defaultCallCount, address, value);
      checkIntRanges(defaultCallCount, numRange(address, 0, memory::memSize),
		     numRange(value, 0,
			      memory::minimumAddressableUnitMax +1));
      memory::mem[address] = value;
    }
  catch(const std::exception & e)
    {
      std::cerr<<"Error: converting alter command arguments (\""
	       <<argsSS.str()<<"\") to integers of types (\""
	       <<typeid(memory::address).name()<<"\") and (\""
	       <<typeid(memory::minimumAddressableUnit).name()<<"\"), recived "
	"exception \""<<e.what()<<".\"\n";
    }
}


void setBreakpoint(std::stringstream argsSS,
	      std::vector<memory::address> & breakpoints)
{
  memory::address address {};
  std::stringstream e {};

  try
    {
      getNumbersFromStrInHex(argsSS, defaultCallCount, address);
      checkIntRanges(defaultCallCount, numRange(address, 0, memory::memSize));

      bool removed {false};
      for(auto iter {breakpoints.begin()}; iter != breakpoints.cend(); ++iter)
	{
	  if(*iter == address)
	    {
	      breakpoints.erase(iter);
	      removed = true;
	      break;
	    }
	}
      if(!removed)
	breakpoints.push_back(address);
    }
  catch(const std::exception & e)
    {
      std::cerr<<"Error: converting set breakpoint command argument (\""
	       <<argsSS.str()<<"\") to integer of type (\""
	       <<typeid(memory::address).name()<<"\"), recived exception \""
	       <<e.what()<<".\"\n";
    }
}


void listBreakpoints(std::vector<memory::address> & breakpoints)
{
  std::cout<<"The following breakpoints are set:\n";
  for(auto bp: breakpoints)
    {
      std::cout<<'\t'<<bp<<'\n';
    }
}


void listMemory(std::stringstream argSS)
{
  std::cout<<"please implement me!\n";
}


#endif
