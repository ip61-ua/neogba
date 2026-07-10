#include "neogba/arm7tdmi/arm_isa.hpp"

using namespace neogba;

arm_operand2_result arm_operand2_compute_i1_rotate0(arm7tdmi*, u32 inst) {
  // operand2 is immediate value with shift.
  return {0, ISA_ARM_FSR_OPERAND2_IMM::get(inst)};
}

arm_operand2_result arm_operand2_compute_i1_rotatenot0(arm7tdmi*, u32 inst) {
  // operand2 is immediate value with shift.
  u32 rotate = 2 * ISA_ARM_FSR_OPERAND2_ROTATE::get(inst), imm{ISA_ARM_FSR_OPERAND2_IMM::get(inst)};
  return {rotate, ((imm >> rotate) | (imm << (32 - rotate)))};
}

arm_operand2_result arm_operand2_compute_i0_40_shifta0_LSL(arm7tdmi* cpu, u32 inst) {
  return {0, cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))};
}
arm_operand2_result arm_operand2_compute_i0_40_shifta0_LSR(arm7tdmi*, u32) { return {0, 0}; }
arm_operand2_result arm_operand2_compute_i0_40_shifta0_ASR(arm7tdmi* cpu, u32 inst) {
  return {0, static_cast<u32>(
                 static_cast<i32>(cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
                 31)};
}
arm_operand2_result arm_operand2_compute_i0_40_shifta0_ROR(arm7tdmi* cpu, u32 inst) {
  return {0, ((cpu->read_cpsr() & arm7tdmi::C) << (31 - 29)) |
                 (cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst)) >> 1)};
}

arm_operand2_result arm_operand2_compute_i0_40_shiftanot0_LSL(arm7tdmi* cpu, u32 inst) {
  u32 shift_amount{ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst)},
      rm{static_cast<u32>(
          static_cast<i32>(cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
          shift_amount)};

  return {shift_amount, rm << shift_amount};
}
arm_operand2_result arm_operand2_compute_i0_40_shiftanot0_LSR(arm7tdmi* cpu, u32 inst) {
  u32 shift_amount{ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst)},
      rm{static_cast<u32>(
          static_cast<i32>(cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
          shift_amount)};

  return {shift_amount, rm >> shift_amount};
}
arm_operand2_result arm_operand2_compute_i0_40_shiftanot0_ASR(arm7tdmi* cpu, u32 inst) {
  u32 shift_amount{ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst)},
      rm{static_cast<u32>(
          static_cast<i32>(cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
          shift_amount)};

  return {shift_amount, static_cast<u32>(static_cast<i32>(rm) >> shift_amount)};
}
arm_operand2_result arm_operand2_compute_i0_40_shiftanot0_ROR(arm7tdmi* cpu, u32 inst) {
  u32 shift_amount{ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst)},
      rm{static_cast<u32>(
          static_cast<i32>(cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
          shift_amount)};

  return {shift_amount, ((rm >> shift_amount) | (rm << (32 - shift_amount)))};
}

arm_operand2_result arm_operand2_compute_i0_41_LSL(arm7tdmi* cpu, u32 inst) {
  u32 shift_amount{(cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst)) & 0xff)},
      rm{static_cast<u32>(
          static_cast<i32>(cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
          shift_amount)};

  return {shift_amount, (shift_amount >= 32) ? 0 : (rm << shift_amount)};
}
arm_operand2_result arm_operand2_compute_i0_41_LSR(arm7tdmi* cpu, u32 inst) {
  u32 shift_amount{(cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst)) & 0xff)},
      rm{static_cast<u32>(
          static_cast<i32>(cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
          shift_amount)};

  return {shift_amount, (shift_amount >= 32) ? 0 : (rm >> shift_amount)};
}
arm_operand2_result arm_operand2_compute_i0_41_ASR(arm7tdmi* cpu, u32 inst) {
  u32 shift_amount{(cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst)) & 0xff)},
      rm{static_cast<u32>(
          static_cast<i32>(cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
          shift_amount)};

  return {shift_amount, static_cast<u32>(static_cast<i32>(rm) >> std::min<u32>(31, shift_amount))};
}
arm_operand2_result arm_operand2_compute_i0_41_ROR(arm7tdmi* cpu, u32 inst) {
  u32 shift_amount{(cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst)) & 0xff)},
      rm{static_cast<u32>(
          static_cast<i32>(cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
          shift_amount)};
  auto masked_shift{shift_amount & 0x1f};

  return {shift_amount,
          (masked_shift == 0) ? rm : ((rm >> masked_shift) | (rm << (32 - masked_shift)))};
}

arm_operand2_result arm_operand2_compute(arm7tdmi* cpu, u32 inst) {
  u32 shift_amount, operable_operand2{};
  u8 i{ISA_ARM_FSR_I::get_raw(inst)};

  if (i) {
    // operand2 is immediate value with shift.

    auto rotate = shift_amount = 2 * ISA_ARM_FSR_OPERAND2_ROTATE::get(inst);
    u32 imm{ISA_ARM_FSR_OPERAND2_IMM::get(inst)};

    operable_operand2 = (rotate == 0) ? imm : ((imm >> rotate) | (imm << (32 - rotate)));
  } else {
    // operand2 is a register with shift.

    u8 rm_idx{ISA_ARM_FSR_OPERAND2_RM::get(inst)};
    u32 rm{cpu->read_active_register(rm_idx)};
    u8 shift_type{ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(inst)};
    bool four{ISA_ARM_FSR_OPERAND2_4::get(inst)};

    shift_amount = four ? (cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst)) & 0xff)
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

      operable_operand2 = static_cast<u32>(static_cast<i32>(rm) >> std::min<u32>(31, shift_amount));
      break;

    case ROR:
      if (is_special_case) {
        // RRX: Rotate 1 bit and include Cin.
        operable_operand2 = ((cpu->read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1);
      } else {
        auto masked_shift = shift_amount & 0x1f;
        operable_operand2 =
            (masked_shift == 0) ? rm : ((rm >> masked_shift) | (rm << (32 - masked_shift)));
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
