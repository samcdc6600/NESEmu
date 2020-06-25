#include <cassert>
#include <limits>
#include "include/utils.hpp"
#ifdef DEBUG
#include "include/mnemonics.hpp"
#endif


bool loadFileProper(const std::string & path, unsigned char buff [],
		    const size_t s);
#ifdef DEBUG // ================ DEBUG FUNCTIONS ===============================
void listMemoryProper(const memory::address addressX,
		 const memory::address addressZ);
#endif


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
	  throw std::invalid_argument(e.str());
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
      std::cout<<std::hex<<i<<":"<<"\t\t"
	       <<memory::address(buff[i])<<'\n';
    }
}


void printMemeory(std::stringstream ssArgs)
{		     // We expect addressStr to be in base addressBase
  memory::address address {};

  try
    {
      getNumbersFromStrInHex(ssArgs, defaultCallCount, address);
      checkIntRanges(defaultCallCount, numRange(address, 0, memory::memSize));
      std::cout<<std::hex<<memory::address(memory::mem[address])<<'\n';
    }
  catch(const std::exception & e)
    {
      std::cerr<<"Error: converting print command argument (\""
	       <<ssArgs.str()<<"\") to integer of type (\""
	       <<typeid(memory::address).name()<<"\"), recived exception \""
	       <<e.what()<<".\"\n";
    }
}


void alterMemory(std::stringstream ssArgs)
{
  memory::address address {};
  memory::minimumAddressableUnit value {};
  
  try
    {
      getNumbersFromStrInHex(ssArgs, defaultCallCount, address, value);
      checkIntRanges(defaultCallCount, numRange(address, 0, memory::memSize),
		     numRange(value, 0,
			      memory::minimumAddressableUnitMax +1));
      memory::mem[address] = value;
    }
  catch(const std::exception & e)
    {
      std::cerr<<"Error: converting alter command arguments (\""
	       <<ssArgs.str()<<"\") to integers of types (\""
	       <<typeid(memory::address).name()<<"\") and (\""
	       <<typeid(memory::minimumAddressableUnit).name()<<"\"), recived "
	"exception \""<<e.what()<<".\"\n";
    }
}


void setBreakpoint(std::stringstream ssArgs,
	      std::vector<memory::address> & breakpoints)
{
  memory::address address {};

  try
    {
      getNumbersFromStrInHex(ssArgs, defaultCallCount, address);
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
	       <<ssArgs.str()<<"\") to integer of type (\""
	       <<typeid(memory::address).name()<<"\"), recived exception \""
	       <<e.what()<<".\"\n";
    }
}


void listBreakpoints(std::vector<memory::address> & breakpoints)
{
  std::cout<<"The following breakpoints are set:\n";
  for(auto bp: breakpoints)
    {
      std::cout<<std::hex<<'\t'<<bp<<'\n';
    }
}


void listMemory(std::stringstream ssArgs)
{
  memory::address addressX {}, addressZ {};

  try
    {
      getNumbersFromStrInHex(ssArgs, defaultCallCount, addressX, addressZ);
      checkIntRanges(defaultCallCount, numRange(addressX, 0, memory::memSize),
		     numRange(addressZ, 0, memory::memSize));
      enforce1stLessThenOrEqTo2nd(defaultCallCount, addressX, addressZ);
      listMemoryProper(addressX, addressZ);
    }
  catch(const std::exception & e)
    {
      std::cerr<<"Error: converting list (memory) command arguments (\""
	       <<ssArgs.str()<<"\") to integers of types (\""
	       <<typeid(memory::address).name()<<"\") and (\""
	       <<typeid(memory::address).name()<<"\"), recived exception \""
	       <<e.what()<<".\"\n";
    }
}


void listMemoryProper(const memory::address addressX,
		 const memory::address addressZ)
{
  std::cout<<"-----------------------------------------------------------------"
    "---------------\n\taddress\t|\tmnemonic\t|\traw value\n-------------------"
    "-------------------------------------------------------------\n";
  for(size_t index {addressX}; index < (addressZ +1); ++index)
    {
      std::cout<<std::hex<<'\t'<<index<<"\t|\t"
	       <<mnemonics::instructionMnemonicsOrganizedByOpcode[memory::mem[index]]
	       <<"\t\t|\t"<<unsigned(memory::mem[index])<<'\n';
    }
}


/* =================== The Following function/s should be the ==================
  =================== last in this file to limit the visibility ================
  ======================== of the follow include statment! =================== */
#include "include/architecturalState.hpp"

void fiddleWithArchitecturalState(std::stringstream ssArgs)
{  
  try
    {
      std::stringstream e {};
      
      unsigned char A {};		// Accumulator
      unsigned char X {}, Y {};		// Index's
      memory::address PC {};		// Program Counter
      unsigned char S {};		// Stack Pointer
      unsigned char status {};		// Status (flags, PSW etc...)
      size_t cycles {};			// Current clock cycle

      char toFiddle {};
      ssArgs>>toFiddle;

      switch(toFiddle)
	{
	case command::fiddleArgs::accumulator:
	  
	  getNumbersFromStrInHex(ssArgs, defaultCallCount, A);
	  checkIntRanges(defaultCallCount, numRange(A, std::numeric_limits<unsigned char>::lowest(),
						    std::numeric_limits<unsigned char>::max() +1));
	  architecturalState::A = A;
	  break;
	case command::fiddleArgs::X:
	  getNumbersFromStrInHex(ssArgs, defaultCallCount, X);
	  checkIntRanges(defaultCallCount, numRange(X, std::numeric_limits<unsigned char>::lowest(),
						    std::numeric_limits<unsigned char>::max() +1));
	  architecturalState::X = X;
	  break;
	case command::fiddleArgs::Y:
	  getNumbersFromStrInHex(ssArgs, defaultCallCount, Y);
	  checkIntRanges(defaultCallCount, numRange(Y, std::numeric_limits<unsigned char>::lowest(),
						    std::numeric_limits<unsigned char>::max() +1));
	  architecturalState::Y = Y;
	  break;
	case command::fiddleArgs::PC:
	  getNumbersFromStrInHex(ssArgs, defaultCallCount, PC);
	  checkIntRanges(defaultCallCount, numRange(PC, 0, size_t(memory::memSize)));
	  architecturalState::PC = PC;
	  break;
	case command::fiddleArgs::stack:
	  getNumbersFromStrInHex(ssArgs, defaultCallCount, S);
	  /* Stack Starts at offset 0x0100 and covers the range [0x0100, 0x01ff]
	     it wraps around (basically just let the numbers do their thing :)
	     .) */
	  checkIntRanges(defaultCallCount, numRange(S, std::numeric_limits<unsigned char>::lowest(),
						    std::numeric_limits<unsigned char>::max() +1));
	  architecturalState::S = S;
	  break;
	case command::fiddleArgs::status:
	  getNumbersFromStrInHex(ssArgs, defaultCallCount, status);
	  checkIntRanges(defaultCallCount, numRange(status, std::numeric_limits<unsigned char>::lowest(),
						    std::numeric_limits<unsigned char>::max() +1));
	  architecturalState::status.flags = status;
	  break;
	case command::fiddleArgs::cycles:
	  getNumbersFromStrInHex(ssArgs, defaultCallCount, cycles);
	  /* Can't do +1 here because we will wrap around. Probably don't need
	     that last cycle anyway ;) */
	  checkIntRanges(defaultCallCount, numRange(status, std::numeric_limits<size_t>::lowest(),
						    std::numeric_limits<size_t>::max()));
	  architecturalState::cycles = cycles;
	  break;
	default:
	  e<<"unknown argument (\""
	   <<ssArgs.str()[command::argsStrippedOfCmdIndex]<<"\")";
	  throw std::invalid_argument(e.str());
	}
    }
  catch(const std::exception & e)
    {
      std::cerr<<"Error: processing fiddle command arguments (\""
	       <<ssArgs.str()<<"\"), recived exception \""
	       <<e.what()<<".\"\n";
    }
}


#endif
