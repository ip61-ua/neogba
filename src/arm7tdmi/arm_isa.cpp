#include "neogba/arm7tdmi/arm_isa.hpp"
#include "neogba/arm7tdmi/cpu.hpp"

using namespace neogba;

void neogba::arm_AND(arm7tdmi& cpu, u32 inst);
void neogba::arm_EOR(arm7tdmi& cpu, u32 inst);
void neogba::arm_SUB(arm7tdmi& cpu, u32 inst);
void neogba::arm_RSB(arm7tdmi& cpu, u32 inst);
void neogba::arm_ADD(arm7tdmi& cpu, u32 inst);
void neogba::arm_ADC(arm7tdmi& cpu, u32 inst);
void neogba::arm_SBC(arm7tdmi& cpu, u32 inst);
void neogba::arm_RSC(arm7tdmi& cpu, u32 inst);
void neogba::arm_TST(arm7tdmi& cpu, u32 inst); // siempre tienen el bit s activo
void neogba::arm_TEQ(arm7tdmi& cpu, u32 inst); // siempre tienen el bit s activo
void neogba::arm_CMP(arm7tdmi& cpu, u32 inst); // siempre tienen el bit s activo
void neogba::arm_CMN(arm7tdmi& cpu, u32 inst); // siempre tienen el bit s activo
void neogba::arm_ORR(arm7tdmi& cpu, u32 inst);
void neogba::arm_MOV(arm7tdmi& cpu, u32 inst);
void neogba::arm_BIC(arm7tdmi& cpu, u32 inst);
void neogba::arm_MVN(arm7tdmi& cpu, u32 inst);
