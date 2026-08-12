#pragma once
#include "neogba/fields.hpp"

namespace neogba {

/// ARM
namespace cond {
enum class cond_enum : u8 {
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
using ISA_ARM_COND = field_delayed<u32, u8, 28, 0xfu, cond_enum>;
} // namespace cond

/// Data processing and FSR transfer
namespace fsr {
enum class opcode_enum : u8 {
  AND = 0b0000,
  EOR = 0b0001,
  SUB = 0b0010,
  RSB = 0b0011,
  ADD = 0b0100,
  ADC = 0b0101,
  SBC = 0b0110,
  RSC = 0b0111,
  TST = 0b1000,
  TEQ = 0b1001,
  CMP = 0b1010,
  CMN = 0b1011,
  ORR = 0b1100,
  MOV = 0b1101,
  BIC = 0b1110,
  MVN = 0b1111,
};
constexpr u32 TEMPLATE{0x00000000u};
using I = /*         */ field_bool<u32, 25>;
using OPCODE = /*    */ field_delayed<u32, u8, 21, 0xfu, opcode_enum>;
using S = /*         */ field_bool<u32, 20>;
using RN = /*        */ field_delayed<u32, u8, 16>;
using RD = /*        */ field_delayed<u32, u8, 12>;
using OPERAND2 = /*  */ field<u32, u16, 0, ((1u << 12) - 1)>;
} // namespace fsr

namespace operand2 {
enum class shift_enum : u8 {
  LSL = 0b00,
  LSR = 0b01,
  ASR = 0b10,
  ROR = 0b11,
};
using SHIFT = /*     */ field_delayed<u32, u16, 4, 0xffu>;
using B4 = /*        */ field_bool<u32, 4>;
using SHIFT_TYPE = /**/ field_delayed<u32, u8, 5, 0x3u, shift_enum>;
using SHIFT_AMOU = /**/ field_delayed<u32, u8, 7, 0x1fu>;
using RS = /*        */ field_delayed<u32, u8, 8>;
using RM = /*        */ field<u32, u8, 0>;
using ROTATE = /*    */ RS;
using IMM = /*       */ field<u32, u8, 0, 0xffu>;
} // namespace operand2

/// Multiply
namespace multiply {
constexpr u32 TEMPLATE{0x00000090u};
using A = /*         */ field_bool<u32, 21>;
using S = /*         */ fsr::S;
using RD = /*        */ fsr::RN;
using RN = /*        */ fsr::RD;
using RS = /*        */ field_delayed<u32, u8, 8>;
using RM = /*        */ operand2::RM;
} // namespace multiply

/// Multiply long
namespace multiplylong {
constexpr u32 TEMPLATE{0x00800090u};
using U = /*         */ field_bool<u32, 22>;
using A = /*         */ multiply::A;
using S = /*         */ multiply::S;
using RDHI = /*      */ multiply::RD;
using RDLO = /*      */ multiply::RN;
using RN = /*        */ multiply::RS;
using RM = /*        */ multiply::RM;
} // namespace multiplylong

/// Single data swap
namespace singleswap {
constexpr u32 TEMPLATE{0x01000090u};
using B = /*         */ multiplylong::U;
using RN = /*        */ fsr::RN;
using RD = /*        */ fsr::RD;
using RM = /*        */ multiply::RM;
} // namespace singleswap

/// Branch and Exchange
namespace branchexchange {
constexpr u32 TEMPLATE{0x012fff10u};
using RN = multiply::RM;
} // namespace branchexchange

/// Halfword data transfer, register offset
namespace halfreg {
constexpr u32 TEMPLATE{0x00000090u};
using P = /*         */ field_bool<u32, 24>;
using U = /*         */ field_bool<u32, 23>;
using W = /*         */ multiply::A;
using L = /*         */ fsr::S;
using RN = /*        */ fsr::RN;
using RD = /*        */ fsr::RD;
using S = /*         */ field_bool<u32, 6>;
using H = /*         */ field_bool<u32, 5>;
using RM = /*        */ multiply::RM;
} // namespace halfreg

/// Halfword data transfer, immediate offset
namespace halfimm {
constexpr u32 TEMPLATE{0x00400090u};
using I = /*         */ fsr::I;
using P = /*         */ halfreg::P;
using U = /*         */ halfreg::U;
using W = /*         */ multiply::A;
using L = /*         */ fsr::S;
using RN = /*        */ fsr::RN;
using RD = /*        */ fsr::RD;
using S = /*         */ halfreg::S;
using H = /*         */ halfreg::H;
using OFFSET = field_split<u32, u8, multiply::RS::shift, multiply::RS::mask, multiply::RM::mask, 4>;
} // namespace halfimm

/// Single data transfer
namespace singletrans {
constexpr u32 TEMPLATE{0x06000000u};
using I = /*         */ halfimm::P;
using P = /*         */ halfimm::P;
using U = /*         */ halfimm::U;
using B = /*         */ singleswap::B;
using W = /*         */ halfimm::W;
using L = /*         */ halfimm::L;
using RN = /*        */ halfimm::RN;
using RD = /*        */ halfimm::RD;
using OFFSET = /*    */ fsr::OPERAND2;
} // namespace singletrans

/// Undefined
namespace undefined {
constexpr u32 TEMPLATE{0x06000010u};
} // namespace undefined

/// Block data transfer
namespace blocktrans {
constexpr u32 TEMPLATE{0x09000000u};
using P = /*         */ halfimm::P;
using U = /*         */ halfimm::U;
using S = /*         */ singleswap::B;
using W = /*         */ halfimm::W;
using L = /*         */ halfimm::L;
using RN = /*        */ halfimm::RN;
using REGLIST = /*   */ field<u32, u16, 0, 0xffffu>;
} // namespace blocktrans

/// Branch
namespace branch {
constexpr u32 TEMPLATE{0x0a000000u};
using L = /*         */ halfimm::P;
using OFFSET = /*    */ field<u32, u32, 0, 0xffffffu>;
} // namespace branch

/// Coprocessor data transfer
namespace coproctrans {
constexpr u32 TEMPLATE{0x0b000000u};
using P = /*         */ halfimm::P;
using U = /*         */ halfimm::U;
using N = /*         */ singleswap::B;
using W = /*         */ halfimm::W;
using L = /*         */ halfimm::L;
using RN = /*        */ halfimm::RN;
using CRD = /*       */ fsr::RD;
using CPSHARP = /*   */ multiply::RS;
using OFFSET = /*    */ field<u32, u8, 0, 0xffu>;
} // namespace coproctrans

/// Coprocessor data operation
namespace coprocop {
constexpr u32 TEMPLATE{0x0e000000u};
using CPOPC = /*     */ field_delayed<u32, u8, 21>;
using CRN = /*       */ halfimm::RN;
using CRD = /*       */ fsr::RD;
using CPSHARP = /*   */ multiply::RS;
using CP = /*        */ field_delayed<u32, u8, 5, 0x7u>;
using CRM = /*       */ multiply::RM;
} // namespace coprocop

/// Coprocessor register transfer
namespace coprocregtrans {
constexpr u32 TEMPLATE{0x0e000010u};
using CPOPC = /*     */ field_delayed<u32, u8, 21, 0x7u>;
using L = /*         */ singletrans::L;
using CRN = /*       */ coprocop::CRN;
using RD = /*        */ coprocop::CRD;
using CPSHARP = /*   */ coprocop::CPSHARP;
using CP = /*        */ coprocop::CP;
using CRM = /*       */ coprocop::CRM;
} // namespace coprocregtrans

/// Software interrupt
namespace swint {
constexpr u32 TEMPLATE{0x0f000000u};
using SWI = /*       */ field<u32, u32, 0, 0xffffffu>;
} // namespace swint

/// Thumb

/// Format 01 - Move shifted register
namespace thumb01 {
constexpr u16 TEMPLATE{0x0000u};
using OP = /*        */ field_delayed<u16, u8, 11, 0x3u>;
using OFFSET5 = /*   */ field_delayed<u16, u8, 6, 0x1fu>;
using RS = /*        */ field_delayed<u16, u8, 3, 0x7u>;
using RD = /*        */ field<u16, u8, 0, 0x7u>;
} // namespace thumb01

/// Format 02 - Add and substract
namespace thumb02 {
constexpr u16 TEMPLATE{0x1c00u};
using OP = /*        */ field_bool<u16, 9>;
using RNOFFSET3 = /* */ field_delayed<u16, u8, 6, 0x7u>;
using RS = /*        */ thumb01::RS;
using RD = /*        */ thumb01::RD;
} // namespace thumb02

/// Format 03 - Move, compare, add, and subtract immediate
namespace thumb03 {
constexpr u16 TEMPLATE{0x2000u};
using OP = /*        */ thumb01::OP;
using RD = /*        */ field_delayed<u16, u8, 8, 0x7u>;
using OFFSET8 = /*   */ field<u16, u8, 0, 0xffu>;
} // namespace thumb03

/// Format 04 - ALU operation
namespace thumb04 {
constexpr u16 TEMPLATE{0x4000u};
using OP = /*        */ field_delayed<u16, u8, 6, 0xfu>;
using RS = /*        */ thumb01::RS;
using RD = /*        */ thumb01::RD;
} // namespace thumb04

/// Format 05 - High register operations and branch exchange
namespace thumb05 {
constexpr u16 TEMPLATE{0x4400u};
using OP = /*        */ field_delayed<u16, u8, 8, 0x7u>;
using H1 = /*        */ field_bool<u16, 7>;
using H2 = /*        */ field_bool<u16, 6>;
using RSHS = /*      */ thumb01::RS;
using RDHD = /*      */ thumb01::RD;
} // namespace thumb05

/// Format 06 - PC-relative load
namespace thumb06 {
constexpr u16 TEMPLATE{0x4800u};
using RD = /*        */ thumb03::RD;
using WORD8 = /*     */ field<u16, u8, 0, 0xffu>;
} // namespace thumb06

/// Format 07 - Load and store with relative offset
namespace thumb07 {
constexpr u16 TEMPLATE{0x5000u};
using L = /*         */ field_bool<u16, 11>;
using B = /*         */ field_bool<u16, 10>;
using RO = /*        */ thumb02::RNOFFSET3;
using RB = /*        */ thumb01::RS;
using RD = /*        */ thumb01::RD;
} // namespace thumb07

/// Format 08 - Load and store sign-extended byte and halfword
namespace thumb08 {
constexpr u16 TEMPLATE{0x5200u};
using H = /*         */ thumb07::L;
using S = /*         */ thumb07::B;
using RO = /*        */ thumb07::RO;
using RB = /*        */ thumb07::RB;
using RD = /*        */ thumb07::RD;
} // namespace thumb08

/// Format 09 - Load and store with immediate offset
namespace thumb09 {
constexpr u16 TEMPLATE{0x6000u};
using B = /*         */ field_bool<u16, 12>;
using L = /*         */ thumb07::L;
using OFFSET5 = /*   */ thumb01::OFFSET5;
using RB = /*        */ thumb01::RS;
using RD = /*        */ thumb01::RD;
} // namespace thumb09

/// Format 10 - Load and store halfword
namespace thumb10 {
constexpr u16 TEMPLATE{0x8000u};
using L = /*         */ thumb09::L;
using OFFSET5 = /*   */ thumb01::OFFSET5;
using RB = /*        */ thumb01::RS;
using RD = /*        */ thumb01::RD;
} // namespace thumb10

/// Format 11 - SP-relative load and store
namespace thumb11 {
constexpr u16 TEMPLATE{0x9000u};
using L = /*         */ thumb10::L;
using RD = /*        */ thumb06::RD;
using WORD8 = /*     */ thumb06::WORD8;
} // namespace thumb11

/// Format 12 - Load address
namespace thumb12 {
constexpr u16 TEMPLATE{0xa000u};
using SP = /*        */ thumb11::L;
using RD = /*        */ thumb11::RD;
using WORD8 = /*     */ thumb11::WORD8;
} // namespace thumb12

/// Format 13 - Add offset to stack pointer
namespace thumb13 {
constexpr u16 TEMPLATE{0xb000u};
using S = /*         */ field_bool<u16, 7>;
using SWORD7 = /*    */ field<u16, u8, 0, 0x7fu>;
} // namespace thumb13

/// Format 14 - Push and pop registers
namespace thumb14 {
constexpr u16 TEMPLATE{0xb400u};
using L = /*         */ thumb11::L;
using R = /*         */ field_bool<u16, 8>;
using RLIST = /*     */ thumb11::WORD8;
} // namespace thumb14

/// Format 15 - Multiple load and store
namespace thumb15 {
constexpr u16 TEMPLATE{0xc000u};
using L = /*         */ thumb12::SP;
using RB = /*        */ thumb12::RD;
using RLIST = /*     */ thumb12::WORD8;
} // namespace thumb15

/// Format 16 - Conditional branch
namespace thumb16 {
constexpr u16 TEMPLATE{0xd000u};
using COND = /*      */ field_delayed<u16, u8, 8>;
using SOFTSET8 = /*  */ thumb12::WORD8;
} // namespace thumb16

/// Format 17 - Software interrupt
namespace thumb17 {
constexpr u16 TEMPLATE{0xdf00u};
using VALUE8 = /*    */ field<u16, u8, 0, 0xffu>;
} // namespace thumb17

/// Format 18 - Unconditional branch
namespace thumb18 {
constexpr u16 TEMPLATE{0xe000u};
using OFFSET11 = /*  */ field<u16, u16, 0, 0x7ffu>;
} // namespace thumb18

/// Format 19 - Long branch with link
namespace thumb19 {
constexpr u16 TEMPLATE = {0xf000u};
using H = /*         */ thumb15::L;
using OFFSET = /*    */ thumb18::OFFSET11;
} // namespace thumb19

} // namespace neogba
