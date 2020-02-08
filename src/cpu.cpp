#include <stdexcept>
#include <sstream>
#include "include/cpu.hpp"
#include "include/mem.hpp"
#include "include/utils.hpp"


/*
  From: http://wiki.nesdev.com/w/index.php/Status_flags#The_B_flag
  "While there are only six flags in the processor status register within the
  CPU, when transferred to the stack, there are two additional bits. These do
  not represent a register that can hold a value but can be used to distinguish
  how the flags were pushed.

  Some 6502 references call this the "B flag", though it does not represent an
  actual CPU register. Two interrupts (/IRQ and /NMI) and two instructions (PHP
  and BRK) push the flags to the stack. In the byte pushed, bit 5 is always set
  to 1, and bit 4 is 1 if from an instruction (PHP or BRK) or 0 if from an
  interrupt line being pulled low (/IRQ or /NMI). This is the only time and
  place where the B flag actually exists: not in the status register itself, but
  in bit 4 of the copy that is written to the stack."
*/


namespace architecturalState
{
  unsigned char A {};		// Accumulator
  unsigned char X {}, Y {};	// Index's
  /* We have set the PC to start at 0x0400 because the test program
     (6502_functional_test.asm:
     https://github.com/koute/pinky/tree/master/mos6502/roms) we are using
     requires that as the starting point and this namespaces scope is restricted
     to this file. (The initial value of PC should be changed once we finish
     implementing the CPU.) */
  unsigned short PC {0x0400};		// Program counter
  unsigned char S {};		// Stack Pointer
  

  typedef union			// Status (look at link below for how to acces members (remove this and the next comment latter.))
  {				// https://stackoverflow.com/questions/3497345/is-there-a-way-to-access-individual-bits-with-a-union
    struct
    {
      unsigned char C : 1;	// Carry
      unsigned char Z : 1;	// Zero
      unsigned char I : 1;	// Interrupt Disable
      unsigned char D : 1;	// Decimal
      unsigned char s0 : 1;	// No CPU effect. (refere to the comment at the
      unsigned char s1 : 1;	// top of the file.)
      unsigned char V : 1;	// Overflow
      unsigned char N : 1;	// Negative
    }u;
    unsigned char flags;
  }status;

  size_t cycles {};
}


bool dispatchInstruction();
#ifdef DEBUG
void debugDispatchInstruction();
#endif


void cpu()
{
  try
    {
      if(!dispatchInstruction())
	{
	  std::stringstream e {};
	  e<<std::hex<<"Error (fatal): opcode("
	   <<unsigned(memory::mem[architecturalState::PC])<<") at pc("
	   <<architecturalState::PC<<") is invalid!\n";
	  throw std::invalid_argument(e.str().c_str());
	}
    }
  catch(const std::exception & e)
    {
      genError(error::CPU_DECODE, e.what());
    }
}


bool dispatchInstruction()
{
#ifdef DEBUG
  std::cout<<"In dispatchInstruction():\n";
#endif

  switch(memory::mem[architecturalState::PC])
    {				// There are 151 official 6502 opcodes organized
      // into 56 instructions (note that the NES does
      // not support decimal mode and also that there
      // are a number of unofficial opcodes.)

    case 0x0000:	// BRK
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0001:	// ORA	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0002:	// STP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0003:	// SLO	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0004:	// NOP	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0005:	// ORA	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0006:	// ASL	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0007:	// SLO	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0008:	// PHP	(God personal home page is terrible!)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0009:	// ORA	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x000a:	// ASL
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x000b:	// ANC	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x000c:	// NOP	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x000d:	// ORA	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x000e:	// ASL	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x000f:	// SLO	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0010:	// BPL	*+d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0011:	// ORA	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0012:	// STP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0013:	// SLO	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0014:	// NOP	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0015:	// ORA	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0016:	// ASL	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0017:	// SLO	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0018:	// CLC
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0019:	// ORA	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x001a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x001b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x001c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x001d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x001e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x001f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2000:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2001:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2002:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2003:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2004:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2005:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2006:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2007:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2008:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2009:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x200a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x200b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x200c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x200d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x200e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x200f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2010:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2011:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2012:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2013:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2014:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2015:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2016:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2017:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2018:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2019:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x201a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x201b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x201c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x201d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x201e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x201f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4000:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4001:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4002:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4003:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4004:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4005:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4006:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4007:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4008:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4009:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x400a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x400b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x400c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x400d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x400e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x400f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4010:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4011:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4012:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4013:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4014:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4015:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4016:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4017:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4018:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4019:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x401a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x401b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x401c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x401d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x401e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x401f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6000:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6001:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6002:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6003:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6004:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6005:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6006:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6007:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6008:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6009:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x600a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x600b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x600c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x600d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x600e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x600f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6010:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6011:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6012:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6013:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6014:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6015:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6016:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6017:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6018:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6019:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x601a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x601b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x601c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x601d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x601e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x601f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8000:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8001:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8002:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8003:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8004:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8005:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8006:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8007:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8008:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8009:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x800a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x800b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x800c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x800d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x800e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x800f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8010:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8011:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8012:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8013:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8014:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8015:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8016:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8017:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8018:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8019:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x801a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x801b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x801c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x801d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x801e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x801f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa000:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa001:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa002:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa003:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa004:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa005:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa006:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa007:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa008:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa009:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa00a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa00b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa00c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa00d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa00e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa00f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa010:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa011:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa012:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa013:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa014:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa015:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa016:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa017:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa018:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa019:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa01a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa01b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa01c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa01d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa01e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa01f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc000:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc001:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc002:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc003:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc004:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc005:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc006:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc007:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc008:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc009:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc00a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc00b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc00c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc00d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc00e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc00f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc010:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc011:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc012:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc013:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc014:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc015:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc016:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc017:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc018:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc019:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc01a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc01b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc01c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc01d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc01e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc01f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe000:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe001:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe002:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe003:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe004:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe005:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe006:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe007:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe008:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe009:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe00a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe00b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe00c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe00d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe00e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe00f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe010:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe011:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe012:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe013:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe014:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe015:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe016:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe017:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe018:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe019:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe01a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe01b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe01c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe01d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe01e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe01f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    default:
      return false;
    }
      
  return true;
}


#ifdef DEBUG
void debugDispatchInstruction()
{
  std::cout<<std::hex<<"\tin cycle "<<architecturalState::cycles
	   <<", read opcode "<<unsigned(memory::mem[architecturalState::PC])
	   <<", at PC "<<architecturalState::PC<<'\n';
}
#endif
