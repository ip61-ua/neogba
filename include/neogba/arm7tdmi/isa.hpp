#pragma once
#include "neogba/types.hpp"

namespace neogba {

namespace {

template <typename instruction_t, typename return_t, u8 n_shift,
          instruction_t bit_mask>
struct IsaField {
  using ins_t = instruction_t;
  using ret_t = return_t;
  static constexpr u8 shift = n_shift;
  static constexpr ins_t mask = bit_mask;

  [[nodiscard]] static inline constexpr ret_t get(ins_t instruction) {
    return static_cast<ret_t>(((instruction) & (mask)) >> shift);
  }

  [[nodiscard]] static inline constexpr ins_t set(ins_t instruction,
                                                  ret_t value) {
    return ((instruction) & (~mask)) | ((value << shift) & mask);
  }
};

template <typename instruction_t, typename return_t, u8 n_shift,
          instruction_t base_mask = 0xfu>
struct IsaFieldDelayed
    : IsaField<instruction_t, bool, n_shift, (base_mask << n_shift)> {};

template <typename instruction_t, u8 n_shift>
struct IsaFieldBool : IsaField<instruction_t, bool, n_shift, (1u << n_shift)> {
  [[nodiscard]] static constexpr bool get(IsaFieldBool::ins_t instruction) {
    return (instruction & IsaFieldBool::mask) != 0;
  }

  [[nodiscard]] static constexpr IsaFieldBool::ins_t
  set(IsaFieldBool::ins_t instruction, bool value) {
    return ((instruction) & (~IsaFieldBool::mask)) |
           (value ? IsaFieldBool::mask : 0);
  }

  [[nodiscard]] static constexpr IsaFieldBool::ins_t
  set0(IsaFieldBool::ins_t instruction) {
    return instruction & ~IsaFieldBool::mask;
  }

  [[nodiscard]] static constexpr IsaFieldBool::inst
  set1(IsaFieldBool::inst instruction) {
    return instruction | IsaFieldBool::mask;
  }

  [[nodiscard]] static constexpr IsaFieldBool::inst
  toggle(IsaFieldBool::inst instruction) {
    return instruction ^ IsaFieldBool::mask;
  }
};

template <typename instruction_t, typename return_t, u8 n_shift,
          instruction_t bit_mask, instruction_t bit_mask2, u8 join_shift>
struct IsaFieldSplit : IsaField<instruction_t, return_t, n_shift, bit_mask> {
  static constexpr u8 join = join_shift;
  static constexpr instruction_t mask2 = bit_mask2;

  [[nodiscard]] static constexpr IsaFieldSplit::ret_t
  get(IsaFieldSplit::ins_t instruction) {
    return static_cast<IsaFieldSplit::ret_t>(
        ((instruction & IsaFieldSplit::mask) >> join) | (instruction & mask2));
  }

  [[nodiscard]] static constexpr IsaFieldSplit::ins_t
  set(IsaFieldSplit::ins_t instruction, IsaFieldSplit::ret_t value) {
    auto val = static_cast<IsaFieldSplit::ins_t>(value);
    return (instruction & ~(IsaFieldSplit::mask | mask2)) | ((val) & (mask2)) |
           ((val << join) & IsaFieldSplit::mask);
  }
};
} // namespace

///
/// ARM
///

using ISA_ARM_COND = IsaField<u32, u8, 28, 0xf0000000u>;

#define ARM_COND_EQ 0000
#define ARM_COND_NE 0001
#define ARM_COND_HSCS 0010
#define ARM_COND_LOCC 0011
#define ARM_COND_MI 0100
#define ARM_COND_PL 0101
#define ARM_COND_VS 0110
#define ARM_COND_VC 0111
#define ARM_COND_HI 1000
#define ARM_COND_LS 1001
#define ARM_COND_GE 1010
#define ARM_COND_LT 1011
#define ARM_COND_GT 1100
#define ARM_COND_LE 1101
#define ARM_COND_AL 1110
#define ARM_COND_NV 1111

///
/// Data processing and FSR transfer
///

#define ARM_FSR_TEMPLATE /**/ 0x02000000u
using ARM_FSR_OPCODE = /*  */ IsaFieldDelayed<u32, u8, 21>;
using ARM_FSR_S = /*       */ IsaFieldBool<u32, 20>;
using ARM_FSR_RN = /*      */ IsaFieldDelayed<u32, u8, 16>;
using ARM_FSR_RD = /*      */ IsaFieldDelayed<u32, u8, 12>;
using ARM_FSR_OPERAND2 = /**/ IsaField<u32, u16, 0, ((1u << 12) - 1)>;

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

NEOGBA_ISA_MASKED_BOOL(ARM_MULTIPLY_A);
NEOGBA_ISA_MASKED_BOOL(ARM_MULTIPLY_S);
NEOGBA_ISA_MASKED_SHIFTED(ARM_MULTIPLY_RD);
NEOGBA_ISA_MASKED_SHIFTED(ARM_MULTIPLY_RN);
NEOGBA_ISA_MASKED_SHIFTED(ARM_MULTIPLY_RS);
NEOGBA_ISA_MASKED(ARM_MULTIPLY_RM);

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

NEOGBA_ISA_MASKED_BOOL(ARM_LONG_U);
NEOGBA_ISA_MASKED_BOOL(ARM_LONG_A);
NEOGBA_ISA_MASKED_BOOL(ARM_LONG_S);
NEOGBA_ISA_MASKED_SHIFTED(ARM_LONG_RDHI);
NEOGBA_ISA_MASKED_SHIFTED(ARM_LONG_RDLO);
NEOGBA_ISA_MASKED_SHIFTED(ARM_LONG_RN);
NEOGBA_ISA_MASKED(ARM_LONG_RM);

///
/// Single data swap
///

#define ARM_SWAP_TEMPLATE 0x01000090u
#define ARM_SWAP_B /*  */ ARM_LONG_U
#define ARM_SWAP_RN /* */ ARM_FSR_RN
#define ARM_SWAP_RD /* */ ARM_FSR_RD
#define ARM_SWAP_RM /* */ ARM_MULTIPLY_RM

NEOGBA_ISA_MASKED_BOOL(ARM_SWAP_B);
NEOGBA_ISA_MASKED_SHIFTED(ARM_SWAP_RN);
NEOGBA_ISA_MASKED_SHIFTED(ARM_SWAP_RD);
NEOGBA_ISA_MASKED(ARM_SWAP_RM);

///
/// Branch and Exchange
///

#define ARM_EXCHANGE_TEMPLATE 0x012fff10u
#define ARM_EXCHANGE_RN /* */ ARM_MULTIPLY_RM

NEOGBA_ISA_MASKED(ARM_EXCHANGE_RN);

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

NEOGBA_ISA_MASKED_BOOL(ARM_HALFREG_P);
NEOGBA_ISA_MASKED_BOOL(ARM_HALFREG_U);
NEOGBA_ISA_MASKED_BOOL(ARM_HALFREG_W);
NEOGBA_ISA_MASKED_BOOL(ARM_HALFREG_L);
NEOGBA_ISA_MASKED_SHIFTED(ARM_HALFREG_RN);
NEOGBA_ISA_MASKED_SHIFTED(ARM_HALFREG_RD);
NEOGBA_ISA_MASKED_BOOL(ARM_HALFREG_S);
NEOGBA_ISA_MASKED_BOOL(ARM_HALFREG_H);
NEOGBA_ISA_MASKED(ARM_HALFREG_RM);

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
#define ARM_HALFIMM_OFFSET                                                     \
  ARM_MULTIPLY_RS, NEOGBA_ISA_GET_MASK(ARM_MULTIPLY_RM), 4

NEOGBA_ISA_MASKED_BOOL(ARM_HALFIMM_P);
NEOGBA_ISA_MASKED_BOOL(ARM_HALFIMM_U);
NEOGBA_ISA_MASKED_BOOL(ARM_HALFIMM_W);
NEOGBA_ISA_MASKED_BOOL(ARM_HALFIMM_L);
NEOGBA_ISA_MASKED_SHIFTED(ARM_HALFIMM_RN);
NEOGBA_ISA_MASKED_SHIFTED(ARM_HALFIMM_RD);
NEOGBA_ISA_SPLIT_OFFSET(ARM_HALFIMM_OFFSET);
NEOGBA_ISA_MASKED_BOOL(ARM_HALFIMM_S);
NEOGBA_ISA_MASKED_BOOL(ARM_HALFIMM_H);

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

NEOGBA_ISA_MASKED_BOOL(ARM_SINGLETRANS_P);
NEOGBA_ISA_MASKED_BOOL(ARM_SINGLETRANS_U);
NEOGBA_ISA_MASKED_BOOL(ARM_SINGLETRANS_B);
NEOGBA_ISA_MASKED_BOOL(ARM_SINGLETRANS_W);
NEOGBA_ISA_MASKED_BOOL(ARM_SINGLETRANS_L);
NEOGBA_ISA_MASKED_SHIFTED(ARM_SINGLETRANS_RN);
NEOGBA_ISA_MASKED_SHIFTED(ARM_SINGLETRANS_RD);
NEOGBA_ISA_MASKED(ARM_SINGLETRANS_OFFSET);

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

NEOGBA_ISA_MASKED_BOOL(ARM_BLOCKTRANS_P);
NEOGBA_ISA_MASKED_BOOL(ARM_BLOCKTRANS_U);
NEOGBA_ISA_MASKED_BOOL(ARM_BLOCKTRANS_S);
NEOGBA_ISA_MASKED_BOOL(ARM_BLOCKTRANS_W);
NEOGBA_ISA_MASKED_BOOL(ARM_BLOCKTRANS_L);
NEOGBA_ISA_MASKED_SHIFTED(ARM_BLOCKTRANS_RN);
NEOGBA_ISA_MASKED(ARM_BLOCKTRANS_REGISTERLIST);

///
/// Branch
///

#define ARM_BRANCH_TEMPLATE /**/ 0x0a000000u
#define ARM_BRANCH_L /*       */ ARM_HALFIMM_P
#define ARM_BRANCH_OFFSET /*  */ u32, u32, 0, 0xffffffu

NEOGBA_ISA_MASKED_BOOL(ARM_BRANCH_L);
NEOGBA_ISA_MASKED(ARM_BRANCH_OFFSET);

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

NEOGBA_ISA_MASKED_BOOL(ARM_COPROCTRANS_P);
NEOGBA_ISA_MASKED_BOOL(ARM_COPROCTRANS_U);
NEOGBA_ISA_MASKED_BOOL(ARM_COPROCTRANS_N);
NEOGBA_ISA_MASKED_BOOL(ARM_COPROCTRANS_W);
NEOGBA_ISA_MASKED_BOOL(ARM_COPROCTRANS_L);
NEOGBA_ISA_MASKED_SHIFTED(ARM_COPROCTRANS_RN);
NEOGBA_ISA_MASKED_SHIFTED(ARM_COPROCTRANS_CRD);
NEOGBA_ISA_MASKED_SHIFTED(ARM_COPROCTRANS_CPSHARP);
NEOGBA_ISA_MASKED(ARM_COPROCTRANS_OFFSET);

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

NEOGBA_ISA_MASKED_SHIFTED(ARM_COPROCOP_CPOPC);
NEOGBA_ISA_MASKED_SHIFTED(ARM_COPROCOP_CRN);
NEOGBA_ISA_MASKED_SHIFTED(ARM_COPROCOP_CRD);
NEOGBA_ISA_MASKED_SHIFTED(ARM_COPROCOP_CPSHARP);
NEOGBA_ISA_MASKED_SHIFTED(ARM_COPROCOP_CP);
NEOGBA_ISA_MASKED(ARM_COPROCOP_CRM);

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

NEOGBA_ISA_MASKED_SHIFTED(ARM_COPROCREGTRANS_CPOPC);
NEOGBA_ISA_MASKED_BOOL(ARM_COPROCREGTRANS_L);
NEOGBA_ISA_MASKED_SHIFTED(ARM_COPROCREGTRANS_CRN);
NEOGBA_ISA_MASKED_SHIFTED(ARM_COPROCREGTRANS_RD);
NEOGBA_ISA_MASKED_SHIFTED(ARM_COPROCREGTRANS_CPSHARP);
NEOGBA_ISA_MASKED_SHIFTED(ARM_COPROCREGTRANS_CP);
NEOGBA_ISA_MASKED(ARM_COPROCREGTRANS_CRM);

///
/// Software interrupt
///

#define ARM_SWINT_TEMPLATE 0x0f000000
#define ARM_SWINT_SWI /**/ u32, u32, 0, 0xffffffu

NEOGBA_ISA_MASKED(ARM_SWINT_SWI);

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

NEOGBA_ISA_MASKED_SHIFTED(THUMB_01_OP);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_01_OFFSET5);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_01_RS);
NEOGBA_ISA_MASKED(THUMB_01_RD);

///
/// Format 02 - Add and substract
///

#define THUMB_02_TEMPLATE /* */ 0x1c00u
#define THUMB_02_OP /*       */ u16, bool, 9, (1u << 9)
#define THUMB_02_RNOFFSET3 /**/ u16, u8, 6, (0x7u << 6)
#define THUMB_02_RS /*       */ THUMB_01_RS
#define THUMB_02_RD /*       */ THUMB_01_RD

NEOGBA_ISA_MASKED_BOOL(THUMB_02_OP);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_02_RNOFFSET3);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_02_RS);
NEOGBA_ISA_MASKED(THUMB_02_RD);

///
/// Format 03 - Move, compare, add, and subtract immediate
///

#define THUMB_03_TEMPLATE /**/ 0x2000u
#define THUMB_03_OP /*      */ THUMB_01_OP
#define THUMB_03_RD /*      */ u16, u8, 8, (0x7u << 8)
#define THUMB_03_OFFSET8 /* */ u16, u8, 0, 0xffu

NEOGBA_ISA_MASKED_SHIFTED(THUMB_03_OP);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_03_RD);
NEOGBA_ISA_MASKED(THUMB_03_OFFSET8);

///
/// Format 04 - ALU operation
///

#define THUMB_04_TEMPLATE /**/ 0x4000u
#define THUMB_04_OP /*      */ u16, u8, 6, (0xfu << 6)
#define THUMB_04_RS /*      */ THUMB_01_RS
#define THUMB_04_RD /*      */ THUMB_01_RD

NEOGBA_ISA_MASKED_SHIFTED(THUMB_04_OP);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_04_RS);
NEOGBA_ISA_MASKED(THUMB_04_RD);

///
/// Format 05 - High register operations and branch exchange
///

#define THUMB_05_TEMPLATE /**/ 0x4400u
#define THUMB_05_OP /*      */ u16, u8, 8, (0x7u << 8)
#define THUMB_05_H1 /*      */ u16, bool, 7, (1u << 7)
#define THUMB_05_H2 /*      */ u16, bool, 6, (1u << 6)
#define THUMB_05_RSHS /*    */ THUMB_01_RS
#define THUMB_05_RDHD /*    */ THUMB_01_RD

NEOGBA_ISA_MASKED_SHIFTED(THUMB_05_OP);
NEOGBA_ISA_MASKED_BOOL(THUMB_05_H1);
NEOGBA_ISA_MASKED_BOOL(THUMB_05_H2);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_05_RSHS);
NEOGBA_ISA_MASKED(THUMB_05_RDHD);

///
/// Format 06 - PC-relative load
///

#define THUMB_06_TEMPLATE /**/ 0x4800u
#define THUMB_06_RD /*      */ THUMB_03_RD
#define THUMB_06_WORD8 /*   */ u16, u8, 0, 0xffu

NEOGBA_ISA_MASKED_SHIFTED(THUMB_06_RD);
NEOGBA_ISA_MASKED(THUMB_06_WORD8);

///
/// Format 07 - Load and store with relative offset
///

#define THUMB_07_TEMPLATE 0x5000u
#define THUMB_07_L /*  */ u16, bool, 11, (1u << 11)
#define THUMB_07_B /*  */ u16, bool, 10, (1u << 10)
#define THUMB_07_RO /* */ THUMB_02_RNOFFSET3
#define THUMB_07_RB /* */ THUMB_01_RS
#define THUMB_07_RD /* */ THUMB_01_RD

NEOGBA_ISA_MASKED_BOOL(THUMB_07_L);
NEOGBA_ISA_MASKED_BOOL(THUMB_07_B);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_07_RO);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_07_RB);
NEOGBA_ISA_MASKED(THUMB_07_RD);

///
/// Format 08 - Load and store sign-extended byte and halfword
///

#define THUMB_08_TEMPLATE 0x5200u
#define THUMB_08_H /*  */ THUMB_07_L
#define THUMB_08_S /*  */ THUMB_07_B
#define THUMB_08_RO /* */ THUMB_07_RO
#define THUMB_08_RB /* */ THUMB_07_RB
#define THUMB_08_RD /* */ THUMB_07_RD

NEOGBA_ISA_MASKED_BOOL(THUMB_08_H);
NEOGBA_ISA_MASKED_BOOL(THUMB_08_S);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_08_RO);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_08_RB);
NEOGBA_ISA_MASKED(THUMB_08_RD);

///
/// Format 09 - Load and store with immediate offset
///

#define THUMB_09_TEMPLATE /**/ 0x6000u
#define THUMB_09_B /*       */ u16, bool, 12, (1u << 12)
#define THUMB_09_L /*       */ THUMB_07_L
#define THUMB_09_OFFSET5 /* */ THUMB_01_OFFSET5
#define THUMB_09_RB /*      */ THUMB_01_RS
#define THUMB_09_RD /*      */ THUMB_01_RD

NEOGBA_ISA_MASKED_BOOL(THUMB_09_B);
NEOGBA_ISA_MASKED_BOOL(THUMB_09_L);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_09_OFFSET5);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_09_RB);
NEOGBA_ISA_MASKED(THUMB_09_RD);

///
/// Format 10 - Load and store halfword
///

#define THUMB_10_TEMPLATE /**/ 0x8000u
#define THUMB_10_L /*       */ THUMB_09_L
#define THUMB_10_OFFSET5 /* */ THUMB_01_OFFSET5
#define THUMB_10_RB /*      */ THUMB_01_RS
#define THUMB_10_RD /*      */ THUMB_01_RD

NEOGBA_ISA_MASKED_BOOL(THUMB_10_L);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_10_OFFSET5);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_10_RB);
NEOGBA_ISA_MASKED(THUMB_10_RD);

///
/// Format 11 - SP-relative load and store
///

#define THUMB_11_TEMPLATE /**/ 0x9000u
#define THUMB_11_L /*       */ THUMB_10_L
#define THUMB_11_RD /*      */ THUMB_06_RD
#define THUMB_11_WORD8 /*   */ THUMB_06_WORD8

NEOGBA_ISA_MASKED_BOOL(THUMB_11_L);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_11_RD);
NEOGBA_ISA_MASKED(THUMB_11_WORD8);

///
/// Format 12 - Load address
///

#define THUMB_12_TEMPLATE /**/ 0xa000u
#define THUMB_12_SP /*      */ THUMB_11_L
#define THUMB_12_RD /*      */ THUMB_11_RD
#define THUMB_12_WORD8 /*   */ THUMB_11_WORD8

NEOGBA_ISA_MASKED_BOOL(THUMB_12_SP);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_12_RD);
NEOGBA_ISA_MASKED(THUMB_12_WORD8);

///
/// Format 13 - Add offset to stack pointer
///

#define THUMB_13_TEMPLATE /**/ 0xb000u
#define THUMB_13_S /*       */ u16, bool, 7, (1u << 7)
#define THUMB_13_SWORD7 /*  */ u16, u8, 0, 0x7fu

NEOGBA_ISA_MASKED_BOOL(THUMB_13_S);
NEOGBA_ISA_MASKED(THUMB_13_SWORD7);

///
/// Format 14 - Push and pop registers
///

#define THUMB_14_TEMPLATE /**/ 0xb400u
#define THUMB_14_L /*       */ THUMB_11_L
#define THUMB_14_R /*       */ u16, u8, 8, (1u << 8)
#define THUMB_14_RLIST /*   */ THUMB_11_WORD8

NEOGBA_ISA_MASKED_BOOL(THUMB_14_L);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_14_R);
NEOGBA_ISA_MASKED(THUMB_14_RLIST);

///
/// Format 15 - Multiple load and store
///

#define THUMB_15_TEMPLATE /**/ 0xc000u
#define THUMB_15_L /*       */ THUMB_12_SP
#define THUMB_15_RB /*      */ THUMB_12_RD
#define THUMB_15_RLIST /*   */ THUMB_12_WORD8

NEOGBA_ISA_MASKED_BOOL(THUMB_15_L);
NEOGBA_ISA_MASKED_SHIFTED(THUMB_15_RB);
NEOGBA_ISA_MASKED(THUMB_15_RLIST);

///
/// Format 16 - Conditional branch
///

#define THUMB_16_TEMPLATE /**/ 0xd000u
#define THUMB_16_COND /*    */ u16, u8, 8, (0xfu << 8)
#define THUMB_16_SOFTSET8 /**/ THUMB_12_WORD8

NEOGBA_ISA_MASKED_SHIFTED(THUMB_16_COND);
NEOGBA_ISA_MASKED(THUMB_16_SOFTSET8);

///
/// Format 17 - Software interrupt
///

#define THUMB_17_TEMPLATE /**/ 0xdf00u
#define THUMB_17_VALUE8 /*  */ u16, u8, 0, 0xffu

NEOGBA_ISA_MASKED(THUMB_17_VALUE8);

///
/// Format 18 - Unconditional branch
///

#define THUMB_18_TEMPLATE 0xe000u
#define THUMB_18_OFFSET11 u16, u16, 0, 0x7ffu

NEOGBA_ISA_MASKED(THUMB_18_OFFSET11);

///
/// Format 19 - Long branch with link
///

#define THUMB_19_TEMPLATE /**/ 0xf000u
#define THUMB_19_H /*       */ THUMB_15_L
#define THUMB_19_OFFSET /*  */ THUMB_18_OFFSET11

NEOGBA_ISA_MASKED_BOOL(THUMB_19_H);
NEOGBA_ISA_MASKED(THUMB_19_OFFSET);

} // namespace neogba
