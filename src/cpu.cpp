#include "include/cpu.hpp"
#include "include/mem.hpp"


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


bool foo()
{
  switch(memory::mem[architecturalState::PC])
    {				// There are 151 official 6502 opcodes organized
				// into 56 instructions (note that the NES does
      				// not support decimal mode and also that there
      				// are a number of unofficial opcodes.)

    case 0x0000:	// BRK
      break;
    case 0x0001:	// ORA
      break;
    case 0x0002:	// STP	(d,x)
      break;
    case 0x0003:	// SLO
      break;
    case 0x0004:	// NOP	(d,x)
      break;
    case 0x0005:	// ORA	d
      break;
    case 0x0006:	// ASL	d
      break;
    case 0x0007:	// SLO	d
      break;
    case 0x0008:	// PHP	d (God personal home page terrible!)
      break;
    case 0x0009:	// ORA
      break;
    case 0x000A:	// ASL	#i
      break;
// 	ANC
// #i 	NOP
// a 	ORA
// a 	ASL
// a 	SLO
// a 	BPL
// *+d 	ORA
// (d),y 	STP
// 	SLO
// (d),y 	NOP
// d,x 	ORA
// d,x 	ASL
// d,x 	SLO
// d,x 	CLC
// 	ORA
// a,y 	NOP
// 	SLO
// a,y 	NOP
// a,x 	ORA
// a,x 	ASL
// a,x 	SLO
// a,x
// 20 	JSR
// a 	AND
// (d,x) 	STP
// 	RLA
// (d,x) 	BIT
// d 	AND
// d 	ROL
// d 	RLA
// d 	PLP
// 	AND
// #i 	ROL
// 	ANC
// #i 	BIT
// a 	AND
// a 	ROL
// a 	RLA
// a 	BMI
// *+d 	AND
// (d),y 	STP
// 	RLA
// (d),y 	NOP
// d,x 	AND
// d,x 	ROL
// d,x 	RLA
// d,x 	SEC
// 	AND
// a,y 	NOP
// 	RLA
// a,y 	NOP
// a,x 	AND
// a,x 	ROL
// a,x 	RLA
// a,x
// 40 	RTI
// 	EOR
// (d,x) 	STP
// 	SRE
// (d,x) 	NOP
// d 	EOR
// d 	LSR
// d 	SRE
// d 	PHA
// 	EOR
// #i 	LSR
// 	ALR
// #i 	JMP
// a 	EOR
// a 	LSR
// a 	SRE
// a 	BVC
// *+d 	EOR
// (d),y 	STP
// 	SRE
// (d),y 	NOP
// d,x 	EOR
// d,x 	LSR
// d,x 	SRE
// d,x 	CLI
// 	EOR
// a,y 	NOP
// 	SRE
// a,y 	NOP
// a,x 	EOR
// a,x 	LSR
// a,x 	SRE
// a,x
// 60 	RTS
// 	ADC
// (d,x) 	STP
// 	RRA
// (d,x) 	NOP
// d 	ADC
// d 	ROR
// d 	RRA
// d 	PLA
// 	ADC
// #i 	ROR
// 	ARR
// #i 	JMP
// (a) 	ADC
// a 	ROR
// a 	RRA
// a 	BVS
// *+d 	ADC
// (d),y 	STP
// 	RRA
// (d),y 	NOP
// d,x 	ADC
// d,x 	ROR
// d,x 	RRA
// d,x 	SEI
// 	ADC
// a,y 	NOP
// 	RRA
// a,y 	NOP
// a,x 	ADC
// a,x 	ROR
// a,x 	RRA
// a,x
// 80 	NOP
// #i 	STA
// (d,x) 	NOP
// #i 	SAX
// (d,x) 	STY
// d 	STA
// d 	STX
// d 	SAX
// d 	DEY
// 	NOP
// #i 	TXA
// 	XAA
// #i 	STY
// a 	STA
// a 	STX
// a 	SAX
// a 	BCC
// *+d 	STA
// (d),y 	STP
// 	AHX
// (d),y 	STY
// d,x 	STA
// d,x 	STX
// d,y 	SAX
// d,y 	TYA
// 	STA
// a,y 	TXS
// 	TAS
// a,y 	SHY
// a,x 	STA
// a,x 	SHX
// a,y 	AHX
// a,y
// A0 	LDY
// #i 	LDA
// (d,x) 	LDX
// #i 	LAX
// (d,x) 	LDY
// d 	LDA
// d 	LDX
// d 	LAX
// d 	TAY
// 	LDA
// #i 	TAX
// 	LAX
// #i 	LDY
// a 	LDA
// a 	LDX
// a 	LAX
// a 	BCS
// *+d 	LDA
// (d),y 	STP
// 	LAX
// (d),y 	LDY
// d,x 	LDA
// d,x 	LDX
// d,y 	LAX
// d,y 	CLV
// 	LDA
// a,y 	TSX
// 	LAS
// a,y 	LDY
// a,x 	LDA
// a,x 	LDX
// a,y 	LAX
// a,y
// C0 	CPY
// #i 	CMP
// (d,x) 	NOP
// #i 	DCP
// (d,x) 	CPY
// d 	CMP
// d 	DEC
// d 	DCP
// d 	INY
// 	CMP
// #i 	DEX
// 	AXS
// #i 	CPY
// a 	CMP
// a 	DEC
// a 	DCP
// a 	BNE
// *+d 	CMP
// (d),y 	STP
// 	DCP
// (d),y 	NOP
// d,x 	CMP
// d,x 	DEC
// d,x 	DCP
// d,x 	CLD
// 	CMP
// a,y 	NOP
// 	DCP
// a,y 	NOP
// a,x 	CMP
// a,x 	DEC
// a,x 	DCP
// a,x
// E0 	CPX
// #i 	SBC
// (d,x) 	NOP
// #i 	ISC
// (d,x) 	CPX
// d 	SBC
// d 	INC
// d 	ISC
// d 	INX
// 	SBC
// #i 	NOP
// 	SBC
// #i 	CPX
// a 	SBC
// a 	INC
// a 	ISC
// a 	BEQ
// *+d 	SBC
// (d),y 	STP
// 	ISC
// (d),y 	NOP
// d,x 	SBC
// d,x 	INC
// d,x 	ISC
// d,x 	SED
// 	SBC
// a,y 	NOP
// 	ISC
// a,y 	NOP
// a,x 	SBC
// a,x 	INC
// a,x 	ISC
// a,x 
    }
}
