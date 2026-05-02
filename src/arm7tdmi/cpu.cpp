#include "neogba/arm7tdmi/cpu.hpp"

using namespace neogba;
using namespace neogba::arm7tdmi;

u32 CPU::fetch() {
  return 0;
}

void CPU::execute() {
  using namespace ArmInstruction;

  if (Branch::is(currentInstruction)) {
    Branch info = Branch::extract(currentInstruction);

    if (info.l)
      registers.write(14, registers.read(RegistersIndex::pc) - 4);

    registers.write(RegistersIndex::pc, (info.offset << 2) + registers.read(RegistersIndex::pc));
    return;
  }

  if (DataProcessingPSRTrans::is(currentInstruction)) {
    DataProcessingPSRTrans info = DataProcessingPSRTrans::extract(currentInstruction);

    /*
    <opcode1>{<cond>}{S} <Rd>, <shifter_operand>
    <opcode1> := MOV | MVN
    <opcode2>{<cond>} <Rn>, <shifter_operand>
    <opcode2> := CMP | CMN | TST | TEQ
    <opcode3>{<cond>}{S} <Rd>, <Rn>, <shifter_operand>
    <opcode3> := ADD | SUB | RSB | ADC | SBC | RSC | AND | BIC | EOR | ORR
  */

    switch (info.opcode) {
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
