#include "neogba/arm7tdmi/isa/arm_mode.hpp"
#include "neogba/arm7tdmi/isa/arm_mode/fsr.hpp"
#include "neogba/arm7tdmi/isa/include.hpp"

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

  table.put_raw(code_lambda(arm_fsr_opcode::AND), arm_AND_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::EOR), arm_EOR_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::SUB), arm_SUB_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::RSB), arm_RSB_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ADD), arm_ADD_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ADC), arm_ADC_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::SBC), arm_SBC_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::RSC), arm_RSC_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ORR), arm_ORR_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::MOV), arm_MOV_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::BIC), arm_BIC_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::MVN), arm_MVN_notS_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::AND, true), arm_AND_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::EOR, true), arm_EOR_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::SUB, true), arm_SUB_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::RSB, true), arm_RSB_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ADD, true), arm_ADD_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ADC, true), arm_ADC_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::SBC, true), arm_SBC_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::RSC, true), arm_RSC_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ORR, true), arm_ORR_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::MOV, true), arm_MOV_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::BIC, true), arm_BIC_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::MVN, true), arm_MVN_S_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::AND, true, true), arm_AND_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::EOR, true, true), arm_EOR_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::SUB, true, true), arm_SUB_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::RSB, true, true), arm_RSB_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ADD, true, true), arm_ADD_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ADC, true, true), arm_ADC_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::SBC, true, true), arm_SBC_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::RSC, true, true), arm_RSC_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ORR, true, true), arm_ORR_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::MOV, true, true), arm_MOV_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::BIC, true, true), arm_BIC_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::MVN, true, true), arm_MVN_S_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::AND, false, true), arm_AND_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::EOR, false, true), arm_EOR_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::SUB, false, true), arm_SUB_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::RSB, false, true), arm_RSB_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ADD, false, true), arm_ADD_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ADC, false, true), arm_ADC_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::SBC, false, true), arm_SBC_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::RSC, false, true), arm_RSC_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::ORR, false, true), arm_ORR_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::MOV, false, true), arm_MOV_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::BIC, false, true), arm_BIC_notS_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::MVN, false, true), arm_MVN_notS_RdPC);

  table.put_raw(code_lambda(arm_fsr_opcode::TST, true), arm_TST_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::TEQ, true), arm_TEQ_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::CMP, true), arm_CMP_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::CMN, true), arm_CMN_notRdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::TST, true, true), arm_TST_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::TEQ, true, true), arm_TEQ_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::CMP, true, true), arm_CMP_RdPC);
  table.put_raw(code_lambda(arm_fsr_opcode::CMN, true, true), arm_CMN_RdPC);

  return table;
}();

void execute_arm(arm7tdmi& cpu, u32 inst) { arm_mode_lut.invoke(inst, cpu, inst); }
} // namespace neogba
