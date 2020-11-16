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


// =================== SUB INSTRUCTION GRANULARITY OPERATIONS ==================
// =========== (The below functions prototypes are used for operations =========
// ============ that do not in them selves constitute instructions.) ===========
/* Here if the function has more then one argument (in general) the first should
   be the register and the second the immediate or datum from memory (that is if
   the function is used as such.) Also note that "minimumAddressableUnit" and
   "isaReg" are both of type unsigned char (so they can be used interchangeably,
   however we try not to do so for reasons of consistency.)  */
// ~~~~~~~~~~~~~~~~~~~~~~<{ Functions for Setting Flags }>~~~~~~~~~~~~~~~~~~~~~~
inline void setCarryFlagOnAdditionOn(const architecturalState::isaReg a,
				     const architecturalState::isaReg b);
inline void setOverFlowOnAdditionOn(const architecturalState::isaReg a,
				    const architecturalState::isaReg b,
				    const architecturalState::isaReg c);
inline void setZeroFlagOn(const architecturalState::isaReg reg);
inline void setDecimalFlagOn(const bool d);
inline void setNegativeFlagOn(const architecturalState::isaReg reg);
// ~~~~~~~~~~~~~~~~<{ Functions for Getting Values From Memory }>~~~~~~~~~~~~~~~
inline memory::minimumAddressableUnit get8BitImmediate();
inline memory::address get16BitImmediate();
inline memory::minimumAddressableUnit
getVarAtIndexedZeroPage(const architecturalState::isaReg index);
inline memory::minimumAddressableUnit getVarAtAddress(const memory::address a);
inline memory::address
getIndexedAbsoluteImmediateAddress(const architecturalState::isaReg index);
inline memory::minimumAddressableUnit
getVarAtIndexedAbsoluteImmediateAddress(const architecturalState::isaReg index);
// ~~~~~~~~~~~~~~~~~<{ Functions for Storing Values in Memory }>~~~~~~~~~~~~~~~~
inline void storeRegAtIndexedZeroPage(const architecturalState::isaReg index,
				      const architecturalState::isaReg reg);
inline void storeRegAtAddress(const memory::address a,
			      const architecturalState::isaReg reg);
inline void
storeRegAtAbsoluteImmediateAddress(const architecturalState::isaReg reg);
inline void
storeRegAtIndexedAbsoluteImmediateAddress(const architecturalState::isaReg index,
					  const architecturalState::isaReg reg);
// ~~~~~~~~<{ Functions for Loading Registers With Values From Memory }>~~~~~~~~
inline void loadAccumulatorIndexed(const architecturalState::isaReg index);
inline void loadPCFrom16BitImmediate();
inline void loadPCFrom16BitImmediateIndirect();
inline void loadPCFromStack();
inline bool add8BitImmediateToPCAndCheckPageBoundryTransition();
// ~~~~~~~~~~~~~~~<{ Called When a Conditional Branch Is Taken }>~~~~~~~~~~~~~~~
inline void branchTaken();
// ~~~~~~~~~~~~~~~~~~~<{ Functions for Pushing to the Stack }>~~~~~~~~~~~~~~~~~~
inline void pushToStack(const memory::minimumAddressableUnit reg);
inline void pushPCPlusTwoToStack();
inline void pushStatusFlagsToStack();
// ~~~~~~~~~~~~~~~<{ Called to Pull Top Value off of the Stack }>~~~~~~~~~~~~~~~
inline memory::minimumAddressableUnit pullFromStack();
// ~~~~~~~~~~~~~~~~~~~~~~~<{ Called to Compare Values }>~~~~~~~~~~~~~~~~~~~~~~~~
inline void cmpAgainsIndexedAbsoluteImmediate(const architecturalState::isaReg
					       index);


// ======================== INSTRUCTION SPECIALIZATIONS  =======================
// ============== (The below functions prototypes comprise full  ===============
// ====== instructions. We call them specializations because many of them  =====
// =========== are variations of the same general instruction type.) ===========
/* Note: PC should be altered after calling "SUB INSTRUCTION GRANULARITY
   OPERATIONS" (see above for SUB INSTRUCTION GRANULARITY OPERATIONS function
   headers), as these functions assume it has not been altered yet! */
inline void brk_00();
inline void php_08();
inline void ora_09();
inline void bpl_10();
inline void clc_18();
inline void jsr_20();
inline void plp_28();
inline void bmi_30();
inline void sec_38();
inline void rti_40();
inline void pha_48();
inline void eor_49();
inline void jmp_4c();
inline void bvc_50();
inline void cli_58();
inline void rts_60();
inline void pla_68();
inline void adc_69();
inline void jmp_6c();
inline void bvs_70();
inline void sei_78();
inline void sta_85();
inline void stx_86();
inline void dey_88();
inline void txa_8a();
inline void sty_8c();
inline void sta_8d();
inline void stx_8e();
inline void bcc_90();
inline void sty_94();
inline void stx_96();
inline void tya_98();
inline void sta_99();
inline void txs_9a();
inline void sta_9d();
inline void ldy_a0();
inline void ldx_a2();
inline void ldy_a4();
inline void lda_a5();
inline void ldx_a6();
inline void tay_a8();
inline void lda_a9();
inline void tax_aa();
inline void lda_ad();
inline void ldx_ae();
inline void bcs_b0();
inline void ldy_b4();
inline void lda_b5();
inline void ldx_b6();
inline void clv_b8();
inline void lda_b9();
inline void tsx_ba();
inline void ldy_bc();
inline void lda_bd();
inline void ldx_be();
inline void cpy_c0();
inline void cmp_c5();
inline void iny_c8();
inline void cmp_c9();
inline void dex_ca();
inline void cmp_cd();
inline void bne_d0();
inline void cmp_d5();
inline void cdl_d8();
inline void cmp_d9();
inline void cmp_dd();
inline void cpx_e0();
inline void cpx_e4();
inline void inx_e8();
inline void nop_ea();
inline void cpx_ec();
inline void beq_f0();
inline void sed_f8();


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


inline void setZeroFlagOn(const architecturalState::isaReg reg)
{
  architecturalState::status.u.Z = !reg ? 1 : 0;
}


inline void setDecimalFlagOn(const bool d)
{
  architecturalState::status.u.D = d;
}


void setNegativeFlagOn(const architecturalState::isaReg reg)
{
  architecturalState::status.u.N = (reg & masks::bit7) ? 1 : 0;
}


inline memory::minimumAddressableUnit get8BitImmediate()
{
  return memory::mem[architecturalState::PC + 1];
}


inline memory::address get16BitImmediate()
{
  return (memory::address(memory::mem[architecturalState::PC + 2]
			  << memory::minimumAddressableUnitSize) |
	  memory::address(memory::mem[architecturalState::PC + 1]));
}


/*! \brief Returns 8 bit value at from zero page at address composed of (8 bit
  immediate + index register)

  : http://www.emulator101.com/6502-addressing-modes.html
  This works just like absolute indexed, but the target address is limited to
  the first 0xFF bytes. The target address will wrap around and will always be
  in the zero page. If the instruction is LDA $C0,X, and X is $60, then the
  target address will be $20. $C0+$60 = $120, but the carry is discarded in the
  calculation of the target address. */
inline memory::minimumAddressableUnit
getVarAtIndexedZeroPage(const architecturalState::isaReg index)
{
  using namespace memory;
  /* https://www.nayuki.io/page/summary-of-c-cpp-integer-rules:
     If any operand of an operator has type bool, char, or short (whether signed
     or unsigned), then it is promoted to (signed) int if int can hold all
     values of the source type; otherwise it is promoted to unsigned int; the
     promotion is designed to be lossless. Examples: */
  const int potentialAddress {index + get8BitImmediate()};
  // If potentialAddress is larger then pageSize wrape around.
  const minimumAddressableUnit ret
    {mem[zeroPageBase + (maskAddressLow & (potentialAddress > (pageSize -1) ?
					   (potentialAddress - pageSize) :
					   potentialAddress))]};
  return ret;
}


inline memory::minimumAddressableUnit getVarAtAddress(const memory::address a)
{
  return memory::mem[a];
}


/*! \brief Used to get an address that is the combination of an index register
  (index) and the current 16-bit operand. Note that this function will
  incremente the PC if a page boundry is crossed! */
inline memory::address
getIndexedAbsoluteImmediateAddress(const architecturalState::isaReg index)
{
  const memory::address baseAddress {get16BitImmediate()};
  const memory::address address {memory::address(baseAddress + index)};
  const memory::address pageNum {memory::address(baseAddress &
						 memory::maskAddressHigh)};
  
  if(pageNum != (address & memory::maskAddressHigh))
    {
      architecturalState::cycles += 1;
    }
  return address;
}


/*! \brief For use with instructions that read an 8-bit value at an
   absolute address indexed by one of the index registers (index) and where the
   absolute address is specified by that instructions 16 bit operand. Note that
   this function will increment the PC if a page boundry is crossed. */
inline memory::minimumAddressableUnit
getVarAtIndexedAbsoluteImmediateAddress(const architecturalState::isaReg index)
{
  return memory::mem[getIndexedAbsoluteImmediateAddress(index)];
}


/*! \brief Stores reg value in zero page at address composed of (8 bit
  immediate + index register)

  : http://www.emulator101.com/6502-addressing-modes.html
  This works just like absolute indexed, but the target address is limited to
  the first 0xFF bytes. The target address will wrap around and will always be
  in the zero page. If the instruction is LDA $C0,X, and X is $60, then the
  target address will be $20. $C0+$60 = $120, but the carry is discarded in the
  calculation of the target address. */
inline void storeRegAtIndexedZeroPage(const architecturalState::isaReg index,
				      const architecturalState::isaReg reg)
{
  using namespace memory;
  /* https://www.nayuki.io/page/summary-of-c-cpp-integer-rules:
     If any operand of an operator has type bool, char, or short (whether signed
     or unsigned), then it is promoted to (signed) int if int can hold all
     values of the source type; otherwise it is promoted to unsigned int; the
     promotion is designed to be lossless. Examples: */
  const int potentialAddress {index + get8BitImmediate()};
  // If potentialAddress is larger then pageSize wrape around.
  memory::minimumAddressableUnit address {};
  address = zeroPageBase + (maskAddressLow & (potentialAddress > (pageSize -1) ?
					      (potentialAddress - pageSize) :
					      potentialAddress));
  mem[address] = reg;
}


inline void storeRegAtAddress(const memory::address a,
			     const architecturalState::isaReg reg)
{
  memory::mem[a] = reg;
}


/*! \brief For use with instructions that store a registers value (reg) at an
  absolute address specified by the instructions 16 bit operand. */
inline void
storeRegAtAbsoluteImmediateAddress(const architecturalState::isaReg reg)
{
  memory::mem[get16BitImmediate()] = reg;
}


/* \brief For use with instructions that store a registers value (reg) at an
   absolute address indexed by one of the index registers (index) and where the
   absolute address is specified by that instructions 16 bit operand. Note that
   this function will increment the PC if a page boundry is crossed.

   Note that when looking at the listing for sta (99) at:
   https://www.masswerk.at/6502/6502_instruction_set.html#STA
   We see the following:
   "abs,Y		....	absolute, Y-indexed	 	OPC $LLHH,Y
   operand is address; effective address is address incremented by Y with
   carry **

   ...

   **  The available 16-bit address space is conceived as consisting of pages of
   256 bytes each, with address hi-bytes represententing the page index. An
   increment with carry may affect the hi-byte and may thus result in a crossing
   of page boundaries, adding an extra cycle to the execution. Increments without
   carry do not affect the hi-byte of an address and no page transitions do
   occur. Generally, increments of 16-bit addresses include a carry, increments
   of zeropage addresses don't. Notably this is not related in any way to the
   state of the carry bit of the accumulator."
   Note also that the page (http://www.thealmightyguru.com/Games/Hacking/Wiki/index.php?title=STA)
   on Nes Hacker for this instruction says the following:
   "...Add one cycle if indexing across page boundary"  */
inline void
storeRegAtIndexedAbsoluteImmediateAddress(const architecturalState::isaReg reg,
					  const architecturalState::isaReg index)
{
  memory::mem[getIndexedAbsoluteImmediateAddress(index)] = reg;
}


inline void loadAccumulatorIndexed(const architecturalState::isaReg index)
{ /* * add 1 cycle if page boundary crossed. "oper, x" means we add x to to
     oper, where x is either the X or the Y register. */
  const memory::address baseAddress {get16BitImmediate()};
  const memory::address address {memory::address(baseAddress + index)};
  const memory::address pageNum {memory::address(baseAddress &
						  memory::maskAddressHigh)};
  if(pageNum != (address & memory::maskAddressHigh))
    ++architecturalState::cycles;
   architecturalState::A = memory::mem[address];
}


inline void loadPCFrom16BitImmediate()
{
  architecturalState::PC = get16BitImmediate();
}


inline void loadPCFromStack()
{
  architecturalState::PC = pullFromStack() |
    (pullFromStack() << memory::minimumAddressableUnitSize);
}


/*! \brief This is a sub function that is only called by jmp_6c(), it has more
  to it than one might expect.

  There is no carry associated with the indirect jump so:

  AN INDIRECT JUMP MUST NEVER USE A
  VECTOR BEGINNING ON THE LAST BYTE
  OF A PAGE

  For example if address $3000 contains $40, $30FF contains $80, and $3100
  contains $50, the result of JMP ($30FF) will be a transfer of control to $4080
  rather than $5080 as you intended i.e. the 6502 took the low byte of the
  address from $30FF and the high byte from $3000. */
inline void loadPCFrom16BitImmediateIndirect()
{ /* First we get the operand (the address of the address we are going to jump
     to.) Then we get the low byte of the address we are going to jump to.
     Finally we get the high byte of the address we are going to jump to,
     however if the low byte of the operand (address of the address) is FF (the
     last address in a page) we get the high byte of the address we are going to
     jump to from the start of the page pointed to by the operand (address of
     the address) rather then the start of the page after that. */
  using namespace memory;
  const address indirectAddress {get16BitImmediate()};
  const address addressLowByte {mem[indirectAddress]};
  const address addressHighByte {(maskAddressLow & (indirectAddress +1)) %
				 pageSize == 0 ?
				 address(mem[indirectAddress + 1 - pageSize]) :
				 address(mem[indirectAddress +1])};
  architecturalState::PC = (addressHighByte
			    << minimumAddressableUnitSize) | addressLowByte;
}


// Return true if we have crossed a page boundry.
inline bool add8BitImmediateToPCAndCheckPageBoundryTransition()
{  
  bool ret {false};
  const memory::address pageNum {memory::address(architecturalState::PC &
						 memory::maskAddressHigh)};

  architecturalState::PC += (signed char)get8BitImmediate();  
  if(pageNum != (architecturalState::PC & memory::maskAddressHigh))
    ret = true;
  return ret;
}


inline void branchTaken()
{
  if(add8BitImmediateToPCAndCheckPageBoundryTransition())
    architecturalState::cycles += 1;
  architecturalState::cycles += 1;
}


inline void pushToStack(const memory::minimumAddressableUnit reg)
{
  storeRegAtAddress(memory::stackBase | architecturalState::S--,
		   reg);
}


inline void pushPCPlusTwoToStack()
{
  pushToStack((architecturalState::PC + 2) >>
	      memory::minimumAddressableUnitSize);
  pushToStack(memory::maskAddressLow & (architecturalState::PC + 2));
}


inline void pushStatusFlagsToStack()
{
  pushToStack(architecturalState::status.flags |
	      architecturalState::bFlagMaskPhpBrkAndIrqNmi);
}


inline memory::minimumAddressableUnit pullFromStack()
{
  return getVarAtAddress(memory::stackBase |
			  ++architecturalState::S);
}


inline void cmpAgainsIndexedAbsoluteImmediate(const architecturalState::isaReg
					       index)
{
    const memory::minimumAddressableUnit compVal
    {memory::minimumAddressableUnit
     (architecturalState::A -
      getVarAtIndexedAbsoluteImmediateAddress(index))};
  /* Note here that we negate the second argument so our addition is actually a
     subtraction. */
  setCarryFlagOnAdditionOn(architecturalState::A,
			   - getVarAtIndexedAbsoluteImmediateAddress(index));
  setZeroFlagOn(compVal);
  setNegativeFlagOn(compVal);
}


// ======================== INSTRUCTION SPECIALIZATIONS  =======================
// ============== (The below functions comprise full instructions. =============
// =========== Functions that belong to the same class of instruction ==========
// ============ (indicated by their prefixs) are grouped together.) ============


/*! \brief Force Break

  Interrupt					||
  Push PC + 2					||
  Push SR			       		||
  (N-, Z-, C-, I = 1, D-, V-) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	BRK		||
  Opcode:			00		||
  Bytes:			1		||
  Cycles:			7		||
  "...the BRK instruction advances the program counter by 2, pushes the Program
  Counter Register and processor status register to the stack, sets the
  Interrupt Flag to temporarily prevent other IRQs from being executed, and
  reloads the Program Counter from the vector at $FFFE-$FFFF.":
  http://www.thealmightyguru.com/Games/Hacking/Wiki/index.php?title=BRK */
inline void brk_00()
{
  pushPCPlusTwoToStack();
  pushStatusFlagsToStack();
  architecturalState::status.u.I = 1;
  architecturalState::PC = (memory::mem[memory::brkPCLoadVector + 1]
			    << memory::minimumAddressableUnitSize) |
    memory::mem[memory::brkPCLoadVector];
  architecturalState::cycles += 7;
}


/*! \brief Push Processor Status on Stack

  Push SR			       		||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	PHP		||
  Opcode:			08		||
  Bytes:			1		||
  Cycles:			3		||

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
  Note that the flags struct is defined as:
  @code
  typedef union
  {
    struct
    {
      unsigned char C : 1;	// Carry	~===<( Lowest order byte )>===~
      unsigned char Z : 1;	// Zero
      unsigned char I : 1;	// Interrupt Disable
      unsigned char D : 1;	// Decimal
      unsigned char s0 : 1;	// No CPU effect. (refere to the comment at the
      unsigned char s1 : 1;	// top of the file.)
      unsigned char V : 1;	// Overflow
      unsigned char N : 1;	// Negative	~===<( Highest order byte )>===~
    }u;
    isaReg flags;
  }Status; @endcode */
inline void php_08()
{
  pushStatusFlagsToStack();
  architecturalState::PC += 1;
  architecturalState::cycles += 3;
}


/*! \brief OR Memory with Accumulator

  A OR M -> A			       		||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Immidiate	||
  Assembly Language Form:	ORA #oper	||
  Opcode:			09		||
  Bytes:			2		||
  Cycles:			2		|| */
inline void ora_09()
{
  architecturalState::A |= get8BitImmediate();
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


/*! \brief Branch on Result Plus.

  branch on N = 0		       		||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Relative	||
  Assembly Language Form:	BPL oper	||
  Opcode:			10		||
  Bytes:			2		||
  Cycles:			2**		||
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
  (N-, Z-, C = 0, I-, D-, V-) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	CLC		||
  Opcode:			18		||
  Bytes:			1		||
  Cycles:			2		|| */
inline void clc_18()
{
  architecturalState::status.u.C = 0;
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


/*! \brief Jump to New Location Saving Return Address

  Push (PC + 2)					||
  (PC + 1) -> PCL				||
  (PC + 2) -> PCH			       	||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Absolute       	||
  Assembly Language Form:	JSR oper       	||
  Opcode:			20		||
  Bytes:			3		||
  Cycles:			6		||
  "I know the 6502 always fetches two bytes on the first two cycles of each
  instruction. For 1-byte opcodes, it throws the extra one away and doesn't
  further increment PC (which was already incremented to fetch the thrown away
  second byte). For 2-byte opcodes, it uses both bytes and does increment PC.
  And for 3-byte ones, it increments PC, fetches the final byte, uses it, and
  increments the PC once more. In JSR (a 3-byte opcode), it must be pushing the
  program counter to the stack before incrementing PC for the last time.":
  https://stackoverflow.com/questions/21465200/6502-assembler-the-rts-command-and-the-stack */
inline void jsr_20()
{ /* "The high byte is pushed first so that the low byte is in the lower
     address": https://stackoverflow.com/questions/21465200/6502-assembler-the-rts-command-and-the-stack */
  pushPCPlusTwoToStack();
  loadPCFrom16BitImmediate();
  architecturalState::cycles += 4;
}


/*! \brief Pull Processor Status from Stack

  Pull SR			       		||
  (From Stack -> (N, Z, C, I, D, V))		||
  Addressing Mode:		Implied		||
  Assembly Language Form:	PLP		||
  Opcode:			28		||
  Bytes:			1		||
  Cycles:			4		|| */
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
  Bytes:			2		||
  Cycles:			2**		||
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


/*! \brief Set Carry Flag

  1 -> C			       		||
  (N-, Z-, C = 1, I-, D-, V-) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	SEC		||
  Opcode:			38		||
  Bytes:			1		||
  Cycles:			2		|| */
inline void sec_38()
{
  architecturalState::status.u.C = 1;
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


/*! \brief Return from Interrupt

  Pull SR					||
  Pull PC					||
  (From Stack -> (N, Z, C, I, D, V)) 	       	||
  Addressing Mode:		Implied		||
  Assembly Language Form:	RTI		||
  Opcode:			40		||
  Bytes:			1		||
  Cycles:			6		|| */
inline void rti_40()
{ /* Note that unlike RTS, the return address on the stack is the actual address
     rather than the address-1. */
  architecturalState::status.flags = pullFromStack();
  loadPCFromStack();
  architecturalState::cycles += 6;
}


/*! \brief Push Accumulator on Stack

  Push A					||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	PHA		||
  Opcode:			48		||
  Bytes:			1		||
  Cycles:			3		|| */
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
  Bytes:			2		||
  Cycles:			2		|| */
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


/*! \brief Branch on Overflow Clear

  Branch on V = 0      				||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Relative       	||
  Assembly Language Form:	BVC oper       	||
  Opcode:			50		||
  Bytes:			2		||
  Cycles:			2**		||
  Branches are dependant on the status of the flag bits when the op code is
  encountered. A branch not taken requires two machine cycles. Add one if the
  branch is taken and add one more if the branch crosses a page boundary. From:
  http://6502.org/tutorials/6502opcodes.html#BCC */
inline void bvc_50()
{
  if(architecturalState::status.u.V == 0)
    branchTaken();
  architecturalState::PC += 2;	// This is done even if branch is taken.
  architecturalState::cycles += 2;
}


/*! \brief Clear Interrupt Disable Bit

  0 -> I					||
  (N-, Z-, C-, I = 0, D-, V-) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	CLI		||
  Opcode:			58		||
  Bytes:			1		||
  Cycles:			2		|| */
inline void cli_58()
{
  architecturalState::status.u.I = 0;
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


/*! \brief Return from Subroutine

  Pull PC					||
  PC + 1 -> PC					||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	RTS		||
  Opcode:			60		||
  Bytes:			1		||
  Cycles:			6		|| */
inline void rts_60()
{				      // The low byte is pulled first.

  loadPCFromStack();
  architecturalState::PC += 1;
  architecturalState::cycles += 6;
}


/*! \brief Pull Accumulator from Stack

  Pull A					||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	PLA		||
  Opcode:			68		||
  Bytes:			1		||
  Cycles:			4		|| */
inline void pla_68()
{
  architecturalState::A = pullFromStack();
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
  architecturalState::PC += 1;
  architecturalState::cycles += 4;
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



/*! \brief Jump to New Location

  (PC + 1) -> PCL				||
  (PC + 1) -> PCH			       	||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Indirect       	||
  Assembly Language Form:	JMP (oper)     	||
  Opcode:			6C		||
  Bytes:			3		||
  Cycles:			5		||

  There is no carry associated with the indirect jump so:

  AN INDIRECT JUMP MUST NEVER USE A
  VECTOR BEGINNING ON THE LAST BYTE
  OF A PAGE

  For example if address $3000 contains $40, $30FF contains $80, and $3100
  contains $50, the result of JMP ($30FF) will be a transfer of control to $4080
  rather than $5080 as you intended i.e. the 6502 took the low byte of the
  address from $30FF and the high byte from $3000. */
inline void jmp_6c()
{
  loadPCFrom16BitImmediateIndirect();
  architecturalState::cycles += 5;
}


/*! \brief Branch on Overflow Set

  Branch on V = 1      				||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Relative       	||
  Assembly Language Form:	BVS oper       	||
  Opcode:			50		||
  Bytes:			2		||
  Cycles:			2**		||
  Branches are dependant on the status of the flag bits when the op code is
  encountered. A branch not taken requires two machine cycles. Add one if the
  branch is taken and add one more if the branch crosses a page boundary. From:
  http://6502.org/tutorials/6502opcodes.html#BCC */
inline void bvs_70()
{
  if(architecturalState::status.u.V == 1)
    branchTaken();
  architecturalState::PC += 2;	// This is done even if branch is taken.
  architecturalState::cycles += 2;
}


/*! \brief Set Interrupt Disable Status

  1 -> I      					||
  (N-, Z-, C-, I = 1, D-, V-) 			||
  Addressing Mode:		Implied       	||
  Assembly Language Form:	SEI       	||
  Opcode:			78		||
  Bytes:			1		||
  Cycles:			2		|| */
inline void sei_78()
{
  architecturalState::status.u.I = 1;
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


/*! \brief Store Accumulator in Memory

  A -> M      					||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		ZeroPage       	||
  Assembly Language Form:	STA oper       	||
  Opcode:			85		||
  Bytes:			2		||
  Cycles:			3		|| */
inline void sta_85()
{
  memory::mem[memory::zeroPageBase | get8BitImmediate()] =
    architecturalState::A;
  architecturalState::PC += 2;
  architecturalState::cycles += 3;
}


/*! \brief Store Index X in Memory

  X -> M      					||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		ZeroPage       	||
  Assembly Language Form:	STX oper       	||
  Opcode:			86		||
  Bytes:			2		||
  Cycles:			3		|| */
inline void stx_86()
{
  memory::mem[memory::zeroPageBase | get8BitImmediate()] =
    architecturalState::X;
  architecturalState::PC += 2;
  architecturalState::cycles += 3;
}


inline void dey_88()
{
  architecturalState::Y -= 1;
  setZeroFlagOn(architecturalState::Y);
  setNegativeFlagOn(architecturalState::Y);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


/*! \brief Transfer Index X to Accumulator

  X -> A				        ||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	TXA		||
  Opcode:			8A		||
  Bytes:			1	        ||
  Cycles:			2		|| */
inline void txa_8a()
{
  architecturalState::A = architecturalState::X;
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


/*! \brief Store Index Y in Memory

  Y -> M				        ||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Absolute       	||
  Assembly Language Form:	STY oper       	||
  Opcode:			8C		||
  Bytes:			3	        ||
  Cycles:			4		|| */
inline void sty_8c()
{
  storeRegAtAbsoluteImmediateAddress(architecturalState::Y);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


inline void sta_8d()
{
  storeRegAtAbsoluteImmediateAddress(architecturalState::A);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


/*! \brief Store Index X in Memory

  X -> M				        ||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Absolute       	||
  Assembly Language Form:	STX oper	||
  Opcode:			8E		||
  Bytes:			3	        ||
  Cycles:			4		|| */
inline void stx_8e()
{
  storeRegAtAbsoluteImmediateAddress(architecturalState::X);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}



/*! \brief Branch on Carry Clear

  branch on C = 0			        ||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Relative	||
  Assembly Language Form:	BCC oper	||
  Opcode:			90		||
  Bytes:			2		||
  Cycles:			2**		||
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


/*! \brief Store Index Y in Memory

  Y -> M				        ||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Zeropage, X	||
  Assembly Language Form:	STY oper, X	||
  Opcode:			94		||
  Bytes:			2		||
  Cycles:			4		|| */
inline void sty_94()
{
  storeRegAtIndexedZeroPage(architecturalState::X, architecturalState::Y);
  architecturalState::PC += 2;
  architecturalState::cycles += 4;
}


/*! \brief Store Index X in Memory

  X -> M				        ||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Zeropage, Y	||
  Assembly Language Form:	STX oper, Y	||
  Opcode:			96		||
  Bytes:			2		||
  Cycles:			4		|| */
inline void stx_96()
{
  storeRegAtIndexedZeroPage(architecturalState::Y, architecturalState::X);
  architecturalState::PC += 2;
  architecturalState::cycles += 4;
}


inline void tya_98()
{
  architecturalState::A = architecturalState::Y;
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


/*! \brief Store Accumulator in Memory

  A -> M				        ||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Absolute, Y	||
  Assembly Language Form:	STA oper, Y    	||
  Opcode:			99		||
  Bytes:			3		||
  Cycles:			4*		||
We note that here Cycles is specified as 5 at:
https://www.masswerk.at/6502/6502_instruction_set.html#STA
and as 4* at:
http://www.thealmightyguru.com/Games/Hacking/Wiki/index.php?title=STA
We use and assume 4* because it is more specific and we assume that the 4* is
because we may crosses a page boundry. Or maybe this is specific to the
Ricoh. */
inline void sta_99()
{
  storeRegAtIndexedAbsoluteImmediateAddress(architecturalState::A,
					    architecturalState::Y);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


/*! \brief Transfer Index X to Stack Register

  X -> SP				       	||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	TXS		||
  Opcode:			9A		||
  Bytes:			1		||
  Cycles:			2		|| */
inline void txs_9a()
{
  architecturalState::S = architecturalState::X;
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


/*! \brief Store Accumulator in Memory

  A -> M				       	||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Absolute, X    	||
  Assembly Language Form:	STA oper, X    	||
  Opcode:			9D		||
  Bytes:			3		||
  Cycles:			4*		||
We note that here Cycles is specified as 5 at:
https://www.masswerk.at/6502/6502_instruction_set.html#STA
and as 4* at:
http://www.thealmightyguru.com/Games/Hacking/Wiki/index.php?title=STA
We use and assume 4* because it is more specific and we assume that the 4* is
because we may crosses a page boundry. Or maybe this is specific to the
Ricoh. */
inline void sta_9d()
{
  storeRegAtIndexedAbsoluteImmediateAddress(architecturalState::A,
					    architecturalState::X);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
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


/*! \brief Load Index Y with Memory

  M -> Y				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Zeropage	||
  Assembly Language Form:	LDY oper       	||
  Opcode:			A4		||
  Bytes:			2		||
  Cycles:			3		|| */
inline void ldy_a4()
{
  architecturalState::Y = {memory::mem[memory::zeroPageBase |
				       get8BitImmediate()]};
  setZeroFlagOn(architecturalState::Y);
  setNegativeFlagOn(architecturalState::Y);
  architecturalState::PC += 2;
  architecturalState::cycles += 3;
}


/*! \brief Load Accumulator with Memory

  M -> A				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Zeropage	||
  Assembly Language Form:	LDA oper       	||
  Opcode:			A5		||
  Bytes:			2		||
  Cycles:			3		|| */
inline void lda_a5()
{
  architecturalState::A = {memory::mem[memory::zeroPageBase |
				       get8BitImmediate()]};
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
  architecturalState::PC += 2;
  architecturalState::cycles += 3;
}


/*! \brief Load Index X with Memory

  M -> X				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Zeropage	||
  Assembly Language Form:	LDX oper       	||
  Opcode:			A6		||
  Bytes:			2		||
  Cycles:			3		|| */
inline void ldx_a6()
{
  architecturalState::X = {memory::mem[memory::zeroPageBase |
				       get8BitImmediate()]};
  setZeroFlagOn(architecturalState::X);
  setNegativeFlagOn(architecturalState::X);
  architecturalState::PC += 2;
  architecturalState::cycles += 3;
}


/*! \brief Transfer Accumulator to Index Y

  A -> Y				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	TAY		||
  Opcode:			A8		||
  Bytes:			1		||
  Cycles:			2		|| */
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


/*! \brief Transfer Accumulator to Index X

  A -> X				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	TAX		||
  Opcode:			AA		||
  Bytes:			1		||
  Cycles:			2		|| */
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
  architecturalState::A = getVarAtAddress(get16BitImmediate());
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


/*! \brief Load Index X with Memory

  M -> X				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Absolute       	||
  Assembly Language Form:	LDX oper       	||
  Opcode:			AE		||
  Bytes:			3		||
  Cycles:			4		|| */
inline void ldx_ae()
{
  architecturalState::X = getVarAtAddress(get16BitImmediate());
  setZeroFlagOn(architecturalState::X);
  setNegativeFlagOn(architecturalState::X);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


/*! \brief Branch on Carry Set

  Branch on C = 1			       	||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Relative	||
  Assembly Language Form:	BCS oper	||
  Opcode:			B0		||
  Bytes:			2		||
  Cycles:			2**		||
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


/*! \brief Load Index Y with Memory

  M -> Y				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Zeropage, X    	||
  Assembly Language Form:	LDY oper, X    	||
  Opcode:			B4		||
  Bytes:			2		||
  Cycles:			4		|| */
inline void ldy_b4()
{
  architecturalState::Y =
    getVarAtIndexedZeroPage(architecturalState::X);
  setZeroFlagOn(architecturalState::Y);
  setNegativeFlagOn(architecturalState::Y);
  architecturalState::PC += 2;
  architecturalState::cycles += 4;
}


/*! \brief Load Accumulator with Memory

  M -> A				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Zeropage, X    	||
  Assembly Language Form:	LDA oper, X    	||
  Opcode:			B5		||
  Bytes:			2		||
  Cycles:			4		|| */
inline void lda_b5()
{
    architecturalState::A =
    getVarAtIndexedZeroPage(architecturalState::X);
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
  architecturalState::PC += 2;
  architecturalState::cycles += 4;
}


/*! \brief Load Index X with Memory

  M -> X				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Zeropage, Y    	||
  Assembly Language Form:	LDX oper, Y    	||
  Opcode:			B6		||
  Bytes:			2		||
  Cycles:			4		|| */
inline void ldx_b6()
{
  architecturalState::X =
    getVarAtIndexedZeroPage(architecturalState::Y);
  setZeroFlagOn(architecturalState::X);
  setNegativeFlagOn(architecturalState::X);
  architecturalState::PC += 2;
  architecturalState::cycles += 4;
}


/*! \brief Clear Overflow Flag

  0 -> V				       	||
  (N-, Z-, C-, I-, D-, V = 0) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	CLV		||
  Opcode:			B8		||
  Bytes:			1		||
  Cycles:			2		|| */
inline void clv_b8()
{
  architecturalState::status.u.V = 0;
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


/*! \brief Load Accumulator with Memory

  M -> A				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Absolute, Y   	||
  Assembly Language Form:	LDA oper, y    	||
  Opcode:			B9		||
  Bytes:			3		||
  Cycles:			4*		||
  Add Y register to 16 bit immediate to get address. Set A register to value at
  address. If a page boundry is crossed add 1 to cycles. */
inline void lda_b9()
{
  architecturalState::A =
    memory::mem[getIndexedAbsoluteImmediateAddress(architecturalState::Y)];
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


/*! \brief Transfer Stack Pointer to Index X

  SP -> X				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	TSX		||
  Opcode:			BA		||
  Bytes:			1		||
  Cycles:			2		|| */
inline void tsx_ba()
{
  architecturalState::X = architecturalState::S;
  setZeroFlagOn(architecturalState::X);
  setNegativeFlagOn(architecturalState::X);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


/*! \brief Load Index Y with Memory

  M -> Y				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Absolute, X    	||
  Assembly Language Form:	LDY oper, X    	||
  Opcode:			BC		||
  Bytes:			3		||
  Cycles:			4*		|| */
inline void ldy_bc()
{
    architecturalState::Y =
    memory::mem[getIndexedAbsoluteImmediateAddress(architecturalState::X)];
  setZeroFlagOn(architecturalState::Y);
  setNegativeFlagOn(architecturalState::Y);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


/*! \brief Load Accumulator with Memory

  M -> A				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Absolute, X    	||
  Assembly Language Form:	LDA oper, X    	||
  Opcode:			BD		||
  Bytes:			3		||
  Cycles:			4*		|| */
inline void lda_bd()
{
  loadAccumulatorIndexed(architecturalState::X);
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


/*! \brief Load Index X with Memory

  M -> X				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Absolute, Y    	||
  Assembly Language Form:	LDX oper, Y    	||
  Opcode:			BE		||
  Bytes:			3		||
  Cycles:			4*		|| 
  Add Y register to 16 bit immediate to get address. Set X register to value at
  address. If a page boundry is crossed add 1 to cycles. */
inline void ldx_be()
{
  architecturalState::X =
    memory::mem[getIndexedAbsoluteImmediateAddress(architecturalState::Y)];
  setZeroFlagOn(architecturalState::X);
  setNegativeFlagOn(architecturalState::X);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


/*! \brief Compare Memory and Index Y

  Y - M						||
  (N+, Z+, C+, I-, D-, V-) 			||
  Addressing Mode:		Immediate	||
  Assembly Language Form:	CPY #oper	||
  Opcode:			C0		||
  Bytes:			2		||
  Cycles:			2		|| */
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
  (N+, Z+, C+, I-, D-, V-) 			||
  Addressing Mode:		Zeropage	||
  Assembly Language Form:	CMP oper	||
  Opcode:			C5		||
  Bytes:			2		||
  Cycles:			3		|| */
inline void cmp_c5()
{
  const memory::minimumAddressableUnit oper {memory::mem[memory::zeroPageBase |
							 get8BitImmediate()]};
  architecturalState::status.u.C = ((architecturalState::A == oper)
				    || (architecturalState::A >
					oper)) ? 1 : 0;
  setZeroFlagOn(architecturalState::A - oper);
  setNegativeFlagOn(architecturalState::A - oper);
  architecturalState::PC += 2;
  architecturalState::cycles += 3;
}


/*! \brief Increment Index Y by One

  Y + 1 -> Y	       				||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	INY		||
  Opcode:			C8		||
  Bytes:			1		||
  Cycles:			2		|| */
inline void iny_c8()
{
  architecturalState::Y += 1;
  setZeroFlagOn(architecturalState::Y);
  setNegativeFlagOn(architecturalState::Y);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


/*! \brief Compare Memory with Accumulator

  A - M						||
  (N+, Z+, C+, I-, D-, V-)			||
  Addressing Mode:		Immediate	||
  Assembly Language Form:	CMP #oper	||
  Opcode:			C9		||
  Bytes:			2		||
  Cycles:			2		||
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
  Bytes:			3		||
  Cycles:			4		|| */
inline void cmp_cd()
{
  architecturalState::status.u.C = ((architecturalState::A == getVarAtAddress(get16BitImmediate()))
				    || (architecturalState::A >
					getVarAtAddress(get16BitImmediate()))) ? 1 : 0;
  setZeroFlagOn(architecturalState::A - getVarAtAddress(get16BitImmediate()));
  setNegativeFlagOn(architecturalState::A - getVarAtAddress(get16BitImmediate()));
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
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


/*! \brief Compare Memory with Accumulator

  A - M						||
  (N+, Z+, C+, I-, D-, V-)			||
  Addressing Mode:		Zeropage, X	||
  Assembly Language Form:	CMP oper, X	||
  Opcode:			D5		||
  Bytes:			2		||
  Cycles:			4		|| */
inline void cmp_d5()
{  
  const memory::minimumAddressableUnit compVal
    {memory::minimumAddressableUnit
     (architecturalState::A -
      getVarAtIndexedZeroPage(architecturalState::X))};
  /* Note here that we negate the second argument so our addition is actually a
     subtraction. */
  setCarryFlagOnAdditionOn(architecturalState::A,
			   - getVarAtIndexedZeroPage(architecturalState::X));
  setZeroFlagOn(compVal);
  setNegativeFlagOn(compVal); 
  architecturalState::PC += 2;
  architecturalState::cycles += 4;
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


/*! \brief Compare Memory with Accumulator

  A - M						||
  (N+, Z+, C+, I-, D-, V-)			||
  Addressing Mode:		Absolute, Y	||
  Assembly Language Form:	CMP oper, Y	||
  Opcode:			D9		||
  Bytes:			3		||
  Cycles:			4*		|| */
inline void cmp_d9()
{
  cmpAgainsIndexedAbsoluteImmediate(architecturalState::Y);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


/*! \brief Compare Memory with Accumulator

  A - M						||
  (N+, Z+, C+, I-, D-, V-)			||
  Addressing Mode:		Absolute, X	||
  Assembly Language Form:	CMP oper, X	||
  Opcode:			DD		||
  Bytes:			3		||
  Cycles:			4*		|| */
inline void cmp_dd()
{
  cmpAgainsIndexedAbsoluteImmediate(architecturalState::X);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


/*! \brief Compare Memory and Index X

  X - M						||
  (N+, Z+, C+, I-, D-, V-)			||
  Addressing Mode:		Immediate	||
  Assembly Language Form:	CPX #oper	||
  Opcode:			E0		||
  Bytes:			2		||
  Cycles:			2		|| */
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


/*! \brief Compare Memory and Index X

  X - M						||
  (N+, Z+, C+, I-, D-, V-)			||
  Addressing Mode:		Zeropage	||
  Assembly Language Form:	CPX oper	||
  Opcode:			E4		||
  Bytes:			2		||
  Cycles:			3		|| */
inline void cpx_e4()
{
  const memory::minimumAddressableUnit oper {memory::mem[memory::zeroPageBase |
							 get8BitImmediate()]};
    architecturalState::status.u.C = ((architecturalState::X == oper)
				    || (architecturalState::X >
					oper)) ? 1 : 0;
  setZeroFlagOn(architecturalState::X - oper);
  setNegativeFlagOn(architecturalState::X - oper);
  architecturalState::PC += 2;
  architecturalState::cycles += 3;
}


/*! \brief Increment Index X by One

  X + 1 -> X   					||
  (N+, Z+, C-, I-, D-, V-)			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	INX		||
  Opcode:			E8		||
  Bytes:			1		||
  Cycles:			2		|| */
inline void inx_e8()
{
  architecturalState::X += 1;
  setZeroFlagOn(architecturalState::X);
  setNegativeFlagOn(architecturalState::X);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


inline void nop_ea()
{
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


/*! \brief Compare Memory and Index X

  X - M   					||
  (N+, Z+, C+, I-, D-, V-)			||
  Addressing Mode:		Absolute	||
  Assembly Language Form:	CPX oper       	||
  Opcode:			EC		||
  Bytes:			3		||
  Cycles:			4		|| */
inline void cpx_ec()
{
  const memory::minimumAddressableUnit oper
    {getVarAtAddress(get16BitImmediate())};
  architecturalState::status.u.C = ((architecturalState::X == oper)
				    || (architecturalState::X >
					oper)) ? 1 : 0;
  setZeroFlagOn(architecturalState::X - oper);
  setNegativeFlagOn(architecturalState::X - oper);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


inline void beq_f0()
{
  if(architecturalState::status.u.Z == 1)
    branchTaken();
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


/*! \brief Set Decimal Flag

  1 -> D   					||
  (N-, Z-, C-, I-, D = 1, V-)			||
  Addressing Mode:		Implied		||
  Assembly Language Form:	SED		||
  Opcode:			F8		||
  Bytes:			1		||
  Cycles:			2		|| */
inline void sed_f8()
{ /*  "Even though the NES doesn't use decimal mode, the opcodes to clear and
      set the flag do work...":
      http://www.thealmightyguru.com/Games/Hacking/Wiki/index.php?title=SED */
  architecturalState::status.u.D = 1;
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


#endif
