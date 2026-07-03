#pragma once
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa.hpp"

namespace neogba {

inline void arm_AND(arm7tdmi& cpu, u32 inst);
inline void arm_EOR(arm7tdmi& cpu, u32 inst);
inline void arm_SUB(arm7tdmi& cpu, u32 inst);
inline void arm_RSB(arm7tdmi& cpu, u32 inst);
inline void arm_ADD(arm7tdmi& cpu, u32 inst);
inline void arm_ADC(arm7tdmi& cpu, u32 inst);
inline void arm_SBC(arm7tdmi& cpu, u32 inst);
inline void arm_RSC(arm7tdmi& cpu, u32 inst);
inline void arm_TST(arm7tdmi& cpu, u32 inst);
inline void arm_TEQ(arm7tdmi& cpu, u32 inst);
inline void arm_CMP(arm7tdmi& cpu, u32 inst);
inline void arm_CMN(arm7tdmi& cpu, u32 inst);
inline void arm_ORR(arm7tdmi& cpu, u32 inst);
inline void arm_MOV(arm7tdmi& cpu, u32 inst);
inline void arm_BIC(arm7tdmi& cpu, u32 inst);
inline void arm_MVN(arm7tdmi& cpu, u32 inst);

} // namespace neogba
