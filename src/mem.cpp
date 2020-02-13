#include <sstream>
#include <iostream>
#include <typeinfo>
#include "include/mem.hpp"


namespace memory
{
  unsigned char mem [memSize] {};
}


#ifdef DEBUG
void printMemeory(std::string addressStr)
{		     // We expect addressStr to be in base addressBase
  try
    {
      constexpr size_t addressBase {16};
      size_t pos {};
      size_t * pPos {&pos};
      memory::address address = std::stoul(addressStr, pPos, addressBase);
      if(addressStr[*pPos] == '\0')
	{
	  if(address >= 0 && address < memory::memSize)
	    {
	      std::cout<<std::hex<<memory::address(memory::mem[address])<<'\n';
	    }
	  else
	    {
	      std::stringstream e {};
	      e<<"address out of range ["<<0<<", "<<memory::memSize<<")";
	      throw std::invalid_argument(e.str().c_str());
	    }
	}
      else
	{
	  std::stringstream e {};
	  e<<"unable to convert characters (\""<<addressStr.substr(*pPos)<<"\") at "
	    "position ("<<*pPos<<") from (\""<<addressStr<<"\") to address.\n";
	  throw std::invalid_argument(e.str().c_str());
	}
    }
  catch(const std::exception & e)
    {
      std::cerr<<"Error: converting address (\""<<addressStr<<"\") to type (\""
	       <<typeid(memory::address).name()<<"\"), recived exception \""
	       <<e.what()<<".\"\n";
    }
}
#endif
