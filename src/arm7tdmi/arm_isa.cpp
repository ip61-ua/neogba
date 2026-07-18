#include "neogba/arm7tdmi/arm_isa.hpp"
#include "neogba/arm7tdmi/cpu.hpp"

using namespace neogba;

void neogba::arm_AND(arm7tdmi& cpu, u32 inst) {
  u8 rn_idx{ISA_ARM_FSR_RN::get(inst)};
  u8 rd_idx{ISA_ARM_FSR_RD::get(inst)};
  auto operand2{arm_operand2_lut.run(inst, cpu, inst)};
  [[maybe_unused]] bool s{ISA_ARM_FSR_S::get(inst)};

  auto res{cpu.read_active_register(rn_idx) & operand2.operable_operand2};

  cpu.write_active_register(rd_idx, res);

  if (s) {
    auto z{res == 0 ? arm7tdmi::Z : 0};
    auto n{(res & 0x80000000) != 0 ? arm7tdmi::N : 0};
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
