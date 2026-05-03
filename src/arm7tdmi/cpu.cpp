#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/types.hpp"

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

    switch (info.opcode) {
    case DataProcessingPSRTrans::AND:
    case DataProcessingPSRTrans::EOR:
    case DataProcessingPSRTrans::SUB:
    case DataProcessingPSRTrans::RSB:
    case DataProcessingPSRTrans::ADD:
    case DataProcessingPSRTrans::ADC: {
      u32 op1 = registers.read(info.rn);
      u32 op2 = info.operand2;
      u32 c = registers.isC() ? 1 : 0;

      u64 result64 = static_cast<uint64_t>(op1) + static_cast<uint64_t>(op2) + c;

      u32 result = static_cast<u32>(result64);
      registers.write(info.rd, result);

      if (info.s) {
        (result == 0) ? registers.setZ() : registers.clearZ();
        (BIT_TO_BOOL(result, 31)) ? registers.setN() : registers.clearN();
        (result64 > 0xffffffff) ? registers.setC() : registers.clearC();

        bool op1sign = BIT_TO_BOOL(op1, 31);
        bool op2sign = BIT_TO_BOOL(op2, 31);
        bool ressign = BIT_TO_BOOL(result, 31);

        ((op1sign == op2sign) && (op1sign != ressign)) ? registers.setV() : registers.clearV();
      }

      break;
    }
    case DataProcessingPSRTrans::SBC:
    case DataProcessingPSRTrans::RSC:
    case DataProcessingPSRTrans::TST:
    case DataProcessingPSRTrans::TEQ:
    case DataProcessingPSRTrans::CMP:
    case DataProcessingPSRTrans::CMN:
    case DataProcessingPSRTrans::ORR:
    case DataProcessingPSRTrans::MOV:
    case DataProcessingPSRTrans::BIC:
    case DataProcessingPSRTrans::MVN:
      break;
    }
  }

  /*
  <opcode1>{<cond>}{S} <Rd>, <shifter_operand>
  <opcode1> := MOV | MVN
  <opcode2>{<cond>} <Rn>, <shifter_operand>
  <opcode2> := CMP | CMN | TST | TEQ
  <opcode3>{<cond>}{S} <Rd>, <Rn>, <shifter_operand>
  <opcode3> := ADD | SUB | RSB | ADC | SBC | RSC | AND | BIC | EOR | ORR
  */
}

void CPU::step() {}
