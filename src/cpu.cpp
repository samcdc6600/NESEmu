#include <stdexcept>
#include <sstream>
#include <bitset>
#include "include/cpu.hpp"
#include "include/architecturalState.hpp"
#include "include/utils.hpp"
#ifdef DEBUG
#include "include/mnemonics.hpp"
#endif


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
  memory::address PC {0x0400};		// Program Counter
  unsigned char S {};		// Stack Pointer
  Status status {};
  size_t cycles {};
}


/* We think it is a little ugly to have to put this include here, however we
   deem it acceptable in light of our other design decisions related to
   "instructions.hpp". The include must be here because "instructions.hpp" must
   be able to see the "architecturalState" namespace. We do not put
   "architecturalState" in "cpu.hpp because we only want it to be accessible
   from this translation unit and the translation unit containing the contents
   of utils.cpp (if builing with the debug flag.) */
#include "include/instructions.hpp"


bool dispatchInstruction();
#ifdef DEBUG
void printArchitecturalState();
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
	  throw std::invalid_argument(e.str());
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
  printArchitecturalState();
#endif

  switch(unsigned(memory::mem[architecturalState::PC]))
    {				// There are 151 official 6502 opcodes organized
      // into 56 instructions (note that the NES does
      // not support decimal mode and also that there
      // are a number of unofficial opcodes.)

    case 0x00:			// BRK
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x01:			// ORA	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x02:			// STP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x03:			// SLO	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x04:			// NOP	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x05:			// ORA	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x06:			// ASL	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x07:			// SLO	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x08:	       		// PHP	(God personal home page is terrible!)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x09:			// ORA	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0a:			// ASL
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0b:			// ANC	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0c:			// NOP	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0d:			// ORA	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0e:			// ASL	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x0f:			// SLO	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x10:			// BPL	*+d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x11:			// ORA	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x12:			// STP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x13:			// SLO	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x14:			// NOP	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x15:			// ORA	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x16:			// ASL	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x17:			// SLO	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x18:			// CLC
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x19:			// ORA	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x1a:			// NOP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x1b:			// SLO	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x1c:			// NOP	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x1d:			// ORA	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x1e:			// ASL	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x1f:			// SLO	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x20:			// JSR	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x21:			// AND	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x22:			// STP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x23:			// RLA	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x24:			// BIT	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x25:			// AND	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x26:			// ROL	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x27:			// RLA	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x28:			// PLP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      plp_28();
      break;
    case 0x29:			// AND	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2a:			// ROL
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2b:			// ANC	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2c:			// BIT	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2d:			// AND	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2e:			// ROL	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x2f:			// RLA	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x30:			// BMI	*+d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x31:			// AND	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x32:			// STP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x33:			// RLA	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x34:			// NOP	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x35:			// AND	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x36:			// ROL	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x37:			// RLA	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x38:			// SEC
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x39:			// AND	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x3a:			// NOP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x3b:			// RLA	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x3c:			// NOP	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x3d:			// AND	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x3e:			// ROL	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x3f:			// RLA	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x40:			// RTI
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x41:			// EOR	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x42:			// STP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x43:			// SRE	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x44:			// NOP	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x45:			// EOR	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x46:			// LSR	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x47:			// SRE	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x48:			// PHA
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x49:			// EOR	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4a:			// LSR
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4b:			// ALR	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4c:			// JMP	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      jmp_4c();
      break;
    case 0x4d:			// EOR	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4e:			// LSR	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x4f:			// SRE	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x50:			// BVC	*+d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x51:			// EOR	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x52:			// STP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x53:			// SRE	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x54:			// NOP	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x55:			// EOR	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x56:			// LSR	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x57:			// SRE	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x58:			// CLI
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x59:			// EOR	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x5a:			// NOP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x5b:			// SRE	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x5c:			// NOP	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x5d:			// EOR	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x5e:			// LSR	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x5f:			// SRE	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x60:			// RTS
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x61:			// ADC	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x62:			// STP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x63:			// RRA	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x64:			// NOP	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x65:			// ADC	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x66:			// ROR	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x67:			// RRA	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x68:			// PLA
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x69:			// ADC	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6a:			// ROR
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6b:			// ARR	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6c:			// JMP	(a)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6d:			// ADC	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6e:			// ROR	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x6f:			// RRA	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x70:			// BVS	*+d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x71:			// ADC	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x72:			// STP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x73:			// RRA	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x74:			// NOP	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x75:			// ADC	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x76:			// ROR	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x77:			// RRA	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x78:			// SEI
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x79:			// ADC	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x7a:			// NOP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x7b:			// RRA	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x7c:			// NOP	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x7d:			// ADC	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x7e:			// ROR	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x7f:			// RRA	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x80:			// NOP	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x81:			// STA	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x82:			// NOP	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x83:			// SAX	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x84:			// STY	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x85:			// STA	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x86:			// STX	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x87:			// SAX	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x88:			// DEY
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      dey_88();
      break;
    case 0x89:			// NOP	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8a:			// TXA
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8b:			// XAA	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8c:			// STY	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8d:			// STA	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      sta_8d();
      break;
    case 0x8e:			// STX	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x8f:			// SAX	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x90:			// BCC	*+d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x91:			// STA	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x92:			// STP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x93:			// AHX	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x94:			// STY	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x95:			// STA	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x96:			// STX	d,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x97:			// SAX	d,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x98:			// TYA
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x99:			// STA	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x9a:			// TXS
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      txs_9a();
      break;
    case 0x9b:			// TAS	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x9c:			// SHY	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x9d:			// STA	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x9e:			// SHX	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0x9f:			// AHX	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa0:			// LDY	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      ldy_a0();
      break;
    case 0xa1:			// LDA	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa2:			// LDX	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      ldx_a2();
      break;
    case 0xa3:			// LAX	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa4:			// LDY	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa5:			// LDA	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa6:			// LDX	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa7:			// LAX	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa8:			// TAY
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xa9:			// LDA	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      lda_a9();
      break;
    case 0xaa:			// TAX
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xab:			// LAX	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xac:			// LDY	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xad:			// LDA	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xae:			// LDX	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xaf:			// LAX	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb0:			// BCS	*+d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb1:			// LDA	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb2:			// STP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb3:			// LAX	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb4:			// LDY	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb5:			// LDA	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb6:			// LDX	d,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb7:			// LAX	d,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb8:			// CLV
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xb9:			// LDA	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xba:			// TSX
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xbb:			// LAS	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xbc:			// LDY	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xbd:			// LDA	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xbe:			// LDX	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xbf:			// LAX	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc0:			// CPY	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc1:			// CMP	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc2:			// NOP	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc3:			// DCP	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc4:			// CPY	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc5:			// CMP	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc6:			// DEC	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc7:			// DCP	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc8:			// INY
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xc9:			// CMP	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xca:			// DEX
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      dex_ca();
      break;
    case 0xcb:			// AXS	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xcc:			// CPY	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xcd:			// CMP	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xce:			// DEC	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xcf:			// DCP	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd0:			// BNE	*+d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      bne_d0();
      break;
    case 0xd1:			// CMP	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd2:			// STP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd3:			// DCP	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd4:			// NOP	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd5:			// CMP	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd6:			// DEC	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd7:			// DCP	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xd8:			// CLD
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      cdl_d8();
      break;
    case 0xd9:			// CMP	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xda:			// NOP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xdb:			// DCP	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xdc:			// NOP	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xcdd:			// CMP	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xde:			// DEC	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xdf:			// DCP	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe0:			// CPX	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe1:			// SBC	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe2:			// NOP	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe3:			// ISC	(d,x)
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe4:			// CPX	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe5:			// SBC	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe6:			// INC	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe7:			// ISC	d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe8:			// INX
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xe9:			// SBC	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xea:			// NOP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      nop_ea();
      break;
    case 0xeb:			// SBC	#i
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xec:			// CPX	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xed:			// SBC	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xee:			// INC	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xef:			// ISC	a
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf0:			// BEQ	*+d
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      beq_f0();
      break;
    case 0xf1:			// SBC	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf2:			// STP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf3:			// ISC	(d),y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf4:			// NOP	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf5:			// SBC	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf6:			// INC	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf7:			// ISC	d,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf8:			// SED
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xf9:			// SBC	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xfa:			// NOP
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xfb:			// ISC	a,y
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xfc:			// NOP	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xfd:			// SBC	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xfe:			// INC	a,x
#ifdef DEBUG
      debugDispatchInstruction();
#endif
      break;
    case 0xff:			// ISC	a,x
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
memory::address getCurrentPC()
{
  return architecturalState::PC;
}


void printArchitecturalState()
{
  std::bitset<architecturalState::statusSize>
    psw {unsigned(architecturalState::status.flags)};
  std::cout<<std::hex<<"        ----------------------------- A "
	   <<" S -------------------------------------\n\tA = ("
	   <<unsigned(architecturalState::A)<<"),\tX     = ("
	   <<unsigned(architecturalState::X)<<"),\tY      = ("
	   <<unsigned(architecturalState::Y)<<"),\tPC = ("
	   <<architecturalState::PC<<"),\n\tS = ("
	   <<unsigned(architecturalState::S)<<"),\tflags = ("
	   <<psw<<"),\tcycles = ("
	   <<std::dec<<architecturalState::cycles<<")\n"
	   <<"        ---------------------------------------------------------"
	   <<"---------------\n";
}


void debugDispatchInstruction()
{
  std::cout<<std::hex<<"\tin cycle ("<<architecturalState::cycles
	   <<"), read opcode ("<<unsigned(memory::mem[architecturalState::PC])
	   <<") with mnemonic ("
	   <<mnemonics::instructionMnemonicsOrganizedByOpcode[memory::mem[architecturalState::PC]]
	   <<"), at PC "<<architecturalState::PC<<'\n';
}
#endif
