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


/* "CLD (Clear Decimal Flag) clears the Decimal Flag in the Processor Status
   Register by setting the 3rd bit 0." "Even though the NES doesn't use decimal
   mode, the opcodes to clear and set the flag do work, so if you need to store
   a bit, this acts as a free space."
   - http://www.thealmightyguru.com/Games/Hacking/Wiki/index.php?title=CLD */
void cdl();
void ldx();


void cdl()
{
  architecturalState::status.u.D = 1;
  architecturalState::PC += 1;
  architecturalState::cycles += 2;
}


void ldx()
{
  switch(unsigned(memory::mem[architecturalState::PC]))
    {
    case:
      break;
    case:
      break;
    case:
      break;
    case:
      break;
    case:
      break;
    }
}


#endif
