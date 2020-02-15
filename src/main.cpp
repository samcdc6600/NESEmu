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
	printMemeory(command.substr(pos));
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
      alterMemory(command.substr(pos));
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
  if(command[helpIndex] != 'h' && command[helpIndex] != 'H')
    std::cerr<<"Invalid command (\""<<command<<"\") entered: ";
  std::cerr<<"Please enter one of the following:\n\th\t: where \"h\" stands for"
    " \"help\" and will print this message. Note\n\t\t  that \"H\" is also "
    "accepted.\n\tp X\t: where \"p\" stands for \"print\" and \"X\" is an "
    "address in hex in\n\t\t  the range ["<<0<<", "<<memory::memSize<<"). Note "
    "that \"P\" is  also accepted.\n\ta X Y\t: Where \"a\" stands for \"alter"
    "\", \"X\" is an address in hex in the\n\t\t  range ["<<0<<", "
	   <<memory::memSize<<"), \"y\" is the value in hex that the "
    "memory at X\n\t\t  will be set to. Note that Y should be an "
	   <<memory::minimumAddressableUnitSize<<"-bit number and A is\n\t\t  "
    "also accepted.\n\tn\t: where \"n\" stands for \"next\". This will cause "
    "the next\n\t\t  instruction to be executed. Note that \"N\" and \"\\n\" "
    "are also\n\t\t  accepted.\n\tq\t: where \"q\" stands for \"quit\" and "
    "cause "<<argv[0]<<" to hault\n\t\t  instruction execution and exit. Note "
    "that \"Q\" is also\n\t\t  accepted.\n";
}


#endif
