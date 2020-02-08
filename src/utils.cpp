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
      char c {};
      for(size_t i {} ; i < s; ++i)
	{
	  c = f.get();
	  if(c != std::char_traits<char>::eof())
	    buff[i] = c;
	  else
	    break;
	}
      return true;
    }
  
  return false;
}


void printBufferAsMemory(const unsigned char buff [], const size_t s)
{
  for(size_t i {}; i < s; i += 2)
    {
      unsigned opcode {buff[i]};
      opcode <<= 8;
      opcode += buff[i + 1];
      std::cerr<<std::hex<<i<<":"<<"\t\t"
	       <<opcode<<'\n';
    }
}
