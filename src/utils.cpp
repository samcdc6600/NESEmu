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
      //      checkStrNumber(addressStr, address, size_t(0), memory::memSize, pPos);
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
  catch(const std::exception & e)
    {
      std::cerr<<"Error: processing print command and converting address (\""
	       <<addressStr<<"\") to type (\""<<typeid(memory::address).name()
	       <<"\"), recived exception \""<<e.what()<<".\"\n";
    }
}


void alterMemory(std::stringstream argsSS)
{
  memory::address address {};
  memory::minimumAddressableUnit value {};

  std::stringstream e {};
  try
    {
      getNumbersFromStr(argsSS, 0, address, value);
      checkIntRanges(0, numRange(address, size_t(0), memory::memSize),
		     numRange(value, size_t(0),
			      memory::minimumAddressableUnitMax +1));
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


#endif





    // argsSS>>std::hex>>address;
    // if(argsSS.fail())
    //   {
    // 	if(argsSS.eof())
    // 	  {
    // 	    e<<"too few arguments (no arguments detected)";
    // 	    throw std::invalid_argument(e.str().c_str());
    // 	  }
    // 	else
    // 	  {
    // 	    e<<"invalid first argument";
    // 	    throw std::invalid_argument(e.str().c_str());
    // 	  }
    //   }
    // else
    //   {
    // 	argsSS>>std::hex>>value;
    // 	if(argsSS.fail())
    // 	  {
    // 	    if(argsSS.eof())
    // 	      {
    // 		e<<"too few arguments (only one argument detected)";
    // 		throw std::invalid_argument(e.str().c_str());
    // 	      }
    // 	    else
    // 	      {
    // 		e<<"invalid second argument";
    // 		throw std::invalid_argument(e.str().c_str());
    // 	      }
    // 	  }
    // 	else
    // 	  {
    // 	    std::string dummy {};
    // 	    argsSS>>dummy;
    // 	    if(dummy.size() == 0)
    // 	      {
    // 		std::cout<<"read in arguments (\""<<address<<"\"), and (\""
    // 			 <<value<<"\")\n";
    // 	      }
    // 	    else
    // 	      {
    // 				std::cout<<"read in arguments (\""<<address<<"\"), and (\""
    // 			 <<value<<"\")\n";
    // 		e<<"too many arguments";
    // 		throw std::invalid_argument(e.str().c_str());
    // 	      }
    // 	  }
    //   }



// constexpr size_t numberBase {16};

// number = std::stoul(numStr, pPos, numberBase);
// if(numStr[*pPos] == '\0')
//   {
//     std::cout<<"number = "<<number<<", max = "<<max<<'\n';
//     if(number < min || number > max)
//       {
// 	std::stringstream e {};
// 	e<<"number out of range ["<<min<<", "<<max<<")";
// 	throw std::invalid_argument(e.str().c_str());
//       }
//   }
//  else
//    {
//      std::stringstream e {};
//      e<<"unable to convert characters (\""<<numStr.substr(*pPos)<<"\") at "
//        "position ("<<*pPos<<") from (\""<<numStr<<"\") to number";
//      throw std::invalid_argument(e.str().c_str());
//    }




    // if(address == 0)
    //   {
    // 	std::cout<<"error arg 1\n";
    //   }
    // else
    //   if(valueStr == 0)
    // 	{
    // 	  std::cout<<"error arg 2\n";
    // 	}
    //    argsSS>>addressStr;
    // pos = argsStr.find(command::argDelim);
    // if(pos == std::string::npos)
    //   {
    // 	e<<"character \""<<command::argDelim<<"\" not found in arguments "
    // 	  "string";
    // 	throw std::invalid_argument(e.str().c_str());
    //   }
    // else
    //   {
    // 	addressStr = argsStr.substr(0, pos);
    // 	valueStr = argsStr.substr(pos + 1);

    // 	if(valueStr.find(command::argDelim) != std::string::npos)
    // 	  {
    // 	    std::cout<<"valueStr.find(command::argDelim) = "<<valueStr.find(command::argDelim)
    // 		     <<", valueStr = "<<valueStr<<'\n';
    // 	    e<<"More then two arguments or trailing space detected";
    // 	    throw std::invalid_argument(e.str().c_str());
    // 	  }

    // 	std::cout<<"addressStr = "<<addressStr<<", valueStr = "<<valueStr<<'\n';

    // 	if(addressStr.size() == 0)
    // 	  {
    // 	    e<<"no arguments detected";
    // 	    throw std::invalid_argument(e.str().c_str());
    // 	  }
    // 	else
    // 	  {
    // 	    if(valueStr.size() == 0)
    // 	      {
    // 		e<<"only one argument detected";
    // 		throw std::invalid_argument(e.str().c_str());
    // 	      }
    // 	    else
    // 	      {
    // 		if((valueStr.size() + addressStr.size()) == argsStr.size())
    // 		  {
    // 		    checkStrNumber(addressStr, address, size_t(0),
    // 				   memory::memSize, pPos);
    // 		    checkStrNumber(valueStr, value, size_t(0),
    // 				   memory::minimumAddressableUnitMax, pPos);
    // 		    memory::mem[address] = value;
    // 		  }
    // 		else
    // 		  {
    // 		    e<<"more then two arguments detected";
    // 		    throw std::invalid_argument(e.str().c_str());
    // 		  }
    // 	      }
    // 	  }
    //   }
