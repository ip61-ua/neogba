#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa-arm.hpp"
#include "neogba/arm7tdmi/registers.hpp"
#include "neogba/types.hpp"

using namespace neogba;
using namespace neogba::arm7;

u32 ARM7TDMI::fetch() {
  return 0;
}

void ARM7TDMI::executeArm(u32 instruction) {
  using namespace neogba::arm7::arm_mode;

  if (Branch::is(instruction)) {
    Branch info = Branch::extract(instruction);

    if (info.l)
      registers.write(14, registers.read(Registers::pc) - 4);

    registers.write(Registers::pc, (info.offset << 2) + registers.read(Registers::pc));
    return;
  }

  if (DataProcessingPSRTrans::is(instruction)) {
    DataProcessingPSRTrans info = DataProcessingPSRTrans::extract(instruction);

    switch (info.opcode) {
    case DataProcessingPSRTrans::AND:
    case DataProcessingPSRTrans::EOR:
    case DataProcessingPSRTrans::SUB:
    case DataProcessingPSRTrans::RSB:
    case DataProcessingPSRTrans::ADD:
    case DataProcessingPSRTrans::ADC: {
      // Addition with carry

      u32 op1{registers.read(info.rn)}, op2{registers.read(info.operand2)};
      u64 result64 =
          static_cast<u64>(op1) + static_cast<u64>(op2) + (registers.isFlag(Registers::C) ? 1 : 0);

      u32 result = static_cast<u32>(result64);
      registers.write(info.rd, result);

      if (info.s) {
        (result == 0) ? registers.setFlag(Registers::Z) : registers.clearFlag(Registers::Z);
        (bitToBool(result, 31)) ? registers.setFlag(Registers::N)
                                : registers.clearFlag(Registers::N);
        (result64 > 0xffffffff) ? registers.setFlag(Registers::C)
                                : registers.clearFlag(Registers::C);

        bool signOp1 = bitToBool(op1, 31);
        bool signOp2 = bitToBool(op2, 31);
        bool signRes = bitToBool(result, 31);

        ((signOp1 == signOp2) && (signOp1 != signRes)) ? registers.setFlag(Registers::V)
                                                       : registers.clearFlag(Registers::V);
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

void ARM7TDMI::step() {}
