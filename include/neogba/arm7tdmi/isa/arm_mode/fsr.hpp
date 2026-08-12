#pragma once
#include "neogba/arm7tdmi/isa/arm_mode/operand2.hpp"
#include <utility>

namespace neogba::arm_fsr {
/**
 * @brief Executes a compile-time specialized ARM data-processing instruction.
 *
 * This template generates the implementation of an ARM Flexible Second Operand (FSR)
 * data-processing instruction. The selected opcode and execution behaviour could be entirely
 * resolved at compile time using template parameters, allowing the compiler to remove unused
 * branches and optimize the generated code for each instruction variant.
 *
 * Depending on the template arguments, the generated implementation may update the CPSR flags,
 * write the result to the program counter, or implement flag-only instructions such as CMP or
 * TST.
 *
 * @tparam opcode Data-processing opcode to execute.
 * @tparam s Whether the instruction updates the CPSR condition flags.
 * @tparam rd_pc Whether the destination register is R15 (PC).
 *
 * @param cpu ARM7TDMI CPU state to execute the instruction on.
 * @param inst Raw 32-bit ARM instruction.
 *
 * @note All instruction-specific decisions are resolved at compile time using `if constexpr`, so
 * the generated machine code contains only the logic required for the selected instruction
 * variant with least branches at execution-time.
 *
 * @warning Setting `rd_pc` when `opcode` is one of (`TST`, `TEQ`, `CMP`, `CMN`) is not a
 * documented behaviour in ARM. Because these opcodes only write side effects (by updating CPSR)
 * and ignore destination `rd` field. According, it is illegal to write that on assembly (`rd`
 * contains trash).
 *
 * @warning If the instruction `opcode` is one of (`TST`, `TEQ`, `CMP`, `CMN`), then the flag S is
 * implicitly set. If else, it means it's another instruction type. This fucntion is not
 * responsible for handling that!
 *
 * @todo Testing this function.
 * @todo Ensure correct handling when r15 is involved as source or as destination.
 *
 * @see arm_operand2_generator
 * @see arm_operand2_lut
 * @see arm_fsr_opcode
 * @see arm7tdmi
 */
template <opcode_enum opcode, bool s = false, bool rd_pc = false>
void fsr(arm7tdmi& cpu, u32 inst) {
  // Meta template variables
  constexpr auto is_logical{opcode == opcode_enum::AND or opcode == opcode_enum::EOR or
                            opcode == opcode_enum::TST or opcode == opcode_enum::TEQ or
                            opcode == opcode_enum::ORR or opcode == opcode_enum::MOV or
                            opcode == opcode_enum::BIC or opcode == opcode_enum::MVN};
  constexpr auto can_write_rd{!(opcode == opcode_enum::TST or opcode == opcode_enum::TEQ or
                                opcode == opcode_enum::CMP or opcode == opcode_enum::CMN)};
  constexpr auto is_inverted_sub{opcode == opcode_enum::RSB or opcode == opcode_enum::RSC};
  constexpr auto is_not_move{opcode != opcode_enum::MOV and opcode != opcode_enum::MVN};
  constexpr auto is_sum{opcode == opcode_enum::ADD or opcode == opcode_enum::ADC or
                        opcode == opcode_enum::CMN};

  // Retrieve values
  u8 rd_idx;
  u32 op1;
  u64 res;
  auto rn_idx{RN::get(inst)};

  if constexpr (rd_pc)
    rd_idx = 0xfu;
  else
    rd_idx = RD::get(inst);

  if constexpr (is_not_move)
    op1 = cpu.read_active_register(rn_idx);

  auto op2{arm_operand2::operand2_table.invoke(inst, cpu, inst)};

  if constexpr (is_inverted_sub)
    std::swap(op1, op2.result);

  // Perform operation
  if constexpr (opcode == opcode_enum::AND or opcode == opcode_enum::TST)
    res = op1 & op2.result;
  else if constexpr (opcode == opcode_enum::EOR or opcode == opcode_enum::TEQ)
    res = op1 ^ op2.result;
  else if constexpr (opcode == opcode_enum::SUB or opcode == opcode_enum::CMP or
                     opcode == opcode_enum::RSB)
    res = static_cast<u64>(op1) - op2.result;
  else if constexpr (opcode == opcode_enum::ADD or opcode == opcode_enum::CMN)
    res = static_cast<u64>(op1) + op2.result;
  else if constexpr (opcode == opcode_enum::ADC)
    res = static_cast<u64>(op1) + op2.result + op2.carry_in;
  else if constexpr (opcode == opcode_enum::SBC or opcode == opcode_enum::RSC)
    res = static_cast<u64>(op1) - op2.result + op2.carry_in - 1;
  else if constexpr (opcode == opcode_enum::ORR)
    res = op1 | op2.result;
  else if constexpr (opcode == opcode_enum::MOV)
    res = op2.result;
  else if constexpr (opcode == opcode_enum::BIC)
    res = op1 & ~op2.result;
  else if constexpr (opcode == opcode_enum::MVN)
    res = ~op2.result;

  // write back the result
  auto res32{static_cast<u32>(res)};
  if constexpr (can_write_rd)
    cpu.write_active_register(rd_idx, res32);

  // Side effects
  if constexpr (s) {
    if constexpr (rd_pc and can_write_rd) {
      cpu.write_cpsr(cpu.read_spsr());

    } else {

      // common
      auto z{static_cast<u32>(res32 == 0) << arm7tdmi::Z_SHIFT}; // (res32 == 0) -> true -> 0x0...01
      u32 n{res32 & 0x80000000}; // N ya está en el bit 31 -> 0 movimientos

      if constexpr (is_logical) {
        auto c{static_cast<u32>(op2.carry_out << arm7tdmi::C_SHIFT)}; // op2.carry_out es 0 o 1.

        // meter V aquí = !necesario -> no está afectado.
        // set_cpsr(mask, values) sobrescribe solo estos `mask`
        cpu.set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C, z | n | c);
      } else {
        auto c{static_cast<u32>(res >> 32)}; // (res >> 32) & 1 es 1 o 0.
        auto v{~(op1 ^ op2.result)};

        if constexpr (not is_sum) {
          c = !c;
          v = ~v;
        }

        c = (c & 1) << arm7tdmi::C_SHIFT; // Mover lo necesario!
        v = (v & (op1 ^ res32) & 0x80000000) >>
            (31 - arm7tdmi::V_SHIFT); // Mover lo justo al bit V.

        cpu.set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C | arm7tdmi::V, z | n | c | v);
      }
    }
  }
}

inline constexpr auto

    arm_fsr_AND_notS_notRdPC{fsr<opcode_enum::AND>},
    arm_fsr_EOR_notS_notRdPC{fsr<opcode_enum::EOR>},
    arm_fsr_SUB_notS_notRdPC{fsr<opcode_enum::SUB>},
    arm_fsr_RSB_notS_notRdPC{fsr<opcode_enum::RSB>},
    arm_fsr_ADD_notS_notRdPC{fsr<opcode_enum::ADD>},
    arm_fsr_ADC_notS_notRdPC{fsr<opcode_enum::ADC>},
    arm_fsr_SBC_notS_notRdPC{fsr<opcode_enum::SBC>},
    arm_fsr_RSC_notS_notRdPC{fsr<opcode_enum::RSC>},
    arm_fsr_ORR_notS_notRdPC{fsr<opcode_enum::ORR>},
    arm_fsr_MOV_notS_notRdPC{fsr<opcode_enum::MOV>},
    arm_fsr_BIC_notS_notRdPC{fsr<opcode_enum::BIC>},
    arm_fsr_MVN_notS_notRdPC{fsr<opcode_enum::MVN>},
    arm_fsr_AND_S_notRdPC{fsr<opcode_enum::AND, true>},
    arm_fsr_EOR_S_notRdPC{fsr<opcode_enum::EOR, true>},
    arm_fsr_SUB_S_notRdPC{fsr<opcode_enum::SUB, true>},
    arm_fsr_RSB_S_notRdPC{fsr<opcode_enum::RSB, true>},
    arm_fsr_ADD_S_notRdPC{fsr<opcode_enum::ADD, true>},
    arm_fsr_ADC_S_notRdPC{fsr<opcode_enum::ADC, true>},
    arm_fsr_SBC_S_notRdPC{fsr<opcode_enum::SBC, true>},
    arm_fsr_RSC_S_notRdPC{fsr<opcode_enum::RSC, true>},
    arm_fsr_ORR_S_notRdPC{fsr<opcode_enum::ORR, true>},
    arm_fsr_MOV_S_notRdPC{fsr<opcode_enum::MOV, true>},
    arm_fsr_BIC_S_notRdPC{fsr<opcode_enum::BIC, true>},
    arm_fsr_MVN_S_notRdPC{fsr<opcode_enum::MVN, true>},
    arm_fsr_AND_S_RdPC{fsr<opcode_enum::AND, true, true>},
    arm_fsr_EOR_S_RdPC{fsr<opcode_enum::EOR, true, true>},
    arm_fsr_SUB_S_RdPC{fsr<opcode_enum::SUB, true, true>},
    arm_fsr_RSB_S_RdPC{fsr<opcode_enum::RSB, true, true>},
    arm_fsr_ADD_S_RdPC{fsr<opcode_enum::ADD, true, true>},
    arm_fsr_ADC_S_RdPC{fsr<opcode_enum::ADC, true, true>},
    arm_fsr_SBC_S_RdPC{fsr<opcode_enum::SBC, true, true>},
    arm_fsr_RSC_S_RdPC{fsr<opcode_enum::RSC, true, true>},
    arm_fsr_ORR_S_RdPC{fsr<opcode_enum::ORR, true, true>},
    arm_fsr_MOV_S_RdPC{fsr<opcode_enum::MOV, true, true>},
    arm_fsr_BIC_S_RdPC{fsr<opcode_enum::BIC, true, true>},
    arm_fsr_MVN_S_RdPC{fsr<opcode_enum::MVN, true, true>},
    arm_fsr_AND_notS_RdPC{fsr<opcode_enum::AND, false, true>},
    arm_fsr_EOR_notS_RdPC{fsr<opcode_enum::EOR, false, true>},
    arm_fsr_SUB_notS_RdPC{fsr<opcode_enum::SUB, false, true>},
    arm_fsr_RSB_notS_RdPC{fsr<opcode_enum::RSB, false, true>},
    arm_fsr_ADD_notS_RdPC{fsr<opcode_enum::ADD, false, true>},
    arm_fsr_ADC_notS_RdPC{fsr<opcode_enum::ADC, false, true>},
    arm_fsr_SBC_notS_RdPC{fsr<opcode_enum::SBC, false, true>},
    arm_fsr_RSC_notS_RdPC{fsr<opcode_enum::RSC, false, true>},
    arm_fsr_ORR_notS_RdPC{fsr<opcode_enum::ORR, false, true>},
    arm_fsr_MOV_notS_RdPC{fsr<opcode_enum::MOV, false, true>},
    arm_fsr_BIC_notS_RdPC{fsr<opcode_enum::BIC, false, true>},
    arm_fsr_MVN_notS_RdPC{fsr<opcode_enum::MVN, false, true>},
    arm_fsr_TST_notRdPC{fsr<opcode_enum::TST, true>},
    arm_fsr_TEQ_notRdPC{fsr<opcode_enum::TEQ, true>},
    arm_fsr_CMP_notRdPC{fsr<opcode_enum::CMP, true>},
    arm_fsr_CMN_notRdPC{fsr<opcode_enum::CMN, true>},
    arm_fsr_TST_RdPC{fsr<opcode_enum::TST, true, true>},
    arm_fsr_TEQ_RdPC{fsr<opcode_enum::TEQ, true, true>},
    arm_fsr_CMP_RdPC{fsr<opcode_enum::CMP, true, true>},
    arm_fsr_CMN_RdPC{fsr<opcode_enum::CMN, true, true>};
} // namespace neogba::arm_fsr
