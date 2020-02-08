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
  unsigned short PC {};		// Program counter
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
}


bool dispatchInstruction();


void cpu()
{
  try
    {
      if(!dispatchInstruction())
	{
	  std::stringstream e {"Error: opcode("};
	  e<<std::hex<<memory::mem[architecturalState::PC]<<") at pc("
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
  switch(memory::mem[architecturalState::PC])
    {				// There are 151 official 6502 opcodes organized
      // into 56 instructions (note that the NES does
      // not support decimal mode and also that there
      // are a number of unofficial opcodes.)

    case 0x0000:	// BRK
      break;
    case 0x0001:	// ORA	(d,x)
      break;
    case 0x0002:	// STP
      break;
    case 0x0003:	// SLO	(d,x)
      break;
    case 0x0004:	// NOP	d
      break;
    case 0x0005:	// ORA	d
      break;
    case 0x0006:	// ASL	d
      break;
    case 0x0007:	// SLO	d
      break;
    case 0x0008:	// PHP	(God personal home page is terrible!)
      break;
    case 0x0009:	// ORA	#i
      break;
    case 0x000a:	// ASL
      break;
    case 0x000b:	// ANC	#i
      break;
    case 0x000c:	// NOP	a
      break;
    case 0x000d:	// ORA	a
      break;
    case 0x000e:	// ASL	a
      break;
    case 0x000f:	// SLO	a
      break;
    case 0x0010:	// BPL	*+d
      break;
    case 0x0011:	// ORA	(d),y
      break;
    case 0x0012:	// STP
      break;
    case 0x0013:	// SLO	(d),y
      break;
    case 0x0014:	// NOP	d,x
      break;
    case 0x0015:	// ORA	d,x
      break;
    case 0x0016:	// ASL	d,x
      break;
    case 0x0017:	// SLO	d,x
      break;
    case 0x0018:	// CLC
      break;
    case 0x0019:	// ORA	a,y
      break;
    case 0x001a:
      break;
    case 0x001b:
      break;
    case 0x001c:
      break;
    case 0x001d:
      break;
    case 0x001e:
      break;
    case 0x001f:
      break;
    case 0x2000:
      break;
    case 0x2001:
      break;
    case 0x2002:
      break;
    case 0x2003:
      break;
    case 0x2004:
      break;
    case 0x2005:
      break;
    case 0x2006:
      break;
    case 0x2007:
      break;
    case 0x2008:
      break;
    case 0x2009:
      break;
    case 0x200a:
      break;
    case 0x200b:
      break;
    case 0x200c:
      break;
    case 0x200d:
      break;
    case 0x200e:
      break;
    case 0x200f:
      break;
    case 0x2010:
      break;
    case 0x2011:
      break;
    case 0x2012:
      break;
    case 0x2013:
      break;
    case 0x2014:
      break;
    case 0x2015:
      break;
    case 0x2016:
      break;
    case 0x2017:
      break;
    case 0x2018:
      break;
    case 0x2019:
      break;
    case 0x201a:
      break;
    case 0x201b:
      break;
    case 0x201c:
      break;
    case 0x201d:
      break;
    case 0x201e:
      break;
    case 0x201f:
      break;
    case 0x4000:
      break;
    case 0x4001:
      break;
    case 0x4002:
      break;
    case 0x4003:
      break;
    case 0x4004:
      break;
    case 0x4005:
      break;
    case 0x4006:
      break;
    case 0x4007:
      break;
    case 0x4008:
      break;
    case 0x4009:
      break;
    case 0x400a:
      break;
    case 0x400b:
      break;
    case 0x400c:
      break;
    case 0x400d:
      break;
    case 0x400e:
      break;
    case 0x400f:
      break;
    case 0x4010:
      break;
    case 0x4011:
      break;
    case 0x4012:
      break;
    case 0x4013:
      break;
    case 0x4014:
      break;
    case 0x4015:
      break;
    case 0x4016:
      break;
    case 0x4017:
      break;
    case 0x4018:
      break;
    case 0x4019:
      break;
    case 0x401a:
      break;
    case 0x401b:
      break;
    case 0x401c:
      break;
    case 0x401d:
      break;
    case 0x401e:
      break;
    case 0x401f:
      break;
    case 0x6000:
      break;
    case 0x6001:
      break;
    case 0x6002:
      break;
    case 0x6003:
      break;
    case 0x6004:
      break;
    case 0x6005:
      break;
    case 0x6006:
      break;
    case 0x6007:
      break;
    case 0x6008:
      break;
    case 0x6009:
      break;
    case 0x600a:
      break;
    case 0x600b:
      break;
    case 0x600c:
      break;
    case 0x600d:
      break;
    case 0x600e:
      break;
    case 0x600f:
      break;
    case 0x6010:
      break;
    case 0x6011:
      break;
    case 0x6012:
      break;
    case 0x6013:
      break;
    case 0x6014:
      break;
    case 0x6015:
      break;
    case 0x6016:
      break;
    case 0x6017:
      break;
    case 0x6018:
      break;
    case 0x6019:
      break;
    case 0x601a:
      break;
    case 0x601b:
      break;
    case 0x601c:
      break;
    case 0x601d:
      break;
    case 0x601e:
      break;
    case 0x601f:
      break;
    case 0x8000:
      break;
    case 0x8001:
      break;
    case 0x8002:
      break;
    case 0x8003:
      break;
    case 0x8004:
      break;
    case 0x8005:
      break;
    case 0x8006:
      break;
    case 0x8007:
      break;
    case 0x8008:
      break;
    case 0x8009:
      break;
    case 0x800a:
      break;
    case 0x800b:
      break;
    case 0x800c:
      break;
    case 0x800d:
      break;
    case 0x800e:
      break;
    case 0x800f:
      break;
    case 0x8010:
      break;
    case 0x8011:
      break;
    case 0x8012:
      break;
    case 0x8013:
      break;
    case 0x8014:
      break;
    case 0x8015:
      break;
    case 0x8016:
      break;
    case 0x8017:
      break;
    case 0x8018:
      break;
    case 0x8019:
      break;
    case 0x801a:
      break;
    case 0x801b:
      break;
    case 0x801c:
      break;
    case 0x801d:
      break;
    case 0x801e:
      break;
    case 0x801f:
      break;
    case 0xa000:
      break;
    case 0xa001:
      break;
    case 0xa002:
      break;
    case 0xa003:
      break;
    case 0xa004:
      break;
    case 0xa005:
      break;
    case 0xa006:
      break;
    case 0xa007:
      break;
    case 0xa008:
      break;
    case 0xa009:
      break;
    case 0xa00a:
      break;
    case 0xa00b:
      break;
    case 0xa00c:
      break;
    case 0xa00d:
      break;
    case 0xa00e:
      break;
    case 0xa00f:
      break;
    case 0xa010:
      break;
    case 0xa011:
      break;
    case 0xa012:
      break;
    case 0xa013:
      break;
    case 0xa014:
      break;
    case 0xa015:
      break;
    case 0xa016:
      break;
    case 0xa017:
      break;
    case 0xa018:
      break;
    case 0xa019:
      break;
    case 0xa01a:
      break;
    case 0xa01b:
      break;
    case 0xa01c:
      break;
    case 0xa01d:
      break;
    case 0xa01e:
      break;
    case 0xa01f:
      break;
    case 0xc000:
      break;
    case 0xc001:
      break;
    case 0xc002:
      break;
    case 0xc003:
      break;
    case 0xc004:
      break;
    case 0xc005:
      break;
    case 0xc006:
      break;
    case 0xc007:
      break;
    case 0xc008:
      break;
    case 0xc009:
      break;
    case 0xc00a:
      break;
    case 0xc00b:
      break;
    case 0xc00c:
      break;
    case 0xc00d:
      break;
    case 0xc00e:
      break;
    case 0xc00f:
      break;
    case 0xc010:
      break;
    case 0xc011:
      break;
    case 0xc012:
      break;
    case 0xc013:
      break;
    case 0xc014:
      break;
    case 0xc015:
      break;
    case 0xc016:
      break;
    case 0xc017:
      break;
    case 0xc018:
      break;
    case 0xc019:
      break;
    case 0xc01a:
      break;
    case 0xc01b:
      break;
    case 0xc01c:
      break;
    case 0xc01d:
      break;
    case 0xc01e:
      break;
    case 0xc01f:
      break;
    case 0xe000:
      break;
    case 0xe001:
      break;
    case 0xe002:
      break;
    case 0xe003:
      break;
    case 0xe004:
      break;
    case 0xe005:
      break;
    case 0xe006:
      break;
    case 0xe007:
      break;
    case 0xe008:
      break;
    case 0xe009:
      break;
    case 0xe00a:
      break;
    case 0xe00b:
      break;
    case 0xe00c:
      break;
    case 0xe00d:
      break;
    case 0xe00e:
      break;
    case 0xe00f:
      break;
    case 0xe010:
      break;
    case 0xe011:
      break;
    case 0xe012:
      break;
    case 0xe013:
      break;
    case 0xe014:
      break;
    case 0xe015:
      break;
    case 0xe016:
      break;
    case 0xe017:
      break;
    case 0xe018:
      break;
    case 0xe019:
      break;
    case 0xe01a:
      break;
    case 0xe01b:
      break;
    case 0xe01c:
      break;
    case 0xe01d:
      break;
    case 0xe01e:
      break;
    case 0xe01f:
      break;
    default:
      return false;
    }
      
  return true;
}
