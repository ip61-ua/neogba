#pragma once
#include "neogba/types.hpp"

namespace neogba {

namespace {
template <typename instruction_t, typename return_t, u8 n_shift, instruction_t bit_mask>
struct isa_field {
  using ins_t = instruction_t;
  using ret_t = return_t;
  static constexpr u8 shift = n_shift;
  static constexpr ins_t mask = bit_mask;

  [[nodiscard]] static inline constexpr ret_t get(ins_t instruction) {
    return static_cast<ret_t>(((instruction) & (mask)) >> shift);
  }

  [[nodiscard]] static inline constexpr ins_t set(ins_t instruction, ret_t value) {
    return ((instruction) & (~mask)) | ((value << shift) & mask);
  }
};

template <typename instruction_t, typename return_t, u8 n_shift, instruction_t base_mask = 0xfu>
struct isa_field_delayed : isa_field<instruction_t, bool, n_shift, (base_mask << n_shift)> {};

template <typename instruction_t, u8 n_shift>
struct isa_field_bool : isa_field<instruction_t, bool, n_shift, (1u << n_shift)> {
  [[nodiscard]] static constexpr bool get(isa_field_bool::ins_t instruction) {
    return (instruction & isa_field_bool::mask) != 0;
  }

  [[nodiscard]] static constexpr isa_field_bool::ins_t set(isa_field_bool::ins_t instruction,
                                                           bool value) {
    return ((instruction) & (~isa_field_bool::mask)) | (value ? isa_field_bool::mask : 0);
  }

  [[nodiscard]] static constexpr isa_field_bool::ins_t set0(isa_field_bool::ins_t instruction) {
    return instruction & ~isa_field_bool::mask;
  }

  [[nodiscard]] static constexpr isa_field_bool::ins_t set1(isa_field_bool::ins_t instruction) {
    return instruction | isa_field_bool::mask;
  }

  [[nodiscard]] static constexpr isa_field_bool::ins_t toggle(isa_field_bool::ins_t instruction) {
    return instruction ^ isa_field_bool::mask;
  }
};

template <typename instruction_t, typename return_t, u8 n_shift, instruction_t bit_mask,
          instruction_t bit_mask2, u8 join_shift>
struct isa_fieldSplit : isa_field<instruction_t, return_t, n_shift, bit_mask> {
  static constexpr u8 join = join_shift;
  static constexpr instruction_t mask2 = bit_mask2;

  [[nodiscard]] static constexpr isa_fieldSplit::ret_t get(isa_fieldSplit::ins_t instruction) {
    return static_cast<isa_fieldSplit::ret_t>(((instruction & isa_fieldSplit::mask) >> join) |
                                              (instruction & mask2));
  }

  [[nodiscard]] static constexpr isa_fieldSplit::ins_t set(isa_fieldSplit::ins_t instruction,
                                                           isa_fieldSplit::ret_t value) {
    auto val = static_cast<isa_fieldSplit::ins_t>(value);
    return (instruction & ~(isa_fieldSplit::mask | mask2)) | ((val) & (mask2)) |
           ((val << join) & isa_fieldSplit::mask);
  }
};
} // namespace

/// ARM
using ISA_ARM_COND = isa_field_delayed<u32, u8, 28>;

enum class arm_cond : u8 {
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
constexpr u32 ISA_ARM_FSR_TEMPLATE{0x02000000u};
using ISA_ARM_FSR_OPCODE = /*     */ isa_field_delayed<u32, u8, 21>;
using ISA_ARM_FSR_S = /*          */ isa_field_bool<u32, 20>;
using ISA_ARM_FSR_RN = /*         */ isa_field_delayed<u32, u8, 16>;
using ISA_ARM_FSR_RD = /*         */ isa_field_delayed<u32, u8, 12>;
using ISA_ARM_FSR_OPERAND2 = /*   */ isa_field<u32, u16, 0, ((1u << 12) - 1)>;

/// Multiply
constexpr u32 ISA_ARM_MULTIPLY_TEMPLATE{0x00000090u};
using ISA_ARM_MULTIPLY_A = /*              */ isa_field_bool<u32, 21>;
using ISA_ARM_MULTIPLY_S = /*              */ ISA_ARM_FSR_S;
using ISA_ARM_MULTIPLY_RD = /*             */ ISA_ARM_FSR_RN;
using ISA_ARM_MULTIPLY_RN = /*             */ ISA_ARM_FSR_RD;
using ISA_ARM_MULTIPLY_RS = /*             */ isa_field_delayed<u32, u8, 8>;
using ISA_ARM_MULTIPLY_RM = /*             */ isa_field_delayed<u32, u8, 0>;

/// Multiply long
constexpr u32 ISA_ARM_LONG_TEMPLATE{0x00800090u};
using ISA_ARM_LONG_U = /*                  */ isa_field_bool<u32, 22>;
using ISA_ARM_LONG_A = /*                  */ ISA_ARM_MULTIPLY_A;
using ISA_ARM_LONG_S = /*                  */ ISA_ARM_MULTIPLY_S;
using ISA_ARM_LONG_RDHI = /*               */ ISA_ARM_MULTIPLY_RD;
using ISA_ARM_LONG_RDLO = /*               */ ISA_ARM_MULTIPLY_RN;
using ISA_ARM_LONG_RN = /*                 */ ISA_ARM_MULTIPLY_RS;
using ISA_ARM_LONG_RM = /*                 */ ISA_ARM_MULTIPLY_RM;

/// Single data swap
constexpr u32 ISA_ARM_SWAP_TEMPLATE{0x01000090u};
using ISA_ARM_SWAP_B = /*                  */ ISA_ARM_LONG_U;
using ISA_ARM_SWAP_RN = /*                 */ ISA_ARM_FSR_RN;
using ISA_ARM_SWAP_RD = /*                 */ ISA_ARM_FSR_RD;
using ISA_ARM_SWAP_RM = /*                 */ ISA_ARM_MULTIPLY_RM;

/// Branch and Exchange
constexpr u32 ISA_ARM_EXCHANGE_TEMPLATE{0x012fff10u};
using ISA_ARM_EXCHANGE_RN = ISA_ARM_MULTIPLY_RM;

/// Halfword data transfer, register offset
constexpr u32 ISA_ARM_HALFREG_TEMPLATE{0x00000090u};
using ISA_ARM_HALFREG_P = /*               */ isa_field_bool<u32, 24>;
using ISA_ARM_HALFREG_U = /*               */ isa_field_bool<u32, 23>;
using ISA_ARM_HALFREG_W = /*               */ ISA_ARM_MULTIPLY_A;
using ISA_ARM_HALFREG_L = /*               */ ISA_ARM_FSR_S;
using ISA_ARM_HALFREG_RN = /*              */ ISA_ARM_FSR_RN;
using ISA_ARM_HALFREG_RD = /*              */ ISA_ARM_FSR_RD;
using ISA_ARM_HALFREG_S = /*               */ isa_field_bool<u32, 6>;
using ISA_ARM_HALFREG_H = /*               */ isa_field_bool<u32, 5>;
using ISA_ARM_HALFREG_RM = /*              */ ISA_ARM_MULTIPLY_RM;

/// Halfword data transfer, immediate offset
constexpr u32 ISA_ARM_HALFIMM_TEMPLATE{0x00400090u};
using ISA_ARM_HALFIMM_P = /*               */ ISA_ARM_HALFREG_P;
using ISA_ARM_HALFIMM_U = /*               */ ISA_ARM_HALFREG_U;
using ISA_ARM_HALFIMM_W = /*               */ ISA_ARM_MULTIPLY_A;
using ISA_ARM_HALFIMM_L = /*               */ ISA_ARM_FSR_S;
using ISA_ARM_HALFIMM_RN = /*              */ ISA_ARM_FSR_RN;
using ISA_ARM_HALFIMM_RD = /*              */ ISA_ARM_FSR_RD;
using ISA_ARM_HALFIMM_S = /*               */ ISA_ARM_HALFREG_S;
using ISA_ARM_HALFIMM_H = /*               */ ISA_ARM_HALFREG_H;
using ISA_ARM_HALFIMM_OFFSET =
    isa_fieldSplit<u32, u8, ISA_ARM_MULTIPLY_RS::shift, ISA_ARM_MULTIPLY_RS::mask,
                   ISA_ARM_MULTIPLY_RM::mask, 4>;

/// Single data transfer
constexpr u32 ISA_ARM_SINGLETRANS_TEMPLATE{0x06000000u};
using ISA_ARM_SINGLETRANS_P = /*           */ ISA_ARM_HALFIMM_P;
using ISA_ARM_SINGLETRANS_U = /*           */ ISA_ARM_HALFIMM_U;
using ISA_ARM_SINGLETRANS_B = /*           */ ISA_ARM_SWAP_B;
using ISA_ARM_SINGLETRANS_W = /*           */ ISA_ARM_HALFIMM_W;
using ISA_ARM_SINGLETRANS_L = /*           */ ISA_ARM_HALFIMM_L;
using ISA_ARM_SINGLETRANS_RN = /*          */ ISA_ARM_HALFIMM_RN;
using ISA_ARM_SINGLETRANS_RD = /*          */ ISA_ARM_HALFIMM_RD;
using ISA_ARM_SINGLETRANS_OFFSET = /*      */ ISA_ARM_FSR_OPERAND2;

/// Undefined
constexpr u32 ISA_ARM_UNDEFINED_TEMPLATE{0x06000010u};

/// Block data transfer
constexpr u32 ISA_ARM_BLOCKTRANS_TEMPLATE{0x09000000u};
using ISA_ARM_BLOCKTRANS_P = /*            */ ISA_ARM_HALFIMM_P;
using ISA_ARM_BLOCKTRANS_U = /*            */ ISA_ARM_HALFIMM_U;
using ISA_ARM_BLOCKTRANS_S = /*            */ ISA_ARM_SWAP_B;
using ISA_ARM_BLOCKTRANS_W = /*            */ ISA_ARM_HALFIMM_W;
using ISA_ARM_BLOCKTRANS_L = /*            */ ISA_ARM_HALFIMM_L;
using ISA_ARM_BLOCKTRANS_RN = /*           */ ISA_ARM_HALFIMM_RN;
using ISA_ARM_BLOCKTRANS_REGISTERLIST = /* */ isa_field<u32, u16, 0, 0xffffu>;

/// Branch
constexpr u32 ISA_ARM_BRANCH_TEMPLATE{0x0a000000u};
using ISA_ARM_BRANCH_L = /*                */ ISA_ARM_HALFIMM_P;
using ISA_ARM_BRANCH_OFFSET = /*           */ isa_field<u32, u32, 0, 0xffffffu>;

/// Coprocessor data transfer
constexpr u32 ISA_ARM_COPROCTRANS_P_TEMPLATE{0x0b000000u};
using ISA_ARM_COPROCTRANS_P = /*           */ ISA_ARM_HALFIMM_P;
using ISA_ARM_COPROCTRANS_U = /*           */ ISA_ARM_HALFIMM_U;
using ISA_ARM_COPROCTRANS_N = /*           */ ISA_ARM_SWAP_B;
using ISA_ARM_COPROCTRANS_W = /*           */ ISA_ARM_HALFIMM_W;
using ISA_ARM_COPROCTRANS_L = /*           */ ISA_ARM_HALFIMM_L;
using ISA_ARM_COPROCTRANS_RN = /*          */ ISA_ARM_HALFIMM_RN;
using ISA_ARM_COPROCTRANS_CRD = /*         */ ISA_ARM_FSR_RD;
using ISA_ARM_COPROCTRANS_CPSHARP = /*     */ ISA_ARM_MULTIPLY_RS;
using ISA_ARM_COPROCTRANS_OFFSET = /*      */ isa_field<u32, u8, 0, 0xffu>;

/// Coprocessor data operation
constexpr u32 ISA_ARM_COPROCOP_TEMPLATE{0x0e000000u};
using ISA_ARM_COPROCOP_CPOPC = /*     */ isa_field_delayed<u32, u8, 21>;
using ISA_ARM_COPROCOP_CRN = /*       */ ISA_ARM_HALFIMM_RN;
using ISA_ARM_COPROCOP_CRD = /*       */ ISA_ARM_FSR_RD;
using ISA_ARM_COPROCOP_CPSHARP = /*   */ ISA_ARM_MULTIPLY_RS;
using ISA_ARM_COPROCOP_CP = /*        */ isa_field_delayed<u32, u8, 5, 0x7u>;
using ISA_ARM_COPROCOP_CRM = /*       */ ISA_ARM_MULTIPLY_RM;

/// Coprocessor register transfer
constexpr u32 ISA_ARM_COPROCREGTRANS_TEMPLATE{0x0e000010u};
using ISA_ARM_COPROCREGTRANS_CPOPC = /* */ isa_field_delayed<u32, u8, 21, 0x7u>;
using ISA_ARM_COPROCREGTRANS_L = /*      */ ISA_ARM_SINGLETRANS_L;
using ISA_ARM_COPROCREGTRANS_CRN = /*    */ ISA_ARM_COPROCOP_CRN;
using ISA_ARM_COPROCREGTRANS_RD = /*     */ ISA_ARM_COPROCOP_CRD;
using ISA_ARM_COPROCREGTRANS_CPSHARP = /**/ ISA_ARM_COPROCOP_CPSHARP;
using ISA_ARM_COPROCREGTRANS_CP = /*     */ ISA_ARM_COPROCOP_CP;
using ISA_ARM_COPROCREGTRANS_CRM = /*    */ ISA_ARM_COPROCOP_CRM;

/// Software interrupt
constexpr u32 ISA_ARM_SWINT_TEMPLATE{0x0f000000u};
using ISA_ARM_SWINT_SWI = /*       */ isa_field<u32, u32, 0, 0xffffffu>;

/// Thumb

/// Format 01 - Move shifted register
constexpr u16 ISA_THUMB_01_TEMPLATE{0x0000u};
using ISA_THUMB_01_OP = /*             */ isa_field_delayed<u16, u8, 11, 0x3u>;
using ISA_THUMB_01_OFFSET5 = /*        */ isa_field_delayed<u16, u8, 6, 0x1fu>;
using ISA_THUMB_01_RS = /*             */ isa_field_delayed<u16, u8, 3, 0x7u>;
using ISA_THUMB_01_RD = /*             */ isa_field<u16, u8, 0, 0x7u>;

/// Format 02 - Add and substract
constexpr u16 ISA_THUMB_02_TEMPLATE{0x1c00u};
using ISA_THUMB_02_OP = /*             */ isa_field_bool<u16, 9>;
using ISA_THUMB_02_RNOFFSET3 = /*      */ isa_field_delayed<u16, u8, 6, 0x7u>;
using ISA_THUMB_02_RS = /*             */ ISA_THUMB_01_RS;
using ISA_THUMB_02_RD = /*             */ ISA_THUMB_01_RD;

/// Format 03 - Move, compare, add, and subtract immediate
constexpr u16 ISA_THUMB_03_TEMPLATE{0x2000u};
using ISA_THUMB_03_OP = /*             */ ISA_THUMB_01_OP;
using ISA_THUMB_03_RD = /*             */ isa_field_delayed<u16, u8, 8, 0x7u>;
using ISA_THUMB_03_OFFSET8 = /*        */ isa_field<u16, u8, 0, 0xffu>;

/// Format 04 - ALU operation
constexpr u16 ISA_THUMB_04_TEMPLATE{0x4000u};
using ISA_THUMB_04_OP = /*             */ isa_field_delayed<u16, u8, 6, 0xfu>;
using ISA_THUMB_04_RS = /*             */ ISA_THUMB_01_RS;
using ISA_THUMB_04_RD = /*             */ ISA_THUMB_01_RD;

/// Format 05 - High register operations and branch exchange
constexpr u16 ISA_THUMB_05_TEMPLATE{0x4400u};
using ISA_THUMB_05_OP = /*             */ isa_field_delayed<u16, u8, 8, 0x7u>;
using ISA_THUMB_05_H1 = /*             */ isa_field_bool<u16, 7>;
using ISA_THUMB_05_H2 = /*             */ isa_field_bool<u16, 6>;
using ISA_THUMB_05_RSHS = /*           */ ISA_THUMB_01_RS;
using ISA_THUMB_05_RDHD = /*           */ ISA_THUMB_01_RD;

/// Format 06 - PC-relative load
constexpr u16 ISA_THUMB_06_TEMPLATE{0x4800u};
using ISA_THUMB_06_RD = /*             */ ISA_THUMB_03_RD;
using ISA_THUMB_06_WORD8 = /*          */ isa_field<u16, u8, 0, 0xffu>;

/// Format 07 - Load and store with relative offset
constexpr u16 ISA_THUMB_07_TEMPLATE{0x5000u};
using ISA_THUMB_07_L = /*              */ isa_field_bool<u16, 11>;
using ISA_THUMB_07_B = /*              */ isa_field_bool<u16, 10>;
using ISA_THUMB_07_RO = /*             */ ISA_THUMB_02_RNOFFSET3;
using ISA_THUMB_07_RB = /*             */ ISA_THUMB_01_RS;
using ISA_THUMB_07_RD = /*             */ ISA_THUMB_01_RD;

/// Format 08 - Load and store sign-extended byte and halfword
constexpr u16 ISA_THUMB_08_TEMPLATE{0x5200u};
using ISA_THUMB_08_H = /*              */ ISA_THUMB_07_L;
using ISA_THUMB_08_S = /*              */ ISA_THUMB_07_B;
using ISA_THUMB_08_RO = /*             */ ISA_THUMB_07_RO;
using ISA_THUMB_08_RB = /*             */ ISA_THUMB_07_RB;
using ISA_THUMB_08_RD = /*             */ ISA_THUMB_07_RD;

/// Format 09 - Load and store with immediate offset
constexpr u16 ISA_THUMB_09_TEMPLATE{0x6000u};
using ISA_THUMB_09_B = /*              */ isa_field_bool<u16, 12>;
using ISA_THUMB_09_L = /*              */ ISA_THUMB_07_L;
using ISA_THUMB_09_OFFSET5 = /*        */ ISA_THUMB_01_OFFSET5;
using ISA_THUMB_09_RB = /*             */ ISA_THUMB_01_RS;
using ISA_THUMB_09_RD = /*             */ ISA_THUMB_01_RD;

/// Format 10 - Load and store halfword
constexpr u16 ISA_THUMB_10_TEMPLATE{0x8000u};
using ISA_THUMB_10_L = /*              */ ISA_THUMB_09_L;
using ISA_THUMB_10_OFFSET5 = /*        */ ISA_THUMB_01_OFFSET5;
using ISA_THUMB_10_RB = /*             */ ISA_THUMB_01_RS;
using ISA_THUMB_10_RD = /*             */ ISA_THUMB_01_RD;

/// Format 11 - SP-relative load and store
constexpr u16 ISA_THUMB_11_TEMPLATE{0x9000u};
using ISA_THUMB_11_L = /*              */ ISA_THUMB_10_L;
using ISA_THUMB_11_RD = /*             */ ISA_THUMB_06_RD;
using ISA_THUMB_11_WORD8 = /*          */ ISA_THUMB_06_WORD8;

/// Format 12 - Load address
constexpr u16 ISA_THUMB_12_TEMPLATE{0xa000u};
using ISA_THUMB_12_SP = /*             */ ISA_THUMB_11_L;
using ISA_THUMB_12_RD = /*             */ ISA_THUMB_11_RD;
using ISA_THUMB_12_WORD8 = /*          */ ISA_THUMB_11_WORD8;

/// Format 13 - Add offset to stack pointer
constexpr u16 ISA_THUMB_13_TEMPLATE{0xb000u};
using ISA_THUMB_13_S = /*              */ isa_field_bool<u16, 7>;
using ISA_THUMB_13_SWORD7 = /*         */ isa_field<u16, u8, 0, 0x7fu>;

/// Format 14 - Push and pop registers
constexpr u16 ISA_THUMB_14_TEMPLATE{0xb400u};
using ISA_THUMB_14_L = /*              */ ISA_THUMB_11_L;
using ISA_THUMB_14_R = /*              */ isa_field_bool<u16, 8>;
using ISA_THUMB_14_RLIST = /*          */ ISA_THUMB_11_WORD8;

/// Format 15 - Multiple load and store
constexpr u16 ISA_THUMB_15_TEMPLATE{0xc000u};
using ISA_THUMB_15_L = /*              */ ISA_THUMB_12_SP;
using ISA_THUMB_15_RB = /*             */ ISA_THUMB_12_RD;
using ISA_THUMB_15_RLIST = /*          */ ISA_THUMB_12_WORD8;

/// Format 16 - Conditional branch
constexpr u16 ISA_THUMB_16_TEMPLATE{0xd000u};
using ISA_THUMB_16_COND = /*           */ isa_field_delayed<u16, u8, 8>;
using ISA_THUMB_16_SOFTSET8 = /*       */ ISA_THUMB_12_WORD8;

/// Format 17 - Software interrupt
constexpr u16 ISA_THUMB_17_TEMPLATE{0xdf00u};
using ISA_THUMB_17_VALUE8 = /*         */ isa_field<u16, u8, 0, 0xffu>;

/// Format 18 - Unconditional branch
constexpr u16 ISA_THUMB_18_TEMPLATE{0xe000u};
using ISA_THUMB_18_OFFSET11 = /*       */ isa_field<u16, u16, 0, 0x7ffu>;

/// Format 19 - Long branch with link
constexpr u16 ISA_THUMB_19_TEMPLATE = {0xf000u};
using ISA_THUMB_19_H = /*              */ ISA_THUMB_15_L;
using ISA_THUMB_19_OFFSET = /*         */ ISA_THUMB_18_OFFSET11;

} // namespace neogba
