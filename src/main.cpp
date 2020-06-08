#include <iostream>
#include "include/utils.hpp"
#include "include/cpu.hpp"
#include "include/mem.hpp"
#ifdef DEBUG
#include <vector>
#endif


namespace startCmd
{				// For argv[]
  constexpr size_t binName {0};
  constexpr size_t romPath {1};
}


void checkArgs(const int argc, const char * argv[]);
void initialise(const int argc, const char * argv[]);
#ifdef DEBUG
bool handleDebugCommand(const char * argv[], bool & next, bool & run,
			std::vector<memory::address> & breakpoints);
void handlePrintCommand(const std::string command);
/* Returns false if a command (command) of the form "C X ... ", has a malformed
   initial command sequence (that is to say that it checks the commands 
   delimiter position and its (the command) size.) */
bool checkCommandWithArgsConstraint(const std::string command);
/* Returns position after the delim which is after "cmdSearchingFor" in
   "cmdInput" (assuming cmdSearchingFor is in cmdInput at all.) */
inline size_t getPosAfterDelimAfterCommand(const std::string cmdInput,
					   const char cmdSearchingFor);
// Does what it says on the tin.
inline std::string addDelimToArg(const SuperString str);
void handleAlterMemoryCommand(const std::string command);
void handleBreakCommand(const std::string command,
			std::vector<memory::address> & breakpoints);
void handleListCommand(const std::string command,
		       std::vector<memory::address> & breakpoints);
void handleRunCommand(const std::string command, bool & run);
inline bool checkCommandWithNoArgsConstraint(const std::string command,
					     const char cmd, const char altCmd);
void handleFiddleCommand(const std::string command);
// Command.size() should be > 0
void handlePrintHelpCommand(const char * argv[], const std::string command);
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
  bool next {false};	       // Don't execute the first instruction.
  bool run {false};	       // Don't execute the first instruction.
  memory::address currentPC {};
  std::vector<memory::address> breakpoints {};
  do
    {
    AFTER_TEST:
      currentPC = getCurrentPC();
      if(std::find(breakpoints.begin(), breakpoints.end(), currentPC) ==
	 breakpoints.end())
	{			// We haven't reached a breakpoint
	  if(next || run)
	    {
	      cpu();
	      if(run)
		  goto AFTER_TEST;
	    }
	}
      else
	{
	  run = false;
	  breakpoints.erase(std::remove(breakpoints.begin(), breakpoints.end(),
					currentPC), breakpoints.end());
	}
      next = false;
      std::cout<<": ";		// Print a prompt...
    }
  while(handleDebugCommand(argv, next, run, breakpoints));
  std::cout<<"================================== Goodbye :) =================="
    "================\n";
#endif
}


void checkArgs(const int argc, const char * argv[])
{
  constexpr size_t minArgs {2}, maxArgs {2};
  if(size_t(argc) < minArgs)
    genError(error::CMD_ARGS, "Error (fatal): ", argc -1, " arguments passed to"
	     " ", argv[startCmd::binName], " but at least ", minArgs -1,
	     " required!\n");
  else
    if(size_t(argc) > maxArgs)
      genError(error::CMD_ARGS, "Error (fatal): ", argc -1, " arguments passed "
	       "to ", argv[startCmd::binName], " but no more than ", maxArgs -1,
	       " allowed!\n");}
}


void initialise(const int argc, const char * argv[])
{
  loadFile(std::string{argv[startCmd::romPath]}, memory::mem, memory::memSize,
	   "loading rom file");
}


#ifdef DEBUG
bool handleDebugCommand(const char * argv[], bool & next, bool & run,
			std::vector<memory::address> & breakpoints)
{
  bool ret {true};
  std::string command {};
  std::getline(std::cin, command);
  if(command.size() != 0)	// We treat no input the same as "n" or "N".
    {
      switch(command[command::cmdIndex])
	{
	case command::printCmd:
	case command::printCmdUpper:
	  handlePrintCommand(command);
	  break;
	case command::alterCmd:
	case command::alterCmdUpper:
	  handleAlterMemoryCommand(command);
	  break;
	case command::nextCmd:
	case command::nextCmdUpper:
	  next = true;
	  break;
	case command::breakpointCmd:
	case command::breakpointCmdUpper:
	  handleBreakCommand(command, breakpoints);
	  break;
	case command::listCmd:
	case command::listCmdUpper:
	  handleListCommand(command, breakpoints);
	  break;
	case command::runCmd:
	case command::runCmdUpper:
	  handleRunCommand(command, run);
	  break;
	case command::fiddleCmd:
	case command::fiddleCmdUpper:
	  handleFiddleCommand(command);
	  break;
	case command::quitCmd:
	case command::quitCmdUpper:
	  ret = false;
	  break;
	case command::helpCmd:
	case command::helpCmdUpper:
	default:
	  handlePrintHelpCommand(argv, command);
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
    if(checkCommandWithArgsConstraint(command))
      {
	if(command[command::cmdIndex] == command::printCmd)
	  pos = getPosAfterDelimAfterCommand(command, command::printCmd);
	else
	  pos = getPosAfterDelimAfterCommand(command, command::printCmdUpper);
	printMemeory(std::stringstream {command.substr(pos)});
      }
    else
      {
	if(command[command::postCmdIndex] != command::argDelim)
	  std::cerr<<"Error: malformed print command (\""<<command
		   <<"\") encountered.\n";
	else
	  std::cerr<<"Error: address missing from print command.\n";
      }
  }
}


inline bool checkCommandWithArgsConstraint(const std::string command)
{
  if(command.size() > command::argumentsPrefixLen &&
     command[command::postCmdIndex] == command::argDelim)
    return true;
  return false;
}


inline size_t getPosAfterDelimAfterCommand(const std::string cmdInput,
					   const char cmdSearchingFor)
{
  return cmdInput.find(addDelimToArg(cmdSearchingFor)) +
    command::argumentsPrefixLen;
}


inline std::string addDelimToArg(const SuperString str)
{
  return str + command::argDelim;
}


void handleAlterMemoryCommand(const std::string command)
{
  size_t pos {};
  if(checkCommandWithArgsConstraint(command))
    {
      if(command[command::cmdIndex] == command::alterCmd)
	pos = getPosAfterDelimAfterCommand(command, command::alterCmd);
      else
	pos = getPosAfterDelimAfterCommand(command, command::alterCmdUpper);
      alterMemory(std::stringstream {command.substr(pos)});
    }
  else
    {
      if(command[command::postCmdIndex] != command::argDelim)
	std::cerr<<"Error: malformed alter command (\""<<command
		 <<"\") encountered.\n";
      else
	std::cerr<<"Error: arguments missing from alter command.\n";
    }
}


void handleBreakCommand(const std::string command,
			std::vector<memory::address> & breakpoints)
{
  size_t pos {};
  if(checkCommandWithArgsConstraint(command))
    {
      if(command[command::cmdIndex] == command::breakpointCmd)
	pos = getPosAfterDelimAfterCommand(command, command::breakpointCmd);
      else
	pos = getPosAfterDelimAfterCommand(command,
					   command::breakpointCmdUpper);
      setBreakpoint(std::stringstream {command.substr(pos)}, breakpoints);
    }
  else
    {
      if(command[command::postCmdIndex] != command::argDelim)
	std::cerr<<"Error: malformed set breakpoint command (\""<<command
		 <<"\") encountered.\n";
      else
	std::cerr<<"Error: arguments missing from set breakpoint command.\n";
    }
}


void handleListCommand(const std::string command,
		       std::vector<memory::address> & breakpoints)
{
  size_t pos {};
  if(checkCommandWithArgsConstraint(command))
    {
      if(command[command::cmdIndex] == command::listCmd)
	pos = getPosAfterDelimAfterCommand(command, command::listCmd);
      else
	pos = getPosAfterDelimAfterCommand(command, command::listCmdUpper);

      if(command[pos] == command::listArgs::breakpoint)
	listBreakpoints(breakpoints);
      else
	listMemory(std::stringstream {command.substr(pos)});
    }
  else
    {
      if(command[command::postCmdIndex] != command::argDelim)
	std::cerr<<"Error: malformed list command (\""<<command
		 <<"\") encountered.\n";
      else
	std::cerr<<"Error: arguments missing from list command.\n";
    }
}


void handleRunCommand(const std::string command, bool & run)
{
  if(checkCommandWithNoArgsConstraint(command, command::runCmd,
				      command::runCmdUpper))
      run = true;
  else
      std::cerr<<"Error: malformed run command (\""<<command
	       <<"\") encountered.\n";
}


/* This would be more flexible as a recursive template function (however we dont
need anything other then two argument right now.) */
inline bool checkCommandWithNoArgsConstraint(const std::string command,
					     const char cmd, const char altCmd)
{
  if(command.size() == command::cmdSizeNoArgs &&
     (command[command::cmdIndex] == cmd ||
      command[command::cmdIndex] == altCmd))
    return true;
  return false;
}


void handleFiddleCommand(const std::string command)
{
  size_t pos {};
  if(checkCommandWithArgsConstraint(command))
    {
      if(command[command::cmdIndex] == command::fiddleCmd)
	pos = getPosAfterDelimAfterCommand(command, command::fiddleCmd);
      else
	pos = getPosAfterDelimAfterCommand(command, command::fiddleCmdUpper);
      fiddleWithArchitecturalState(std::stringstream {command.substr(pos)});
    }
  else
    {
      if(command[command::postCmdIndex] != command::argDelim)
	std::cerr<<"Error: malformed fiddle command (\""<<command
		 <<"\") encountered.\n";
      else
	std::cerr<<"Error: arguments missing from fiddle command.\n";      
    }
}


void handlePrintHelpCommand(const char * argv[], const std::string command)
{ /* We don't know how to escape '\n' when it's a char in the stream. So '\n'
     for the "next" command will have to be changed manually if
     "command::alterCmd" is changed. */
  /* This is definitly the sickest and best way to write out this output
     statment! */
  if(command[command::cmdIndex] != command::helpCmd &&
     command[command::cmdIndex] != command::helpCmdUpper)
    std::cerr<<"Invalid command (\""<<command<<"\") entered: ";
  std::cerr<<"Please enter one of the following:\n\t"<<command::helpCmd<<"\t\t:"
    " where \""<<command::helpCmd<<"\" stands for \"help\" and will print this "
    "\n\t\t\t  message. Note that \""<<command::helpCmdUpper<<"\" is also "
    "accepted.\n\t"<<command::printCmd<<" X\t\t: where \""<<command::printCmd
	   <<"\" stands for \"print\" and \"X\" is an address in\n\t\t\t  hex "
    "in the range ["<<0<<", "<<memory::memSize<<"). Note that \""
	   <<command::printCmdUpper<<"\" is also\n\t\t\t  accepted.\n\t"
	   <<command::alterCmd<<" X Y\t\t: Where \""<<command::alterCmd<<"\" "
    "stands for \"alter\", \"X\" is an address in hex\n\t\t\t  in the range ["
	   <<0<<", "<<memory::memSize<<"), \"y\" is the value in hex that\n\t\t"
    "\t  the memory at X will be set to. Note that Y should be\n\t\t\t  an "
	   <<memory::minimumAddressableUnitSize<<"-bit number and "
	   <<command::alterCmdUpper<<" is also accepted.\n\t"<<command::nextCmd
	   <<"\t\t: where \""<<command::nextCmd<<"\" stands for \"next\". This "
    "will cause the next\n\t\t\t  instruction to be executed. Note that \""
	   <<command::nextCmdUpper<<"\" and \"\\n\" are\n\t\t\t  also accepted."
    "\n\t"<<command::breakpointCmd<<" X\t\t: where \""
	   <<command::breakpointCmd<<"\" stands for \"breakpoint\" and \"X\" is"
    " an\n\t\t\t  address in hex in the range ["<<0<<", "<<memory::memSize
	   <<"). Execution\n\t\t\t  stops at the instruction before the "
    "breakpoint!\n\t\t\t  Multiple breakpoints can be set. Breakpoints can be\n"
    "\t\t\t  unset by issuing the very same command used to set the\n\t\t\t  "
    "breakpoint. Note that \""<<command::breakpointCmdUpper<<"\" is also "
    "accepted.\n\t"<<command::listCmd<<" {"<<command::listArgs::breakpoint<<" |"
    " X Z}\t: where \""<<command::listCmd<<"\" stands for \"list\", \""
	   <<command::listArgs::breakpoint<<"\" stands for \n\t\t\t  \""
    "breakpoints\" and both \"X\" and \"Z\" are addresses.\n\t\t\t  Giving the "
    "list command the argument "<<command::listArgs::breakpoint<<" will cause "
    "it\n\t\t\t  to list all breakpoints and giving it addresses X and\n\t\t\t "
    " Z as it's arguments will cause it to list out the\n\t\t\t  contents of "
    "memory in the range [X, Z]. Note that "<<command::listCmdUpper<<"\n\t\t\t "
    " is also accepted.\n\t"<<command::runCmd<<"\t\t: where \""
	   <<command::runCmd<<"\" stands for \"run\". This will cause "
	   <<argv[startCmd::binName]<<"\n\t\t\t  to execute instructions untill"
    " the PC is equal to a\n\t\t\t  breakpoint (if there are no breakpoints set"
    " then\n\t\t\t  execution will not stop.) Note that \""
	   <<command::runCmdUpper<<"\" is also\n\t\t\t  accepted.\n\t"
	   <<command::fiddleCmd<<" X Y\t\t: where \""<<command::fiddleCmd<<"\" "
    "stands for \"fiddle with architectural\n\t\t\t  state\", \"X\" is one of {"
	   <<command::fiddleArgs::accumulator<<" | "<<command::fiddleArgs::X
	   <<" | "<<command::fiddleArgs::Y<<" | "<<command::fiddleArgs::PC
	   <<" | "<<command::fiddleArgs::stack<<" | "
	   <<command::fiddleArgs::status<<" | "<<command::fiddleArgs::cycles
	   <<"}\n\t\t\t  (where a stands for \"accumulator\", "
	   <<command::fiddleArgs::X<<" stands for \"X\", "
	   <<command::fiddleArgs::Y<<"\n\t\t\t  stands for \"Y\", "
	   <<command::fiddleArgs::PC<<" stands for \"program counter\", "
	   <<command::fiddleArgs::stack<<"\n\t\t\t  stands for \"stack pointer"
    "\" "<<command::fiddleArgs::status<<" stands for \"flags\" aka\n\t\t\t  \""
    "status\" and "<<command::fiddleArgs::cycles<<" stands for \"cycles\") and "
    "Y is the value\n\t\t\t  to be assigned to X. Note that \""
	   <<command::fiddleCmdUpper<<"\" is also accepted.\n\t"
	   <<command::quitCmd<<"\t\t: where \""<<command::quitCmd<<"\" stands "
    "for \"quit\" and cause "<<argv[startCmd::binName]<<" to\n\t\t\t  hault "
    "instruction execution and exit. Note that \""<<command::quitCmdUpper
	   <<"\" is\n\t\t\t  also accepted.\n";
}


#endif
