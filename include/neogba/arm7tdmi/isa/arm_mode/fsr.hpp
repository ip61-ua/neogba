#pragma once
#include "neogba/arm7tdmi/isa/arm_mode/operand2.hpp"
#include <utility>

namespace neogba::arm_fsr {

struct fsr_tflags {
  opcode_enum opcode : 4 {0};
  bool s : 1 {false};

  inline constexpr auto is_valid() const {
    const bool is_test{opcode == opcode_enum::TST || opcode == opcode_enum::TEQ ||
                       opcode == opcode_enum::CMP || opcode == opcode_enum::CMN};

    if (is_test && !s)
      return false;

    return true;
  }
};

template <fsr_tflags flags> void fsr(arm7tdmi& cpu, u32 inst) {
  static_assert(flags.is_valid(), "Invalid Template Flags");

  // Meta template variables
  constexpr auto is_logical{flags.opcode == opcode_enum::AND or flags.opcode == opcode_enum::EOR or
                            flags.opcode == opcode_enum::TST or flags.opcode == opcode_enum::TEQ or
                            flags.opcode == opcode_enum::ORR or flags.opcode == opcode_enum::MOV or
                            flags.opcode == opcode_enum::BIC or flags.opcode == opcode_enum::MVN};
  constexpr auto can_write_rd{
      !(flags.opcode == opcode_enum::TST or flags.opcode == opcode_enum::TEQ or
        flags.opcode == opcode_enum::CMP or flags.opcode == opcode_enum::CMN)};
  constexpr auto is_inverted_sub{flags.opcode == opcode_enum::RSB or
                                 flags.opcode == opcode_enum::RSC};
  constexpr auto is_not_move{flags.opcode != opcode_enum::MOV and flags.opcode != opcode_enum::MVN};
  constexpr auto is_sum{flags.opcode == opcode_enum::ADD or flags.opcode == opcode_enum::ADC or
                        flags.opcode == opcode_enum::CMN};

  // Retrieve values
  u8 rd_idx{RD::get(inst)}, rn_idx{RN::get(inst)};
  u32 op1;
  u64 res;

  if constexpr (is_not_move)
    op1 = cpu.read_active_register(rn_idx);

  auto op2{arm_operand2::operand2_table.invoke(inst, cpu, inst)};

  if constexpr (is_inverted_sub)
    std::swap(op1, op2.result);

  // Perform operation
  if constexpr (flags.opcode == opcode_enum::AND or flags.opcode == opcode_enum::TST)
    res = op1 & op2.result;
  else if constexpr (flags.opcode == opcode_enum::EOR or flags.opcode == opcode_enum::TEQ)
    res = op1 ^ op2.result;
  else if constexpr (flags.opcode == opcode_enum::SUB or flags.opcode == opcode_enum::CMP or
                     flags.opcode == opcode_enum::RSB)
    res = static_cast<u64>(op1) - op2.result;
  else if constexpr (flags.opcode == opcode_enum::ADD or flags.opcode == opcode_enum::CMN)
    res = static_cast<u64>(op1) + op2.result;
  else if constexpr (flags.opcode == opcode_enum::ADC)
    res = static_cast<u64>(op1) + op2.result + op2.carry_in;
  else if constexpr (flags.opcode == opcode_enum::SBC or flags.opcode == opcode_enum::RSC)
    res = static_cast<u64>(op1) - op2.result + op2.carry_in - 1;
  else if constexpr (flags.opcode == opcode_enum::ORR)
    res = op1 | op2.result;
  else if constexpr (flags.opcode == opcode_enum::MOV)
    res = op2.result;
  else if constexpr (flags.opcode == opcode_enum::BIC)
    res = op1 & ~op2.result;
  else if constexpr (flags.opcode == opcode_enum::MVN)
    res = ~op2.result;

  // write back the result
  auto res32{static_cast<u32>(res)};
  if constexpr (can_write_rd)
    cpu.write_active_register(rd_idx, res32);

  // Side effects
  if constexpr (flags.s) {
    if (rd_idx == pc and can_write_rd) { // TODO: Revisar PC cuando esté ya aproximándose
      cpu.write_cpsr(cpu.read_spsr());
    } else {
      // common
      auto z{arm7tdmi::Z::h(res32 == 0)};
      u32 n{res32 & 0x80000000}; // N ya está en el bit 31 -> 0 movimientos

      if constexpr (is_logical) {
        auto c{arm7tdmi::C::h(op2.carry_out)}; // op2.carry_out es 0 o 1.

        // meter V aquí = !necesario -> no está afectado.
        // set_cpsr(mask, values) sobrescribe solo estos `mask`
        cpu.set_cpsr(arm7tdmi::Z::mask | arm7tdmi::N::mask | arm7tdmi::C::mask, z | n | c);
      } else {
        auto c{static_cast<u32>(res >> 32)}; // (res >> 32) & 1 es 1 o 0.
        auto v{~(op1 ^ op2.result)};

        if constexpr (not is_sum) {
          c = !c;
          v = ~v;
        }

        c = arm7tdmi::C::h(c); // Mover lo necesario!
        v = (v & (op1 ^ res32) & 0x80000000) >>
            (31 - arm7tdmi::V::shift); // Mover lo justo al bit V.

        cpu.set_cpsr(arm7tdmi::Z::mask | arm7tdmi::N::mask | arm7tdmi::C::mask | arm7tdmi::V::mask,
                     z | n | c | v);
      }
    }
  }
};

} // namespace neogba::arm_fsr
