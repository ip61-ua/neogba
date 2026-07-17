#include "neogba/arm7tdmi/arm_isa.hpp"
#include "neogba/arm7tdmi/cpu.hpp"

using namespace neogba;

// I && rotate == 0
arm_operand2_result neogba::arm_operand2_compute_i1_rotate0(arm7tdmi&, u32 inst) {
  auto imm{ISA_ARM_FSR_OPERAND2_IMM::get(inst)};
  auto carry_out{false};

  return {carry_out, imm};
}

// I && rotate != 0
arm_operand2_result neogba::arm_operand2_compute_i1_rotatenot0(arm7tdmi&, u32 inst) {
  auto imm{ISA_ARM_FSR_OPERAND2_IMM::get(inst)};
  auto rotate{static_cast<u32>(2u * ISA_ARM_FSR_OPERAND2_ROTATE::get(inst))};
  auto result{static_cast<u32>((imm >> rotate) | (imm << (32 - rotate)))};
  auto carry_out{static_cast<bool>(result >> 31)};

  return {carry_out, result};
}

// !I && !4 && shift == 0 && LSL
// edge case
arm_operand2_result neogba::arm_operand2_compute_i0_40_shifta0_LSL(arm7tdmi& cpu, u32 inst) {
  auto rm{cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))};
  auto carry_out{false};

  return {carry_out, rm};
}

// !I && !4 && shift == 0 && LSL
arm_operand2_result neogba::arm_operand2_compute_i0_40_shifta0_LSR(arm7tdmi& cpu, u32 inst) {
  auto rm{cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))};
  auto carry_out{static_cast<bool>(rm >> 31)};

  return {carry_out, 0};
}

arm_operand2_result neogba::arm_operand2_compute_i0_40_shifta0_ASR(arm7tdmi& cpu, u32 inst) {
  return {false, static_cast<u32>(static_cast<i32>(cpu.read_active_register(
                                      ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
                                  31)};
}
arm_operand2_result neogba::arm_operand2_compute_i0_40_shifta0_ROR(arm7tdmi& cpu, u32 inst) {
  return {false, ((cpu.read_cpsr() & arm7tdmi::C) << (31 - 29)) |
                     (cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst)) >> 1)};
}

arm_operand2_result neogba::arm_operand2_compute_i0_40_shiftanot0_LSL(arm7tdmi& cpu, u32 inst) {
  u32 shift_amount{ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst)},
      rm{static_cast<u32>(
          static_cast<i32>(cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
          shift_amount)};

  return {shift_amount, rm << shift_amount};
}
arm_operand2_result neogba::arm_operand2_compute_i0_40_shiftanot0_LSR(arm7tdmi& cpu, u32 inst) {
  u32 shift_amount{ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst)},
      rm{static_cast<u32>(
          static_cast<i32>(cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
          shift_amount)};

  return {((rm >> (shift_amount - 1)) & 1) == 1u, rm >> shift_amount};
}
arm_operand2_result neogba::arm_operand2_compute_i0_40_shiftanot0_ASR(arm7tdmi& cpu, u32 inst) {
  u32 shift_amount{ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst)},
      rm{static_cast<u32>(
          static_cast<i32>(cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
          shift_amount)};

  return {shift_amount, static_cast<u32>(static_cast<i32>(rm) >> shift_amount)};
}
arm_operand2_result neogba::arm_operand2_compute_i0_40_shiftanot0_ROR(arm7tdmi& cpu, u32 inst) {
  u32 shift_amount{ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst)},
      rm{static_cast<u32>(
          static_cast<i32>(cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
          shift_amount)};

  return {shift_amount, ((rm >> shift_amount) | (rm << (32 - shift_amount)))};
}

arm_operand2_result neogba::arm_operand2_compute_i0_41_LSL(arm7tdmi& cpu, u32 inst) {
  u32 shift_amount{(cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst)) & 0xff)},
      rm{static_cast<u32>(
          static_cast<i32>(cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
          shift_amount)};

  return {shift_amount, (shift_amount >= 32) ? 0 : (rm << shift_amount)};
}
arm_operand2_result neogba::arm_operand2_compute_i0_41_LSR(arm7tdmi& cpu, u32 inst) {
  u32 shift_amount{(cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst)) & 0xff)},
      rm{static_cast<u32>(
          static_cast<i32>(cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
          shift_amount)};

  return {shift_amount, (shift_amount >= 32) ? 0 : (rm >> shift_amount)};
}
arm_operand2_result neogba::arm_operand2_compute_i0_41_ASR(arm7tdmi& cpu, u32 inst) {
  u32 shift_amount{(cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst)) & 0xff)},
      rm{static_cast<u32>(
          static_cast<i32>(cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
          shift_amount)};

  return {shift_amount, static_cast<u32>(static_cast<i32>(rm) >> std::min<u32>(31, shift_amount))};
}
arm_operand2_result neogba::arm_operand2_compute_i0_41_ROR(arm7tdmi& cpu, u32 inst) {
  u32 shift_amount{(cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst)) & 0xff)},
      rm{static_cast<u32>(
          static_cast<i32>(cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RM::get(inst))) >>
          shift_amount)};
  auto masked_shift{shift_amount & 0x1f};

  return {shift_amount,
          (masked_shift == 0) ? rm : ((rm >> masked_shift) | (rm << (32 - masked_shift)))};
}

arm_operand2_result neogba::arm_operand2_compute(arm7tdmi& cpu, u32 inst) {
  u32 shift_amount, operable_operand2{};
  u8 i{ISA_ARM_FSR_I::get_raw(inst)};

  if (i) {
    //       operand2 is immediate value with shift.

    auto rotate = shift_amount = 2 * ISA_ARM_FSR_OPERAND2_ROTATE::get(inst);
    u32 imm{ISA_ARM_FSR_OPERAND2_IMM::get(inst)};

    operable_operand2 = (rotate == 0) ? imm : ((imm >> rotate) | (imm << (32 - rotate)));
  } else {
    //        operand2 is a register with shift.

    u8 rm_idx{ISA_ARM_FSR_OPERAND2_RM::get(inst)};
    u32 rm{cpu.read_active_register(rm_idx)};
    u8 shift_type{ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(inst)};
    bool four{ISA_ARM_FSR_OPERAND2_4::get(inst)};

    shift_amount = four ? (cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst)) & 0xff)
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
        shift_amount = 32; //  ASR #0
      }

      operable_operand2 = static_cast<u32>(static_cast<i32>(rm) >> std::min<u32>(31, shift_amount));
      break;

    case ROR:
      if (is_special_case) {
        //           RRX: Rotate 1 bit and include Cin.
        operable_operand2 = ((cpu.read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1);
      } else {
        auto masked_shift = shift_amount & 0x1f;
        operable_operand2 =
            (masked_shift == 0) ? rm : ((rm >> masked_shift) | (rm << (32 - masked_shift)));
      }
      break;
    }
  }
}

// para las lógicas el bit v no está afectado si (S=1 ^ rd != r15)
// -(s ^ -r15) -> update
// -S v r15 -> update

void neogba::arm_AND(arm7tdmi& cpu, u32 inst) {
  u8 rn_idx{ISA_ARM_FSR_RN::get(inst)};
  u8 rd_idx{ISA_ARM_FSR_RD::get(inst)};
  auto operand2{arm_operand2_lut.run(inst, cpu, inst)};
  [[maybe_unused]] bool s{ISA_ARM_FSR_S::get(inst)};

  auto res{cpu.read_active_register(rn_idx) & operand2.operable_operand2};

  cpu.write_active_register(rd_idx, res);

  if (s) {
    auto z{res == 0 ? arm7tdmi::Z : 0};
    auto n{(res & 0x8000000) != 0 ? arm7tdmi::N : 0};
    auto v{rd_idx == pc ? 0 /* update logic */ : cpu.read_cpsr() & arm7tdmi::V};

    cpu.set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C | arm7tdmi::V, z | n | v);
  }
}

void arm_EOR(arm7tdmi& cpu, u32 inst);
void arm_SUB(arm7tdmi& cpu, u32 inst);
void arm_RSB(arm7tdmi& cpu, u32 inst);
void arm_ADD(arm7tdmi& cpu, u32 inst);
void arm_ADC(arm7tdmi& cpu, u32 inst);
void arm_SBC(arm7tdmi& cpu, u32 inst);
void arm_RSC(arm7tdmi& cpu, u32 inst);
void arm_TST(arm7tdmi& cpu, u32 inst); // siempre tienen el bit s activo
void arm_TEQ(arm7tdmi& cpu, u32 inst); // siempre tienen el bit s activo
void arm_CMP(arm7tdmi& cpu, u32 inst); // siempre tienen el bit s activo
void arm_CMN(arm7tdmi& cpu, u32 inst); // siempre tienen el bit s activo
void arm_ORR(arm7tdmi& cpu, u32 inst);
void arm_MOV(arm7tdmi& cpu, u32 inst);
void arm_BIC(arm7tdmi& cpu, u32 inst);
void arm_MVN(arm7tdmi& cpu, u32 inst);
