/* This file should only be included by cpu.cpp (and also by utils.cpp if
   building with the debug flag.) */
#ifndef ARCHITECUTRAL_STATE_HPP_
#define ARCHITECUTRAL_STATE_HPP_


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
  typedef unsigned largerThenAXY;
  typedef unsigned char isaReg;
  extern isaReg A;		// Accumulator
  extern isaReg X, Y;	// Index's
  extern memory::address PC;		// Program Counter
  extern isaReg S;		// Stack Pointer
  constexpr memory::address stackBase {0x100}; // Base address of stack
  

  typedef union
  {
    struct
    {
      isaReg C : 1;	// Carry	~===<( Lowest order byte  )>===~
      isaReg Z : 1;	// Zero
      isaReg I : 1;	// Interrupt Disable
      isaReg D : 1;	// Decimal
      isaReg s0 : 1;	// No CPU effect. (refere to the comment at the
      isaReg s1 : 1;	// top of the file.)
      isaReg V : 1;	// Overflow
      isaReg N : 1;	// Negative	~===<( Highest order byte )>===~
    }u;
    isaReg flags;
  }Status;
  constexpr size_t statusSize {8};
  /* The use of these variables is explained in a comment near the top of the
     file. */
  constexpr isaReg bFlagMaskPhpBrkAndIrqNmi {0b00110000};
  constexpr isaReg bFlagMaskIrqNmi {0b11101111};

  extern Status status;
  extern size_t cycles;
}


#endif
