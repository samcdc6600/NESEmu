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
  unsigned short PC {0x03f6};		// Program counter
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

  switch(unsigned(memory::mem[architecturalState::PC]))
    {				// There are 151 official 6502 opcodes organized
      // into 56 instructions (note that the NES does
      // not support decimal mode and also that there
      // are a number of unofficial opcodes.)

    case 0x00:	// BRK
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x01:	// ORA	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x02:	// STP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x03:	// SLO	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x04:	// NOP	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x05:	// ORA	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x06:	// ASL	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x07:	// SLO	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x08:	// PHP	(God personal home page is terrible!)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x09:	// ORA	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0a:	// ASL
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0b:	// ANC	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0c:	// NOP	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0d:	// ORA	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0e:	// ASL	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0f:	// SLO	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x10:	// BPL	*+d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x11:	// ORA	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x12:	// STP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x13:	// SLO	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x14:	// NOP	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x15:	// ORA	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x16:	// ASL	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x17:	// SLO	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x18:	// CLC
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x19:	// ORA	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x1a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x1b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x1c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x1d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x1e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x1f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x20:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x21:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x22:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x23:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x24:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x25:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x26:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x27:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x28:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x29:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x30:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x31:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x32:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x33:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x34:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x35:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x36:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x37:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x38:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x39:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x3a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x3b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x3c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x3d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x3e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x3f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x40:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x41:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x42:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x43:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x44:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x45:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x46:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x47:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x48:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x49:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x50:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x51:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x52:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x53:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x54:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x55:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x56:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x57:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x58:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x59:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x5a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x5b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x5c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x5d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x5e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x5f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x60:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x61:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x62:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x63:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x64:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x65:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x66:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x67:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x68:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x69:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x70:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x71:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x72:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x73:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x74:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x75:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x76:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x77:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x78:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x79:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x7a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x7b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x7c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x7d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x7e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x7f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x80:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x81:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x82:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x83:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x84:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x85:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x86:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x87:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x88:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x89:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x90:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x91:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x92:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x93:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x94:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x95:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x96:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x97:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x98:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x99:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x9a:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x9b:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x9c:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x9d:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x9e:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x9f:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa0:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa1:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa2:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa3:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa4:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa5:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa6:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa7:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa8:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa9:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xaa:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xab:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xac:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xad:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xae:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xaf:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb0:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb1:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb2:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb3:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb4:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb5:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb6:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb7:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb8:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb9:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xba:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xbb:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xbc:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xbd:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xbe:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xbf:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc0:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc1:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc2:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc3:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc4:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc5:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc6:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc7:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc8:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc9:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xca:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xcb:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xcc:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xcd:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xce:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xcf:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd0:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd1:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd2:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd3:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd4:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd5:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd6:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd7:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd8:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd9:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xda:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xdb:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xdc:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xcdd:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xde:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xdf:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe0:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe1:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe2:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe3:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe4:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe5:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe6:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe7:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe8:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe9:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xea:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xeb:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xec:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xed:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xee:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xef:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf0:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf1:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf2:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf3:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf4:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf5:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf6:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf7:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf8:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf9:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xfa:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xfb:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xfc:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xfd:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xfe:
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xff:
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
