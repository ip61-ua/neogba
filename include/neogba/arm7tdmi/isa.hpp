#pragma once
#include "neogba/types.hpp"

#define ISA_GETTER_SHIFTED(type, name, prefix)                                 \
  inline type name(type inst) {                                                \
    return (inst & ((prefix##_MASK))) >> (((prefix##_SHIFT)));                 \
  }

#define ISA_GETTER(type, name, prefix)                                         \
  inline type name(type inst) { return inst & (((prefix##_MASK))); }

#define ISA_ISSER(type, name, prefix)                                          \
  inline bool name(type inst) { return (inst & (((prefix##_MASK)))) != 0; }

#define ISA_GETTER_SPLIT_OFFSET(type, name, prefix)                            \
  inline type name(type inst) {                                                \
    return (((inst) & (prefix##_1_MASK)) >> (prefix##_JOIN)) |                 \
           ((inst) & (prefix##_2_MASK));                                       \
  }

///
/// ARM
///

#define ARM_COND_SHIFT /*  */ 28
#define ARM_COND_MASK /*   */ (0xfu << ARM_COND_SHIFT)

// NO DEVUELVE el campo condición rotado, sino que EXCLUSIVAMENTE OPACA los bits
// distractores.
// Returns condition bits in their encoded position [31:28].
ISA_GETTER(u32, arm_get_cond, ARM_COND);

///
/// Data processing and FSR transfer
///

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

ISA_GETTER_SHIFTED(u32, arm_fsr_get_opcode, ARM_FSR_OPCODE);

ISA_ISSER(u32, arm_fsr_is_s, ARM_FSR_S);

ISA_GETTER_SHIFTED(u32, arm_fsr_get_rn, ARM_FSR_RN);
ISA_GETTER_SHIFTED(u32, arm_fsr_get_rd, ARM_FSR_RD);

ISA_GETTER(u32, arm_fsr_get_operand2, ARM_FSR_OPERAND2);

///
/// Multiply
///

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

ISA_ISSER(u32, arm_multiply_is_a, ARM_MULTIPLY_A);
ISA_ISSER(u32, arm_multiply_is_s, ARM_MULTIPLY_S);

ISA_GETTER_SHIFTED(u32, arm_multiply_get_rd, ARM_MULTIPLY_RD);
ISA_GETTER_SHIFTED(u32, arm_multiply_get_rn, ARM_MULTIPLY_RN);
ISA_GETTER_SHIFTED(u32, arm_multiply_get_rs, ARM_MULTIPLY_RS);

ISA_GETTER(u32, arm_multiply_get_rm, ARM_MULTIPLY_RM);

///
/// Multiply long
///

#define ARM_MULTIPLY_LONG_U_SHIFT /*    */ 22
#define ARM_MULTIPLY_LONG_U_MASK /*     */ (1u << ARM_MULTIPLY_LONG_U_SHIFT)
#define ARM_MULTIPLY_LONG_A_SHIFT /*    */ ARM_MULTIPLY_A_SHIFT
#define ARM_MULTIPLY_LONG_A_MASK /*     */ ARM_MULTIPLY_A_MASK
#define ARM_MULTIPLY_LONG_S_SHIFT /*    */ ARM_MULTIPLY_S_SHIFT
#define ARM_MULTIPLY_LONG_S_MASK /*     */ ARM_MULTIPLY_S_MASK
#define ARM_MULTIPLY_LONG_RDHI_SHIFT /* */ ARM_MULTIPLY_RD_SHIFT
#define ARM_MULTIPLY_LONG_RDHI_MASK /*  */ ARM_MULTIPLY_RD_MASK
#define ARM_MULTIPLY_LONG_RDLO_SHIFT /* */ ARM_MULTIPLY_RN_SHIFT
#define ARM_MULTIPLY_LONG_RDLO_MASK /*  */ ARM_MULTIPLY_RN_MASK
#define ARM_MULTIPLY_LONG_RN_SHIFT /*   */ ARM_MULTIPLY_RS_SHIFT
#define ARM_MULTIPLY_LONG_RN_MASK /*    */ ARM_MULTIPLY_RS_MASK
#define ARM_MULTIPLY_LONG_RM_SHIFT /*   */ ARM_MULTIPLY_RM_SHIFT
#define ARM_MULTIPLY_LONG_RM_MASK /*    */ ARM_MULTIPLY_RM_MASK

ISA_ISSER(u32, arm_multiply_long_is_u, ARM_MULTIPLY_LONG_U);
ISA_ISSER(u32, arm_multiply_long_is_a, ARM_MULTIPLY_LONG_A);
ISA_ISSER(u32, arm_multiply_long_is_s, ARM_MULTIPLY_LONG_S);

ISA_GETTER_SHIFTED(u32, arm_multiply_long_get_rdhi, ARM_MULTIPLY_LONG_RDHI);
ISA_GETTER_SHIFTED(u32, arm_multiply_long_get_rdlo, ARM_MULTIPLY_LONG_RDLO);
ISA_GETTER_SHIFTED(u32, arm_multiply_long_get_rn, ARM_MULTIPLY_LONG_RN);

ISA_GETTER(u32, arm_multiply_long_get_rm, ARM_MULTIPLY_LONG_RM);

///
/// Single data swap
///

#define ARM_SINGLE_DATA_SWAP_B_SHIFT /*    */ ARM_MULTIPLY_LONG_U_SHIFT
#define ARM_SINGLE_DATA_SWAP_B_MASK /*     */ ARM_MULTIPLY_LONG_U_MASK
#define ARM_SINGLE_DATA_SWAP_RN_SHIFT /*   */ ARM_FSR_RN_SHIFT
#define ARM_SINGLE_DATA_SWAP_RN_MASK /*    */ ARM_FSR_RN_MASK
#define ARM_SINGLE_DATA_SWAP_RD_SHIFT /*   */ ARM_FSR_RD_SHIFT
#define ARM_SINGLE_DATA_SWAP_RD_MASK /*    */ ARM_FSR_RD_MASK
#define ARM_SINGLE_DATA_SWAP_RM_SHIFT /*   */ ARM_MULTIPLY_RM_SHIFT
#define ARM_SINGLE_DATA_SWAP_RM_MASK /*    */ ARM_MULTIPLY_RM_MASK

ISA_ISSER(u32, arm_single_data_swap_is_b, ARM_SINGLE_DATA_SWAP_B);

ISA_GETTER_SHIFTED(u32, arm_single_data_swap_get_rn, ARM_SINGLE_DATA_SWAP_RN);
ISA_GETTER_SHIFTED(u32, arm_single_data_swap_get_rd, ARM_SINGLE_DATA_SWAP_RD);
ISA_GETTER(u32, arm_single_data_swap_get_rm, ARM_SINGLE_DATA_SWAP_RM);

///
/// Branch and Exchange
///

#define ARM_BRANCH_AND_EXCHANGE_RN_SHIFT /*   */ ARM_MULTIPLY_RM_SHIFT
#define ARM_BRANCH_AND_EXCHANGE_RN_MASK /*    */ ARM_MULTIPLY_RM_MASK

ISA_GETTER(u32, arm_branch_and_exchange_get_rn, ARM_BRANCH_AND_EXCHANGE_RN);

///
/// Halfword data transfer, register offset
///

#define ARM_HALF_DATA_TRANS_REG_P_SHIFT 24
#define ARM_HALF_DATA_TRANS_REG_P_MASK (1u << ARM_HALF_DATA_TRANS_REG_P_SHIFT)
#define ARM_HALF_DATA_TRANS_REG_U_SHIFT 23
#define ARM_HALF_DATA_TRANS_REG_U_MASK (1u << ARM_HALF_DATA_TRANS_REG_U_SHIFT)
#define ARM_HALF_DATA_TRANS_REG_W_SHIFT /*    */ ARM_MULTIPLY_A_SHIFT
#define ARM_HALF_DATA_TRANS_REG_W_MASK /*     */ ARM_MULTIPLY_A_MASK
#define ARM_HALF_DATA_TRANS_REG_L_SHIFT /*    */ ARM_FSR_S_SHIFT
#define ARM_HALF_DATA_TRANS_REG_L_MASK /*     */ ARM_FSR_S_MASK
#define ARM_HALF_DATA_TRANS_REG_RN_SHIFT /*   */ ARM_FSR_RN_SHIFT
#define ARM_HALF_DATA_TRANS_REG_RN_MASK /*    */ ARM_FSR_RN_MASK
#define ARM_HALF_DATA_TRANS_REG_RD_SHIFT /*   */ ARM_FSR_RD_SHIFT
#define ARM_HALF_DATA_TRANS_REG_RD_MASK /*    */ ARM_FSR_RD_MASK
#define ARM_HALF_DATA_TRANS_REG_S_SHIFT 6
#define ARM_HALF_DATA_TRANS_REG_S_MASK (1u << ARM_HALF_DATA_TRANS_REG_S_SHIFT)
#define ARM_HALF_DATA_TRANS_REG_H_SHIFT 5
#define ARM_HALF_DATA_TRANS_REG_H_MASK (1u << ARM_HALF_DATA_TRANS_REG_H_SHIFT)
#define ARM_HALF_DATA_TRANS_REG_RM_SHIFT /*   */ ARM_MULTIPLY_RM_SHIFT
#define ARM_HALF_DATA_TRANS_REG_RM_MASK /*    */ ARM_MULTIPLY_RM_MASK

ISA_ISSER(u32, arm_half_data_trans_reg_is_p, ARM_HALF_DATA_TRANS_REG_P);
ISA_ISSER(u32, arm_half_data_trans_reg_is_u, ARM_HALF_DATA_TRANS_REG_U);
ISA_ISSER(u32, arm_half_data_trans_reg_is_w, ARM_HALF_DATA_TRANS_REG_W);
ISA_ISSER(u32, arm_half_data_trans_reg_is_l, ARM_HALF_DATA_TRANS_REG_L);

ISA_GETTER_SHIFTED(u32, arm_half_data_trans_reg_get_rn,
                   ARM_HALF_DATA_TRANS_REG_RN);
ISA_GETTER_SHIFTED(u32, arm_half_data_trans_reg_get_rd,
                   ARM_HALF_DATA_TRANS_REG_RD);

ISA_ISSER(u32, arm_half_data_trans_reg_is_s, ARM_HALF_DATA_TRANS_REG_S);
ISA_ISSER(u32, arm_half_data_trans_reg_is_h, ARM_HALF_DATA_TRANS_REG_H);

ISA_GETTER(u32, arm_half_data_trans_reg_get_rm, ARM_HALF_DATA_TRANS_REG_RM);

///
/// Halfword data transfer, immediate offset
///

#define ARM_HALF_DATA_TRANS_IMM_P_SHIFT ARM_HALF_DATA_TRANS_REG_P_SHIFT
#define ARM_HALF_DATA_TRANS_IMM_P_MASK ARM_HALF_DATA_TRANS_REG_P_MASK
#define ARM_HALF_DATA_TRANS_IMM_U_SHIFT ARM_HALF_DATA_TRANS_REG_U_SHIFT
#define ARM_HALF_DATA_TRANS_IMM_U_MASK ARM_HALF_DATA_TRANS_REG_U_MASK
#define ARM_HALF_DATA_TRANS_IMM_W_SHIFT /*    */ ARM_MULTIPLY_A_SHIFT
#define ARM_HALF_DATA_TRANS_IMM_W_MASK /*     */ ARM_MULTIPLY_A_MASK
#define ARM_HALF_DATA_TRANS_IMM_L_SHIFT /*    */ ARM_FSR_S_SHIFT
#define ARM_HALF_DATA_TRANS_IMM_L_MASK /*     */ ARM_FSR_S_MASK
#define ARM_HALF_DATA_TRANS_IMM_RN_SHIFT /*   */ ARM_FSR_RN_SHIFT
#define ARM_HALF_DATA_TRANS_IMM_RN_MASK /*    */ ARM_FSR_RN_MASK
#define ARM_HALF_DATA_TRANS_IMM_RD_SHIFT /*   */ ARM_FSR_RD_SHIFT
#define ARM_HALF_DATA_TRANS_IMM_RD_MASK /*    */ ARM_FSR_RD_MASK
#define ARM_HALF_DATA_TRANS_IMM_S_SHIFT ARM_HALF_DATA_TRANS_REG_S_SHIFT
#define ARM_HALF_DATA_TRANS_IMM_S_MASK ARM_HALF_DATA_TRANS_REG_S_MASK
#define ARM_HALF_DATA_TRANS_IMM_H_SHIFT ARM_HALF_DATA_TRANS_REG_H_SHIFT
#define ARM_HALF_DATA_TRANS_IMM_H_MASK ARM_HALF_DATA_TRANS_REG_H_MASK
#define ARM_HALF_DATA_TRANS_IMM_OFFSET_1_MASK ARM_MULTIPLY_RS_MASK
#define ARM_HALF_DATA_TRANS_IMM_OFFSET_2_MASK ARM_MULTIPLY_RM_MASK
#define ARM_HALF_DATA_TRANS_IMM_OFFSET_JOIN 4

ISA_ISSER(u32, arm_half_data_trans_imm_is_p, ARM_HALF_DATA_TRANS_IMM_P);
ISA_ISSER(u32, arm_half_data_trans_imm_is_u, ARM_HALF_DATA_TRANS_IMM_U);
ISA_ISSER(u32, arm_half_data_trans_imm_is_w, ARM_HALF_DATA_TRANS_IMM_W);
ISA_ISSER(u32, arm_half_data_trans_imm_is_l, ARM_HALF_DATA_TRANS_IMM_L);

ISA_GETTER_SHIFTED(u32, arm_half_data_trans_imm_get_rn,
                   ARM_HALF_DATA_TRANS_IMM_RN);
ISA_GETTER_SHIFTED(u32, arm_half_data_trans_imm_get_rd,
                   ARM_HALF_DATA_TRANS_IMM_RD);

ISA_GETTER_SPLIT_OFFSET(u32, arm_half_data_trans_imm_get_offset,
                        ARM_HALF_DATA_TRANS_IMM_OFFSET);

ISA_ISSER(u32, arm_half_data_trans_imm_is_s, ARM_HALF_DATA_TRANS_IMM_S);
ISA_ISSER(u32, arm_half_data_trans_imm_is_h, ARM_HALF_DATA_TRANS_IMM_H);

///
/// Single data transfer
///

#define ARM_SINGLE_DATA_TRANS_P_SHIFT ARM_HALF_DATA_TRANS_IMM_P_SHIFT
#define ARM_SINGLE_DATA_TRANS_P_MASK ARM_HALF_DATA_TRANS_IMM_P_MASK
#define ARM_SINGLE_DATA_TRANS_U_SHIFT ARM_HALF_DATA_TRANS_IMM_U_SHIFT
#define ARM_SINGLE_DATA_TRANS_U_MASK ARM_HALF_DATA_TRANS_IMM_U_MASK
#define ARM_SINGLE_DATA_TRANS_B_SHIFT ARM_SINGLE_DATA_SWAP_B_SHIFT
#define ARM_SINGLE_DATA_TRANS_B_MASK ARM_SINGLE_DATA_SWAP_B_MASK
#define ARM_SINGLE_DATA_TRANS_W_SHIFT ARM_HALF_DATA_TRANS_IMM_W_SHIFT
#define ARM_SINGLE_DATA_TRANS_W_MASK ARM_HALF_DATA_TRANS_IMM_W_MASK
#define ARM_SINGLE_DATA_TRANS_L_SHIFT ARM_HALF_DATA_TRANS_IMM_L_SHIFT
#define ARM_SINGLE_DATA_TRANS_L_MASK ARM_HALF_DATA_TRANS_IMM_L_MASK
#define ARM_SINGLE_DATA_TRANS_RN_SHIFT ARM_HALF_DATA_TRANS_IMM_RN_SHIFT
#define ARM_SINGLE_DATA_TRANS_RN_MASK ARM_HALF_DATA_TRANS_IMM_RN_MASK
#define ARM_SINGLE_DATA_TRANS_RD_SHIFT ARM_HALF_DATA_TRANS_IMM_RD_SHIFT
#define ARM_SINGLE_DATA_TRANS_RD_MASK ARM_HALF_DATA_TRANS_IMM_RD_MASK
#define ARM_SINGLE_DATA_TRANS_OFFSET_SHIFT ARM_FSR_OPERAND2_SHIFT
#define ARM_SINGLE_DATA_TRANS_OFFSET_MASK ARM_FSR_OPERAND2_MASK

ISA_ISSER(u32, arm_single_data_trans_is_p, ARM_SINGLE_DATA_TRANS_P);
ISA_ISSER(u32, arm_single_data_trans_is_u, ARM_SINGLE_DATA_TRANS_U);
ISA_ISSER(u32, arm_single_data_trans_is_b, ARM_SINGLE_DATA_TRANS_B);
ISA_ISSER(u32, arm_single_data_trans_is_w, ARM_SINGLE_DATA_TRANS_W);
ISA_ISSER(u32, arm_single_data_trans_is_l, ARM_SINGLE_DATA_TRANS_L);

ISA_GETTER_SHIFTED(u32, arm_single_data_trans_get_rn, ARM_SINGLE_DATA_TRANS_RN);
ISA_GETTER_SHIFTED(u32, arm_single_data_trans_get_rd, ARM_SINGLE_DATA_TRANS_RD);

ISA_GETTER(u32, arm_single_data_trans_get_offset, ARM_SINGLE_DATA_TRANS_OFFSET);

///
/// Undefined
///

// lol

///
/// Block data transfer
///

#define ARM_BLOCK_DATA_TRANS_P_SHIFT ARM_HALF_DATA_TRANS_IMM_P_SHIFT
#define ARM_BLOCK_DATA_TRANS_P_MASK ARM_HALF_DATA_TRANS_IMM_P_MASK
#define ARM_BLOCK_DATA_TRANS_U_SHIFT ARM_HALF_DATA_TRANS_IMM_U_SHIFT
#define ARM_BLOCK_DATA_TRANS_U_MASK ARM_HALF_DATA_TRANS_IMM_U_MASK
#define ARM_BLOCK_DATA_TRANS_S_SHIFT ARM_SINGLE_DATA_SWAP_B_SHIFT
#define ARM_BLOCK_DATA_TRANS_S_MASK ARM_SINGLE_DATA_SWAP_B_MASK
#define ARM_BLOCK_DATA_TRANS_W_SHIFT ARM_HALF_DATA_TRANS_IMM_W_SHIFT
#define ARM_BLOCK_DATA_TRANS_W_MASK ARM_HALF_DATA_TRANS_IMM_W_MASK
#define ARM_BLOCK_DATA_TRANS_L_SHIFT ARM_HALF_DATA_TRANS_IMM_L_SHIFT
#define ARM_BLOCK_DATA_TRANS_L_MASK ARM_HALF_DATA_TRANS_IMM_L_MASK
#define ARM_BLOCK_DATA_TRANS_RN_SHIFT ARM_HALF_DATA_TRANS_IMM_RN_SHIFT
#define ARM_BLOCK_DATA_TRANS_RN_MASK ARM_HALF_DATA_TRANS_IMM_RN_MASK
#define ARM_BLOCK_DATA_TRANS_REGISTERLIST_SHIFT 0
#define ARM_BLOCK_DATA_TRANS_REGISTERLIST_MASK (0xffffu)

ISA_ISSER(u32, arm_block_data_trans_is_p, ARM_BLOCK_DATA_TRANS_P);
ISA_ISSER(u32, arm_block_data_trans_is_u, ARM_BLOCK_DATA_TRANS_U);
ISA_ISSER(u32, arm_block_data_trans_is_s, ARM_BLOCK_DATA_TRANS_S);
ISA_ISSER(u32, arm_block_data_trans_is_w, ARM_BLOCK_DATA_TRANS_W);
ISA_ISSER(u32, arm_block_data_trans_is_l, ARM_BLOCK_DATA_TRANS_L);

ISA_GETTER_SHIFTED(u32, arm_block_data_trans_get_rn, ARM_BLOCK_DATA_TRANS_RN);

ISA_GETTER(u32, arm_block_data_trans_get_registerlist,
           ARM_BLOCK_DATA_TRANS_REGISTERLIST);

///
/// Branch
///

#define ARM_BRANCH_L_SHIFT ARM_HALF_DATA_TRANS_IMM_P_SHIFT
#define ARM_BRANCH_L_MASK ARM_HALF_DATA_TRANS_IMM_P_MASK
#define ARM_BRANCH_OFFSET_SHIFT 0
#define ARM_BRANCH_OFFSET_MASK (0xffffffu)

ISA_ISSER(u32, arm_branch_is_l, ARM_BLOCK_DATA_TRANS_L);

ISA_GETTER(u32, arm_branch_get_offset, ARM_BRANCH_OFFSET);

///
/// Coprocessor data transfer
///

#define ARM_COPROC_DATA_TRANS_P_SHIFT ARM_HALF_DATA_TRANS_IMM_P_SHIFT
#define ARM_COPROC_DATA_TRANS_P_MASK ARM_HALF_DATA_TRANS_IMM_P_MASK
#define ARM_COPROC_DATA_TRANS_U_SHIFT ARM_HALF_DATA_TRANS_IMM_U_SHIFT
#define ARM_COPROC_DATA_TRANS_U_MASK ARM_HALF_DATA_TRANS_IMM_U_MASK
#define ARM_COPROC_DATA_TRANS_N_SHIFT ARM_SINGLE_DATA_SWAP_B_SHIFT
#define ARM_COPROC_DATA_TRANS_N_MASK ARM_SINGLE_DATA_SWAP_B_MASK
#define ARM_COPROC_DATA_TRANS_W_SHIFT ARM_HALF_DATA_TRANS_IMM_W_SHIFT
#define ARM_COPROC_DATA_TRANS_W_MASK ARM_HALF_DATA_TRANS_IMM_W_MASK
#define ARM_COPROC_DATA_TRANS_L_SHIFT ARM_HALF_DATA_TRANS_IMM_L_SHIFT
#define ARM_COPROC_DATA_TRANS_L_MASK ARM_HALF_DATA_TRANS_IMM_L_MASK
#define ARM_COPROC_DATA_TRANS_RN_SHIFT ARM_HALF_DATA_TRANS_IMM_RN_SHIFT
#define ARM_COPROC_DATA_TRANS_RN_MASK ARM_HALF_DATA_TRANS_IMM_RN_MASK
#define ARM_COPROC_DATA_TRANS_CRD_SHIFT ARM_FSR_RD_SHIFT
#define ARM_COPROC_DATA_TRANS_CRD_MASK ARM_FSR_RD_MASK
#define ARM_COPROC_DATA_TRANS_CPSHARP_SHIFT ARM_MULTIPLY_RS_SHIFT
#define ARM_COPROC_DATA_TRANS_CPSHARP_MASK ARM_MULTIPLY_RS_MASK
#define ARM_COPROC_DATA_TRANS_OFFSET_SHIFT 0
#define ARM_COPROC_DATA_TRANS_OFFSET_MASK 0xffu

ISA_ISSER(u32, arm_coproc_data_trans_is_p, ARM_COPROC_DATA_TRANS_P);
ISA_ISSER(u32, arm_coproc_data_trans_is_u, ARM_COPROC_DATA_TRANS_U);
ISA_ISSER(u32, arm_coproc_data_trans_is_n, ARM_COPROC_DATA_TRANS_N);
ISA_ISSER(u32, arm_coproc_data_trans_is_w, ARM_COPROC_DATA_TRANS_W);
ISA_ISSER(u32, arm_coproc_data_trans_is_l, ARM_COPROC_DATA_TRANS_L);

ISA_GETTER_SHIFTED(u32, arm_coproc_data_trans_rn, ARM_COPROC_DATA_TRANS_RN);
ISA_GETTER_SHIFTED(u32, arm_coproc_data_trans_crd, ARM_COPROC_DATA_TRANS_CRD);
ISA_GETTER_SHIFTED(u32, arm_coproc_data_trans_cpsharp,
                   ARM_COPROC_DATA_TRANS_CPSHARP);
ISA_GETTER(u32, arm_coproc_data_trans_offset, ARM_COPROC_DATA_TRANS_OFFSET);

///
/// Coprocessor data operation
///

#define ARM_COPROC_DATA_OP_CPOPC_SHIFT ARM_HALF_DATA_TRANS_IMM_L_SHIFT
#define ARM_COPROC_DATA_OP_CPOPC_MASK 0xfu
#define ARM_COPROC_DATA_OP_CRN_SHIFT ARM_HALF_DATA_TRANS_IMM_RN_SHIFT
#define ARM_COPROC_DATA_OP_CRN_MASK ARM_HALF_DATA_TRANS_IMM_RN_MASK
#define ARM_COPROC_DATA_OP_CRD_SHIFT ARM_FSR_RD_SHIFT
#define ARM_COPROC_DATA_OP_CRD_MASK ARM_FSR_RD_MASK
#define ARM_COPROC_DATA_OP_CPSHARP_SHIFT ARM_MULTIPLY_RS_SHIFT
#define ARM_COPROC_DATA_OP_CPSHARP_MASK ARM_MULTIPLY_RS_MASK
#define ARM_COPROC_DATA_OP_CP_SHIFT ARM_HALF_DATA_TRANS_IMM_H_SHIFT
#define ARM_COPROC_DATA_OP_CP_MASK 0x7u
#define ARM_COPROC_DATA_OP_CRM_SHIFT ARM_MULTIPLY_RM_SHIFT
#define ARM_COPROC_DATA_OP_CRM_MASK ARM_MULTIPLY_RM_MASK

ISA_GETTER_SHIFTED(u32, arm_coproc_data_op_get_cpopc, ARM_COPROC_DATA_OP_CPOPC);
ISA_GETTER_SHIFTED(u32, arm_coproc_data_op_get_crn, ARM_COPROC_DATA_OP_CRN);
ISA_GETTER_SHIFTED(u32, arm_coproc_data_op_get_crd, ARM_COPROC_DATA_OP_CRD);
ISA_GETTER_SHIFTED(u32, arm_coproc_data_op_get_cpsharp,
                   ARM_COPROC_DATA_OP_CPSHARP);
ISA_GETTER_SHIFTED(u32, arm_coproc_data_op_get_cp, ARM_COPROC_DATA_OP_CP);
ISA_GETTER(u32, arm_coproc_data_op_get_crm, ARM_COPROC_DATA_OP_CRM);

///
/// Coprocessor register transfer
///

#define ARM_COPROC_REG_TRANS_CPOPC_SHIFT ARM_HALF_DATA_TRANS_IMM_W_SHIFT
#define ARM_COPROC_REG_TRANS_CPOPC_MASK 0x7u
#define ARM_COPROC_REG_TRANS_CRN_SHIFT ARM_HALF_DATA_TRANS_IMM_RN_SHIFT
#define ARM_COPROC_REG_TRANS_CRN_MASK ARM_HALF_DATA_TRANS_IMM_RN_MASK
#define ARM_COPROC_REG_TRANS_RD_SHIFT ARM_FSR_RD_SHIFT
#define ARM_COPROC_REG_TRANS_RD_MASK ARM_FSR_RD_MASK
#define ARM_COPROC_REG_TRANS_CPSHARP_SHIFT ARM_MULTIPLY_RS_SHIFT
#define ARM_COPROC_REG_TRANS_CPSHARP_MASK ARM_MULTIPLY_RS_MASK
#define ARM_COPROC_REG_TRANS_CP_SHIFT ARM_HALF_DATA_TRANS_IMM_H_SHIFT
#define ARM_COPROC_REG_TRANS_CP_MASK 0x7u
#define ARM_COPROC_REG_TRANS_CRM_SHIFT ARM_MULTIPLY_RM_SHIFT
#define ARM_COPROC_REG_TRANS_CRM_MASK ARM_MULTIPLY_RM_MASK

ISA_GETTER_SHIFTED(u32, arm_coproc_reg_trans_get_cpopc,
                   ARM_COPROC_REG_TRANS_CPOPC);
ISA_GETTER_SHIFTED(u32, arm_coproc_reg_trans_get_crn, ARM_COPROC_REG_TRANS_CRN);
ISA_GETTER_SHIFTED(u32, arm_coproc_reg_trans_get_rd, ARM_COPROC_REG_TRANS_RD);
ISA_GETTER_SHIFTED(u32, arm_coproc_reg_trans_get_cpsharp,
                   ARM_COPROC_REG_TRANS_CPSHARP);
ISA_GETTER_SHIFTED(u32, arm_coproc_reg_trans_get_cp, ARM_COPROC_REG_TRANS_CP);
ISA_GETTER(u32, arm_coproc_reg_trans_get_crm, ARM_COPROC_REG_TRANS_CRM);

///
/// Software interrupt
///

#define ARM_SW_INT_SWI_SHIFT 0
#define ARM_SW_INT_SWI_MASK (0xffffffu)

ISA_GETTER(u32, arm_sw_int_get_swi, ARM_SW_INT_SWI);

///
/// Thumb
///

///
/// Format 01 - Move shifted register
///

#define THUMB_01_OP_SHIFT /*        */ 11
#define THUMB_01_OP_MASK /*         */ (0x3u << THUMB_01_OP_SHIFT)
#define THUMB_01_OFFSET5_SHIFT /*   */ 6
#define THUMB_01_OFFSET5_MASK /*    */ (0x1fu << THUMB_01_OFFSET5_SHIFT)
#define THUMB_01_RS_SHIFT /*        */ 3
#define THUMB_01_RS_MASK /*         */ (0x7u << THUMB_01_RS_SHIFT)
#define THUMB_01_RD_SHIFT /*        */ 0
#define THUMB_01_RD_MASK /*         */ 0x7u

ISA_GETTER_SHIFTED(u16, thumb_01_get_op, THUMB_01_OP);
ISA_GETTER_SHIFTED(u16, thumb_01_get_offset5, THUMB_01_OFFSET5);
ISA_GETTER_SHIFTED(u16, thumb_01_get_rs, THUMB_01_RS);
ISA_GETTER(u16, thumb_01_get_rd, THUMB_01_RD);

///
/// Format 02 - Add and substract
///

#define THUMB_02_OP_SHIFT /*        */ 9
#define THUMB_02_OP_MASK /*         */ (1u << THUMB_02_OP_SHIFT)
#define THUMB_02_RNOFFSET3_SHIFT THUMB_01_OFFSET5_SHIFT
#define THUMB_02_RNOFFSET3_MASK (THUMB_01_RD_MASK << THUMB_02_RNOFFSET3_SHIFT)
#define THUMB_02_RS_SHIFT /*        */ THUMB_01_RS_SHIFT
#define THUMB_02_RS_MASK /*         */ THUMB_01_RS_MASK
#define THUMB_02_RD_SHIFT /*        */ THUMB_01_RD_SHIFT
#define THUMB_02_RD_MASK /*         */ THUMB_01_RD_MASK

ISA_ISSER(u16, thumb_02_is_op, THUMB_02_OP);
ISA_GETTER_SHIFTED(u16, thumb_02_get_rnoffset3, THUMB_02_RNOFFSET3);
ISA_GETTER_SHIFTED(u16, thumb_02_get_rs, THUMB_02_RS);
ISA_GETTER(u16, thumb_02_get_rd, THUMB_02_RD);

///
/// Format 03 - Move, compare, add, and subtract immediate
///

#define THUMB_03_OP_SHIFT /*        */ THUMB_01_OP_SHIFT
#define THUMB_03_OP_MASK /*         */ THUMB_01_OP_MASK
#define THUMB_03_RD_SHIFT /*        */ 8
#define THUMB_03_RD_MASK /*         */ (THUMB_01_RD_MASK << THUMB_03_RD_SHIFT)
#define THUMB_03_OFFSET8_SHIFT /*   */ 0
#define THUMB_03_OFFSET8_MASK /*    */ 0x3ffu

ISA_GETTER_SHIFTED(u16, thumb_03_get_op, THUMB_03_OP);
ISA_GETTER_SHIFTED(u16, thumb_03_get_rd, THUMB_03_RD);
ISA_GETTER(u16, thumb_03_get_offset8, THUMB_03_OFFSET8);

///
/// Format 04 - ALU operation
///

#define THUMB_04_OP_SHIFT /*        */ THUMB_01_OFFSET5_SHIFT
#define THUMB_04_OP_MASK /*         */ (0xfu << THUMB_04_OP_SHIFT)
#define THUMB_04_RS_SHIFT /*        */ THUMB_01_RS_SHIFT
#define THUMB_04_RS_MASK /*         */ THUMB_01_RS_MASK
#define THUMB_04_RD_SHIFT /*        */ THUMB_01_RD_SHIFT
#define THUMB_04_RD_MASK /*         */ THUMB_01_RD_MASK

ISA_GETTER_SHIFTED(u16, thumb_04_get_op, THUMB_04_OP);
ISA_GETTER_SHIFTED(u16, thumb_04_get_rs, THUMB_04_RS);
ISA_GETTER(u16, thumb_04_get_rd, THUMB_04_RD);

///
/// Format 05 - High register operations and branch exchange
///

#define THUMB_05_OP_SHIFT /*        */ (THUMB_01_OFFSET5_SHIFT + 2)
#define THUMB_05_OP_MASK /*         */ (0x3u << THUMB_05_OP_SHIFT)
#define THUMB_05_H1_SHIFT /*        */ (THUMB_01_OFFSET5_SHIFT + 1)
#define THUMB_05_H1_MASK /*         */ (1u << THUMB_05_H1_SHIFT)
#define THUMB_05_H2_SHIFT /*        */ THUMB_01_OFFSET5_SHIFT
#define THUMB_05_H2_MASK /*         */ (1u << THUMB_05_H2_SHIFT)
#define THUMB_05_RSHS_SHIFT /*      */ THUMB_01_RS_SHIFT
#define THUMB_05_RSHS_MASK /*       */ THUMB_01_RS_MASK
#define THUMB_05_RDHD_SHIFT /*      */ THUMB_01_RD_SHIFT
#define THUMB_05_RDHD_MASK /*       */ THUMB_01_RD_MASK

ISA_GETTER_SHIFTED(u16, thumb_05_get_op, THUMB_05_OP);
ISA_ISSER(u16, thumb_05_is_h1, THUMB_05_H1);
ISA_ISSER(u16, thumb_05_is_h2, THUMB_05_H2);
ISA_GETTER_SHIFTED(u16, thumb_05_get_rshs, THUMB_05_RSHS);
ISA_GETTER(u16, thumb_05_get_rdhd, THUMB_05_RDHD);

///
/// Format 06 - PC-relative load
///

#define THUMB_06_RD_SHIFT /*        */ THUMB_03_RD_SHIFT
#define THUMB_06_RD_MASK /*         */ THUMB_03_RD_MASK
#define THUMB_06_WORD8_SHIFT /*      */ THUMB_01_RD_SHIFT
#define THUMB_06_WORD8_MASK /*       */ 0x3ffu

ISA_GETTER_SHIFTED(u16, thumb_06_get_rd, THUMB_06_RD);
ISA_GETTER(u16, thumb_06_get_word8, THUMB_06_WORD8);

///
/// Format 07 - Load and store with relative offset
///

#define THUMB_07_L_SHIFT /*    */ THUMB_01_OP_SHIFT
#define THUMB_07_L_MASK /*     */ (0x1u << THUMB_07_L_SHIFT)
#define THUMB_07_B_SHIFT /*    */ (THUMB_01_OP_SHIFT - 1)
#define THUMB_07_B_MASK /*     */ (0x1u << THUMB_07_B_SHIFT)
#define THUMB_07_RO_SHIFT /*   */ THUMB_01_OFFSET5_SHIFT
#define THUMB_07_RO_MASK /*    */ (0x7u << THUMB_07_RO_SHIFT)
#define THUMB_07_RB_SHIFT /*   */ THUMB_01_RS_SHIFT
#define THUMB_07_RB_MASK /*    */ THUMB_01_RS_MASK
#define THUMB_07_RD_SHIFT /*   */ THUMB_01_RD_SHIFT
#define THUMB_07_RD_MASK /*    */ THUMB_01_RD_MASK

ISA_ISSER(u16, thumb_07_is_l, THUMB_07_L);
ISA_ISSER(u16, thumb_07_is_b, THUMB_07_B);
ISA_GETTER_SHIFTED(u16, thumb_07_get_ro, THUMB_07_RO);
ISA_GETTER_SHIFTED(u16, thumb_07_get_rb, THUMB_07_RB);
ISA_GETTER(u16, thumb_07_get_rd, THUMB_07_RD);

///
/// Format 08 - Load and store sign-extended byte and halfword
///

#define THUMB_08_H_SHIFT /*    */ THUMB_07_L_SHIFT
#define THUMB_08_H_MASK /*     */ THUMB_07_L_MASK
#define THUMB_08_S_SHIFT /*    */ THUMB_07_B_SHIFT
#define THUMB_08_S_MASK /*     */ THUMB_07_B_MASK
#define THUMB_08_RO_SHIFT /*   */ THUMB_07_RO_SHIFT
#define THUMB_08_RO_MASK /*    */ THUMB_07_RO_MASK
#define THUMB_08_RB_SHIFT /*   */ THUMB_07_RB_SHIFT
#define THUMB_08_RB_MASK /*    */ THUMB_07_RB_MASK
#define THUMB_08_RD_SHIFT /*   */ THUMB_07_RD_SHIFT
#define THUMB_08_RD_MASK /*    */ THUMB_07_RD_MASK

ISA_ISSER(u16, thumb_08_is_h, THUMB_08_H);
ISA_ISSER(u16, thumb_08_is_s, THUMB_08_S);
ISA_GETTER_SHIFTED(u16, thumb_08_get_ro, THUMB_08_RO);
ISA_GETTER_SHIFTED(u16, thumb_08_get_rb, THUMB_08_RB);
ISA_GETTER(u16, thumb_08_get_rd, THUMB_08_RD);
