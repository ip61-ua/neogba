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

/// ARM
using ISA_ARM_COND = IsaFieldDelayed<u32, u8, 28>;

enum ARMConditions : u8 {
  EQ = 0b0000,
  NE = 0b0001,
  HSCS = 0b0010,
  LOCC = 0b0011,
  MI = 0b0100,
  PL = 0b0101,
  VS = 0b0110,
  VC = 0b0111,
  HI = 0b1000,
  LS = 0b1001,
  GE = 0b1010,
  LT = 0b1011,
  GT = 0b1100,
  LE = 0b1101,
  AL = 0b1110,
  NV = 0b1111,
};

/// Data processing and FSR transfer
constexpr u32 ARM_FSR_TEMPLATE{0x02000000u};
using ARM_FSR_OPCODE = /*        */ IsaFieldDelayed<u32, u8, 21>;
using ARM_FSR_S = /*             */ IsaFieldBool<u32, 20>;
using ARM_FSR_RN = /*            */ IsaFieldDelayed<u32, u8, 16>;
using ARM_FSR_RD = /*            */ IsaFieldDelayed<u32, u8, 12>;
using ARM_FSR_OPERAND2 = /*      */ IsaField<u32, u16, 0, ((1u << 12) - 1)>;

/// Multiply
constexpr u32 ARM_MULTIPLY_TEMPLATE{0x00000090u};
using ARM_MULTIPLY_A = /*              */ IsaFieldBool<u32, 21>;
using ARM_MULTIPLY_S = /*              */ ARM_FSR_S;
using ARM_MULTIPLY_RD = /*             */ ARM_FSR_RN;
using ARM_MULTIPLY_RN = /*             */ ARM_FSR_RD;
using ARM_MULTIPLY_RS = /*             */ IsaFieldDelayed<u32, u8, 8>;
using ARM_MULTIPLY_RM = /*             */ IsaFieldDelayed<u32, u8, 0>;

/// Multiply long
constexpr u32 ARM_LONG_TEMPLATE{0x00800090u};
using ARM_LONG_U = /*                  */ IsaFieldBool<u32, 22>;
using ARM_LONG_A = /*                  */ ARM_MULTIPLY_A;
using ARM_LONG_S = /*                  */ ARM_MULTIPLY_S;
using ARM_LONG_RDHI = /*               */ ARM_MULTIPLY_RD;
using ARM_LONG_RDLO = /*               */ ARM_MULTIPLY_RN;
using ARM_LONG_RN = /*                 */ ARM_MULTIPLY_RS;
using ARM_LONG_RM = /*                 */ ARM_MULTIPLY_RM;

/// Single data swap
constexpr u32 ARM_SWAP_TEMPLATE{0x01000090u};
using ARM_SWAP_B = /*                  */ ARM_LONG_U;
using ARM_SWAP_RN = /*                 */ ARM_FSR_RN;
using ARM_SWAP_RD = /*                 */ ARM_FSR_RD;
using ARM_SWAP_RM = /*                 */ ARM_MULTIPLY_RM;

/// Branch and Exchange
constexpr u32 ARM_EXCHANGE_TEMPLATE{0x012fff10u};
using ARM_EXCHANGE_RN = ARM_MULTIPLY_RM;

/// Halfword data transfer, register offset
constexpr u32 ARM_HALFREG_TEMPLATE{0x00000090u};
using ARM_HALFREG_P = /*               */ IsaFieldBool<u32, 24>;
using ARM_HALFREG_U = /*               */ IsaFieldBool<u32, 23>;
using ARM_HALFREG_W = /*               */ ARM_MULTIPLY_A;
using ARM_HALFREG_L = /*               */ ARM_FSR_S;
using ARM_HALFREG_RN = /*              */ ARM_FSR_RN;
using ARM_HALFREG_RD = /*              */ ARM_FSR_RD;
using ARM_HALFREG_S = /*               */ IsaFieldBool<u32, 6>;
using ARM_HALFREG_H = /*               */ IsaFieldBool<u32, 5>;
using ARM_HALFREG_RM = /*              */ ARM_MULTIPLY_RM;

/// Halfword data transfer, immediate offset
constexpr u32 ARM_HALFIMM_TEMPLATE{0x00400090u};
using ARM_HALFIMM_P = /*               */ ARM_HALFREG_P;
using ARM_HALFIMM_U = /*               */ ARM_HALFREG_U;
using ARM_HALFIMM_W = /*               */ ARM_MULTIPLY_A;
using ARM_HALFIMM_L = /*               */ ARM_FSR_S;
using ARM_HALFIMM_RN = /*              */ ARM_FSR_RN;
using ARM_HALFIMM_RD = /*              */ ARM_FSR_RD;
using ARM_HALFIMM_S = /*               */ ARM_HALFREG_S;
using ARM_HALFIMM_H = /*               */ ARM_HALFREG_H;
using ARM_HALFIMM_OFFSET =
    IsaFieldSplit<u32, u8, ARM_MULTIPLY_RS::shift, ARM_MULTIPLY_RS::mask,
                  ARM_MULTIPLY_RM::mask, 4>;

/// Single data transfer
constexpr u32 ARM_SINGLETRANS_TEMPLATE{0x06000000u};
using ARM_SINGLETRANS_P = /*           */ ARM_HALFIMM_P;
using ARM_SINGLETRANS_U = /*           */ ARM_HALFIMM_U;
using ARM_SINGLETRANS_B = /*           */ ARM_SWAP_B;
using ARM_SINGLETRANS_W = /*           */ ARM_HALFIMM_W;
using ARM_SINGLETRANS_L = /*           */ ARM_HALFIMM_L;
using ARM_SINGLETRANS_RN = /*          */ ARM_HALFIMM_RN;
using ARM_SINGLETRANS_RD = /*          */ ARM_HALFIMM_RD;
using ARM_SINGLETRANS_OFFSET = /*      */ ARM_FSR_OPERAND2;

/// Undefined
constexpr u32 ARM_UNDEFINED_TEMPLATE{0x06000010u};

/// Block data transfer
constexpr u32 ARM_BLOCKTRANS_TEMPLATE{0x09000000u};
using ARM_BLOCKTRANS_P = /*            */ ARM_HALFIMM_P;
using ARM_BLOCKTRANS_U = /*            */ ARM_HALFIMM_U;
using ARM_BLOCKTRANS_S = /*            */ ARM_SWAP_B;
using ARM_BLOCKTRANS_W = /*            */ ARM_HALFIMM_W;
using ARM_BLOCKTRANS_L = /*            */ ARM_HALFIMM_L;
using ARM_BLOCKTRANS_RN = /*           */ ARM_HALFIMM_RN;
using ARM_BLOCKTRANS_REGISTERLIST = /* */ IsaField<u32, u16, 0, 0xffffu>;

/// Branch
constexpr u32 ARM_BRANCH_TEMPLATE{0x0a000000u};
using ARM_BRANCH_L = /*                */ ARM_HALFIMM_P;
using ARM_BRANCH_OFFSET = /*           */ IsaField<u32, u32, 0, 0xffffffu>;

/// Coprocessor data transfer
constexpr u32 ARM_COPROCTRANS_P_TEMPLATE{0x0b000000u};
using ARM_COPROCTRANS_P = /*           */ ARM_HALFIMM_P;
using ARM_COPROCTRANS_U = /*           */ ARM_HALFIMM_U;
using ARM_COPROCTRANS_N = /*           */ ARM_SWAP_B;
using ARM_COPROCTRANS_W = /*           */ ARM_HALFIMM_W;
using ARM_COPROCTRANS_L = /*           */ ARM_HALFIMM_L;
using ARM_COPROCTRANS_RN = /*          */ ARM_HALFIMM_RN;
using ARM_COPROCTRANS_CRD = /*         */ ARM_FSR_RD;
using ARM_COPROCTRANS_CPSHARP = /*     */ ARM_MULTIPLY_RS;
using ARM_COPROCTRANS_OFFSET = /*      */ IsaField<u32, u8, 0, 0xffu>;

/// Coprocessor data operation
constexpr u32 ARM_COPROCOP_TEMPLATE{0x0e000000u};
using ARM_COPROCOP_CPOPC = /*          */ IsaFieldDelayed<u32, u8, 21>;
using ARM_COPROCOP_CRN = /*            */ ARM_HALFIMM_RN;
using ARM_COPROCOP_CRD = /*            */ ARM_FSR_RD;
using ARM_COPROCOP_CPSHARP = /*        */ ARM_MULTIPLY_RS;
using ARM_COPROCOP_CP = /*             */ IsaFieldDelayed<u32, u8, 5, 0x7u>;
using ARM_COPROCOP_CRM = /*            */ ARM_MULTIPLY_RM;

/// Coprocessor register transfer
constexpr u32 ARM_COPROCREGTRANS_TEMPLATE{0x0e000010u};
using ARM_COPROCREGTRANS_CPOPC = /*    */ IsaFieldDelayed<u32, u8, 21, 0x7u>;
using ARM_COPROCREGTRANS_L = /*        */ ARM_SINGLETRANS_L;
using ARM_COPROCREGTRANS_CRN = /*      */ ARM_COPROCOP_CRN;
using ARM_COPROCREGTRANS_RD = /*       */ ARM_COPROCOP_CRD;
using ARM_COPROCREGTRANS_CPSHARP = /*  */ ARM_COPROCOP_CPSHARP;
using ARM_COPROCREGTRANS_CP = /*       */ ARM_COPROCOP_CP;
using ARM_COPROCREGTRANS_CRM = /*      */ ARM_COPROCOP_CRM;

/// Software interrupt
constexpr u32 ARM_SWINT_TEMPLATE{0x0f000000u};
using ARM_SWINT_SWI = /**/ IsaField<u32, u32, 0, 0xffffffu>;

/// Thumb

/// Format 01 - Move shifted register
constexpr u16 THUMB_01_TEMPLATE{0x0000u};
using THUMB_01_OP = /*             */ IsaFieldDelayed<u16, u8, 11, 0x3u>;
using THUMB_01_OFFSET5 = /*        */ IsaFieldDelayed<u16, u8, 6, 0x1fu>;
using THUMB_01_RS = /*             */ IsaFieldDelayed<u16, u8, 3, 0x7u>;
using THUMB_01_RD = /*             */ IsaField<u16, u8, 0, 0x7u>;

/// Format 02 - Add and substract
constexpr u16 THUMB_02_TEMPLATE{0x1c00u};
using THUMB_02_OP = /*             */ IsaFieldBool<u16, 9>;
using THUMB_02_RNOFFSET3 = /*      */ IsaFieldDelayed<u16, u8, 6, 0x7u>;
using THUMB_02_RS = /*             */ THUMB_01_RS;
using THUMB_02_RD = /*             */ THUMB_01_RD;

/// Format 03 - Move, compare, add, and subtract immediate
constexpr u16 THUMB_03_TEMPLATE{0x2000u};
using THUMB_03_OP = /*             */ THUMB_01_OP;
using THUMB_03_RD = /*             */ IsaFieldDelayed<u16, u8, 8, 0x7u>;
using THUMB_03_OFFSET8 = /*        */ IsaField<u16, u8, 0, 0xffu>;

/// Format 04 - ALU operation
constexpr u16 THUMB_04_TEMPLATE{0x4000u};
using THUMB_04_OP = /*             */ IsaFieldDelayed<u16, u8, 6, 0xfu>;
using THUMB_04_RS = /*             */ THUMB_01_RS;
using THUMB_04_RD = /*             */ THUMB_01_RD;

/// Format 05 - High register operations and branch exchange
constexpr u16 THUMB_05_TEMPLATE{0x4400u};
using THUMB_05_OP = /*             */ IsaFieldDelayed<u16, u8, 8, 0x7u>;
using THUMB_05_H1 = /*             */ IsaFieldBool<u16, 7>;
using THUMB_05_H2 = /*             */ IsaFieldBool<u16, 6>;
using THUMB_05_RSHS = /*           */ THUMB_01_RS;
using THUMB_05_RDHD = /*           */ THUMB_01_RD;

/// Format 06 - PC-relative load
constexpr u16 THUMB_06_TEMPLATE{0x4800u};
using THUMB_06_RD = /*             */ THUMB_03_RD;
using THUMB_06_WORD8 = /*          */ IsaField<u16, u8, 0, 0xffu>;

/// Format 07 - Load and store with relative offset
constexpr u16 THUMB_07_TEMPLATE{0x5000u};
using THUMB_07_L = /*              */ IsaFieldBool<u16, 11>;
using THUMB_07_B = /*              */ IsaFieldBool<u16, 10>;
using THUMB_07_RO = /*             */ THUMB_02_RNOFFSET3;
using THUMB_07_RB = /*             */ THUMB_01_RS;
using THUMB_07_RD = /*             */ THUMB_01_RD;

/// Format 08 - Load and store sign-extended byte and halfword
constexpr u16 THUMB_08_TEMPLATE{0x5200u};
using THUMB_08_H = /*              */ THUMB_07_L;
using THUMB_08_S = /*              */ THUMB_07_B;
using THUMB_08_RO = /*             */ THUMB_07_RO;
using THUMB_08_RB = /*             */ THUMB_07_RB;
using THUMB_08_RD = /*             */ THUMB_07_RD;

/// Format 09 - Load and store with immediate offset
constexpr u16 THUMB_09_TEMPLATE{0x6000u};
using THUMB_09_B = /*              */ IsaFieldBool<u16, 12>;
using THUMB_09_L = /*              */ THUMB_07_L;
using THUMB_09_OFFSET5 = /*        */ THUMB_01_OFFSET5;
using THUMB_09_RB = /*             */ THUMB_01_RS;
using THUMB_09_RD = /*             */ THUMB_01_RD;

/// Format 10 - Load and store halfword
constexpr u16 THUMB_10_TEMPLATE{0x8000u};
using THUMB_10_L = /*              */ THUMB_09_L;
using THUMB_10_OFFSET5 = /*        */ THUMB_01_OFFSET5;
using THUMB_10_RB = /*             */ THUMB_01_RS;
using THUMB_10_RD = /*             */ THUMB_01_RD;

/// Format 11 - SP-relative load and store
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
