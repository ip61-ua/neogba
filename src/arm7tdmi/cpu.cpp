#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/registers.hpp"

using namespace neogba;
using namespace neogba::arm7tdmi;

u32 CPU::fetch() {
  return 0;
}

void CPU::execute() {
  if (currentInstruction & 0x0E000000) { // isBranchInstruction
    if (currentInstruction & 0x01000000) // isBranchAndLink
      registers.write(14, registers.read(RegistersIndex::pc) - 4);

    registers.write(RegistersIndex::pc,
                    ((currentInstruction & 0x00FFFFFF) << 2) + registers.read(RegistersIndex::pc));
    return;
  }

  if ((currentInstruction & 0x0C000000) == 0) { // isDataProcessingInstruction
    bool i = currentInstruction & 0x02000000, s = currentInstruction & 0x100000;
    u32 opcode = (currentInstruction & 0x01E00000) >> 24, Rn = currentInstruction & 0xF0000 >> 16,
        Rd = currentInstruction & 0xF000 >> 12;

    /*
      <opcode1>{<cond>}{S} <Rd>, <shifter_operand>
      <opcode1> := MOV | MVN
      <opcode2>{<cond>} <Rn>, <shifter_operand>
      <opcode2> := CMP | CMN | TST | TEQ
      <opcode3>{<cond>}{S} <Rd>, <Rn>, <shifter_operand>
      <opcode3> := ADD | SUB | RSB | ADC | SBC | RSC | AND | BIC | EOR | ORR
    */

    switch (opcode) {
    case DataProcessingOpcode::MOV:
    case DataProcessingOpcode::MVN:
      break;

    case DataProcessingOpcode::CMP:
    case DataProcessingOpcode::CMN:
    case DataProcessingOpcode::TST:
    case DataProcessingOpcode::TEQ:
      break;

    default:
      break;
    }
  }
}

void CPU::step() {}
