#pragma once
#include "neogba/types.hpp"

#define /* */ ISA_UNPACK_INSTT(inst, ret, shift, mask) inst
#define /*  */ ISA_UNPACK_RETT(inst, ret, shift, mask) ret
#define /* */ ISA_UNPACK_SHIFT(inst, ret, shift, mask) shift
#define /*  */ ISA_UNPACK_MASK(inst, ret, shift, mask) mask

#define /* */ ISA_UNPACK_OFF_INSTT(inst, ret, shift, mask, mask2, join) inst
#define /*  */ ISA_UNPACK_OFF_RETT(inst, ret, shift, mask, mask2, join) ret
#define /* */ ISA_UNPACK_OFF_SHIFT(inst, ret, shift, mask, mask2, join) shift
#define /*  */ ISA_UNPACK_OFF_MASK(inst, ret, shift, mask, mask2, join) mask
#define /*  */ ISA_UNPACK_OFF_MSK2(inst, ret, shift, mask, mask2, join) mask2
#define /*  */ ISA_UNPACK_OFF_JOIN(inst, ret, shift, mask, mask2, join) join

#define ISA_GET_INSTT(...) /* */ ISA_UNPACK_INSTT(__VA_ARGS__)
#define ISA_GET_RETT(...) /*  */ ISA_UNPACK_RETT(__VA_ARGS__)
#define ISA_GET_SHIFT(...) /* */ ISA_UNPACK_SHIFT(__VA_ARGS__)
#define ISA_GET_MASK(...) /*  */ ISA_UNPACK_MASK(__VA_ARGS__)

#define ISA_GET2_INSTT(...) /* */ ISA_UNPACK_INSTT(__VA_ARGS__)
#define ISA_GET2_RETT(...) /*  */ ISA_UNPACK_RETT(__VA_ARGS__)
#define ISA_GET2_SHIFT(...) /* */ ISA_UNPACK_SHIFT(__VA_ARGS__)
#define ISA_GET2_MASK(...) /*  */ ISA_UNPACK_MASK(__VA_ARGS__)
#define ISA_GET2_MSK2(...) /*  */ ISA_UNPACK_MSK2(__VA_ARGS__)
#define ISA_GET2_JOIN(...) /*  */ ISA_UNPACK_JOIN(__VA_ARGS__)

#define ISA_SHIFTED(field)                                                     \
  [[nodiscard]] inline ISA_GET_RETT(field)                                     \
      isa_get_##field(ISA_GET_INSTT(field) inst) {                             \
    return static_cast<ISA_GET_RETT(field)>(inst >> ISA_GET_SHIFT(field));     \
  }                                                                            \
                                                                               \
  [[nodiscard]] inline ISA_GET_INSTT(field) isa_set_##field(                   \
      ISA_GET_INSTT(field) inst, ISA_GET_INSTT(field) field##_value) {         \
    return (inst & ~ISA_GET_MASK(field)) |                                     \
           (field##_value << ISA_GET_SHIFT(field));                            \
  }

#define ISA_MASKED_SHIFTED(field)                                              \
  [[nodiscard]] inline ISA_GET_RETT(field)                                     \
      isa_get_##field(ISA_GET_INSTT(field) inst) {                             \
    return static_cast<ISA_GET_RETT(field)>((inst & ISA_GET_MASK(field)) >>    \
                                            ISA_GET_SHIFT(field));             \
  }                                                                            \
                                                                               \
  [[nodiscard]] inline ISA_GET_INSTT(field) isa_set_##field(                   \
      ISA_GET_INSTT(field) inst, ISA_GET_INSTT(field) field##_value) {         \
    return (inst & ~ISA_GET_MASK(field)) |                                     \
           ((field##_value << ISA_GET_SHIFT(field)) & ISA_GET_MASK(field));    \
  }

#define ISA_MASKED_BOOL(field)                                                 \
  [[nodiscard]] inline bool isa_is_##field(ISA_GET_INSTT(field) inst) {        \
    return ((inst & ISA_GET_MASK(field)) != 0);                                \
  }                                                                            \
                                                                               \
  [[nodiscard]] inline ISA_GET_INSTT(field)                                    \
      isa_set_##field(ISA_GET_INSTT(field) inst, bool field##_value) {         \
    return (inst & ~ISA_GET_MASK(field)) |                                     \
           ((field##_value) ? (ISA_GET_MASK(field)) : 0);                      \
  }                                                                            \
                                                                               \
  [[nodiscard]] inline ISA_GET_INSTT(field)                                    \
      isa_set0_##field(ISA_GET_INSTT(field) inst) {                            \
    return (inst & ~ISA_GET_MASK(field));                                      \
  }                                                                            \
                                                                               \
  [[nodiscard]] inline ISA_GET_INSTT(field)                                    \
      isa_set1_##field(ISA_GET_INSTT(field) inst) {                            \
    return (inst | ISA_GET_MASK(field));                                       \
  }                                                                            \
                                                                               \
  [[nodiscard]] inline ISA_GET_INSTT(field)                                    \
      isa_toggle_##field(ISA_GET_INSTT(field) inst) {                          \
    return /* xor */ (inst ^ ISA_GET_MASK(field));                             \
  }

#define ISA_MASKED(field)                                                      \
  [[nodiscard]] inline ISA_GET_RETT(field)                                     \
      isa_get_##field(ISA_GET_INSTT(field) inst) {                             \
    return static_cast<ISA_GET_RETT(field)>((inst & ISA_GET_MASK(field)));     \
  }                                                                            \
                                                                               \
  [[nodiscard]] inline ISA_GET_INSTT(field) isa_set_##field(                   \
      ISA_GET_INSTT(field) inst, ISA_GET_INSTT(field) field##_value) {         \
    return (inst & ~ISA_GET_MASK(field)) |                                     \
           (((field##_value << ISA_GET_SHIFT(field)) & ISA_GET_MASK(field)));  \
  }

#define ISA_SPLIT_OFFSET(field)                                                \
  [[nodiscard]] inline ISA_GET2_RETT(field)                                    \
      isa_get_##field(ISA_GET2_INSTT(field) inst) {                            \
    return static_cast<ISA_GET2_RETT(field)>(                                  \
        ((inst & ISA_GET2_MASK(field)) >> ISA_GET2_JOIN(field)) |              \
        (inst & ISA_GET2_MSK2(field)));                                        \
  }                                                                            \
                                                                               \
  [[nodiscard]] inline ISA_GET2_INSTT(field) isa_set_##field(                  \
      ISA_GET2_INSTT(field) inst, ISA_GET2_INSTT(field) field##_value) {       \
    return (inst & ~(ISA_GET2_MASK(field) | ISA_GET2_MSK2(field))) |           \
           (field##_value & ISA_GET2_MSK2(field)) |                            \
           ((field##_value << ISA_GET2_JOIN(field)) & ISA_GET2_MASK(field));   \
  }

///
/// ARM
///

#define ARM_COND u32, u8, 28, 0xf0000000u
ISA_SHIFTED(ARM_COND)

// con esto podemos hacer esto
// auto a = isa_get_ARM_COND(0x0);
// auto b = isa_set_ARM_COND(0x0, 0x2);

///
/// Data processing and FSR transfer
///

#define ARM_FSR_OPCODE /*   */ u32, u8, 21, (0xfu << 21)
#define ARM_FSR_S /*        */ u32, bool, 20, (1u << 20)
#define ARM_FSR_RN /*       */ u32, u8, 16, (0xfu << 16)
#define ARM_FSR_RD /*       */ u32, u8, 12, (0xfu << 12)
#define ARM_FSR_OPERAND2 /* */ u32, u8, 0, ((1u << 12) - 1)

ISA_MASKED_SHIFTED(ARM_FSR_OPCODE);
ISA_MASKED_BOOL(ARM_FSR_S);
ISA_MASKED_SHIFTED(ARM_FSR_RN);
ISA_MASKED_SHIFTED(ARM_FSR_RD);
ISA_MASKED(ARM_FSR_OPERAND2);

///
/// Multiply
///

#define ARM_MULTIPLY_A /*  */ u32, bool, 21, (0x1u << 21)
#define ARM_MULTIPLY_S /*  */ ARM_FSR_S
#define ARM_MULTIPLY_RD /* */ ARM_FSR_RN
#define ARM_MULTIPLY_RN /* */ ARM_FSR_RD
#define ARM_MULTIPLY_RS /* */ u32, u8, 8, (0xfu << 8)
#define ARM_MULTIPLY_RM /* */ u32, u8, 0, 0xfu

ISA_MASKED_BOOL(ARM_MULTIPLY_A);
ISA_MASKED_BOOL(ARM_MULTIPLY_S);
ISA_MASKED_SHIFTED(ARM_MULTIPLY_RD);
ISA_MASKED_SHIFTED(ARM_MULTIPLY_RN);
ISA_MASKED_SHIFTED(ARM_MULTIPLY_RS);
ISA_MASKED(ARM_MULTIPLY_RM);

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

ISA_MASKED_BOOL(, ARM_MULTIPLY_LONG_U);
ISA_MASKED_BOOL(, ARM_MULTIPLY_LONG_A);
ISA_MASKED_BOOL(, ARM_MULTIPLY_LONG_S);

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

ISA_MASKED_BOOL(s_b, ARM_SINGLE_DATA_SWAP_B);

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

ISA_MASKED_BOOL(eg_is_p, ARM_HALF_DATA_TRANS_REG_P);
ISA_MASKED_BOOL(eg_is_u, ARM_HALF_DATA_TRANS_REG_U);
ISA_MASKED_BOOL(eg_is_w, ARM_HALF_DATA_TRANS_REG_W);
ISA_MASKED_BOOL(eg_is_l, ARM_HALF_DATA_TRANS_REG_L);

ISA_GETTER_SHIFTED(u32, arm_half_data_trans_reg_get_rn,
                   ARM_HALF_DATA_TRANS_REG_RN);
ISA_GETTER_SHIFTED(u32, arm_half_data_trans_reg_get_rd,
                   ARM_HALF_DATA_TRANS_REG_RD);

ISA_MASKED_BOOL(eg_is_s, ARM_HALF_DATA_TRANS_REG_S);
ISA_MASKED_BOOL(eg_is_h, ARM_HALF_DATA_TRANS_REG_H);

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

ISA_MASKED_BOOL(mm_is_p, ARM_HALF_DATA_TRANS_IMM_P);
ISA_MASKED_BOOL(mm_is_u, ARM_HALF_DATA_TRANS_IMM_U);
ISA_MASKED_BOOL(mm_is_w, ARM_HALF_DATA_TRANS_IMM_W);
ISA_MASKED_BOOL(mm_is_l, ARM_HALF_DATA_TRANS_IMM_L);

ISA_GETTER_SHIFTED(u32, arm_half_data_trans_imm_get_rn,
                   ARM_HALF_DATA_TRANS_IMM_RN);
ISA_GETTER_SHIFTED(u32, arm_half_data_trans_imm_get_rd,
                   ARM_HALF_DATA_TRANS_IMM_RD);

ISA_GETTER_SPLIT_OFFSET(u32, arm_half_data_trans_imm_get_offset,
                        ARM_HALF_DATA_TRANS_IMM_OFFSET);

ISA_MASKED_BOOL(mm_is_s, ARM_HALF_DATA_TRANS_IMM_S);
ISA_MASKED_BOOL(mm_is_h, ARM_HALF_DATA_TRANS_IMM_H);

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

ISA_MASKED_BOOL(s_p, ARM_SINGLE_DATA_TRANS_P);
ISA_MASKED_BOOL(s_u, ARM_SINGLE_DATA_TRANS_U);
ISA_MASKED_BOOL(s_b, ARM_SINGLE_DATA_TRANS_B);
ISA_MASKED_BOOL(s_w, ARM_SINGLE_DATA_TRANS_W);
ISA_MASKED_BOOL(s_l, ARM_SINGLE_DATA_TRANS_L);

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

ISA_MASKED_BOOL(s_p, ARM_BLOCK_DATA_TRANS_P);
ISA_MASKED_BOOL(s_u, ARM_BLOCK_DATA_TRANS_U);
ISA_MASKED_BOOL(s_s, ARM_BLOCK_DATA_TRANS_S);
ISA_MASKED_BOOL(s_w, ARM_BLOCK_DATA_TRANS_W);
ISA_MASKED_BOOL(s_l, ARM_BLOCK_DATA_TRANS_L);

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

ISA_MASKED_BOOL(ARM_BLOCK_DATA_TRANS_L);

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

ISA_MASKED_BOOL(s_p, ARM_COPROC_DATA_TRANS_P);
ISA_MASKED_BOOL(s_u, ARM_COPROC_DATA_TRANS_U);
ISA_MASKED_BOOL(s_n, ARM_COPROC_DATA_TRANS_N);
ISA_MASKED_BOOL(s_w, ARM_COPROC_DATA_TRANS_W);
ISA_MASKED_BOOL(s_l, ARM_COPROC_DATA_TRANS_L);

ISA_GETTER_SHIFTED(u32, arm_coproc_data_trans_rn, ARM_COPROC_DATA_TRANS_RN);
ISA_GETTER_SHIFTED(u32, arm_coproc_data_trans_crd, ARM_COPROC_DATA_TRANS_CRD);
ISA_GETTER_SHIFTED(u32, arm_coproc_data_trans_cpsharp,
                   ARM_COPROC_DATA_TRANS_CPSHARP);
ISA_GETTER(u32, arm_coproc_data_trans_offset, ARM_COPROC_DATA_TRANS_OFFSET);

///
/// Coprocessor data operation
///

#define ARM_COPROC_DATA_OP_CPOPC_SHIFT ARM_HALF_DATA_TRANS_IMM_L_SHIFT
#define ARM_COPROC_DATA_OP_CPOPC_MASK (0xfu << ARM_COPROC_DATA_OP_CPOPC_SHIFT)
#define ARM_COPROC_DATA_OP_CRN_SHIFT ARM_HALF_DATA_TRANS_IMM_RN_SHIFT
#define ARM_COPROC_DATA_OP_CRN_MASK ARM_HALF_DATA_TRANS_IMM_RN_MASK
#define ARM_COPROC_DATA_OP_CRD_SHIFT ARM_FSR_RD_SHIFT
#define ARM_COPROC_DATA_OP_CRD_MASK ARM_FSR_RD_MASK
#define ARM_COPROC_DATA_OP_CPSHARP_SHIFT ARM_MULTIPLY_RS_SHIFT
#define ARM_COPROC_DATA_OP_CPSHARP_MASK ARM_MULTIPLY_RS_MASK
#define ARM_COPROC_DATA_OP_CP_SHIFT ARM_HALF_DATA_TRANS_IMM_H_SHIFT
#define ARM_COPROC_DATA_OP_CP_MASK (0x7u << ARM_COPROC_DATA_OP_CP_SHIFT)
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
#define ARM_COPROC_REG_TRANS_CPOPC_MASK                                        \
  (0x7u << ARM_COPROC_REG_TRANS_CPOPC_SHIFT)
#define ARM_COPROC_REG_TRANS_L_SHIFT ARM_SINGLE_DATA_TRANS_L_SHIFT
#define ARM_COPROC_REG_TRANS_L_MASK ARM_SINGLE_DATA_TRANS_L_MASK
#define ARM_COPROC_REG_TRANS_CRN_SHIFT ARM_HALF_DATA_TRANS_IMM_RN_SHIFT
#define ARM_COPROC_REG_TRANS_CRN_MASK ARM_HALF_DATA_TRANS_IMM_RN_MASK
#define ARM_COPROC_REG_TRANS_RD_SHIFT ARM_FSR_RD_SHIFT
#define ARM_COPROC_REG_TRANS_RD_MASK ARM_FSR_RD_MASK
#define ARM_COPROC_REG_TRANS_CPSHARP_SHIFT ARM_MULTIPLY_RS_SHIFT
#define ARM_COPROC_REG_TRANS_CPSHARP_MASK ARM_MULTIPLY_RS_MASK
#define ARM_COPROC_REG_TRANS_CP_SHIFT ARM_HALF_DATA_TRANS_IMM_H_SHIFT
#define ARM_COPROC_REG_TRANS_CP_MASK (0x7u << ARM_COPROC_REG_TRANS_CP_SHIFT)
#define ARM_COPROC_REG_TRANS_CRM_SHIFT ARM_MULTIPLY_RM_SHIFT
#define ARM_COPROC_REG_TRANS_CRM_MASK ARM_MULTIPLY_RM_MASK

ISA_GETTER_SHIFTED(u32, arm_coproc_reg_trans_get_cpopc,
                   ARM_COPROC_REG_TRANS_CPOPC);
ISA_MASKED_BOOL(s_l, ARM_COPROC_REG_TRANS_L);
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

ISA_MASKED_BOOL(THUMB_02_OP);
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
#define THUMB_03_OFFSET8_MASK /*    */ 0xffu

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
ISA_MASKED_BOOL(THUMB_05_H1);
ISA_MASKED_BOOL(THUMB_05_H2);
ISA_GETTER_SHIFTED(u16, thumb_05_get_rshs, THUMB_05_RSHS);
ISA_GETTER(u16, thumb_05_get_rdhd, THUMB_05_RDHD);

///
/// Format 06 - PC-relative load
///

#define THUMB_06_RD_SHIFT /*    */ THUMB_03_RD_SHIFT
#define THUMB_06_RD_MASK /*     */ THUMB_03_RD_MASK
#define THUMB_06_WORD8_SHIFT /* */ THUMB_01_RD_SHIFT
#define THUMB_06_WORD8_MASK /*  */ 0xffu

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

ISA_MASKED_BOOL(THUMB_07_L);
ISA_MASKED_BOOL(THUMB_07_B);
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

ISA_MASKED_BOOL(THUMB_08_H);
ISA_MASKED_BOOL(THUMB_08_S);
ISA_GETTER_SHIFTED(u16, thumb_08_get_ro, THUMB_08_RO);
ISA_GETTER_SHIFTED(u16, thumb_08_get_rb, THUMB_08_RB);
ISA_GETTER(u16, thumb_08_get_rd, THUMB_08_RD);

///
/// Format 09 - Load and store with immediate offset
///

#define THUMB_09_B_SHIFT /*         */ (THUMB_01_OP_SHIFT + 1)
#define THUMB_09_B_MASK /*          */ (0x1u << THUMB_09_B_SHIFT)
#define THUMB_09_L_SHIFT /*         */ THUMB_01_OP_SHIFT
#define THUMB_09_L_MASK /*          */ (0x1u << THUMB_09_L_SHIFT)
#define THUMB_09_OFFSET5_SHIFT /*   */ THUMB_01_OFFSET5_SHIFT
#define THUMB_09_OFFSET5_MASK /*    */ THUMB_01_OFFSET5_MASK
#define THUMB_09_RB_SHIFT /*        */ THUMB_01_RS_SHIFT
#define THUMB_09_RB_MASK /*         */ THUMB_01_RS_MASK
#define THUMB_09_RD_SHIFT /*        */ THUMB_01_RD_SHIFT
#define THUMB_09_RD_MASK /*         */ THUMB_01_RD_MASK

ISA_MASKED_BOOL(THUMB_09_B);
ISA_MASKED_BOOL(THUMB_09_L);
ISA_GETTER_SHIFTED(u16, thumb_09_get_offset5, THUMB_09_OFFSET5);
ISA_GETTER_SHIFTED(u16, thumb_09_get_rb, THUMB_09_RB);
ISA_GETTER(u16, thumb_09_get_rd, THUMB_09_RD);

///
/// Format 10 - Load and store halfword
///

#define THUMB_10_L_SHIFT /*         */ THUMB_01_OP_SHIFT
#define THUMB_10_L_MASK /*          */ (0x1u << THUMB_10_L_SHIFT)
#define THUMB_10_OFFSET5_SHIFT /*   */ THUMB_01_OFFSET5_SHIFT
#define THUMB_10_OFFSET5_MASK /*    */ THUMB_01_OFFSET5_MASK
#define THUMB_10_RB_SHIFT /*        */ THUMB_01_RS_SHIFT
#define THUMB_10_RB_MASK /*         */ THUMB_01_RS_MASK
#define THUMB_10_RD_SHIFT /*        */ THUMB_01_RD_SHIFT
#define THUMB_10_RD_MASK /*         */ THUMB_01_RD_MASK

ISA_MASKED_BOOL(THUMB_10_L);
ISA_GETTER_SHIFTED(u16, thumb_10_get_offset5, THUMB_10_OFFSET5);
ISA_GETTER_SHIFTED(u16, thumb_10_get_rb, THUMB_10_RB);
ISA_GETTER(u16, thumb_10_get_rd, THUMB_10_RD);

///
/// Format 11 - SP-relative load and store
///

#define THUMB_11_L_SHIFT /*     */ THUMB_10_L_SHIFT
#define THUMB_11_L_MASK /*      */ THUMB_10_L_MASK
#define THUMB_11_RD_SHIFT /*    */ THUMB_06_RD_SHIFT
#define THUMB_11_RD_MASK /*     */ THUMB_06_RD_MASK
#define THUMB_11_WORD8_SHIFT /* */ THUMB_06_WORD8_SHIFT
#define THUMB_11_WORD8_MASK /*  */ THUMB_06_WORD8_MASK

ISA_MASKED_BOOL(THUMB_11_L);
ISA_GETTER_SHIFTED(u16, thumb_11_get_rd, THUMB_11_RD);
ISA_GETTER(u16, thumb_11_get_word8, THUMB_11_WORD8);

///
/// Format 12 - Load address
///

#define THUMB_12_SP_SHIFT /*    */ THUMB_11_L_SHIFT
#define THUMB_12_SP_MASK /*     */ THUMB_11_L_MASK
#define THUMB_12_RD_SHIFT /*    */ THUMB_11_RD_SHIFT
#define THUMB_12_RD_MASK /*     */ THUMB_11_RD_MASK
#define THUMB_12_WORD8_SHIFT /* */ THUMB_11_WORD8_SHIFT
#define THUMB_12_WORD8_MASK /*  */ THUMB_11_WORD8_MASK

ISA_MASKED_BOOL(THUMB_12_SP);
ISA_GETTER_SHIFTED(u16, thumb_12_get_rd, THUMB_12_RD);
ISA_GETTER(u16, thumb_12_get_word8, THUMB_12_WORD8);

///
/// Format 13 - Add offset to stack pointer
///

#define THUMB_13_S_SHIFT /*      */ 7
#define THUMB_13_S_MASK /*       */ (0x1u << THUMB_13_S_SHIFT)
#define THUMB_13_SWORD7_SHIFT /* */ 0
#define THUMB_13_SWORD7_MASK /*  */ 0x7fu

ISA_MASKED_BOOL(THUMB_13_S);
ISA_GETTER(u16, thumb_13_get_sword7, THUMB_13_SWORD7);

///
/// Format 14 - Push and pop registers
///

#define THUMB_14_L_SHIFT /*     */ THUMB_11_L_SHIFT
#define THUMB_14_L_MASK /*      */ THUMB_11_L_MASK
#define THUMB_14_R_SHIFT /*     */ THUMB_11_RD_SHIFT
#define THUMB_14_R_MASK /*      */ (0x1u << THUMB_14_R_SHIFT)
#define THUMB_14_RLIST_SHIFT /* */ THUMB_11_WORD8_SHIFT
#define THUMB_14_RLIST_MASK /*  */ THUMB_11_WORD8_MASK

ISA_MASKED_BOOL(THUMB_14_L);
ISA_GETTER_SHIFTED(u16, thumb_14_is_r, THUMB_14_R);
ISA_GETTER(u16, thumb_14_get_rlist, THUMB_14_RLIST);

///
/// Format 15 - Multiple load and store
///

#define THUMB_15_L_SHIFT /*     */ THUMB_12_SP_SHIFT
#define THUMB_15_L_MASK /*      */ THUMB_12_SP_MASK
#define THUMB_15_RB_SHIFT /*    */ THUMB_12_RD_SHIFT
#define THUMB_15_RB_MASK /*     */ THUMB_12_RD_MASK
#define THUMB_15_RLIST_SHIFT /* */ THUMB_12_WORD8_SHIFT
#define THUMB_15_RLIST_MASK /*  */ THUMB_12_WORD8_MASK

ISA_MASKED_BOOL(THUMB_15_L);
ISA_GETTER_SHIFTED(u16, thumb_15_get_rb, THUMB_15_RB);
ISA_GETTER(u16, thumb_15_get_rlist, THUMB_15_RLIST);

///
/// Format 16 - Conditional branch
///

#define THUMB_16_COND_SHIFT /*     */ THUMB_12_RD_SHIFT
#define THUMB_16_COND_MASK /*      */ (0xfu << THUMB_16_COND_SHIFT)
#define THUMB_16_SOFTSET8_SHIFT /* */ THUMB_12_WORD8_SHIFT
#define THUMB_16_SOFTSET8_MASK /*  */ THUMB_12_WORD8_MASK

ISA_GETTER_SHIFTED(u16, thumb_16_get_cond, THUMB_16_COND);
ISA_GETTER(u16, thumb_16_get_softset8, THUMB_16_SOFTSET8);

///
/// Format 17 - Software interrupt
///

#define THUMB_17_VALUE8_SHIFT /* */ 0
#define THUMB_17_VALUE8_MASK /*  */ 0xffu

ISA_GETTER(u16, thumb_17_get_value8, THUMB_17_VALUE8);

///
/// Format 18 - Unconditional branch
///

#define THUMB_18_OFFSET11_SHIFT /* */ 0
#define THUMB_18_OFFSET11_MASK /*  */ 0x7ffu

ISA_GETTER(u16, thumb_18_get_offset11, THUMB_18_OFFSET11);

///
/// Format 19 - Long branch with link
///

#define THUMB_19_H_SHIFT /*     */ THUMB_15_L_SHIFT
#define THUMB_19_H_MASK /*      */ THUMB_15_L_MASK
#define THUMB_19_OFFSET_SHIFT /* */ THUMB_18_OFFSET11_SHIFT
#define THUMB_19_OFFSET_MASK /*  */ THUMB_18_OFFSET11_MASK

ISA_MASKED_BOOL(THUMB_19_H);
ISA_GETTER(u16, thumb_19_get_offset, THUMB_19_OFFSET);
