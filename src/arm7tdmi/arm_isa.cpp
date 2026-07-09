#include "neogba/arm7tdmi/arm_isa.hpp"

using namespace neogba;

arm_operand2_result arm_operand2_compute(arm7tdmi* cpu, u32 inst) {
  u32 shift_amount, operable_operand2{};
  u8 i{ISA_ARM_FSR_I::get_raw(inst)};

  if (i) {
    // operand2 is immediate value with shift.

    shift_amount = 2 * ISA_ARM_FSR_OPERAND2_ROTATE::get(inst);
    u32 imm{ISA_ARM_FSR_OPERAND2_IMM::get(inst)};

    operable_operand2 =
        (shift_amount == 0) ? imm : ((imm >> shift_amount) | (imm << (32 - shift_amount)));
  } else {

    // operand2 is a register with shift.

    u8 rm_idx{ISA_ARM_FSR_OPERAND2_RM::get(inst)};
    u32 rm{cpu->read_active_register(rm_idx)};
    u8 shift_type{ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(inst)};
    bool four{ISA_ARM_FSR_OPERAND2_4::get(inst)};

    shift_amount = four ? cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst))
                        : ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst);

    bool is_special_case{!four && shift_amount == 0};

    switch (shift_type) {

    case LSL:
      if (is_special_case) {
        operable_operand2 = rm; // LSL #0
      } else {
        operable_operand2 = (shift_amount >= 32) ? 0 : (rm << shift_amount);
      }
      break;

    case LSR:
      if (is_special_case)
        shift_amount = 32; // LSR #0

      operable_operand2 = (shift_amount >= 32) ? 0 : (rm >> shift_amount);
      break;

    case ASR:
      if (is_special_case) {
        shift_amount = 32; // ASR #0
      }

      operable_operand2 =
          static_cast<u32>(static_cast<int32_t>(rm) >> std::min<u32>(31, shift_amount));
      break;

    case ROR:
      if (is_special_case) {
        // RRX: Rotate 1 bit and include Cin.
        if (cpu->is_cpsr(arm7tdmi::C, arm7tdmi::C))
          operable_operand2 = 0x80000000;

        operable_operand2 |= (rm >> 1);
      } else {
        shift_amount &= (1 << 5) - 1;
        operable_operand2 =
            (shift_amount == 0) ? rm : ((rm >> shift_amount) | (rm << (32 - shift_amount)));
      }
      break;
    }
  }

  return {shift_amount, operable_operand2};
}

void arm_AND(arm7tdmi* cpu, u32 inst) {
  // u32 operable_operand2{};

  u8 rn_idx{ISA_ARM_FSR_RN::get(inst)};
  u8 rd_idx{ISA_ARM_FSR_RD::get(inst)};

  [[maybe_unused]] bool s{ISA_ARM_FSR_S::get(inst)};

  auto result{neogba::arm_operand2_compute(cpu, inst)};

  u32 res = cpu->read_active_register(rn_idx) & result.operable_operand2;

  cpu->write_active_register(rd_idx, res);

  if (s)
    cpu->set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C | arm7tdmi::V,
                  (res == 0 ? arm7tdmi::Z : 0) | (((res & 0x8000000) != 0) ? arm7tdmi::N : 0));
}
