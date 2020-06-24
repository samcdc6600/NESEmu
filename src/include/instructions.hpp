/* This file is only intended for use with "cpu.cpp". It exists only to break up
   "cpu.cpp". This is beneficial because it allows a logical splitting of the
   logic that handles the CPU instructions from the rest of the code for the CPU
   in cpu.cpp and more importantly it allows us to reduce the length of the
   cpu.cpp file as well as allowing us to have both file open in two different
   editor windows simultaneously. We put both function declarations and
   definitions here becase we are accessing the "architecturalState" namespace
   and our functions are inline, both of these factors necessitate that our
   function definitions be in this file. */
#ifndef INSTRUCTIONS_HPP_
#define INSTRUCTIONS_HPP_
// We have a separet function for each opcode for performance reasons.

// =================== SUB INSTRUCTION GRANULARITY OPERATIONS ==================
// =========== (The below functions prototypes are used for operations =========
// ============ that do not in them selves constitute instructions.) ===========
/* Here if the function has more then one argument (in general) the first should
   be the register and the second the immediate or datum from memory (that is if
   the function is used as such.) Also note that "minimumAddressableUnit" and
   "isaReg" are both of type unsigned char (so they can be used interchangeably,
   however we try not to do so for reasons of consistency.)  */
inline void setCarryFlagOnAdditionOn(const architecturalState::isaReg a,
				     const architecturalState::isaReg b);
inline void setOverFlowOnAdditionOn(const architecturalState::isaReg a,
				    const architecturalState::isaReg b,
				    const architecturalState::isaReg c);
inline void setZeroFlagOn(const architecturalState::isaReg var);
inline void setDecimalFlagOn(const bool d);
inline void setNegativeFlagOn(const architecturalState::isaReg var);
inline memory::minimumAddressableUnit get8BitImmediate();
inline memory::address get16BitImmediate();
inline void storeAbsoluteThis(const architecturalState::isaReg var);
inline void loadPCFrom16BitImmediate();
// Return true if we have crossed a page boundry
inline bool add8BitImmediateToPCAndCheckPageBoundryTransition();
inline void branchTaken();
inline memory::minimumAddressableUnit pullFromStack();
inline memory::minimumAddressableUnit get8BitAtAddress(const memory::address a);

// ======================== INSTRUCTION SPECIALIZATIONS  =======================
// ============== (The below functions prototypes comprise full  ===============
// ==== instructions. Functions that belong to the same class of instruction ===
// ============ (indicated by their prefixs) are grouped together.) ============
/* Note: PC should be altered after calling "SUB INSTRUCTION GRANULARITY
   OPERATIONS", as these functions assume it has not been altered yet! */
/* PLP  Pull Processor Status from Stack (where pull is analogous to pop.) */
inline void bpl_10();	// BPL	*+d
inline void clc_18();	// CLC
inline void plp_28();	// PLP
inline void eor_49();	// EOR	#i
inline void jmp_4c();	// JMP	a
inline void adc_69();	// ADC	#i
inline void dey_88();	// DEY
inline void sta_8d();	// STA	a
inline void tya_98();	// TYA
inline void txs_9a();	// TXS
inline void ldy_a0();	// LDY	#i
inline void ldx_a2();	// LDX	#i
inline void lda_a9();	// TAX
inline void tax_aa();	// TAX
inline void lda_ad();	// LDA	a
inline void cmp_c9();	// CMP	#i
inline void dex_ca();	// DEX
inline void bne_d0();	// BNE	*+d
inline void cdl_d8();	// CLD
inline void nop_ea();	// NOP
inline void beq_f0();	// BEQ	*+d


// =================== SUB INSTRUCTION GRANULARITY OPERATIONS ==================
// ============ (The below functions are used for operations that do ===========
// ================ not in them selves constitute instructions.) ===============


inline void setCarryFlagOnAdditionOn(const architecturalState::isaReg a,
				     const architecturalState::isaReg b)
{
  architecturalState::status.u.C =
    (masks::bit8 & (architecturalState::largerThenAXY(a) + b)) ? 1 : 0;
}


inline void setOverFlowOnAdditionOn(const architecturalState::isaReg a,
				    const architecturalState::isaReg b,
				    const architecturalState::isaReg c)
{
  /* An explination of the following:
     https://stackoverflow.com/questions/16845912/determining-carry-and-overflow-flag-in-6502-emulation-in-java  */
  architecturalState::status.u.V = (~(a ^ b)) & (a ^ c) & masks::bit7;
}


inline void setZeroFlagOn(const architecturalState::isaReg var)
{
  architecturalState::status.u.Z = !var ? 1 : 0;
}


inline void setDecimalFlagOn(const bool d)
{
  architecturalState::status.u.D = d;
}


void setNegativeFlagOn(const architecturalState::isaReg var)
{
  architecturalState::status.u.N = (var & masks::bit7) ? 1 : 0;
}


inline memory::minimumAddressableUnit get8BitImmediate()
{
  return memory::mem[architecturalState::PC + 1];
}


inline memory::address get16BitImmediate()
{
   return (memory::address(memory::mem[architecturalState::PC + 2])
			  << memory::minimumAddressableUnitSize) |
     memory::address(memory::mem[architecturalState::PC + 1]);
}


inline void storeAbsoluteThis(const architecturalState::isaReg var)
{
  memory::mem[get16BitImmediate()] = var;
}


inline void loadPCFrom16BitImmediate()
{
  architecturalState::PC = get16BitImmediate();
}


inline bool add8BitImmediateToPCAndCheckPageBoundryTransition()
{  
  bool ret {false};
  const memory::address pageNum {memory::address(architecturalState::PC %
						 memory::pageSize)};
  
  architecturalState::PC += (signed char)get8BitImmediate();
  
  if(pageNum != (architecturalState::PC % memory::pageSize))
    ret = true;
  return ret;
}


inline void branchTaken()
{
  if(add8BitImmediateToPCAndCheckPageBoundryTransition())
    architecturalState::cycles += 1;
  architecturalState::cycles += 1;
}


inline memory::minimumAddressableUnit pullFromStack()
{
  return get8BitAtAddress(architecturalState::stackBase |
			  architecturalState::S--);
}


inline memory::minimumAddressableUnit get8BitAtAddress(const memory::address a)
{
  return memory::mem[a];
}


// ======================== INSTRUCTION SPECIALIZATIONS  =======================
// ============== (The below functions comprise full instructions. =============
// =========== Functions that belong to the same class of instruction ==========
// ============ (indicated by their prefixs) are grouped together.) ============


inline void bpl_10()
{ /* Branches are dependant on the status of the flag bits when the op code is
     encountered. A branch not taken requires two machine cycles. Add one if the
     branch is taken and add one more if the branch crosses a page boundary. */
  if(architecturalState::status.u.N == 0)
    branchTaken();
  architecturalState::PC += 2;	// This is done even if branch is taken.
  architecturalState::cycles += 2;
}


inline void clc_18()
{				// Clear Carry Flag
  architecturalState::status.u.C = 0;
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


inline void plp_28()
{ /* With the 6502, the stack is always on page one ($100-$1FF) and works top
     down. - http://6502.org/tutorials/6502opcodes.html#PLP */
  architecturalState::status.flags = pullFromStack();
  architecturalState::PC += 1;
  architecturalState::cycles += 4;
}


/*! \brief Exclusive-OR Memory with Accumulator.

  A EOR M -> A					||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Immediate	||
  Assembly Language Form:	EOR #Operand	||
  Opcode:			49		||
  Bytes 2					||
  Cycles 2					|| */
inline void eor_49()
{
  architecturalState::A ^= get8BitImmediate();
  setNegativeFlagOn(architecturalState::A);
  setZeroFlagOn(architecturalState::A);
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


inline void jmp_4c()
{
  loadPCFrom16BitImmediate();
  architecturalState::cycles += 3;
}


inline void adc_69()
{
  architecturalState::isaReg aR {architecturalState::isaReg(architecturalState::A
							    + get8BitImmediate())};
  setCarryFlagOnAdditionOn(architecturalState::A, get8BitImmediate());
  setOverFlowOnAdditionOn(architecturalState::A, get8BitImmediate(), aR);
  architecturalState::A = aR;
  setNegativeFlagOn(architecturalState::A);
  setZeroFlagOn(architecturalState::A);
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


inline void dey_88()
{
  architecturalState::Y -= 1;
  setNegativeFlagOn(architecturalState::Y);
  setZeroFlagOn(architecturalState::Y);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


inline void sta_8d()
{
  storeAbsoluteThis(architecturalState::A);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


inline void tya_98()
{
  architecturalState::A = architecturalState::Y;
  setNegativeFlagOn(architecturalState::A);
  setZeroFlagOn(architecturalState::A);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


inline void txs_9a()
{ /* "TXS (Transfer X Index to Stack Pointer) transfers the value in the X
     index to the stack pointer."
     - http://www.thealmightyguru.com/Games/Hacking/Wiki/index.php?title=TXS */
  setNegativeFlagOn(architecturalState::X);
  setZeroFlagOn(architecturalState::X);
  architecturalState::S = architecturalState::X;
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}

inline void ldy_a0()
{
  architecturalState::Y = get8BitImmediate();
  setNegativeFlagOn(architecturalState::Y);
  setZeroFlagOn(architecturalState::Y);
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


inline void ldx_a2()
{
  architecturalState::X = get8BitImmediate();
  setNegativeFlagOn(architecturalState::X);
  setZeroFlagOn(architecturalState::X);
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


inline void lda_a9()
{
  architecturalState::A = get8BitImmediate();
  setNegativeFlagOn(architecturalState::A);
  setZeroFlagOn(architecturalState::A);
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


inline void tax_aa()
{
  architecturalState::X = architecturalState::A;
  setNegativeFlagOn(architecturalState::X);
  setZeroFlagOn(architecturalState::X);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


inline void lda_ad()
{
  architecturalState::A = memory::mem[get16BitImmediate()];
  setNegativeFlagOn(architecturalState::A);
  setZeroFlagOn(architecturalState::A);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


inline void cmp_c9()
{ /* Compare sets flags as if a subtraction had been carried out. If the value
     in the accumulator is equal or greater than the compared value, the Carry
     will be set. The equal (Z) and negative (N) flags will be set based on
     equality or lack thereof and the sign (i.e. A>=$80) of the accumulator.
     - http://6502.org/tutorials/6502opcodes.html#CMP */
  architecturalState::status.u.C = ((architecturalState::A == get8BitImmediate())
				    || (architecturalState::A >
					get8BitImmediate())) ? 1 : 0;
  setZeroFlagOn(architecturalState::A - get8BitImmediate());
  setNegativeFlagOn(architecturalState::A - get8BitImmediate());
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


inline void dex_ca()
{
  architecturalState::X -= 1;
  setNegativeFlagOn(architecturalState::X);
  setZeroFlagOn(architecturalState::X);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


inline void bne_d0()
{ /* "Branches are dependant on the status of the flag bits when the op code is
     encountered. A branch not taken requires two machine cycles. Add one if the
     branch is taken and add one more if the branch crosses a page boundary."
     - http://6502.org/tutorials/6502opcodes.html#BNE */
  if(architecturalState::status.u.Z == 0)
    branchTaken();
  architecturalState::PC += 2;	// This is done even if branch is taken.
  architecturalState::cycles += 2;
}


inline void cdl_d8()
{ /* "CLD (Clear Decimal Flag) clears the Decimal Flag in the Processor Status
     Register by setting the 3rd bit 0." "Even though the NES doesn't use
     decimal mode, the opcodes to clear and set the flag do work, so if you need
     to store a bit, this acts as a free space."
     - http://www.thealmightyguru.com/Games/Hacking/Wiki/index.php?title=CLD */
  setDecimalFlagOn(false);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


inline void nop_ea()
{
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


inline void beq_f0()
{
  if(architecturalState::status.u.Z == 1)
    branchTaken();
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


#endif
