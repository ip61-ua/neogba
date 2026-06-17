#pragma once

// Generic

#define ARM_COND_SHIFT /*  */ 28
#define ARM_COND_MASK /*   */ 0xf0000000u

#define ARM_GET_COND(inst) (((inst)) & ARM_COND_MASK) // optimización: no shift

// Data processing and FSR transfer

#define ARM_FSR_OPCODE_SHIFT /*   */ 21
#define ARM_FSR_OPCODE_MASK /*    */ (0xfu << ARM_FSR_OPCODE_SHIFT)

#define ARM_FSR_S_SHIFT /*        */ 20
#define ARM_FSR_S_MASK /*         */ (1u << ARM_FSR_S_SHIFT)

#define ARM_FSR_RN_SHIFT /*       */ 16
#define ARM_FSR_RN_MASK /*        */ (0xfu << ARM_FSR_RN_SHIFT)

#define ARM_FSR_RD_SHIFT /*       */ 12
#define ARM_FSR_RD_MASK /*        */ (0xfu << ARM_FSR_RD_SHIFT)

#define ARM_FSR_OPERAND2_SHIFT /* */ 0
#define ARM_FSR_OPERAND2_MASK /*  */ ((1u << 12) - 1)

#define ARM_FSR_GET_OPCODE(inst) (((inst)) & ARM_FSR_OPCODE_MASK)

#define ARM_FSR_IS_S(inst) ((((inst)) & ARM_FSR_S_MASK) != 0)

#define ARM_FSR_GET_RN(inst) ((((inst)) & ARM_FSR_RN_MASK) >> ARM_FSR_RN_SHIFT)
#define ARM_FSR_GET_RD(inst) ((((inst)) & ARM_FSR_RD_MASK) >> ARM_FSR_RD_SHIFT)
#define ARM_FSR_GET_OPERAND2(inst) (((inst)) & ARM_FSR_OPERAND2_MASK)

// Multiply

#define ARM_MULTIPLY_A_SHIFT /*    */ 21
#define ARM_MULTIPLY_A_MASK /*     */ (1u << ARM_MULTIPLY_A_SHIFT)

#define ARM_MULTIPLY_S_SHIFT /*    */ ARM_FSR_S_SHIFT
#define ARM_MULTIPLY_S_MASK /*     */ ARM_FSR_S_MASK

#define ARM_MULTIPLY_RD_SHIFT /*   */ ARM_FSR_RN_SHIFT
#define ARM_MULTIPLY_RD_MASK /*    */ ARM_FSR_RN_MASK

#define ARM_MULTIPLY_RN_SHIFT /*   */ ARM_FSR_RD_SHIFT
#define ARM_MULTIPLY_RN_MASK /*    */ ARM_FSR_RD_MASK

#define ARM_MULTIPLY_RS_SHIFT /*   */ 8
#define ARM_MULTIPLY_RS_MASK /*    */ (0xfu << ARM_MULTIPLY_RS_SHIFT)

#define ARM_MULTIPLY_RM_SHIFT /*   */ 0
#define ARM_MULTIPLY_RM_MASK /*    */ (0xfu)

#define ARM_MULTIPLY_IS_A(inst) ((((inst)) & ARM_MULTIPLY_A_MASK) != 0)
#define ARM_MULTIPLY_IS_S(inst) (ARM_FSR_IS_S(inst))

#define ARM_MULTIPLY_GET_RD(inst) (ARM_FSR_GET_RN(inst))
#define ARM_MULTIPLY_GET_RN(inst) (ARM_FSR_GET_RD(inst))
#define ARM_MULTIPLY_GET_RS(inst)                                              \
  ((((inst)) & (ARM_MULTIPLY_RS_MASK)) >> ARM_MULTIPLY_RS_SHIFT)
#define ARM_MULTIPLY_GET_RM(inst) (((inst)) & ARM_MULTIPLY_RM_MASK)
