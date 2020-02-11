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
void handleDebugCommand(const char c);
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

  char c {};
  do
    {
      cpu();
      
      std::cout<<'\n';
      std::cin>>c;
      #ifdef DEBUG
      handleDebugCommand(c);
      #endif
    }
  while(c != 'q' && c != 'Q');
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
void handleDebugCommand(const char c)
{
  std::string arg {};
  switch(c)
    {
    case 'p':
      std::cin>>arg;
      printMemeory(arg);
      break;
    }
}
#endif
