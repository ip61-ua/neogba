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

#define ISA_GET2_INSTT(...) /* */ ISA_UNPACK_OFF_INSTT(__VA_ARGS__)
#define ISA_GET2_RETT(...) /*  */ ISA_UNPACK_OFF_RETT(__VA_ARGS__)
#define ISA_GET2_SHIFT(...) /* */ ISA_UNPACK_OFF_SHIFT(__VA_ARGS__)
#define ISA_GET2_MASK(...) /*  */ ISA_UNPACK_OFF_MASK(__VA_ARGS__)
#define ISA_GET2_MSK2(...) /*  */ ISA_UNPACK_OFF_MSK2(__VA_ARGS__)
#define ISA_GET2_JOIN(...) /*  */ ISA_UNPACK_OFF_JOIN(__VA_ARGS__)

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

#define ARM_FSR_TEMPLATE /**/ 0x02000000u
#define ARM_FSR_OPCODE /*  */ u32, u8, 21, (0xfu << 21)
#define ARM_FSR_S /*       */ u32, bool, 20, (1u << 20)
#define ARM_FSR_RN /*      */ u32, u8, 16, (0xfu << 16)
#define ARM_FSR_RD /*      */ u32, u8, 12, (0xfu << 12)
#define ARM_FSR_OPERAND2 /**/ u32, u16, 0, ((1u << 12) - 1)

ISA_MASKED_SHIFTED(ARM_FSR_OPCODE);
ISA_MASKED_BOOL(ARM_FSR_S);
ISA_MASKED_SHIFTED(ARM_FSR_RN);
ISA_MASKED_SHIFTED(ARM_FSR_RD);
ISA_MASKED(ARM_FSR_OPERAND2);

///
/// Multiply
///

#define ARM_MULTIPLY_TEMPLATE 0x00000090u
#define ARM_MULTIPLY_A /*  */ u32, bool, 21, (1u << 21)
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

#define ARM_LONG_TEMPLATE 0x00800090
#define ARM_LONG_U /*   */ u32, bool, 22, (1u << 22)
#define ARM_LONG_A /*   */ ARM_MULTIPLY_A
#define ARM_LONG_S /*   */ ARM_MULTIPLY_S
#define ARM_LONG_RDHI /**/ ARM_MULTIPLY_RD
#define ARM_LONG_RDLO /**/ ARM_MULTIPLY_RN
#define ARM_LONG_RN /*  */ ARM_MULTIPLY_RS
#define ARM_LONG_RM /*  */ ARM_MULTIPLY_RM

ISA_MASKED_BOOL(ARM_LONG_U);
ISA_MASKED_BOOL(ARM_LONG_A);
ISA_MASKED_BOOL(ARM_LONG_S);
ISA_MASKED_SHIFTED(ARM_LONG_RDHI);
ISA_MASKED_SHIFTED(ARM_LONG_RDLO);
ISA_MASKED_SHIFTED(ARM_LONG_RN);
ISA_MASKED(ARM_LONG_RM);

///
/// Single data swap
///

#define ARM_SWAP_TEMPLATE 0x01000090u
#define ARM_SWAP_B /*  */ ARM_LONG_U
#define ARM_SWAP_RN /* */ ARM_FSR_RN
#define ARM_SWAP_RD /* */ ARM_FSR_RD
#define ARM_SWAP_RM /* */ ARM_MULTIPLY_RM

ISA_MASKED_BOOL(ARM_SWAP_B);
ISA_MASKED_SHIFTED(ARM_SWAP_RN);
ISA_MASKED_SHIFTED(ARM_SWAP_RD);
ISA_MASKED(ARM_SWAP_RM);

///
/// Branch and Exchange
///

#define ARM_EXCHANGE_TEMPLATE 0x012fff10u
#define ARM_EXCHANGE_RN /* */ ARM_MULTIPLY_RM

ISA_MASKED(ARM_EXCHANGE_RN);

///
/// Halfword data transfer, register offset
///

#define ARM_HALFREG_TEMPLATE 0x00000090u
#define ARM_HALFREG_P /*   */ u32, bool, 24, (1u << 24)
#define ARM_HALFREG_U /*   */ u32, bool, 23, (1u << 23)
#define ARM_HALFREG_W /*   */ ARM_MULTIPLY_A
#define ARM_HALFREG_L /*   */ ARM_FSR_S
#define ARM_HALFREG_RN /*  */ ARM_FSR_RN
#define ARM_HALFREG_RD /*  */ ARM_FSR_RD
#define ARM_HALFREG_S /*   */ u32, bool, 6, (1u << 6)
#define ARM_HALFREG_H /*   */ u32, bool, 5, (1u << 5)
#define ARM_HALFREG_RM /*  */ ARM_MULTIPLY_RM

ISA_MASKED_BOOL(ARM_HALFREG_P);
ISA_MASKED_BOOL(ARM_HALFREG_U);
ISA_MASKED_BOOL(ARM_HALFREG_W);
ISA_MASKED_BOOL(ARM_HALFREG_L);
ISA_MASKED_SHIFTED(ARM_HALFREG_RN);
ISA_MASKED_SHIFTED(ARM_HALFREG_RD);
ISA_MASKED_BOOL(ARM_HALFREG_S);
ISA_MASKED_BOOL(ARM_HALFREG_H);
ISA_MASKED(ARM_HALFREG_RM);

///
/// Halfword data transfer, immediate offset
///

#define ARM_HALFIMM_TEMPLATE /**/ 0x00400090u
#define ARM_HALFIMM_P /*       */ ARM_HALFREG_P
#define ARM_HALFIMM_U /*       */ ARM_HALFREG_U
#define ARM_HALFIMM_W /*       */ ARM_MULTIPLY_A
#define ARM_HALFIMM_L /*       */ ARM_FSR_S
#define ARM_HALFIMM_RN /*      */ ARM_FSR_RN
#define ARM_HALFIMM_RD /*      */ ARM_FSR_RD
#define ARM_HALFIMM_S /*       */ ARM_HALFREG_S
#define ARM_HALFIMM_H /*       */ ARM_HALFREG_H
#define ARM_HALFIMM_OFFSET ARM_MULTIPLY_RS, ISA_GET_MASK(ARM_MULTIPLY_RM), 4

ISA_MASKED_BOOL(ARM_HALFIMM_P);
ISA_MASKED_BOOL(ARM_HALFIMM_U);
ISA_MASKED_BOOL(ARM_HALFIMM_W);
ISA_MASKED_BOOL(ARM_HALFIMM_L);
ISA_MASKED_SHIFTED(ARM_HALFIMM_RN);
ISA_MASKED_SHIFTED(ARM_HALFIMM_RD);
ISA_SPLIT_OFFSET(ARM_HALFIMM_OFFSET);
ISA_MASKED_BOOL(ARM_HALFIMM_S);
ISA_MASKED_BOOL(ARM_HALFIMM_H);

///
/// Single data transfer
///

#define ARM_SINGLETRANS_TEMPLATE /**/ 0x06000000u
#define ARM_SINGLETRANS_P /*       */ ARM_HALFIMM_P
#define ARM_SINGLETRANS_U /*       */ ARM_HALFIMM_U
#define ARM_SINGLETRANS_B /*       */ ARM_SWAP_B
#define ARM_SINGLETRANS_W /*       */ ARM_HALFIMM_W
#define ARM_SINGLETRANS_L /*       */ ARM_HALFIMM_L
#define ARM_SINGLETRANS_RN /*      */ ARM_HALFIMM_RN
#define ARM_SINGLETRANS_RD /*      */ ARM_HALFIMM_RD
#define ARM_SINGLETRANS_OFFSET /*  */ ARM_FSR_OPERAND2

ISA_MASKED_BOOL(ARM_SINGLETRANS_P);
ISA_MASKED_BOOL(ARM_SINGLETRANS_U);
ISA_MASKED_BOOL(ARM_SINGLETRANS_B);
ISA_MASKED_BOOL(ARM_SINGLETRANS_W);
ISA_MASKED_BOOL(ARM_SINGLETRANS_L);
ISA_MASKED_SHIFTED(ARM_SINGLETRANS_RN);
ISA_MASKED_SHIFTED(ARM_SINGLETRANS_RD);
ISA_MASKED(ARM_SINGLETRANS_OFFSET);

///
/// Undefined
///

#define ARM_UNDEFINED_TEMPLATE 0x06000010u

///
/// Block data transfer
///

#define ARM_BLOCKTRANS_TEMPLATE /*    */ 0x09000000u
#define ARM_BLOCKTRANS_P /*           */ ARM_HALFIMM_P
#define ARM_BLOCKTRANS_U /*           */ ARM_HALFIMM_U
#define ARM_BLOCKTRANS_S /*           */ ARM_SWAP_B
#define ARM_BLOCKTRANS_W /*           */ ARM_HALFIMM_W
#define ARM_BLOCKTRANS_L /*           */ ARM_HALFIMM_L
#define ARM_BLOCKTRANS_RN /*          */ ARM_HALFIMM_RN
#define ARM_BLOCKTRANS_REGISTERLIST /**/ u32, u16, 0, 0xffffu

ISA_MASKED_BOOL(ARM_BLOCKTRANS_P);
ISA_MASKED_BOOL(ARM_BLOCKTRANS_U);
ISA_MASKED_BOOL(ARM_BLOCKTRANS_S);
ISA_MASKED_BOOL(ARM_BLOCKTRANS_W);
ISA_MASKED_BOOL(ARM_BLOCKTRANS_L);
ISA_MASKED_SHIFTED(ARM_BLOCKTRANS_RN);
ISA_MASKED(ARM_BLOCKTRANS_REGISTERLIST);

///
/// Branch
///

#define ARM_BRANCH_TEMPLATE /**/ 0x0a000000u
#define ARM_BRANCH_L /*       */ ARM_HALFIMM_P
#define ARM_BRANCH_OFFSET /*  */ u32, u32, 0, 0xffffffu

ISA_MASKED_BOOL(ARM_BRANCH_L);
ISA_MASKED(ARM_BRANCH_OFFSET);

///
/// Coprocessor data transfer
///

#define ARM_COPROCTRANS_P_TEMPLATE 0x0b000000u
#define ARM_COPROCTRANS_P ARM_HALFIMM_P
#define ARM_COPROCTRANS_U ARM_HALFIMM_U
#define ARM_COPROCTRANS_N ARM_SWAP_B
#define ARM_COPROCTRANS_W ARM_HALFIMM_W
#define ARM_COPROCTRANS_L ARM_HALFIMM_L
#define ARM_COPROCTRANS_RN ARM_HALFIMM_RN
#define ARM_COPROCTRANS_CRD ARM_FSR_RD
#define ARM_COPROCTRANS_CPSHARP ARM_MULTIPLY_RS
#define ARM_COPROCTRANS_OFFSET u32, u8, 0, 0xffu

ISA_MASKED_BOOL(ARM_COPROCTRANS_P);
ISA_MASKED_BOOL(ARM_COPROCTRANS_U);
ISA_MASKED_BOOL(ARM_COPROCTRANS_N);
ISA_MASKED_BOOL(ARM_COPROCTRANS_W);
ISA_MASKED_BOOL(ARM_COPROCTRANS_L);
ISA_MASKED_SHIFTED(ARM_COPROCTRANS_RN);
ISA_MASKED_SHIFTED(ARM_COPROCTRANS_CRD);
ISA_MASKED_SHIFTED(ARM_COPROCTRANS_CPSHARP);
ISA_MASKED(ARM_COPROCTRANS_OFFSET);

///
/// Coprocessor data operation
///

#define ARM_COPROCOP_TEMPLATE /**/ 0x0e000000u
#define ARM_COPROCOP_CPOPC /*   */ u32, u8, 21, (0xfu << 21)
#define ARM_COPROCOP_CRN /*     */ ARM_HALFIMM_RN
#define ARM_COPROCOP_CRD /*     */ ARM_FSR_RD
#define ARM_COPROCOP_CPSHARP /* */ ARM_MULTIPLY_RS
#define ARM_COPROCOP_CP /*      */ u32, u8, 5, (0x7u << 5)
#define ARM_COPROCOP_CRM /*     */ ARM_MULTIPLY_RM

ISA_MASKED_SHIFTED(ARM_COPROCOP_CPOPC);
ISA_MASKED_SHIFTED(ARM_COPROCOP_CRN);
ISA_MASKED_SHIFTED(ARM_COPROCOP_CRD);
ISA_MASKED_SHIFTED(ARM_COPROCOP_CPSHARP);
ISA_MASKED_SHIFTED(ARM_COPROCOP_CP);
ISA_MASKED(ARM_COPROCOP_CRM);

///
/// Coprocessor register transfer
///

#define ARM_COPROCREGTRANS_TEMPLATE /**/ 0x0e000010u
#define ARM_COPROCREGTRANS_CPOPC /*   */ u32, u8, 21, (0x7u << 21)
#define ARM_COPROCREGTRANS_L /*       */ ARM_SINGLETRANS_L
#define ARM_COPROCREGTRANS_CRN /*     */ ARM_COPROCOP_CRN
#define ARM_COPROCREGTRANS_RD /*      */ ARM_COPROCOP_CRD
#define ARM_COPROCREGTRANS_CPSHARP /* */ ARM_COPROCOP_CPSHARP
#define ARM_COPROCREGTRANS_CP /*      */ ARM_COPROCOP_CP
#define ARM_COPROCREGTRANS_CRM /*     */ ARM_COPROCOP_CRM

ISA_MASKED_SHIFTED(ARM_COPROCREGTRANS_CPOPC);
ISA_MASKED_BOOL(ARM_COPROCREGTRANS_L);
ISA_MASKED_SHIFTED(ARM_COPROCREGTRANS_CRN);
ISA_MASKED_SHIFTED(ARM_COPROCREGTRANS_RD);
ISA_MASKED_SHIFTED(ARM_COPROCREGTRANS_CPSHARP);
ISA_MASKED_SHIFTED(ARM_COPROCREGTRANS_CP);
ISA_MASKED(ARM_COPROCREGTRANS_CRM);

///
/// Software interrupt
///

#define ARM_SWINT_TEMPLATE 0x0f000000
#define ARM_SWINT_SWI /**/ u32, u32, 0, 0xffffffu

ISA_MASKED(ARM_SWINT_SWI);

///
/// Thumb
///

///
/// Format 01 - Move shifted register
///

#define THUMB_01_TEMPLATE /**/ 0x0000u
#define THUMB_01_OP /*      */ u16, u8, 11, (0x3u << 11)
#define THUMB_01_OFFSET5 /* */ u16, u8, 6, (0x1fu << 6)
#define THUMB_01_RS /*      */ u16, u8, 3, (0x7u << 3)
#define THUMB_01_RD /*      */ u16, u8, 0, 0x7u

ISA_MASKED_SHIFTED(THUMB_01_OP);
ISA_MASKED_SHIFTED(THUMB_01_OFFSET5);
ISA_MASKED_SHIFTED(THUMB_01_RS);
ISA_MASKED(THUMB_01_RD);

///
/// Format 02 - Add and substract
///

#define THUMB_02_TEMPLATE /* */ 0x1c00u
#define THUMB_02_OP /*       */ u16, bool, 9, (1u << 9)
#define THUMB_02_RNOFFSET3 /**/ u16, u8, 6, (0x7u << 6)
#define THUMB_02_RS /*       */ THUMB_01_RS
#define THUMB_02_RD /*       */ THUMB_01_RD

ISA_MASKED_BOOL(THUMB_02_OP);
ISA_MASKED_SHIFTED(THUMB_02_RNOFFSET3);
ISA_MASKED_SHIFTED(THUMB_02_RS);
ISA_MASKED(THUMB_02_RD);

///
/// Format 03 - Move, compare, add, and subtract immediate
///

#define THUMB_03_TEMPLATE /**/ 0x2000u
#define THUMB_03_OP /*      */ THUMB_01_OP
#define THUMB_03_RD /*      */ u16, u8, 8, (0x7u << 8)
#define THUMB_03_OFFSET8 /* */ u16, u8, 0, 0xffu

ISA_MASKED_SHIFTED(THUMB_03_OP);
ISA_MASKED_SHIFTED(THUMB_03_RD);
ISA_MASKED(THUMB_03_OFFSET8);

///
/// Format 04 - ALU operation
///

#define THUMB_04_TEMPLATE /**/ 0x4000u
#define THUMB_04_OP /*      */ u16, u8, 6, (0xfu << 6)
#define THUMB_04_RS /*      */ THUMB_01_RS
#define THUMB_04_RD /*      */ THUMB_01_RD

ISA_MASKED_SHIFTED(THUMB_04_OP);
ISA_MASKED_SHIFTED(THUMB_04_RS);
ISA_MASKED(THUMB_04_RD);

///
/// Format 05 - High register operations and branch exchange
///

#define THUMB_05_TEMPLATE /**/ 0x4400u
#define THUMB_05_OP /*      */ u16, u8, 8, (0x7u << 8)
#define THUMB_05_H1 /*      */ u16, bool, 7, (1u << 7)
#define THUMB_05_H2 /*      */ u16, bool, 6, (1u << 6)
#define THUMB_05_RSHS /*    */ THUMB_01_RS
#define THUMB_05_RDHD /*    */ THUMB_01_RD

ISA_MASKED_SHIFTED(THUMB_05_OP);
ISA_MASKED_BOOL(THUMB_05_H1);
ISA_MASKED_BOOL(THUMB_05_H2);
ISA_MASKED_SHIFTED(THUMB_05_RSHS);
ISA_MASKED(THUMB_05_RDHD);

///
/// Format 06 - PC-relative load
///

#define THUMB_06_TEMPLATE /**/ 0x4800u
#define THUMB_06_RD /*      */ THUMB_03_RD
#define THUMB_06_WORD8 /*   */ u16, u8, 0, 0xffu

ISA_MASKED_SHIFTED(THUMB_06_RD);
ISA_MASKED(THUMB_06_WORD8);

///
/// Format 07 - Load and store with relative offset
///

#define THUMB_07_TEMPLATE 0x5000
#define THUMB_07_L /*  */ u16, bool, 11, (1u << 11)
#define THUMB_07_B /*  */ u16, bool, 10, (1u << 10)
#define THUMB_07_RO /* */ THUMB_02_RNOFFSET3
#define THUMB_07_RB /* */ THUMB_01_RS
#define THUMB_07_RD /* */ THUMB_01_RD

ISA_MASKED_BOOL(THUMB_07_L);
ISA_MASKED_BOOL(THUMB_07_B);
ISA_MASKED_SHIFTED(THUMB_07_RO);
ISA_MASKED_SHIFTED(THUMB_07_RB);
ISA_MASKED(THUMB_07_RD);

///
/// Format 08 - Load and store sign-extended byte and halfword
///

#define THUMB_08_TEMPLATE 0x5200
#define THUMB_08_H /*  */ THUMB_07_L
#define THUMB_08_S /*  */ THUMB_07_B
#define THUMB_08_RO /* */ THUMB_07_RO
#define THUMB_08_RB /* */ THUMB_07_RB
#define THUMB_08_RD /* */ THUMB_07_RD

ISA_MASKED_BOOL(THUMB_08_H);
ISA_MASKED_BOOL(THUMB_08_S);
ISA_MASKED_SHIFTED(THUMB_08_RO);
ISA_MASKED_SHIFTED(THUMB_08_RB);
ISA_MASKED(THUMB_08_RD);

///
/// Format 09 - Load and store with immediate offset
///

#define THUMB_09_TEMPLATE /**/ 0x6000
#define THUMB_09_B /*       */ u16, bool, 12, (1u << 12)
#define THUMB_09_L /*       */ THUMB_07_L
#define THUMB_09_OFFSET5 /* */ THUMB_01_OFFSET5
#define THUMB_09_RB /*      */ THUMB_01_RS
#define THUMB_09_RD /*      */ THUMB_01_RD

ISA_MASKED_BOOL(THUMB_09_B);
ISA_MASKED_BOOL(THUMB_09_L);
ISA_MASKED_SHIFTED(THUMB_09_OFFSET5);
ISA_MASKED_SHIFTED(THUMB_09_RB);
ISA_MASKED(THUMB_09_RD);

///
/// Format 10 - Load and store halfword
///

#define THUMB_10_TEMPLATE /**/ 0x8000
#define THUMB_10_L /*       */ THUMB_09_L
#define THUMB_10_OFFSET5 /* */ THUMB_01_OFFSET5
#define THUMB_10_RB /*      */ THUMB_01_RS
#define THUMB_10_RD /*      */ THUMB_01_RD

ISA_MASKED_BOOL(THUMB_10_L);
ISA_MASKED_SHIFTED(THUMB_10_OFFSET5);
ISA_MASKED_SHIFTED(THUMB_10_RB);
ISA_MASKED(THUMB_10_RD);

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
ISA_MASKED_SHIFTED(THUMB_11_RD);
ISA_MASKED(THUMB_11_WORD8);

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
ISA_MASKED_SHIFTED(THUMB_12_RD);
ISA_MASKED(THUMB_12_WORD8);

///
/// Format 13 - Add offset to stack pointer
///

#define THUMB_13_S_SHIFT /*      */ 7
#define THUMB_13_S_MASK /*       */ (0x1u << THUMB_13_S_SHIFT)
#define THUMB_13_SWORD7_SHIFT /* */ 0
#define THUMB_13_SWORD7_MASK /*  */ 0x7fu

ISA_MASKED_BOOL(THUMB_13_S);
ISA_MASKED(THUMB_13_SWORD7);

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
ISA_MASKED_SHIFTED(THUMB_14_R);
ISA_MASKED(THUMB_14_RLIST);

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
ISA_MASKED_SHIFTED(THUMB_15_RB);
ISA_MASKED(THUMB_15_RLIST);

///
/// Format 16 - Conditional branch
///

#define THUMB_16_COND_SHIFT /*     */ THUMB_12_RD_SHIFT
#define THUMB_16_COND_MASK /*      */ (0xfu << THUMB_16_COND_SHIFT)
#define THUMB_16_SOFTSET8_SHIFT /* */ THUMB_12_WORD8_SHIFT
#define THUMB_16_SOFTSET8_MASK /*  */ THUMB_12_WORD8_MASK

ISA_MASKED_SHIFTED(THUMB_16_COND);
ISA_MASKED(THUMB_16_SOFTSET8);

///
/// Format 17 - Software interrupt
///

#define THUMB_17_VALUE8_SHIFT /* */ 0
#define THUMB_17_VALUE8_MASK /*  */ 0xffu

ISA_MASKED(THUMB_17_VALUE8);

///
/// Format 18 - Unconditional branch
///

#define THUMB_18_OFFSET11_SHIFT /* */ 0
#define THUMB_18_OFFSET11_MASK /*  */ 0x7ffu

ISA_MASKED(THUMB_18_OFFSET11);

///
/// Format 19 - Long branch with link
///

#define THUMB_19_H_SHIFT /*     */ THUMB_15_L_SHIFT
#define THUMB_19_H_MASK /*      */ THUMB_15_L_MASK
#define THUMB_19_OFFSET_SHIFT /* */ THUMB_18_OFFSET11_SHIFT
#define THUMB_19_OFFSET_MASK /*  */ THUMB_18_OFFSET11_MASK

ISA_MASKED_BOOL(THUMB_19_H);
ISA_MASKED(THUMB_19_OFFSET);
