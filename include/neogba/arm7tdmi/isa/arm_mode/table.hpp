#pragma once
#include "neogba/arm7tdmi/isa/arm_mode/fsr.hpp"

namespace neogba {

inline constexpr auto arm_mode_lut = []() consteval {
  using namespace arm_fsr;

  lut<void (*)(arm7tdmi&, u32), 1 << 6,
      [](std::size_t idx) -> std::size_t {
        auto opcode{OPCODE::get(idx)};
        auto s{S::get(idx)};
        auto rd_pc{RD::get(idx) == 0xf};

        return (opcode << 2) | s << 1 | rd_pc;
      }>
      table;
  constexpr auto code_lambda = [](opcode_enum opcode, bool s = false,
                                  bool rd_pc = false) -> std::size_t {
    return (static_cast<std::size_t>(opcode) << 2) | (static_cast<std::size_t>(s) << 1) |
           static_cast<std::size_t>(rd_pc);
  };

  table.put_raw(code_lambda(opcode_enum::AND), arm_fsr_AND_notS_notRdPC);
  table.put_raw(code_lambda(opcode_enum::EOR), arm_fsr_EOR_notS_notRdPC);
  table.put_raw(code_lambda(opcode_enum::SUB), arm_fsr_SUB_notS_notRdPC);
  table.put_raw(code_lambda(opcode_enum::RSB), arm_fsr_RSB_notS_notRdPC);
  table.put_raw(code_lambda(opcode_enum::ADD), arm_fsr_ADD_notS_notRdPC);
  table.put_raw(code_lambda(opcode_enum::ADC), arm_fsr_ADC_notS_notRdPC);
  table.put_raw(code_lambda(opcode_enum::SBC), arm_fsr_SBC_notS_notRdPC);
  table.put_raw(code_lambda(opcode_enum::RSC), arm_fsr_RSC_notS_notRdPC);
  table.put_raw(code_lambda(opcode_enum::ORR), arm_fsr_ORR_notS_notRdPC);
  table.put_raw(code_lambda(opcode_enum::MOV), arm_fsr_MOV_notS_notRdPC);
  table.put_raw(code_lambda(opcode_enum::BIC), arm_fsr_BIC_notS_notRdPC);
  table.put_raw(code_lambda(opcode_enum::MVN), arm_fsr_MVN_notS_notRdPC);
  table.put_raw(code_lambda(opcode_enum::AND, true), arm_fsr_AND_S_notRdPC);
  table.put_raw(code_lambda(opcode_enum::EOR, true), arm_fsr_EOR_S_notRdPC);
  table.put_raw(code_lambda(opcode_enum::SUB, true), arm_fsr_SUB_S_notRdPC);
  table.put_raw(code_lambda(opcode_enum::RSB, true), arm_fsr_RSB_S_notRdPC);
  table.put_raw(code_lambda(opcode_enum::ADD, true), arm_fsr_ADD_S_notRdPC);
  table.put_raw(code_lambda(opcode_enum::ADC, true), arm_fsr_ADC_S_notRdPC);
  table.put_raw(code_lambda(opcode_enum::SBC, true), arm_fsr_SBC_S_notRdPC);
  table.put_raw(code_lambda(opcode_enum::RSC, true), arm_fsr_RSC_S_notRdPC);
  table.put_raw(code_lambda(opcode_enum::ORR, true), arm_fsr_ORR_S_notRdPC);
  table.put_raw(code_lambda(opcode_enum::MOV, true), arm_fsr_MOV_S_notRdPC);
  table.put_raw(code_lambda(opcode_enum::BIC, true), arm_fsr_BIC_S_notRdPC);
  table.put_raw(code_lambda(opcode_enum::MVN, true), arm_fsr_MVN_S_notRdPC);
  table.put_raw(code_lambda(opcode_enum::AND, true, true), arm_fsr_AND_S_RdPC);
  table.put_raw(code_lambda(opcode_enum::EOR, true, true), arm_fsr_EOR_S_RdPC);
  table.put_raw(code_lambda(opcode_enum::SUB, true, true), arm_fsr_SUB_S_RdPC);
  table.put_raw(code_lambda(opcode_enum::RSB, true, true), arm_fsr_RSB_S_RdPC);
  table.put_raw(code_lambda(opcode_enum::ADD, true, true), arm_fsr_ADD_S_RdPC);
  table.put_raw(code_lambda(opcode_enum::ADC, true, true), arm_fsr_ADC_S_RdPC);
  table.put_raw(code_lambda(opcode_enum::SBC, true, true), arm_fsr_SBC_S_RdPC);
  table.put_raw(code_lambda(opcode_enum::RSC, true, true), arm_fsr_RSC_S_RdPC);
  table.put_raw(code_lambda(opcode_enum::ORR, true, true), arm_fsr_ORR_S_RdPC);
  table.put_raw(code_lambda(opcode_enum::MOV, true, true), arm_fsr_MOV_S_RdPC);
  table.put_raw(code_lambda(opcode_enum::BIC, true, true), arm_fsr_BIC_S_RdPC);
  table.put_raw(code_lambda(opcode_enum::MVN, true, true), arm_fsr_MVN_S_RdPC);
  table.put_raw(code_lambda(opcode_enum::AND, false, true), arm_fsr_AND_notS_RdPC);
  table.put_raw(code_lambda(opcode_enum::EOR, false, true), arm_fsr_EOR_notS_RdPC);
  table.put_raw(code_lambda(opcode_enum::SUB, false, true), arm_fsr_SUB_notS_RdPC);
  table.put_raw(code_lambda(opcode_enum::RSB, false, true), arm_fsr_RSB_notS_RdPC);
  table.put_raw(code_lambda(opcode_enum::ADD, false, true), arm_fsr_ADD_notS_RdPC);
  table.put_raw(code_lambda(opcode_enum::ADC, false, true), arm_fsr_ADC_notS_RdPC);
  table.put_raw(code_lambda(opcode_enum::SBC, false, true), arm_fsr_SBC_notS_RdPC);
  table.put_raw(code_lambda(opcode_enum::RSC, false, true), arm_fsr_RSC_notS_RdPC);
  table.put_raw(code_lambda(opcode_enum::ORR, false, true), arm_fsr_ORR_notS_RdPC);
  table.put_raw(code_lambda(opcode_enum::MOV, false, true), arm_fsr_MOV_notS_RdPC);
  table.put_raw(code_lambda(opcode_enum::BIC, false, true), arm_fsr_BIC_notS_RdPC);
  table.put_raw(code_lambda(opcode_enum::MVN, false, true), arm_fsr_MVN_notS_RdPC);
  table.put_raw(code_lambda(opcode_enum::TST, true), arm_fsr_TST_notRdPC);
  table.put_raw(code_lambda(opcode_enum::TEQ, true), arm_fsr_TEQ_notRdPC);
  table.put_raw(code_lambda(opcode_enum::CMP, true), arm_fsr_CMP_notRdPC);
  table.put_raw(code_lambda(opcode_enum::CMN, true), arm_fsr_CMN_notRdPC);
  table.put_raw(code_lambda(opcode_enum::TST, true, true), arm_fsr_TST_RdPC);
  table.put_raw(code_lambda(opcode_enum::TEQ, true, true), arm_fsr_TEQ_RdPC);
  table.put_raw(code_lambda(opcode_enum::CMP, true, true), arm_fsr_CMP_RdPC);
  table.put_raw(code_lambda(opcode_enum::CMN, true, true), arm_fsr_CMN_RdPC);

  return table;
}();
} // namespace neogba
