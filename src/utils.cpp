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
void printBufferAsMemory(const memory::minimumAddressableUnit buff [],
			 const size_t s)
{
  for(size_t i {}; i < s; ++i)
    {
      std::cerr<<std::hex<<i<<":"<<"\t\t"
	       <<memory::address(buff[i])<<'\n';
    }
}


void printMemeory(const std::string addressStr)
{		     // We expect addressStr to be in base addressBase
  memory::address address {};
  size_t pos {};
  size_t * pPos {&pos};
  try
    {
      if(checkStrNumber(addressStr, address, size_t(0), memory::memSize,
				pPos))
	{
	  if(addressStr[*pPos] == '\0')
	    {
	      std::cout<<std::hex<<memory::address(memory::mem[address])<<'\n';
	    }
	  else
	    {
	      std::stringstream e {};
	      e<<"more then one argument and or trailing space detected";
	      throw std::invalid_argument(e.str().c_str());
	    }
	}
    }
  catch(const std::exception & e)
    {
      std::cerr<<"Error: processing print command and converting address (\""
	       <<addressStr<<"\") to type (\""<<typeid(memory::address).name()
	       <<"\"), recived exception \""<<e.what()<<".\"\n";
    }
}


void alterMemory(const std::string argsStr)
{
  memory::address address {};
  size_t pos {};
  size_t * pPos {&pos};
  try{
    if(checkStrNumber(argsStr, address, size_t(0),
 		    memory::minimumAddressableUnitMax, pPos))
      {
	if(argsStr[*pPos] == ' ' && *pPos < argsStr.size() &&
	   argsStr[*pPos +1] != ' ')
	  {
	    std::cout<<"hello !";
	  }
	else
	  {
	    std::stringstream e {};
	    e<<"only one argument detected";
	    throw std::invalid_argument(e.str().c_str());
	  }
      }
  }
  catch(const std::exception & e)
    {
      std::cerr<<"Error: processing alter  command and converting address (\""
	       <<argsStr<<"\") to type (\""<<typeid(memory::address).name()
	       <<"\"), recived exception \""<<e.what()<<".\"\n";
    }
}


template <typename T1, typename T2, typename T3>
bool checkStrNumber(const std::string numStr, T1 & number, const T2 min,
			    const T3 max, size_t * pPos)
{
  bool ret {false};
  constexpr size_t numberBase {16};

  assert(std::numeric_limits<T1>::min() >= min
	 && "Error (fatal): in \"checkStrNumber()\" in translation unit"
	 " \"utils.cpp\" numbers type's (T1) minimum value less then min.\n");
  assert(std::numeric_limits<T1>::max() <= max
	 && "Error (fatal): in \"checkStrNumber()\" in translation unit"
	 " \"utils.cpp\" numbers type's (T1) maximum value more then max.\n");

  number = std::stoul(numStr, pPos, numberBase);
  if(numStr[*pPos] == '\0' || numStr[*pPos] == ' ')
    {
      if(number >= min && number < max)
	{
	  return ret = true;
	}
      else
	{
	  std::stringstream e {};
	  e<<"number out of range ["<<min<<", "<<max<<")";
	  throw std::invalid_argument(e.str().c_str());
	}
    }
  else
    {
      std::stringstream e {};
      e<<"unable to convert characters (\""<<numStr.substr(*pPos)<<"\") at "
	"position ("<<*pPos<<") from (\""<<numStr<<"\") to number";
      throw std::invalid_argument(e.str().c_str());
    }
  return ret;
}
#endif

