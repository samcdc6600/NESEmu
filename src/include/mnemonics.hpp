#ifndef MNEMONICS_HPP_
#define MNEMONICS_HPP_

#ifdef DEBUG
// We thses strings are currently only used to aid in debuging.
namespace mnemonics
{
  const std::string instructionMnemonicsOrganizedByOpcode []
  {
      "BRK", "ORA", "STP", "SLO", "NOP", "ORA", "ASL", "SLO",
      "PHP", "ORA", "ASL", "ANC", "NOP", "ORA", "ASL", "SLO",
      "BPL", "ORA", "STP", "SLO", "NOP", "ORA", "ASL", "SLO",
      "CLC", "ORA", "NOP", "SLO", "NOP", "ORA", "ASL", "SLO",
      "JSR", "AND", "STP", "RLA", "BIT", "AND", "ROL", "RLA",
      "PLP", "AND", "ROL", "ANC", "BIT", "AND", "ROL", "RLA",
      "BMI", "AND", "STP", "RLA", "NOP", "AND", "ROL", "RLA",
      "SEC", "AND", "NOP", "RLA", "NOP", "AND", "ROL", "RLA",
      "RTI", "EOR", "STP", "SRE", "NOP", "EOR", "LSR", "SRE",
      "PHA", "EOR", "LSR", "ALR", "JMP", "EOR", "LSR", "SRE",
      "BVC", "EOR", "STP", "SRE", "NOP", "EOR", "LSR", "SRE",
      "CLI", "EOR", "NOP", "SRE", "NOP", "EOR", "LSR", "SRE",
      "RTS", "ADC", "STP", "RRA", "NOP", "ADC", "ROR", "RRA",
      "PLA", "ADC", "ROR", "ARR", "JMP", "ADC", "ROR", "RRA",
      "BVS", "ADC", "STP", "RRA", "NOP", "ADC", "ROR", "RRA",
      "SEI", "ADC", "NOP", "RRA", "NOP", "ADC", "ROR", "RRA",
      "NOP", "STA", "NOP", "SAX", "STY", "STA", "STX", "SAX",
      "DEY", "NOP", "TXA", "XAA", "STY", "STA", "STX", "SAX",
      "BCC", "STA", "STP", "AHX", "STY", "STA", "STX", "SAX",
      "TYA", "STA", "TXS", "TAS", "SHY", "STA", "SHX", "AHX",
      "LDY", "LDA", "LDX", "LAX", "LDY", "LDA", "LDX", "LAX",
      "TAY", "LDA", "TAX", "LAX", "LDY", "LDA", "LDX", "LAX",
      "BCS", "LDA", "STP", "LAX", "LDY", "LDA", "LDX", "LAX",
      "CLV", "LDA", "TSX", "LAS", "LDY", "LDA", "LDX", "LAX",
      "CPY", "CMP", "NOP", "DCP", "CPY", "CMP", "DEC", "DCP",
      "INY", "CMP", "DEX", "AXS", "CPY", "CMP", "DEC", "DCP",
      "BNE", "CMP", "STP", "DCP", "NOP", "CMP", "DEC", "DCP",
      "CLD", "CMP", "NOP", "DCP", "NOP", "CMP", "DEC", "DCP",
      "CPX", "SBC", "NOP", "ISC", "CPX", "SBC", "INC", "ISC",
      "INX", "SBC", "NOP", "SBC", "CPX", "SBC", "INC", "ISC",
      "BEQ", "SBC", "STP", "ISC", "NOP", "SBC", "INC", "ISC",
      "SED", "SBC", "NOP", "ISC", "NOP", "SBC", "INC", "ISC"
  };
}
#endif
#endif
