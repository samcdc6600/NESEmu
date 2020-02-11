#ifndef INSTRUCTIONS_HPP_
#define INSTRUCTIONS_HPP_
/* This translation unit is only intended for use with "cpu.cpp". It exists only
   to break up "cpu.cpp". This is beneficial because it allows a logical
   splitting of the logic that handles the CPU instructions from the rest of the
   code for the CPU in cpu.cpp and more importantly it allows us to reduce the
   length of the cpu.cpp translation unit as well as allowing us to have both
   translation units open in two different editor windows simultaneously.
   We put both function declarations and definitions here becase we are
   accessing the "architecturalState" namespace and our functions are inline,
   both of these factors necessitate that our function definitions be in this
   translation unit. */
// We have a separet function for each opcode for performance reasons.

// =================== SUB INSTRUCTION GRANULARITY OPERATIONS ==================
// =========== (The below functions prototypes are used for operations =========
// ============ that do not in them selves constitute instructions.) ===========
inline void setZeroFlagOn(const memory::minimumAddressableUnit var);
inline void setDecimalFlagOn(const bool d);
inline void setNegativeFlagOn(const memory::minimumAddressableUnit var);
inline memory::address getImmediateAddress();
inline void storeAbsoluteThis(const memory::minimumAddressableUnit var);
inline void loadPCFromImmediate();

// ======================== INSTRUCTION SPECIALIZATIONS  =======================
// ============== (The below functions prototypes comprise full  ===============
// ==== instructions. Functions that belong to the same class of instruction ===
// ============ (indicated by their prefixs) are grouped together.) ============
/* Note: PC should be altered after calling "SUB INSTRUCTION GRANULARITY
   OPERATIONS", as these functions assume it has not been altered yet! */
inline void jmp_4c();
inline void sta_8d();
/* "TXS (Transfer X Index to Stack Pointer) transfers the value in the X index 
   to the stack pointer."
   - http://www.thealmightyguru.com/Games/Hacking/Wiki/index.php?title=TXS */
inline void txs_9a();
inline void ldx_a2();
inline void lda_a9();
/* "CLD (Clear Decimal Flag) clears the Decimal Flag in the Processor Status
   Register by setting the 3rd bit 0." "Even though the NES doesn't use decimal
   mode, the opcodes to clear and set the flag do work, so if you need to store
   a bit, this acts as a free space."
   - http://www.thealmightyguru.com/Games/Hacking/Wiki/index.php?title=CLD */
inline void cdl_d8();


// =================== SUB INSTRUCTION GRANULARITY OPERATIONS ==================
// ============ (The below functions are used for operations that do ===========
// ================ not in them selves constitute instructions.) ===============


inline void setDecimalFlagOn(const bool d)
{
  architecturalState::status.u.D = d;
}


inline void setZeroFlagOn(const memory::minimumAddressableUnit var)
{
  architecturalState::status.u.Z = !var ? 1 : 0;
}


void setNegativeFlagOn(const memory::minimumAddressableUnit var)
{
  architecturalState::status.u.N =
    (var & masks::bit7) ? 1 : 0;
}


inline memory::address getImmediateAddress()
{
  return memory::address(memory::mem[architecturalState::PC + 1]) +
	      memory::address((memory::mem[architecturalState::PC + 2])
			      << memory::minimumAddressableUnitSize);
}


inline void storeAbsoluteThis(const memory::minimumAddressableUnit var)
{
  memory::mem[getImmediateAddress()] = var;
}


inline void loadPCFromImmediate()
{
  architecturalState::PC = getImmediateAddress();
}


// ======================== INSTRUCTION SPECIALIZATIONS  =======================
// ============== (The below functions comprise full instructions. =============
// =========== Functions that belong to the same class of instruction ==========
// ============ (indicated by their prefixs) are grouped together.) ============


inline void jmp_4c()
{
  std::cout<<"PC = "<<architecturalState::PC<<'\n';
  loadPCFromImmediate();
  std::cout<<"PC = "<<architecturalState::PC<<'\n';
  architecturalState::PC += 3;
  architecturalState::cycles += 3;
}


inline void sta_8d()
{
  storeAbsoluteThis(architecturalState::A);
  architecturalState::PC += 3;
  architecturalState::cycles += 4;
}


inline void txs_9a()
{
  setNegativeFlagOn(architecturalState::X);
  setZeroFlagOn(architecturalState::X);
  architecturalState::S = architecturalState::X;
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


inline void ldx_a2()
{
  architecturalState::X = memory::mem[architecturalState::PC + 1];
  setNegativeFlagOn(architecturalState::X);
  setZeroFlagOn(architecturalState::X);
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


inline void lda_a9()
{
  architecturalState::A = memory::mem[architecturalState::PC + 1];
  setNegativeFlagOn(architecturalState::A);
  setZeroFlagOn(architecturalState::A);
  architecturalState::PC += 2;
  architecturalState::cycles += 2;
}


inline void cdl_d8()
{
  setDecimalFlagOn(false);
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


#endif
