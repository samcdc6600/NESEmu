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
inline void setOverflowOnAdditionOn(const architecturalState::isaReg a,
				    const architecturalState::isaReg b,
				    const architecturalState::isaReg c);
/* For use with functions that set the overflow flag directly (that is without
   addition) such as bit_24(). */
inline void setOverflowOnVar(const memory::minimumAddressableUnit var);
inline void setZeroFlagOn(const architecturalState::isaReg reg);
inline void setDecimalFlagOn(const bool d);
inline void setNegativeFlagOn(const architecturalState::isaReg reg);
// ~~~~~~~~~~~~~~~~<{ Functions for Getting Values From Memory }>~~~~~~~~~~~~~~~
inline memory::minimumAddressableUnit get8BitImmediate();
inline memory::address get16BitImmediate();
inline memory::minimumAddressableUnit
getVarAtIndexedZeroPage(const architecturalState::isaReg index);
inline memory::minimumAddressableUnit getVarAtAddress(const memory::address a);
// Used for things including and similar to "LDA oper,Y."
inline memory::address
getIndexedAbsoluteImmediateAddress(const architecturalState::isaReg index);
// Used for things including and similar to "LDA (oper),Y."
inline memory::address
getPostIndexedIndirectImmediateAddress(const architecturalState::isaReg index);
// Used for things including and similar to "CMP (oper, X)."
inline memory::address
getPreIndexedIndirectImmediateAddress(const architecturalState::isaReg index);
inline memory::minimumAddressableUnit
getVarAtIndexedAbsoluteImmediateAddress(const architecturalState::isaReg index);
// ~~~~~~~~~~~~~~~~~<{ Functions for Storing Values in Memory }>~~~~~~~~~~~~~~~~
// Used for things including and similar "ASL oper, X."
inline void storeVarAtIndexedZeroPage(const architecturalState::isaReg index,
				      memory::minimumAddressableUnit var);
inline void storeRegAtIndexedZeroPage(const architecturalState::isaReg index,
				      const architecturalState::isaReg reg);
inline void storeRegAtAddress(const memory::address a,
			      const architecturalState::isaReg reg);
inline void
storeRegAtAbsoluteImmediateAddress(const architecturalState::isaReg reg);
inline void
StoreVarAtIndexedAbsoluteImmediateAddress(const architecturalState::isaReg index,
				      memory::minimumAddressableUnit var);
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
inline void pushStatusFlagsToStackWithBSet();
// ~~~~~~~~~~~~~~~<{ Called to Pull Top Value off of the Stack }>~~~~~~~~~~~~~~~
inline memory::minimumAddressableUnit pullFromStack();
inline memory::minimumAddressableUnit pullStatusFlagsFromStack();
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
inline void asl_06();
inline void php_08();
inline void ora_09();
inline void asl_0a();
inline void asl_0e();
inline void bpl_10();
inline void asl_16();
inline void clc_18();
inline void asl_1e();
inline void jsr_20();
inline void bit_24();
inline void rol_26();
inline void plp_28();
inline void rol_2a();
inline void bit_2c();
inline void rol_2e();
inline void bmi_30();
inline void rol_36();
inline void sec_38();
inline void rol_3e();
inline void rti_40();
inline void lsr_46();
inline void pha_48();
inline void eor_49();
inline void lsr_4a();
inline void jmp_4c();
inline void lsr_4e();
inline void bvc_50();
inline void lsr_56();
inline void cli_58();
inline void lsr_5e();
inline void rts_60();
inline void ror_66();
inline void pla_68();
inline void adc_69();
inline void ror_6a();
inline void jmp_6c();
inline void ror_6e();
inline void bvs_70();
inline void ror_76();
inline void sei_78();
inline void sta_81();
inline void sty_84();
inline void sta_85();
inline void stx_86();
inline void dey_88();
inline void txa_8a();
inline void sty_8c();
inline void sta_8d();
inline void stx_8e();
inline void bcc_90();
inline void sta_91();
inline void sty_94();
inline void sta_95();
inline void stx_96();
inline void tya_98();
inline void sta_99();
inline void txs_9a();
inline void sta_9d();
inline void ldy_a0();
inline void lda_a1();
inline void ldx_a2();
inline void ldy_a4();
inline void lda_a5();
inline void ldx_a6();
inline void tay_a8();
inline void lda_a9();
inline void tax_aa();
inline void ldy_ac();
inline void lda_ad();
inline void ldx_ae();
inline void bcs_b0();
inline void lda_b1();
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
inline void cmp_c1();
inline void cpy_c4();
inline void cmp_c5();
inline void iny_c8();
inline void cmp_c9();
inline void dex_ca();
inline void cpy_cc();
inline void cmp_cd();
inline void bne_d0();
inline void cmp_d1();
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


inline void setOverflowOnAdditionOn(const architecturalState::isaReg a,
				    const architecturalState::isaReg b,
				    const architecturalState::isaReg c)
{
  /* An explination of the following:
     https://stackoverflow.com/questions/16845912/determining-carry-and-overflow-flag-in-6502-emulation-in-java  */
  architecturalState::status.u.V = (~(a ^ b)) & (a ^ c) & masks::bit7;
}


inline void setOverflowOnVar(const memory::minimumAddressableUnit var)
{
  architecturalState::status.u.V = var ? 1 : 0;
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


/*! \brief Returns 8 bit value from zero page at address composed of (8 bit
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
  increment cycles if a page boundry is crossed! */
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


/*! \brief Used to get an address that is located at:
  ((immediate) + ((immediate +1) << 8)) + index,
  where immediate is an 8-bit immidate and index is an index register. Note
  thst this function will increment cycles if a page boundry is crossed!  */
inline memory::address
getPostIndexedIndirectImmediateAddress(const architecturalState::isaReg index)
{
  // Get address pointed to by immediate.
  const memory::address baseAddress
    {memory::address(memory::mem[memory::zeroPageBase | get8BitImmediate()] |
		     (memory::mem[memory::zeroPageBase | get8BitImmediate() +1]
		      << memory::minimumAddressableUnitSize))};
  // Calculate address (baseAddress (address pointed to by immediate) + index.)
  const memory::address address
    {memory::address(baseAddress + index)};
  // Calculate page number.
  const memory::address pageNum {memory::address(baseAddress &
						 memory::maskAddressHigh)};
  if(pageNum != (address & memory::maskAddressHigh))
    {				// If page boundry was crossed.
      architecturalState::cycles += 1;
    }

  return address;
}


/* All 8 instructions that this function should be applicable to acording to:
   https://www.masswerk.at/6502/6502_instruction_set.html
   take 6 cycles. Therfore there should be no need to check for the crossing of
   any page boundrys. */
inline memory::address
getPreIndexedIndirectImmediateAddress(const architecturalState::isaReg index)
{	// Get address pointed to by immediate + X.
  const memory::address addressOfAddress
    {memory::address(memory::minimumAddressableUnit(get8BitImmediate() +
						    index))};
  // Return address that addressOfAddress points to
  return (memory::address(memory::mem[addressOfAddress] |
			  ((memory::mem[addressOfAddress +1])
			   << memory::minimumAddressableUnitSize)));
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


/*! \brief Stores an 8 bit value in the zero page at address composed of (8 bit
  immediate + index register)

  : http://www.emulator101.com/6502-addressing-modes.html
  This works just like absolute indexed, but the target address is limited to
  the first 0xFF bytes. The target address will wrap around and will always be
  in the zero page. */
inline void storeVarAtIndexedZeroPage(const architecturalState::isaReg index,
				      memory::minimumAddressableUnit var)
{
  using namespace memory;

  const int potentialAddress {index + get8BitImmediate()};
  // If potentialAddress is larger then pageSize wrape around.
  mem[zeroPageBase + (maskAddressLow & (potentialAddress > (pageSize -1) ?
					(potentialAddress - pageSize) :
					potentialAddress))] = var;
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
  const memory::address address
    {memory::address(memory::minimumAddressableUnit(index +
						    get8BitImmediate()))};
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


inline void
StoreVarAtIndexedAbsoluteImmediateAddress(const architecturalState::isaReg index,
				      memory::minimumAddressableUnit var)
{
    memory::mem[getIndexedAbsoluteImmediateAddress(index)] = var;
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
storeRegAtIndexedAbsoluteImmediateAddress(const architecturalState::isaReg index,
					  const architecturalState::isaReg reg)
{
  StoreVarAtIndexedAbsoluteImmediateAddress(index, reg);
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


inline void pushStatusFlagsToStackWithBSet()
{
  pushToStack(architecturalState::status.flags |
	      architecturalState::statusFlagMaskForPhpBrk);
}


inline memory::minimumAddressableUnit pullFromStack()
{
  return getVarAtAddress(memory::stackBase |
			  ++architecturalState::S);
}


inline memory::minimumAddressableUnit pullStatusFlagsFromStack()
{
  return architecturalState::statusFlagMaskPull & pullFromStack();
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
  pushStatusFlagsToStackWithBSet();
  architecturalState::status.u.I = 1;
  architecturalState::PC = (memory::mem[memory::brkPCLoadVector + 1]
			    << memory::minimumAddressableUnitSize) |
    memory::mem[memory::brkPCLoadVector];
  architecturalState::cycles += 7;
}


/*! \brief Shift Left One Bit (Memory or Accumulator)

  C <- [76543210] <- 0		       		|| 
  (N+, Z+, C+, I-, D-, V-) 			||
  Addressing Mode:		Zeropage       	||
  Assembly Language Form:	ASL oper       	||
  Opcode:			06		||
  Bytes:			2		||
  Cycles:			5		|| */
inline void asl_06()
{
  memory::minimumAddressableUnit var {memory::mem[memory::zeroPageBase |
							get8BitImmediate()]};
  architecturalState::status.u.C =
    ((var & masks::bit7) ? 1 : 0);
  var <<= 1;
  setZeroFlagOn(var);
  setNegativeFlagOn(var);
  memory::mem[memory::zeroPageBase | get8BitImmediate()] = var;
  architecturalState::PC += 2;
  architecturalState::cycles += 5;
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
  pushStatusFlagsToStackWithBSet();
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


/*! \brief Shift Left One Bit (Memory or Accumulator)

  C <- [76543210] <- 0	       	       		||
  (N+, Z+, C+, I-, D-, V-) 			||
  Addressing Mode:		Accumulator	||
  Assembly Language Form:	ALS A		||
  Opcode:			0A		||
  Bytes:			1		||
  Cycles:			2		|| */
inline void asl_0a()
{
  architecturalState::status.u.C =
    ((architecturalState::A & masks::bit7) ? 1 : 0);
  architecturalState::A <<= 1;
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A); 
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


/*! \brief Shift Left One Bit (Memory or Accumulator)

  C <- [76543210] <- 0	       	       		||
  (N+, Z+, C+, I-, D-, V-) 			||
  Addressing Mode:		Absolute	||
  Assembly Language Form:	ASL oper       	||
  Opcode:			0E		||
  Bytes:			3		||
  Cycles:			6		|| */
inline void asl_0e()
{
  memory::minimumAddressableUnit var {memory::mem[get16BitImmediate()]};
  architecturalState::status.u.C =
    ((var & masks::bit7) ? 1 : 0);
  var <<= 1;
  setZeroFlagOn(var);
  setNegativeFlagOn(var);
  memory::mem[get16BitImmediate()] = var;
  architecturalState::PC += 3;
  architecturalState::cycles += 6;
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


/*! \brief Shift Left One Bit (Memory or Accumulator)

  C <- [76543210] <- 0		       		|| 
  (N+, Z+, C+, I-, D-, V-) 			||
  Addressing Mode:		Zeropage, X    	||
  Assembly Language Form:	ASL oper, X    	||
  Opcode:			16		||
  Bytes:			2		||
  Cycles:			6		|| */
inline void asl_16()
{
  memory::minimumAddressableUnit var
    {getVarAtIndexedZeroPage(architecturalState::X)};
  architecturalState::status.u.C =
    ((var & masks::bit7) ? 1 : 0);
  var <<= 1;
  setZeroFlagOn(var);
  setNegativeFlagOn(var);
  storeVarAtIndexedZeroPage(architecturalState::X, var);
  architecturalState::PC += 2;
  architecturalState::cycles += 6;
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


/*! \brief Shift Left One Bit (Memory or Accumulator)

  C <- [76543210] <- 0		       		|| 
  (N+, Z+, C+, I-, D-, V-) 			||
  Addressing Mode:		Absolute, X    	||
  Assembly Language Form:	ASL oper, X    	||
  Opcode:			1E		||
  Bytes:			3		||
  Cycles:			7		|| */
inline void asl_1e()
{
  memory::minimumAddressableUnit var
    {memory::mem[getIndexedAbsoluteImmediateAddress(architecturalState::X)]};
  architecturalState::status.u.C =
    ((var & masks::bit7) ? 1 : 0);
  var <<= 1;
  setZeroFlagOn(var);
  setNegativeFlagOn(var);
  StoreVarAtIndexedAbsoluteImmediateAddress(architecturalState::X, var);
  architecturalState::PC += 3;
  architecturalState::cycles += 7;
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


/*! \brief Test Bits in Memory with Accumulator

  A AND M, M7 -> N, M6 -> V    	       		||
  (M7 -> N, Z+, C-, I-, D-, M6 -> V)		||
  Addressing Mode:		Zeropage       	||
  Assembly Language Form:	BIT oper       	||
  Opcode:			24		||
  Bytes:			2		||
  Cycles:			3		||
  bits 7 and 6 of operand are transfered to bit 7 and 6 of SR (N,V);
  the zeroflag is set to the result of operand AND accumulator. */
inline void bit_24()
{
  const memory::minimumAddressableUnit var {memory::mem[memory::zeroPageBase |
							 get8BitImmediate()]};
  setNegativeFlagOn(masks::bit7 & var);
  setOverflowOnVar(masks::bit6 & var);
  setZeroFlagOn(architecturalState::A & var);
  architecturalState::PC += 2;
  architecturalState::cycles += 3;
}


/*! \brief Rotate One Bit Left (Memory or Accumulator)

  C <- [76543210] <- C	       	       		||
  (N+, Z+, C+, I, D, V)				||
  Addressing Mode:		Zeropage    	||
  Assembly Language Form:	ROL oper       	||
  Opcode:			26		||
  Bytes:			2		||
  Cycles:			5		||
  http://www.6502.org/tutorials/6502opcodes.html#ROL:
  ROL shifts all bits left one position. The Carry is shifted into bit 0 and the
  original bit 7 is shifted into the Carry. */
inline void rol_26()
{
  memory::minimumAddressableUnit var {memory::mem[memory::zeroPageBase |
							get8BitImmediate()]};
  const architecturalState::isaReg RMB	// Right most bit.
    {architecturalState::isaReg((var & masks::bit7) ? 1 : 0)};
  var <<= 1;	// Do shift.
  // Set bit0 to carry.
  var = architecturalState::status.u.C ? var | masks::bit0 : var;
  architecturalState::status.u.C = RMB;	// Set carry to RMB before shift.
  memory::mem[memory::zeroPageBase | get8BitImmediate()] = var;
  setZeroFlagOn(var);
  setNegativeFlagOn(var);  
  architecturalState::PC += 2;
  architecturalState::cycles += 5;
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
  architecturalState::status.flags = pullStatusFlagsFromStack();
  architecturalState::PC += 1;
  architecturalState::cycles += 4;
}


/*! \brief Rotate One Bit Left (Memory or Accumulator)

  C <- [76543210] <- C	       	       		||
  (N+, Z+, C+, I, D, V)				||
  Addressing Mode:		Accumulator    	||
  Assembly Language Form:	ROL A		||
  Opcode:			2A		||
  Bytes:			1		||
  Cycles:			2		||
  http://www.6502.org/tutorials/6502opcodes.html#ROL:
  ROL shifts all bits left one position. The Carry is shifted into bit 0 and the
  original bit 7 is shifted into the Carry. */
inline void rol_2a()
{
  const architecturalState::isaReg RMB	// Right most bit.
    {architecturalState::isaReg((architecturalState::A & masks::bit7) ? 1 : 0)};
  architecturalState::A <<= 1;		// Do shift.
  architecturalState::A = architecturalState::status.u.C ? // Set bit0 to carry.
    architecturalState::A | masks::bit0 : architecturalState::A;
  architecturalState::status.u.C = RMB;	// Set carry to RMB before shift.
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);  
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


/*! \brief Test Bits in Memory with Accumulator

  A AND M, M7 -> N, M6 -> V    	       		||
  (M7 -> N, Z+, C-, I-, D-, M6 -> V)		||
  Addressing Mode:		Absolute       	||
  Assembly Language Form:	BIT oper       	||
  Opcode:			2C		||
  Bytes:			3		||
  Cycles:			4		||
  bits 7 and 6 of operand are transfered to bit 7 and 6 of SR (N,V);
  the zeroflag is set to the result of operand AND accumulator. */
inline void bit_2c()
{
  const memory::minimumAddressableUnit var {memory::mem[get16BitImmediate()]};
  setNegativeFlagOn(masks::bit7 & var);
  setOverflowOnVar(masks::bit6 & var);
  setZeroFlagOn(architecturalState::A & var);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


/*! \brief Rotate One Bit Left (Memory or Accumulator)

  C <- [76543210] <- C	       	       		||
  (N+, Z+, C+, I, D, V)				||
  Addressing Mode:		Absolute    	||
  Assembly Language Form:	ROL oper       	||
  Opcode:			2E		||
  Bytes:			3		||
  Cycles:			6		||
  http://www.6502.org/tutorials/6502opcodes.html#ROL:
  ROL shifts all bits left one position. The Carry is shifted into bit 0 and the
  original bit 7 is shifted into the Carry. */
inline void rol_2e()
{
  memory::minimumAddressableUnit var {memory::mem[get16BitImmediate()]};
  const architecturalState::isaReg RMB	// Right most bit.
    {architecturalState::isaReg((var & masks::bit7) ? 1 : 0)};
  var <<= 1;	// Do shift.
  // Set bit0 to carry.
  var = architecturalState::status.u.C ? var | masks::bit0 : var;
  architecturalState::status.u.C = RMB;	// Set carry to RMB before shift.
  memory::mem[get16BitImmediate()] = var;
  setZeroFlagOn(var);
  setNegativeFlagOn(var);  
  architecturalState::PC += 3;
  architecturalState::cycles += 6;
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


/*! \brief Rotate One Bit Left (Memory or Accumulator)

  C <- [76543210] <- C	       	       		||
  (N+, Z+, C+, I, D, V)				||
  Addressing Mode:		Zeropage, X    	||
  Assembly Language Form:	ROL oper, X    	||
  Opcode:			36		||
  Bytes:			2		||
  Cycles:			6		||
  http://www.6502.org/tutorials/6502opcodes.html#ROL:
  ROL shifts all bits left one position. The Carry is shifted into bit 0 and the
  original bit 7 is shifted into the Carry. */
inline void rol_36()
{
  memory::minimumAddressableUnit var
    {getVarAtIndexedZeroPage(architecturalState::X)};
  const architecturalState::isaReg RMB	// Right most bit.
    {architecturalState::isaReg((var & masks::bit7) ? 1 : 0)};
  var <<= 1;	// Do shift.
  // Set bit0 to carry.
  var = architecturalState::status.u.C ? var | masks::bit0 : var;
  architecturalState::status.u.C = RMB;	// Set carry to RMB before shift.
  storeVarAtIndexedZeroPage(architecturalState::X, var);
  setZeroFlagOn(var);
  setNegativeFlagOn(var);  
  architecturalState::PC += 2;
  architecturalState::cycles += 5;
}


/*! \brief Set Carry Flag

  1 -> C			       		||
  (N-, Z-, C = 1, I-, D-, V-) 			||
  Addressing Mode1:		Implied		||
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


/*! \brief Rotate One Bit Left (Memory or Accumulator)

  C <- [76543210] <- C	       	       		||
  (N+, Z+, C+, I, D, V)				||
  Addressing Mode:		Absolute, X    	||
  Assembly Language Form:	ROL oper, X    	||
  Opcode:			3E		||
  Bytes:			3		||
  Cycles:			7		||
  http://www.6502.org/tutorials/6502opcodes.html#ROL:
  ROL shifts all bits left one position. The Carry is shifted into bit 0 and the
  original bit 7 is shifted into the Carry. */
inline void rol_3e()
{
  memory::minimumAddressableUnit var
    {memory::mem[getIndexedAbsoluteImmediateAddress(architecturalState::X)]};
  const architecturalState::isaReg RMB	// Right most bit.
    {architecturalState::isaReg((var & masks::bit7) ? 1 : 0)};
  var <<= 1;	// Do shift.
  // Set bit0 to carry.
  var = architecturalState::status.u.C ? var | masks::bit0 : var;
  architecturalState::status.u.C = RMB;	// Set carry to RMB before shift.
  StoreVarAtIndexedAbsoluteImmediateAddress(architecturalState::X, var);
  setZeroFlagOn(var);
  setNegativeFlagOn(var);  
  architecturalState::PC += 3;
  architecturalState::cycles += 7;
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
  architecturalState::status.flags = pullStatusFlagsFromStack();
  loadPCFromStack();
  architecturalState::cycles += 6;
}


/*! \brief Shift One Bit Right (Memory or Accumulator)

  0 -> [76543210] -> C		       		||
  (N = 0, Z+, C+, I-, D-, V-) 	       		||
  Addressing Mode:		Zeropage       	||
  Assembly Language Form:	LSR oper       	||
  Opcode:			46		||
  Bytes:			2		||
  Cycles:			5		||
  LSR shifts all bits right one position. 0 is shifted into bit 7 and the
  original bit 0 is shifted into the Carry:
  http://6502.org/tutorials/6502opcodes.html#LSR */
inline void lsr_46()
{
  memory::minimumAddressableUnit var {memory::mem[memory::zeroPageBase |
						  get8BitImmediate()]};
  architecturalState::status.u.C =
    ((var & masks::bit0) ? 1 : 0);
  
  var >>= 1;
  memory::mem[memory::zeroPageBase | get8BitImmediate()] = var;
  setZeroFlagOn(var);
  architecturalState::status.u.N = 0;
  
  architecturalState::PC += 2;
  architecturalState::cycles += 5;
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


/*! \brief Shift One Bit Right (Memory or Accumulator)

  0 -> [76543210] -> C	       			||
  (N = 0, Z+, C+, I-, D-, V-) 			||
  Addressing Mode:		Accumulator	||
  Assembly Language Form:	LSR A   	||
  Opcode:			4A		||
  Bytes:			1		||
  Cycles:			2		||
  LSR shifts all bits right one position. 0 is shifted into bit 7 and the
  original bit 0 is shifted into the Carry:
  http://6502.org/tutorials/6502opcodes.html#LSR */
inline void lsr_4a()
{
  architecturalState::status.u.C =
    ((architecturalState::A & masks::bit0) ? 1 : 0);
  
  architecturalState::A >>= 1;
  setZeroFlagOn(architecturalState::A);
  architecturalState::status.u.N = 0;
  
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


inline void jmp_4c()
{
  loadPCFrom16BitImmediate();
  architecturalState::cycles += 3;
}


/*! \brief Shift One Bit Right (Memory or Accumulator)

  0 -> [76543210] -> C		       		||
  (N = 0, Z+, C+, I-, D-, V-) 	       		||
  Addressing Mode:		Absolute       	||
  Assembly Language Form:	LSR oper       	||
  Opcode:			4E		||
  Bytes:			3		||
  Cycles:			6		||
  LSR shifts all bits right one position. 0 is shifted into bit 7 and the
  original bit 0 is shifted into the Carry:
  http://6502.org/tutorials/6502opcodes.html#LSR */
inline void lsr_4e()
{
  memory::minimumAddressableUnit var {memory::mem[get16BitImmediate()]};
  architecturalState::status.u.C =
    ((var & masks::bit0) ? 1 : 0);
  
  var >>= 1;
  memory::mem[get16BitImmediate()] = var;
  setZeroFlagOn(var);
  architecturalState::status.u.N = 0;
  
  architecturalState::PC += 3;
  architecturalState::cycles += 6;
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


/*! \brief Shift One Bit Right (Memory or Accumulator)

  0 -> [76543210] -> C		       		||
  (N = 0, Z+, C+, I-, D-, V-) 	       		||
  Addressing Mode:		Zeropage, X    	||
  Assembly Language Form:	LSR oper, X    	||
  Opcode:			56		||
  Bytes:			2		||
  Cycles:			6		||
  LSR shifts all bits right one position. 0 is shifted into bit 7 and the
  original bit 0 is shifted into the Carry:
  http://6502.org/tutorials/6502opcodes.html#LSR */
inline void lsr_56()
{
  memory::minimumAddressableUnit var
    {getVarAtIndexedZeroPage(architecturalState::X)};
  architecturalState::status.u.C =
    ((var & masks::bit0) ? 1 : 0);
  
  var >>= 1;
  storeVarAtIndexedZeroPage(architecturalState::X, var);
  setZeroFlagOn(var);
  architecturalState::status.u.N = 0;
  
  architecturalState::PC += 2;
  architecturalState::cycles += 6;
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


/*! \brief Shift One Bit Right (Memory or Accumulator)

  0 -> [76543210] -> C		       		||
  (N = 0, Z+, C+, I-, D-, V-) 	       		||
  Addressing Mode:		Absolute, X    	||
  Assembly Language Form:	LSR oper, X    	||
  Opcode:			5E		||
  Bytes:			3		||
  Cycles:			7		||
  LSR shifts all bits right one position. 0 is shifted into bit 7 and the
  original bit 0 is shifted into the Carry:
  http://6502.org/tutorials/6502opcodes.html#LSR */
inline void lsr_5e()
{
  memory::minimumAddressableUnit var
    {memory::mem[getIndexedAbsoluteImmediateAddress(architecturalState::X)]};
  architecturalState::status.u.C =
    ((var & masks::bit0) ? 1 : 0);
  
  var >>= 1;
  StoreVarAtIndexedAbsoluteImmediateAddress(architecturalState::X, var);
  setZeroFlagOn(var);
  architecturalState::status.u.N = 0;
  
  architecturalState::PC += 3;
  architecturalState::cycles += 7;
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


/*! \brief Rotate One Bit Right (Memory or Accumulator)

  C -> [76543210] -> C		       		||
  (N+, Z+, C+, I-, D-, V-) 			||
  Addressing Mode:		Zeropage       	||
  Assembly Language Form:	ROR oper       	||
  Opcode:			66		||
  Bytes:			2		||
  Cycles:			5		||
  http://www.6502.org/tutorials/6502opcodes.html#ROL:
  ROR shifts all bits right one position. The Carry is shifted into bit 7 and
  the original bit 0 is shifted into the Carry. */
inline void ror_66()
{
  memory::minimumAddressableUnit var {memory::mem[memory::zeroPageBase |
						  get8BitImmediate()]};
  const architecturalState::isaReg LMB	// Right most bit.
    {architecturalState::isaReg((var & masks::bit0) ? 1 : 0)};
  var >>= 1;		// Do shift.
  // Set bit7 to carry.
  var = architecturalState::status.u.C ? var | masks::bit7 : var;
  memory::mem[memory::zeroPageBase | get8BitImmediate()] = var;
  architecturalState::status.u.C = LMB;	// Set carry to LMB before shift.
  setZeroFlagOn(var);
  setNegativeFlagOn(var);  
  architecturalState::PC += 2;
  architecturalState::cycles += 5;
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
  setOverflowOnAdditionOn(architecturalState::A, get8BitImmediate(), aR);
  architecturalState::A = aR;
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


/*! \brief Rotate One Bit Right (Memory or Accumulator)

  C -> [76543210] -> C		       		||
  (N+, Z+, C+, I-, D-, V-) 			||
  Addressing Mode:		Accumulator    	||
  Assembly Language Form:	ROR A		||
  Opcode:			6A		||
  Bytes:			1		||
  Cycles:			2		||
  http://www.6502.org/tutorials/6502opcodes.html#ROL:
  ROR shifts all bits right one position. The Carry is shifted into bit 7 and
  the original bit 0 is shifted into the Carry. */
inline void ror_6a()
{
    const architecturalState::isaReg LMB	// Right most bit.
    {architecturalState::isaReg((architecturalState::A & masks::bit0) ? 1 : 0)};
    architecturalState::A >>= 1;		// Do shift.
  architecturalState::A = architecturalState::status.u.C ? // Set bit7 to carry.
    architecturalState::A | masks::bit7 : architecturalState::A;
  architecturalState::status.u.C = LMB;	// Set carry to LMB before shift.
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);  
  architecturalState::PC += 1;
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


/*! \brief Rotate One Bit Right (Memory or Accumulator)

  C -> [76543210] -> C		       		||
  (N+, Z+, C+, I-, D-, V-) 			||
  Addressing Mode:		Absolute       	||
  Assembly Language Form:	ROR oper       	||
  Opcode:			6E		||
  Bytes:			3		||
  Cycles:			6		||
  http://www.6502.org/tutorials/6502opcodes.html#ROL:
  ROR shifts all bits right one position. The Carry is shifted into bit 7 and
  the original bit 0 is shifted into the Carry. */
inline void ror_6e()
{
  memory::minimumAddressableUnit var {memory::mem[get16BitImmediate()]};
  const architecturalState::isaReg LMB	// Right most bit.
    {architecturalState::isaReg((var & masks::bit0) ? 1 : 0)};
  var >>= 1;		// Do shift.
  // Set bit7 to carry.
  var = architecturalState::status.u.C ? var | masks::bit7 : var;
  memory::mem[get16BitImmediate()] = var;
  architecturalState::status.u.C = LMB;	// Set carry to LMB before shift.
  setZeroFlagOn(var);
  setNegativeFlagOn(var);  
  architecturalState::PC += 3;
  architecturalState::cycles += 6;
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


/*! \brief Rotate One Bit Right (Memory or Accumulator)

  C -> [76543210] -> C		       		||
  (N+, Z+, C+, I-, D-, V-) 			||
  Addressing Mode:		Zeropage, X    	||
  Assembly Language Form:	ROR oper, X    	||
  Opcode:			76		||
  Bytes:			2		||
  Cycles:			6		||
  http://www.6502.org/tutorials/6502opcodes.html#ROL:
  ROR shifts all bits right one position. The Carry is shifted into bit 7 and
  the original bit 0 is shifted into the Carry. */
inline void ror_76()
{
  memory::minimumAddressableUnit var
    {getVarAtIndexedZeroPage(architecturalState::X)};
  const architecturalState::isaReg LMB	// Right most bit.
    {architecturalState::isaReg((var & masks::bit0) ? 1 : 0)};
  var >>= 1;		// Do shift.
  // Set bit7 to carry.
  var = architecturalState::status.u.C ? var | masks::bit7 : var;
  storeVarAtIndexedZeroPage(architecturalState::X, var);
  architecturalState::status.u.C = LMB;	// Set carry to LMB before shift.
  setZeroFlagOn(var);
  setNegativeFlagOn(var);  
  architecturalState::PC += 2;
  architecturalState::cycles += 5;
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
  Addressing Mode:		(Indirect, X)  	||
  Assembly Language Form:	STA (oper, X)  	||
  Opcode:			81		||
  Bytes:			2		||
  Cycles:			6		|| */
inline void sta_81()
{
  memory::mem[getPreIndexedIndirectImmediateAddress(architecturalState::X)] =
    architecturalState::A;
  architecturalState::PC += 2;
  architecturalState::cycles += 6;
}


/*! \brief Store Index Y in Memory

  Y -> M      					||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Zeropage       	||
  Assembly Language Form:	STY oper       	||
  Opcode:			84		||
  Bytes:			2		||
  Cycles:			3		|| */
inline void sty_84()
{
  memory::mem[memory::zeroPageBase | get8BitImmediate()] =
    architecturalState::Y;
  architecturalState::PC += 2;
  architecturalState::cycles += 3;
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
anch is taken and add one more if the branch crosses a page boundary. From:
  http://6502.org/tutorials/6502opcodes.html#BCC */
inline void bcc_90()
{
  if(architecturalState::status.u.C == 0)
    branchTaken();
  architecturalState::PC += 2;	// This is done even if branch is taken.
  architecturalState::cycles += 2;
}


/*! \brief Store Accumulator in Memory

  A -> M				        ||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		(Indirect), Y	||
  Assembly Language Form:	STA (oper), Y	||
  Opcode:			91		||
  Bytes:			2		||
  Cycles:			6		|| */
inline void sta_91()
{
  storeRegAtAddress(getPostIndexedIndirectImmediateAddress(architecturalState::Y),
		    architecturalState::A);
  architecturalState::PC += 2;
  architecturalState::cycles += 5;
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


/*! \brief Store Accumulator in Memory

  A -> M				        ||
  (N-, Z-, C-, I-, D-, V-) 			||
  Addressing Mode:		Zeropage, X	||
  Assembly Language Form:	STA oper, X	||
  Opcode:			95		||
  Bytes:			2		||
  Cycles:			4		|| */
inline void sta_95()
{
  storeRegAtIndexedZeroPage(architecturalState::X, architecturalState::A);
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
  storeRegAtIndexedAbsoluteImmediateAddress(architecturalState::Y,
					    architecturalState::A);
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
  storeRegAtIndexedAbsoluteImmediateAddress(architecturalState::X,
					    architecturalState::A);
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


/*! \brief Load Accumulator with Memory

  M -> A				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		(Indirect, X)	||
  Assembly Language Form:	LDA (oper, X)   ||
  Opcode:			A1		||
  Bytes:			2		||
  Cycles:			6		||
  https://sites.google.com/site/6502asembly/6502-instruction-set/lda/the-addressing-mode-summary-of-lda:
  Load Accumulator from address obtained from the address calculated from "$20
  adding content of Index Register X" Address must wrap around! */
inline void lda_a1()
{
  architecturalState::A =
    getVarAtAddress(getPreIndexedIndirectImmediateAddress(architecturalState::X));
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
  architecturalState::PC += 2;
  architecturalState::cycles += 6;
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


/*! \brief Load Index Y with Memory

  M -> Y				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		Absolute       	||
  Assembly Language Form:	LDY oper       	||
  Opcode:			AC		||
  Bytes:			3		||
  Cycles:			4		|| */
inline void ldy_ac()
{
  architecturalState::Y = getVarAtAddress(get16BitImmediate());
  setZeroFlagOn(architecturalState::Y);
  setNegativeFlagOn(architecturalState::Y);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
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


/*! \brief Load Accumulator with Memory

  M -> A				       	||
  (N+, Z+, C-, I-, D-, V-) 			||
  Addressing Mode:		(Indirect), Y	||
  Assembly Language Form:	LDA (oper), Y	||
  Opcode:			B1		||
  Bytes:			2		||
  Cycles:			5*		||
  https://sites.google.com/site/6502asembly/6502-instruction-set/lda/the-addressing-mode-summary-of-lda:
  Load Accumulator from address obtained from the address calculated from "the
  value stored in the address $20" adding content of Index Register Y */
inline void lda_b1()
{
  architecturalState::A =
    getVarAtAddress(getPostIndexedIndirectImmediateAddress(architecturalState::Y));
  setZeroFlagOn(architecturalState::A);
  setNegativeFlagOn(architecturalState::A);
  architecturalState::PC += 2;
  architecturalState::cycles += 5;
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
  Addressing Mode:		(Indirect, X)	||
  Assembly Language Form:	CMP (oper, X)	||
  Opcode:			C1		||
  Bytes:			2		||
  Cycles:			6		|| */
inline void cmp_c1()
{
  const memory::address address
    {getPreIndexedIndirectImmediateAddress(architecturalState::X)};
  const memory::minimumAddressableUnit compVal {memory::minimumAddressableUnit
    (architecturalState::A - getVarAtAddress(address))};

  /* Note here that we negate the second argument so our addition is actually a
     subtraction. */
  setCarryFlagOnAdditionOn(architecturalState::A, - getVarAtAddress(address));
  setZeroFlagOn(compVal);
  setNegativeFlagOn(compVal); 
  architecturalState::PC += 2;
  architecturalState::cycles += 6;
}


/*! \brief Compare Memory and Index Y

  Y - M						||
  (N+, Z+, C+, I-, D-, V-) 			||
  Addressing Mode:		Zeropage	||
  Assembly Language Form:	CPY oper	||
  Opcode:			C4		||
  Bytes:			2		||
  Cycles:			3		|| */
inline void cpy_c4()
{
  const memory::minimumAddressableUnit var {memory::mem[memory::zeroPageBase |
							 get8BitImmediate()]};
  architecturalState::status.u.C = ((architecturalState::Y == var)
				    || (architecturalState::Y >
					var)) ? 1 : 0;
  setZeroFlagOn(architecturalState::Y - var);
  setNegativeFlagOn(architecturalState::Y - var);
  architecturalState::PC += 2;
  architecturalState::cycles += 3;
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
  memory::minimumAddressableUnit var {memory::mem[memory::zeroPageBase |
							 get8BitImmediate()]};
  architecturalState::status.u.C = ((architecturalState::A == var)
				    || (architecturalState::A >
					var)) ? 1 : 0;
  setZeroFlagOn(architecturalState::A - var);
  setNegativeFlagOn(architecturalState::A - var);
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


/*! \brief Compare Memory and Index Y

  Y - M						||
  (N+, Z+, C+, I-, D-, V-)			||
  Addressing Mode:		Absolute	||
  Assembly Language Form:	CPY oper	||
  Opcode:			CC		||
  Bytes:			3		||
  Cycles:			4		|| */
inline void cpy_cc()
{
  const memory::minimumAddressableUnit var
    {getVarAtAddress(get16BitImmediate())};
  architecturalState::status.u.C = ((architecturalState::Y == var)
				    || (architecturalState::Y >
					var)) ? 1 : 0;
  setZeroFlagOn(architecturalState::Y - var);
  setNegativeFlagOn(architecturalState::Y - var);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
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
  Addressing Mode:		(Indirect), Y	||
  Assembly Language Form:	CMP (oper), Y	||
  Opcode:			D1		||
  Bytes:			2		||
  Cycles:			5*		|| */
inline void cmp_d1()
{
  const memory::address address
    {getPostIndexedIndirectImmediateAddress(architecturalState::Y)};

  const memory::minimumAddressableUnit compVal {memory::minimumAddressableUnit
    (architecturalState::A - getVarAtAddress(address))};

  /* Note here that we negate the second argument so our addition is actually a
     subtraction. */
  setCarryFlagOnAdditionOn(architecturalState::A, - getVarAtAddress(address));
  setZeroFlagOn(compVal);
  setNegativeFlagOn(compVal); 
  architecturalState::PC += 2;
  architecturalState::cycles += 5;
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
  const memory::minimumAddressableUnit var {memory::mem[memory::zeroPageBase |
							 get8BitImmediate()]};
    architecturalState::status.u.C = ((architecturalState::X == var)
				    || (architecturalState::X >
					var)) ? 1 : 0;
  setZeroFlagOn(architecturalState::X - var);
  setNegativeFlagOn(architecturalState::X - var);
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
  const memory::minimumAddressableUnit var
    {getVarAtAddress(get16BitImmediate())};
  architecturalState::status.u.C = ((architecturalState::X == var)
				    || (architecturalState::X >
					var)) ? 1 : 0;
  setZeroFlagOn(architecturalState::X - var);
  setNegativeFlagOn(architecturalState::X - var);
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
