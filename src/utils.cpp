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


#ifdef DEBUG
void printBufferAsMemory(const memory::minimumAddressableUnit buff [], const size_t s)
{
  for(size_t i {}; i < s; ++i)
    {
      std::cerr<<std::hex<<i<<":"<<"\t\t"
	       <<memory::address(buff[i])<<'\n';
    }
}
#endif
