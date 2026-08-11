#pragma once
#include "neogba/arm7tdmi/isa/arm_mode/fsr.hpp"

namespace neogba {

inline constexpr auto arm_mode_lut = []() consteval {
  lut<void (*)(arm7tdmi&, u32), 1 << 6,
      [](std::size_t idx) -> std::size_t {
        // <arm_fsr_opcode opcode, bool s = false, bool rd_pc = false>

        auto opcode{ISA_ARM_FSR_OPCODE::get(idx)};
        auto s{ISA_ARM_FSR_S::get(idx)};
        auto rd_pc{ISA_ARM_FSR_RD::get(idx) == 0xf};

        return (opcode << 2) | s << 1 | rd_pc;
      }>
      table;
  constexpr auto code_lambda = [](arm_fsr_opcode opcode, bool s = false,
                                  bool rd_pc = false) -> std::size_t {
    return (static_cast<std::size_t>(opcode) << 2) | (static_cast<std::size_t>(s) << 1) |
           static_cast<std::size_t>(rd_pc);
  };

  table.put_raw(code_lambda(arm_fsr_opcode::AND), arm_fsr_AND_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::EOR), arm_fsr_EOR_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::SUB), arm_fsr_SUB_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::RSB), arm_fsr_RSB_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ADD), arm_fsr_ADD_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ADC), arm_fsr_ADC_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::SBC), arm_fsr_SBC_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::RSC), arm_fsr_RSC_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ORR), arm_fsr_ORR_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::MOV), arm_fsr_MOV_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::BIC), arm_fsr_BIC_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::MVN), arm_fsr_MVN_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::AND, true), arm_fsr_AND_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::EOR, true), arm_fsr_EOR_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::SUB, true), arm_fsr_SUB_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::RSB, true), arm_fsr_RSB_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ADD, true), arm_fsr_ADD_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ADC, true), arm_fsr_ADC_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::SBC, true), arm_fsr_SBC_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::RSC, true), arm_fsr_RSC_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ORR, true), arm_fsr_ORR_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::MOV, true), arm_fsr_MOV_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::BIC, true), arm_fsr_BIC_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::MVN, true), arm_fsr_MVN_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::AND, true, true), arm_fsr_AND_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::EOR, true, true), arm_fsr_EOR_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::SUB, true, true), arm_fsr_SUB_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::RSB, true, true), arm_fsr_RSB_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ADD, true, true), arm_fsr_ADD_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ADC, true, true), arm_fsr_ADC_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::SBC, true, true), arm_fsr_SBC_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::RSC, true, true), arm_fsr_RSC_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ORR, true, true), arm_fsr_ORR_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::MOV, true, true), arm_fsr_MOV_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::BIC, true, true), arm_fsr_BIC_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::MVN, true, true), arm_fsr_MVN_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::AND, false, true), arm_fsr_AND_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::EOR, false, true), arm_fsr_EOR_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::SUB, false, true), arm_fsr_SUB_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::RSB, false, true), arm_fsr_RSB_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ADD, false, true), arm_fsr_ADD_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ADC, false, true), arm_fsr_ADC_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::SBC, false, true), arm_fsr_SBC_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::RSC, false, true), arm_fsr_RSC_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ORR, false, true), arm_fsr_ORR_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::MOV, false, true), arm_fsr_MOV_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::BIC, false, true), arm_fsr_BIC_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::MVN, false, true), arm_fsr_MVN_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::TST, true), arm_fsr_TST_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::TEQ, true), arm_fsr_TEQ_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::CMP, true), arm_fsr_CMP_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::CMN, true), arm_fsr_CMN_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::TST, true, true), arm_fsr_TST_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::TEQ, true, true), arm_fsr_TEQ_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::CMP, true, true), arm_fsr_CMP_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::CMN, true, true), arm_fsr_CMN_RdPC);

  return table;
}();
} // namespace neogba
