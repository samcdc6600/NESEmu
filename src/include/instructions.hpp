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
inline void pushToStack(const memory::minimumAddressableUnit var);
inline memory::minimumAddressableUnit get8BitAtAddress(const memory::address a);
inline void set8BitAtAddress(const memory::address a,
			     const memory::minimumAddressableUnit var);
// ======================== INSTRUCTION SPECIALIZATIONS  =======================
// ============== (The below functions prototypes comprise full  ===============
// ==== instructions. Functions that belong to the same class of instruction ===
// ============ (indicated by their prefixs) are grouped together.) ============
/* Note: PC should be altered after calling "SUB INSTRUCTION GRANULARITY
   OPERATIONS", as these functions assume it has not been altered yet! */
/* PLP  Pull Processor Status from Stack (where pull is analogous to pop.) */
inline void bpl_10();
inline void clc_18();
inline void plp_28();
inline void bmi_30();
inline void pha_48();
inline void eor_49();
inline void jmp_4c();
inline void adc_69();
inline void dey_88();
inline void sta_8d();
inline void bcc_90();
inline void tya_98();
inline void txs_9a();
inline void ldy_a0();
inline void ldx_a2();
inline void tay_a8();
inline void lda_a9();
inline void tax_aa();
inline void lda_ad();
inline void bcs_b0();
inline void cpy_c0();
inline void cmp_c9();
inline void dex_ca();
inline void cmp_cd();
inline void bne_d0();
inline void cdl_d8();
inline void cpx_e0();
inline void nop_ea();
inline void beq_f0();


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
			  ++architecturalState::S);
}


inline void pushToStack(const memory::minimumAddressableUnit var)
{
  set8BitAtAddress(architecturalState::stackBase | architecturalState::S--,
		   var);
}


inline memory::minimumAddressableUnit get8BitAtAddress(const memory::address a)
{
  return memory::mem[a];
}


inline void set8BitAtAddress(const memory::address a,
			     const memory::minimumAddressableUnit var)
{
  memory::mem[a] = var;
}


// ======================== INSTRUCTION SPECIALIZATIONS  =======================
// ============== (The below functions comprise full instructions. =============
// =========== Functions that belong to the same class of instruction ==========
// ============ (indicated by their prefixs) are grouped together.) ============


/*! \brief Branch on Result Plus.

  branch on N = 0		       		||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Relative	||
  Assembly Language Form:	BPL oper	||
  Opcode:			10		||
  Bytes 2					||
  Cycles 2**					||
  Branches are dependant on the status of the flag bits when the op code is
  encountered. A branch not taken requires two machine cycles. Add one if the
  branch is taken and add one more if the branch crosses a page boundary. From:
  http://6502.org/tutorials/6502opcodes.html#BCC */
inline void bpl_10()
{
  if(architecturalState::status.u.N == 0)
    branchTaken();
  architecturalState::PC += 2;	// This is done even if branch is taken.
  architecturalState::cycles += 2;
}


/*! \brief Clear Carry Flag.

  0 -> C			       		||
  (N-, Z-, C 0, I-, D-, V-) 			||
  Addressing Mode:		implied		||
  Assembly Language Form:	CLC		||
  Opcode:			18		||
  Bytes 1					||
  Cycles 2					|| */
inline void clc_18()
{
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


/*! \brief Branch on Result Minus

  Branch on N = 1		       		||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Relative	||
  Assembly Language Form:	BMI oper	||
  Opcode:			30		||
  Bytes 2					||
  Cycles 2**					||
  Branches are dependant on the status of the flag bits when the op code is
  encountered. A branch not taken requires two machine cycles. Add one if the
  branch is taken and add one more if the branch crosses a page boundary. From:
  http://6502.org/tutorials/6502opcodes.html#BCC */
inline void bmi_30()
{
  if(architecturalState::status.u.N == 1)
    branchTaken();
  architecturalState::PC += 2;	// This is done even if branch is taken.
  architecturalState::cycles += 2;
}


/*! \brief Push Accumulator on Stack

  Push A					||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	PHA		||
  Opcode:			48		||
  Bytes 1					||
  Cycles 3					|| */
inline void pha_48()
{
  pushToStack(architecturalState::A);
  architecturalState::PC += 1;
  architecturalState::cycles += 3;
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
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
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
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


inline void dey_88()
{
  architecturalState::Y -= 1;
  setZeroFlagOn(architecturalState::Y);
  setNegativeFlagOn(architecturalState::Y);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


inline void sta_8d()
{
  storeAbsoluteThis(architecturalState::A);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}



/*! \brief Branch on Carry Clear

  branch on C = 0			        ||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Relative	||
  Assembly Language Form:	BCC oper	||
  Opcode:			90		||
  Bytes 2					||
  Cycles 2**					||
  Branches are dependant on the status of the flag bits when the op code is
  encountered. A branch not taken requires two machine cycles. Add one if the
  branch is taken and add one more if the branch crosses a page boundary. From:
  http://6502.org/tutorials/6502opcodes.html#BCC */
inline void bcc_90()
{
  if(architecturalState::status.u.C == 0)
    branchTaken();
  architecturalState::PC += 2;	// This is done even if branch is taken.
  architecturalState::cycles += 2;
}


inline void tya_98()
{
  architecturalState::A = architecturalState::Y;
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


inline void txs_9a()
{ /* "TXS (Transfer X Index to Stack Pointer) transfers the value in the X
     index to the stack pointer."
     - http://www.thealmightyguru.com/Games/Hacking/Wiki/index.php?title=TXS */
  setZeroFlagOn(architecturalState::X);
  setNegativeFlagOn(architecturalState::X);
  architecturalState::S = architecturalState::X;
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}

inline void ldy_a0()
{
  architecturalState::Y = get8BitImmediate();
  setZeroFlagOn(architecturalState::Y);
  setNegativeFlagOn(architecturalState::Y);
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


inline void ldx_a2()
{
  architecturalState::X = get8BitImmediate();
  setZeroFlagOn(architecturalState::X);
  setNegativeFlagOn(architecturalState::X);
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


/*! \brief Transfer Accumulator to Index Y

  A -> Y				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	TAY		||
  Opcode:			A8		||
  Bytes 1					||
  Cycles 2					|| */
inline void tay_a8()
{
  architecturalState::Y = architecturalState::A;
  setZeroFlagOn(architecturalState::Y);
  setNegativeFlagOn(architecturalState::Y);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


inline void lda_a9()
{
  architecturalState::A = get8BitImmediate();
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


inline void tax_aa()
{
  architecturalState::X = architecturalState::A;
  setZeroFlagOn(architecturalState::X);
  setNegativeFlagOn(architecturalState::X);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


inline void lda_ad()
{
  architecturalState::A = get8BitAtAddress(get16BitImmediate());
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


/*! \brief Branch on Carry Set

  Branch on C = 1			       	||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Relative	||
  Assembly Language Form:	BCS oper	||
  Opcode:			B0		||
  Bytes 2					||
  Cycles 2**					||
  Branches are dependant on the status of the flag bits when the op code is
  encountered. A branch not taken requires two machine cycles. Add one if the
  branch is taken and add one more if the branch crosses a page boundary. From:
  http://6502.org/tutorials/6502opcodes.html#BCC */
inline void bcs_b0()
{
  if(architecturalState::status.u.C == 1)
    branchTaken();
  architecturalState::PC += 2;	// This is done even if branch is taken.
  architecturalState::cycles += 2;
}


/*! \brief Compare Memory and Index Y

  Y - M						||
  (N+, Z+, C+, I-, D-, V-) 			||
  Addressing Mode:		Immediate	||
  Assembly Language Form:	CPY #oper	||
  Opcode:			C0		||
  Bytes 2					||
  Cycles 2					|| */
inline void cpy_c0()
{
  architecturalState::status.u.C = ((architecturalState::Y == get8BitImmediate())
				    || (architecturalState::Y >
					get8BitImmediate())) ? 1 : 0;
  setZeroFlagOn(architecturalState::Y - get8BitImmediate());
  setNegativeFlagOn(architecturalState::Y - get8BitImmediate());
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


/*! \brief Compare Memory with Accumulator

  A - M						||
  (N+, Z+, C+, I-, D-, V-)			||
  Addressing Mode:		Immediate	||
  Assembly Language Form:	CMP #oper	||
  Opcode:			C9		||
  Bytes 2					||
  Cycles 2					||
  Compare sets flags as if a subtraction had been carried out. If the value
  in the accumulator is equal or greater than the compared value, the Carry
  will be set. The equal (Z) and negative (N) flags will be set based on
  equality or lack thereof and the sign (i.e. A>=$80) of the accumulator.
  - http://6502.org/tutorials/6502opcodes.html#CMP */
inline void cmp_c9()
{
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
  setZeroFlagOn(architecturalState::X);
  setNegativeFlagOn(architecturalState::X);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


/*! \brief Compare Memory with Accumulator

  A - M						||
  (N+, Z+, C+, I-, D-, V-)			||
  Addressing Mode:		Absolute	||
  Assembly Language Form:	CMP oper	||
  Opcode:			CD		||
  Bytes 3					||
  Cycles 4					|| */
inline void cmp_cd()
{
  architecturalState::status.u.C = ((architecturalState::A == get8BitAtAddress(get16BitImmediate()))
				    || (architecturalState::A >
					get8BitAtAddress(get16BitImmediate()))) ? 1 : 0;
  setZeroFlagOn(architecturalState::A - get8BitAtAddress(get16BitImmediate()));
  setNegativeFlagOn(architecturalState::A - get8BitAtAddress(get16BitImmediate()));
  std::cout<<std::hex<<get16BitImmediate()<<"\n";
  std::cout<<std::hex<<get8BitAtAddress(get16BitImmediate())<<"\n";
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


/*! \brief Compare Memory with Accumulator

  A - M						||
  (N+, Z+, C+, I-, D-, V-)			||
  Addressing Mode:		Immediate	||
  Assembly Language Form:	CMP #oper	||
  Opcode:			C9		||
  Bytes 2					||
  Cycles 2					||
  Compare sets flags as if a subtraction had been carried out. If the value
  in the accumulator is equal or greater than the compared value, the Carry
  will be set. The equal (Z) and negative (N) flags will be set based on
  equality or lack thereof and the sign (i.e. A>=$80) of the accumulator.
  - http://6502.org/tutorials/6502opcodes.html#CMP */
/*inline void cmp_c9()
{
  architecturalState::status.u.C = ((architecturalState::A == get8BitImmediate())
				    || (architecturalState::A >
					get8BitImmediate())) ? 1 : 0;
  setZeroFlagOn(architecturalState::A - get8BitImmediate());
  setNegativeFlagOn(architecturalState::A - get8BitImmediate());
  architecturalState::PC += 2;
  architecturalState::cycles += 2;*/


inline void bne_d0()
{ /* "Branches are dependant on the status of the flag bits when the op code is
     encountered. A branch not taken requires two machine cycles. Add one if the
     branch is taken and add one more if the branch crosses a page boundary."
     - http://6502.org/tutorials/6502opcodes.html#BNE */
  if(architecturalState::status.u.Z == 0)
    branchTaken();
  std::cout<<"architecturalState::PC = "<<architecturalState::PC<<'\n';
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


/*! \brief Compare Memory and Index X

  X - M						||
  (N+, Z+, C+, I-, D-, V-)			||
  Addressing Mode:		Immediate	||
  Assembly Language Form:	CPX #oper	||
  Opcode:			e0		||
  Bytes 2					||
  Cycles 2					|| */
inline void cpx_e0()
{
  architecturalState::status.u.C = ((architecturalState::X == get8BitImmediate())
				    || (architecturalState::X >
					get8BitImmediate())) ? 1 : 0;
  setZeroFlagOn(architecturalState::X - get8BitImmediate());
  setNegativeFlagOn(architecturalState::X - get8BitImmediate());
  architecturalState::PC += 2;
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
