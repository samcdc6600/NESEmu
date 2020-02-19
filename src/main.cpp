#include <iostream>
#include "include/utils.hpp"
#include "include/cpu.hpp"
#include "include/mem.hpp"


namespace cmd
{
  constexpr size_t binName {0};
  constexpr size_t romPath {1};
}


void checkArgs(const int argc, const char * argv[]);
void initialise(const int argc, const char * argv[]);
#ifdef DEBUG
bool handleDebugCommand(const char * argv[], bool & next);
void handlePrintCommand(const std::string command);
void handleAlterMemory(const std::string command);
// Command.size() should be > 0
void handlePrintHelp(const char * argv[], const std::string command);
#endif


int main(const int argc, const char * argv[])
{
#ifdef DEBUG

  std::cout<<"============================= Running debug build ==============="
    "===============\n";
#endif

  checkArgs(argc, argv);
  initialise(argc, argv);
  //  printBufferAsMemory(memory::mem, memory::memSize);

#ifndef DEBUG
  do
    {
      cpu();
    }
  while(true);
#endif

#ifdef DEBUG
  bool next {true};		// Always execute the first instruction
  do
    {
      if(next)
	cpu();
      next = false;
      std::cout<<": ";		// Print a prompt...
    }
  while(handleDebugCommand(argv, next));
  std::cout<<"================================== Goodbye :) =================="
    "================\n";
#endif
}


void checkArgs(const int argc, const char * argv[])
{
  constexpr size_t minArgs {2}, maxArgs {2};
  if(size_t(argc) < minArgs)
    genError(error::CMD_ARGS, "Error (fatal): ", argc -1, " arguments passed to"
	     " ", argv[cmd::binName], " but at least ", minArgs, " required!"
	     "\n");
  else
    if(size_t(argc) > maxArgs)
      genError(error::CMD_ARGS, "Error (fatal): ", argc -1, " arguments passed "
	       "to ", argv[cmd::binName], " but no more than ", maxArgs,
	       " allowed!\n");
}


void initialise(const int argc, const char * argv[])
{
  loadFile(std::string{argv[cmd::romPath]}, memory::mem, memory::memSize,
	   "loading rom file");
}


#ifdef DEBUG
bool handleDebugCommand(const char * argv[], bool & next)
{
  bool ret {true};
  std::string command {};
  std::getline(std::cin, command);
  if(command.size() != 0)	// We treat no input the same as "n" or "N".
    {
      switch(command[0])
	{
	case 'p':
	case 'P':
	  handlePrintCommand(command);
	  break;
	case 'a':
	case 'A':
	  handleAlterMemory(command);
	  break;
	case 'n':
	case 'N':
	  next = true;
	  break;
	case 'q':
	case 'Q':
	  ret = false;
	  break;
	case 'h':
	case 'H':
	default:
	  handlePrintHelp(argv, command);
	}
    }
  else
    {				// Remeber '\n' is equivalent to 'n'.
      next = true;
    }
  return ret;
}


void handlePrintCommand(const std::string command)
{
  {
    size_t pos {};
    if(command.size() > command::argumentsPrefixLen &&
       command[1] == command::argDelim)
      {
	if(command[0] == 'p')
	  pos = command.find("p ") + command::argumentsPrefixLen;
	else
	  pos = command.find("P ") + command::argumentsPrefixLen;
	printMemeory(std::stringstream {command.substr(pos)});
      }
    else
      {
	if(command[1] != ' ')
	  std::cerr<<"Error: malformed print command (\""<<command
		   <<"\") encountered.\n";
	else
	  std::cerr<<"Error: address missing from print command.\n";
      }
  }
}


void handleAlterMemory(const std::string command)
{
  size_t pos {};
  if(command.size() > command::argumentsPrefixLen &&
     command[1] == command::argDelim)
    {
      if(command[0] == 'a')
	pos = command.find("a ") + command::argumentsPrefixLen;
      else
	pos = command.find("A ") + command::argumentsPrefixLen;
      alterMemory(std::stringstream {command.substr(pos)});
    }
  else
    {
      if(command[1] != ' ')
	std::cerr<<"Error: malformed alter command (\""<<command
		 <<"\") encountered.\n";
      else
	std::cerr<<"Error: arguments missing from alter command.\n";
    }
}


void handlePrintHelp(const char * argv[], const std::string command)
{
  size_t helpIndex {};
  /* This is definitly the sickest and best way to write out this output
     statment! */
  if(command[helpIndex] != 'h' && command[helpIndex] != 'H')
    std::cerr<<"Invalid command (\""<<command<<"\") entered: ";
  std::cerr<<"Please enter one of the following:\n\th\t\t: where \"h\" stands "
    "for \"help\" and will print this \n\t\t\t  message. Note that \"H\" is "
    "also accepted.\n\tp X\t\t: where \"p\" stands for \"print\" and \"X\" is "
    "an address in\n\t\t\t  hex in the range ["<<0<<", "<<memory::memSize<<"). "
    "Note that \"P\" is also\n\t\t\t  accepted.\n\ta X Y\t\t: Where \"a\" "
    "stands for \"alter\", \"X\" is an address in hex\n\t\t\t  in the range ["
	   <<0<<", "<<memory::memSize<<"), \"y\" is the value in hex that\n\t\t"
    "\t  the memory at X will be set to. Note that Y should be\n\t\t\t  an "
	   <<memory::minimumAddressableUnitSize<<"-bit number and A is also "
    "accepted.\n\tn\t\t: where \"n\" stands for \"next\". This will cause the "
    "next\n\t\t\t  instruction to be executed. Note that \"N\" and \"\\n\" are"
    "\n\t\t\t  also accepted.\n\tb X\t\t: where \"b\" stands for \"breakpoint\""
    " and \"X\" is an\n\t\t\t  address in hex in the range ["<<0<<", "
	   <<memory::memSize<<"). Multiple\n\t\t\t  breakpoints can be set. "
    "Breakpoints can be unset by\n\t\t\t  issuing the very same command used to"
    " set the\n\t\t\t  breakpoint. Note that \"B\" is also accepted.\n\tl {b | "
    "X Z}\t: where \"l\" stands for \"list\", \"b\" stands for \n\t\t\t  \""
    "breakpoints\" and both \"X\" and \"Z\" are addresses.\n\t\t\t  Giving the "
    "list command the argument b will cause it\n\t\t\t  to list all breakpoints"
    " and giving it addresses X and\n\t\t\t  Y as it's arguments will cause it "
    "to list out the\n\t\t\t  contents of memory in the range [X, Y].\n\tr\t\t:"
    " where \"r\" stands for \"run\". This will cause "<<argv[cmd::binName]
	   <<"\n\t\t\t  to execute instructions untill the PC is equal to a\n\t"
    "\t\t  breakpoint (if there are no breakpoints set then\n\t\t\t  execution "
    "will not stop.) Note that \"R\" is also\n\t\t\t  accepted.\n\tq\t\t: where"
    " \"q\" stands for \"quit\" and cause "<<argv[0]<<" to\n\t\t\t  hault "
    "instruction execution and exit. Note that \"Q\" is\n\t\t\t  also "
    "accepted.\n";
}


#endif
