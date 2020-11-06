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
  bool ret {true};
  
  switch(unsigned(memory::mem[architecturalState::PC]))
    {				// There are 151 official 6502 opcodes organized
      // into 56 instructions (note that the NES does
      // not support decimal mode and also that there
      // are a number of unofficial opcodes.)

    case 0x00:			// BRK
      brk_00();
      break;
    case 0x01:			// ORA	(d,x)
      break;
    case 0x02:			// STP
      break;
    case 0x03:			// SLO	(d,x)
      break;
    case 0x04:			// NOP	d
      break;
    case 0x05:			// ORA	d
      break;
    case 0x06:			// ASL	d
      break;
    case 0x07:			// SLO	d
      break;
    case 0x08:	       		// PHP	(God personal home page is terrible!)
      php_08();
      break;
    case 0x09:			// ORA	#i
      ora_09();
      break;
    case 0x0a:			// ASL
      break;
    case 0x0b:			// ANC	#i
      break;
    case 0x0c:			// NOP	a
      break;
    case 0x0d:			// ORA	a
      break;
    case 0x0e:			// ASL	a
      break;
    case 0x0f:			// SLO	a
      break;
    case 0x10:			// BPL	*+d
      bpl_10();
      break;
    case 0x11:			// ORA	(d),y
      break;
    case 0x12:			// STP
      break;
    case 0x13:			// SLO	(d),y
      break;
    case 0x14:			// NOP	d,x
      break;
    case 0x15:			// ORA	d,x
      break;
    case 0x16:			// ASL	d,x
      break;
    case 0x17:			// SLO	d,x
      break;
    case 0x18:			// CLC
      clc_18();
      break;
    case 0x19:			// ORA	a,y
      break;
    case 0x1a:			// NOP
      break;
    case 0x1b:			// SLO	a,y
      break;
    case 0x1c:			// NOP	a,x
      break;
    case 0x1d:			// ORA	a,x
      break;
    case 0x1e:			// ASL	a,x
      break;
    case 0x1f:			// SLO	a,x
      break;
    case 0x20:			// JSR	a
      jsr_20();
      break;
    case 0x21:			// AND	(d,x)
      break;
    case 0x22:			// STP
      break;
    case 0x23:			// RLA	(d,x)
      break;
    case 0x24:			// BIT	d
      break;
    case 0x25:			// AND	d
      break;
    case 0x26:			// ROL	d
      break;
    case 0x27:			// RLA	d
      break;
    case 0x28:			// PLP
      plp_28();
      break;
    case 0x29:			// AND	#i
      break;
    case 0x2a:			// ROL
      break;
    case 0x2b:			// ANC	#i
      break;
    case 0x2c:			// BIT	a
      break;
    case 0x2d:			// AND	a
      break;
    case 0x2e:			// ROL	a
      break;
    case 0x2f:			// RLA	a
      break;
    case 0x30:			// BMI	*+d
      bmi_30();
      break;
    case 0x31:			// AND	(d),y
      break;
    case 0x32:			// STP
      break;
    case 0x33:			// RLA	(d),y
      break;
    case 0x34:			// NOP	d,x
      break;
    case 0x35:			// AND	d,x
      break;
    case 0x36:			// ROL	d,x
      break;
    case 0x37:			// RLA	d,x
      break;
    case 0x38:			// SEC
      sec_38();
      break;
    case 0x39:			// AND	a,y
      break;
    case 0x3a:			// NOP
      break;
    case 0x3b:			// RLA	a,y
      break;
    case 0x3c:			// NOP	a,x
      break;
    case 0x3d:			// AND	a,x
      break;
    case 0x3e:			// ROL	a,x
      break;
    case 0x3f:			// RLA	a,x
      break;
    case 0x40:			// RTI
      rti_40();
      break;
    case 0x41:			// EOR	(d,x)
      break;
    case 0x42:			// STP
      break;
    case 0x43:			// SRE	(d,x)
      break;
    case 0x44:			// NOP	d
      break;
    case 0x45:			// EOR	d
      break;
    case 0x46:			// LSR	d
      break;
    case 0x47:			// SRE	d
      break;
    case 0x48:			// PHA
      pha_48();
      break;
    case 0x49:			// EOR	#i
      eor_49();
      break;
    case 0x4a:			// LSR
      break;
    case 0x4b:			// ALR	#i
      break;
    case 0x4c:			// JMP	a
      jmp_4c();
      break;
    case 0x4d:			// EOR	a
      break;
    case 0x4e:			// LSR	a
      break;
    case 0x4f:			// SRE	a
      break;
    case 0x50:			// BVC	*+d
      bvc_50();
      break;
    case 0x51:			// EOR	(d),y
      break;
    case 0x52:			// STP
      break;
    case 0x53:			// SRE	(d),y
      break;
    case 0x54:			// NOP	d,x
      break;
    case 0x55:			// EOR	d,x
      break;
    case 0x56:			// LSR	d,x
      break;
    case 0x57:			// SRE	d,x
      break;
    case 0x58:			// CLI
      cli_58();
      break;
    case 0x59:			// EOR	a,y
      break;
    case 0x5a:			// NOP
      break;
    case 0x5b:			// SRE	a,y
      break;
    case 0x5c:			// NOP	a,x
      break;
    case 0x5d:			// EOR	a,x
      break;
    case 0x5e:			// LSR	a,x
      break;
    case 0x5f:			// SRE	a,x
      break;
    case 0x60:			// RTS
      rts_60();
      break;
    case 0x61:			// ADC	(d,x)
      break;
    case 0x62:			// STP
      break;
    case 0x63:			// RRA	(d,x)
      break;
    case 0x64:			// NOP	d
      break;
    case 0x65:			// ADC	d
      break;
    case 0x66:			// ROR	d
      break;
    case 0x67:			// RRA	d
      break;
    case 0x68:			// PLA
      pla_68();
      break;
    case 0x69:			// ADC	#i
      adc_69();
      break;
    case 0x6a:			// ROR
      break;
    case 0x6b:			// ARR	#i
      break;
    case 0x6c:			// JMP	(a)
      jmp_6c();
      break;
    case 0x6d:			// ADC	a
      break;
    case 0x6e:			// ROR	a
      break;
    case 0x6f:			// RRA	a
      break;
    case 0x70:			// BVS	*+d
      bvs_70();
      break;
    case 0x71:			// ADC	(d),y
      break;
    case 0x72:			// STP
      break;
    case 0x73:			// RRA	(d),y
      break;
    case 0x74:			// NOP	d,x
      break;
    case 0x75:			// ADC	d,x
      break;
    case 0x76:			// ROR	d,x
      break;
    case 0x77:			// RRA	d,x
      break;
    case 0x78:			// SEI
      sei_78();
      break;
    case 0x79:			// ADC	a,y
      break;
    case 0x7a:			// NOP
      break;
    case 0x7b:			// RRA	a,y
      break;
    case 0x7c:			// NOP	a,x
      break;
    case 0x7d:			// ADC	a,x
      break;
    case 0x7e:			// ROR	a,x
      break;
    case 0x7f:			// RRA	a,x
      break;
    case 0x80:			// NOP	#i
      break;
    case 0x81:			// STA	(d,x)
      break;
    case 0x82:			// NOP	#i
      break;
    case 0x83:			// SAX	(d,x)
      break;
    case 0x84:			// STY	d
      break;
    case 0x85:			// STA	d
      sta_85();
      break;
    case 0x86:			// STX	d
      stx_86();
      break;
    case 0x87:			// SAX	d
      break;
    case 0x88:			// DEY
      dey_88();
      break;
    case 0x89:			// NOP	#i
      break;
    case 0x8a:			// TXA
      txa_8a();
      break;
    case 0x8b:			// XAA	#i
      break;
    case 0x8c:			// STY	a
      break;
    case 0x8d:			// STA	a
      sta_8d();
      break;
    case 0x8e:			// STX	a
      break;
    case 0x8f:			// SAX	a
      break;
    case 0x90:			// BCC	*+d
      bcc_90();
      break;
    case 0x91:			// STA	(d),y
      break;
    case 0x92:			// STP
      break;
    case 0x93:			// AHX	(d),y
      break;
    case 0x94:			// STY	(d),y
      break;
    case 0x95:			// STA	d,x
      break;
    case 0x96:			// STX	d,y
      break;
    case 0x97:			// SAX	d,y
      break;
    case 0x98:			// TYA
      tya_98();
      break;
    case 0x99:			// STA	a,y
      sta_99();
      break;
    case 0x9a:			// TXS
      txs_9a();
      break;
    case 0x9b:			// TAS	a,y
      break;
    case 0x9c:			// SHY	a,x
      break;
    case 0x9d:			// STA	a,x
      break;
    case 0x9e:			// SHX	a,y
      break;
    case 0x9f:			// AHX	a,y
      break;
    case 0xa0:			// LDY	#i
      ldy_a0();
      break;
    case 0xa1:			// LDA	(d,x)
      break;
    case 0xa2:			// LDX	#i
      ldx_a2();
      break;
    case 0xa3:			// LAX	(d,x)
      break;
    case 0xa4:			// LDY	d
      break;
    case 0xa5:			// LDA	d
      lda_a5();
      break;
    case 0xa6:			// LDX	d
      ldx_a6();
      break;
    case 0xa7:			// LAX	d
      break;
    case 0xa8:			// TAY
     tay_a8();
      break;
    case 0xa9:			// LDA	#i
      lda_a9();
      break;
    case 0xaa:			// TAX
      tax_aa();
      break;
    case 0xab:			// LAX	#i
      break;
    case 0xac:			// LDY	a
      break;
    case 0xad:			// LDA	a
      lda_ad();
      break;
    case 0xae:			// LDX	a
      break;
    case 0xaf:			// LAX	a
      break;
    case 0xb0:			// BCS	*+d
      bcs_b0();
      break;
    case 0xb1:			// LDA	(d),y
      break;
    case 0xb2:			// STP
      break;
    case 0xb3:			// LAX	(d),y
      break;
    case 0xb4:			// LDY	d,x
      break;
    case 0xb5:			// LDA	d,x
      break;
    case 0xb6:			// LDX	d,y
      ldx_b6();
      break;
    case 0xb7:			// LAX	d,y
      break;
    case 0xb8:			// CLV
      clv_b8();
      break;
    case 0xb9:			// LDA	a,y
      break;
    case 0xba:			// TSX
      tsx_ba();
      break;
    case 0xbb:			// LAS	a,y
      break;
    case 0xbc:			// LDY	a,x
      break;
    case 0xbd:			// LDA	a,x
      lda_bd();
      break;
    case 0xbe:			// LDX	a,y
      ldx_be();
      break;
    case 0xbf:			// LAX	a,y
      break;
    case 0xc0:			// CPY	#i
      cpy_c0();
      break;
    case 0xc1:			// CMP	(d,x)
      break;
    case 0xc2:			// NOP	#i
      break;
    case 0xc3:			// DCP	(d,x)
      break;
    case 0xc4:			// CPY	d
      break;
    case 0xc5:			// CMP	d
      break;
    case 0xc6:			// DEC	d
      break;
    case 0xc7:			// DCP	d
      break;
    case 0xc8:			// INY
      iny_c8();
      break;
    case 0xc9:			// CMP	#i
      cmp_c9();
      break;
    case 0xca:			// DEX
      dex_ca();
      break;
    case 0xcb:			// AXS	#i
      break;
    case 0xcc:			// CPY	a
      break;
    case 0xcd:			// CMP	a
      cmp_cd();
      break;
    case 0xce:			// DEC	a
      break;
    case 0xcf:			// DCP	a
      break;
    case 0xd0:			// BNE	*+d
      bne_d0();
      break;
    case 0xd1:			// CMP	(d),y
      break;
    case 0xd2:			// STP
      break;
    case 0xd3:			// DCP	(d),y
      break;
    case 0xd4:			// NOP	d,x
      break;
    case 0xd5:			// CMP	d,x
      break;
    case 0xd6:			// DEC	d,x
      break;
    case 0xd7:			// DCP	d,x
      break;
    case 0xd8:			// CLD
      cdl_d8();
      break;
    case 0xd9:			// CMP	a,y
      cmp_d9();
      break;
    case 0xda:			// NOP
      break;
    case 0xdb:			// DCP	a,y
      break;
    case 0xdc:			// NOP	a,x
      break;
    case 0xcdd:			// CMP	a,x
      break;
    case 0xde:			// DEC	a,x
      break;
    case 0xdf:			// DCP	a,x
      break;
    case 0xe0:			// CPX	#i
      cpx_e0();
      break;
    case 0xe1:			// SBC	(d,x)
      break;
    case 0xe2:			// NOP	#i
      break;
    case 0xe3:			// ISC	(d,x)
      break;
    case 0xe4:			// CPX	d
      break;
    case 0xe5:			// SBC	d
      break;
    case 0xe6:			// INC	d
      break;
    case 0xe7:			// ISC	d
      break;
    case 0xe8:			// INX
      inx_e8();
      break;
    case 0xe9:			// SBC	#i
      break;
    case 0xea:			// NOP
      nop_ea();
      break;
    case 0xeb:			// SBC	#i
      break;
    case 0xec:			// CPX	a
      break;
    case 0xed:			// SBC	a
      break;
    case 0xee:			// INC	a
      break;
    case 0xef:			// ISC	a
      break;
    case 0xf0:			// BEQ	*+d
      beq_f0();
      break;
    case 0xf1:			// SBC	(d),y
      break;
    case 0xf2:			// STP
      break;
    case 0xf3:			// ISC	(d),y
      break;
    case 0xf4:			// NOP	d,x
      break;
    case 0xf5:			// SBC	d,x
      break;
    case 0xf6:			// INC	d,x
      break;
    case 0xf7:			// ISC	d,x
      break;
    case 0xf8:			// SED
      sed_f8();
      break;
    case 0xf9:			// SBC	a,y
      break;
    case 0xfa:			// NOP
      break;
    case 0xfb:			// ISC	a,y
      break;
    case 0xfc:			// NOP	a,x
      break;
    case 0xfd:			// SBC	a,x
      break;
    case 0xfe:			// INC	a,x
      break;
    case 0xff:			// ISC	a,x
      break;
    default:
      ret = false;
    }

#ifdef DEBUG
  std::cout<<"Exiting dispatchInstruction() with state:\n";
  printArchitecturalState();
  debugDispatchInstruction();
#endif
  
  return ret;
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
