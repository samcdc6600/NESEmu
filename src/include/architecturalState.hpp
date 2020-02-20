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
  extern unsigned char A;		// Accumulator
  extern unsigned char X, Y;	// Index's
  extern memory::address PC;		// Program Counter
  extern unsigned char S;		// Stack Pointer
  constexpr memory::address stackBase {0x100}; // Base address of stack
  

  typedef union
  {
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
  }Status;
  constexpr size_t statusSize {8};

  extern Status status;
  extern size_t cycles;
}


#endif
