#pragma once
#include "neogba/arm7tdmi/memory.hpp"
#include "neogba/arm7tdmi/registers.hpp"
#include "neogba/types.hpp"
#include <format>
#include <memory>
#include <string>

namespace neogba::arm7tdmi {

enum Cond : u8 {
  EQ = 0b0000, // 0000 = EQ - Z set (equal)
  NE = 0b0001, // 0001 = NE - Z clear (not equal)
  HS = 0b0010, // 0010 = HS / CS - C set (unsigned higher or same)
  LO = 0b0011, // 0011 = LO / CC - C clear (unsigned lower)
  MI = 0b0100, // 0100 = MI - N set (negative)
  PL = 0b0101, // 0101 = PL - N clear (positive or zero)
  VS = 0b0110, // 0110 = VS - V set (overflow)
  VC = 0b0111, // 0111 = VC - V clear (no overflow)
  HI = 0b1000, // 1000 = HI - C set and Z clear (unsigned higher)
  LS = 0b1001, // 1001 = LS - C clear or Z (set unsigned lower or same)
  GE = 0b1010, // 1010 = GE - N set and V set, or N clear and V clear (> or =)
  LT = 0b1011, // 1011 = LT - N set and V clear, or N clear and V set (>)
  GT = 0b1100, // 1100 = GT - Z clear, and either N set and V set, or N clear and V set (>)
  LE = 0b1101, // 1101 = LE - Z set, or N set and V clear, or N clear and V set (<, or =)
  AL = 0b1110, // 1110 = AL - always
  NV = 0b1111, // 1111 = NV - reserved.
};

namespace ArmInstruction {

struct MultiplyAccumulate {
  bool a;
  bool s;
  u8 rd;
  u8 rn;
  u8 rs;
  u8 rm;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0fc00090) == 0x90;
  }

  ARM_INSTRUCTION_EXTRACT(instruction, MultiplyAccumulate) {
    return {.a = BIT_TO_BOOL(instruction, 21),
            .s = BIT_TO_BOOL(instruction, 20),
            .rd = EXTRACT_BIT_MASK(instruction, u8, 16, 0xF),
            .rn = EXTRACT_BIT_MASK(instruction, u8, 12, 0xF),
            .rs = EXTRACT_BIT_MASK(instruction, u8, 8, 0xF),
            .rm = EXTRACT_BIT_MASK(instruction, u8, 0, 0xf)};
  }

  ARM_INSTRUCTION_TOASM {
    return "Not implemented yet";
  }
};

struct MultiplyAccumulateLong {
  bool u;
  bool a;
  bool s;
  u8 rd_msw;
  u8 rd_lsw;
  u8 rn;
  u8 rm;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0f800090) == 0x800090;
  }

  ARM_INSTRUCTION_EXTRACT(instruction, MultiplyAccumulateLong) {
    return {.u = BIT_TO_BOOL(instruction, 22),
            .a = BIT_TO_BOOL(instruction, 21),
            .s = BIT_TO_BOOL(instruction, 20),
            .rd_msw = EXTRACT_BIT_MASK(instruction, u8, 16, 0xf),
            .rd_lsw = EXTRACT_BIT_MASK(instruction, u8, 12, 0xf),
            .rn = EXTRACT_BIT_MASK(instruction, u8, 8, 0xf),
            .rm = EXTRACT_BIT_MASK(instruction, u8, 0, 0xf)};
  }

  ARM_INSTRUCTION_TOASM {
    return "Not implemented yet";
  }
};

struct BranchAndExchange {
  u8 rn;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0ffffff0) == 0x012fff10;
  }

  ARM_INSTRUCTION_EXTRACT(instruction, BranchAndExchange) {
    return {.rn = EXTRACT_BIT_MASK(instruction, u8, 0, 0xf)};
  }

  ARM_INSTRUCTION_TOASM {
    return "Not implemented yet";
  }
};

struct SingleDataSwap {
  bool b;
  u8 rn;
  u8 rd;
  u8 rm;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0fb00ff0) == 0x1000090;
  }

  ARM_INSTRUCTION_EXTRACT(instruction, SingleDataSwap) {
    return {.b = BIT_TO_BOOL(instruction, 22),
            .rn = EXTRACT_BIT_MASK(instruction, u8, 16, 0xf),
            .rd = EXTRACT_BIT_MASK(instruction, u8, 12, 0xf),
            .rm = EXTRACT_BIT_MASK(instruction, u8, 0, 0xf)};
  }

  ARM_INSTRUCTION_TOASM {
    return "Not implemented yet";
  }
};

struct HalfwordDataTransRegisterOffset {
  bool p;
  bool u;
  bool w;
  bool l;
  u8 rn;
  u8 rd;
  u8 rm;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0e400ff0) == 0xb0;
  }

  ARM_INSTRUCTION_EXTRACT(instruction, HalfwordDataTransRegisterOffset) {
    return {.p = BIT_TO_BOOL(instruction, 24),
            .u = BIT_TO_BOOL(instruction, 23),
            .w = BIT_TO_BOOL(instruction, 21),
            .l = BIT_TO_BOOL(instruction, 20),
            .rn = EXTRACT_BIT_MASK(instruction, u8, 16, 0xf),
            .rd = EXTRACT_BIT_MASK(instruction, u8, 12, 0xf),
            .rm = EXTRACT_BIT_MASK(instruction, u8, 0, 0xf)};
  }

  ARM_INSTRUCTION_TOASM {
    return "Not implemented yet";
  }
};

struct HalfwordDataTransImmediateOffset {
  bool p;
  bool u;
  bool w;
  bool l;
  u8 rn;
  u8 rd;
  u8 offset;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0e4000f0) == 0x4000b0;
  }

  ARM_INSTRUCTION_EXTRACT(instruction, HalfwordDataTransImmediateOffset) {
    return {.p = BIT_TO_BOOL(instruction, 24),
            .u = BIT_TO_BOOL(instruction, 23),
            .w = BIT_TO_BOOL(instruction, 21),
            .l = BIT_TO_BOOL(instruction, 20),
            .rn = EXTRACT_BIT_MASK(instruction, u8, 16, 0xf),
            .rd = EXTRACT_BIT_MASK(instruction, u8, 12, 0xf),
            .offset = static_cast<u8>((EXTRACT_BIT_MASK(instruction, u8, 8, 0xf) << 4) |
                                      EXTRACT_BIT_MASK(instruction, u8, 0, 0xf))};
  }

  ARM_INSTRUCTION_TOASM {
    return "Not implemented yet";
  }
};

struct SignedDataTrans {
  bool p;
  bool u;
  bool b;
  bool w;
  bool l;
  u8 rn;
  u8 rd;
  u8 addr_mode;
  bool h;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0e0000d0) == 0xd0;
  }

  ARM_INSTRUCTION_EXTRACT(instruction, SignedDataTrans) {
    return {.p = BIT_TO_BOOL(instruction, 24),
            .u = BIT_TO_BOOL(instruction, 23),
            .b = BIT_TO_BOOL(instruction, 22),
            .w = BIT_TO_BOOL(instruction, 21),
            .l = BIT_TO_BOOL(instruction, 20),
            .rn = EXTRACT_BIT_MASK(instruction, u8, 16, 0xf),
            .rd = EXTRACT_BIT_MASK(instruction, u8, 12, 0xf),
            .addr_mode = static_cast<u8>((EXTRACT_BIT_MASK(instruction, u8, 8, 0xf) << 4) |
                                         EXTRACT_BIT_MASK(instruction, u8, 0, 0xf)),
            .h = BIT_TO_BOOL(instruction, 5)};
  }

  ARM_INSTRUCTION_TOASM {
    return "Not implemented yet";
  }
};

struct DataProcessingPSRTrans {
  enum opcodeT : u8 {
    AND = 0b0000, // AND Logical AND Rd := Rn AND shifter_operand
    EOR = 0b0001, // EOR Logical Exclusive OR Rd := Rn EOR shifter_operand
    SUB = 0b0010, // SUB Subtract Rd := Rn - shifter_operand
    RSB = 0b0011, // RSB Reverse Subtract Rd := shifter_operand - Rn
    ADD = 0b0100, // ADD Add Rd := Rn + shifter_operand
    ADC = 0b0101, // ADC Add with Carry Rd := Rn + shifter_operand + Carry Flag
    SBC = 0b0110, // SBC Subtract with Carry Rd := Rn - shifter_operand - NOT(Carry Flag)
    RSC = 0b0111, // RSC Reverse Subtract with Carry Rd := shifter_operand - Rn - NOT(Carry Flag)
    TST = 0b1000, // TST Test Update flags after Rn AND shifter_operand
    TEQ = 0b1001, // TEQ Test Equivalence Update flags after Rn EOR shifter_operand
    CMP = 0b1010, // CMP Compare Update flags after Rn - shifter_operand
    CMN = 0b1011, // CMN Compare Negated Update flags after Rn + shifter_operand
    ORR = 0b1100, // ORR Logical (inclusive) OR Rd := Rn OR shifter_operand
    MOV = 0b1101, // MOV Move Rd := shifter_operand (no first operand)
    BIC = 0b1110, // BIC Bit Clear Rd := Rn AND NOT(shifter_operand)
    MVN = 0b1111, // MVN Move Not Rd := NOT shifter_operand (no first operand)
  };

  opcodeT opcode;
  bool s;
  u8 rn;
  u8 rd;
  u16 operand2;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0c000000) == 0;
  }

  ARM_INSTRUCTION_EXTRACT(instruction, DataProcessingPSRTrans) {
    return {
        .opcode = EXTRACT_BIT_MASK(instruction, opcodeT, 21, 0xf),
        .s = BIT_TO_BOOL(instruction, 20),
        .rn = EXTRACT_BIT_MASK(instruction, u8, 16, 0xf),
        .rd = EXTRACT_BIT_MASK(instruction, u8, 12, 0xf),
        .operand2 = EXTRACT_BIT_MASK(instruction, u16, 0, 0xfff),
    };
  }

  ARM_INSTRUCTION_TOASM {
    return "Not implemented yet";
  }
};

struct LoadStoreRegisterUnsigned {
  bool i;
  bool p;
  bool u;
  bool b;
  bool w;
  bool l;
  u8 rn;
  u8 rd;
  u16 addr_mode;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0c000000) == 0x4000000;
  }

  ARM_INSTRUCTION_EXTRACT(instruction, LoadStoreRegisterUnsigned) {
    return {.i = BIT_TO_BOOL(instruction, 25),
            .p = BIT_TO_BOOL(instruction, 24),
            .u = BIT_TO_BOOL(instruction, 23),
            .b = BIT_TO_BOOL(instruction, 22),
            .w = BIT_TO_BOOL(instruction, 21),
            .l = BIT_TO_BOOL(instruction, 20),
            .rn = EXTRACT_BIT_MASK(instruction, u8, 16, 0xf),
            .rd = EXTRACT_BIT_MASK(instruction, u8, 12, 0xf),
            .addr_mode = EXTRACT_BIT_MASK(instruction, u16, 0, 0xfff)};
  }

  ARM_INSTRUCTION_TOASM {
    return "Not implemented yet";
  }
};

struct Undefined {
  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0e000010) == 0x6000010;
  }

  ARM_INSTRUCTION_EXTRACT(unused, Undefined) {
    return {};
  }

  ARM_INSTRUCTION_TOASM {
    return "Not implemented yet";
  }
};

struct BlockDataTrans {
  bool p;
  bool u;
  bool w;
  bool l;
  u8 rn;
  u16 register_list;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0e400000) == 0x8000000;
  }

  ARM_INSTRUCTION_EXTRACT(instruction, BlockDataTrans) {
    return {.p = BIT_TO_BOOL(instruction, 24),
            .u = BIT_TO_BOOL(instruction, 23),
            .w = BIT_TO_BOOL(instruction, 21),
            .l = BIT_TO_BOOL(instruction, 20),
            .rn = EXTRACT_BIT_MASK(instruction, u8, 16, 0xf),
            .register_list = EXTRACT_BIT_MASK(instruction, u16, 0, 0xffff)};
  }

  ARM_INSTRUCTION_TOASM {
    return "Not implemented yet";
  }
};

struct Branch {
  bool l;
  u32 offset;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0e000000) == 0xa000000;
  }

  ARM_INSTRUCTION_EXTRACT(instruction, Branch) {
    return {.l = BIT_TO_BOOL(instruction, 24),
            .offset = EXTRACT_BIT_MASK(instruction, u32, 0, 0xffffff)};
  }

  ARM_INSTRUCTION_TOASM {
    return "Not implemented yet";
  }
};

struct CoprocDataTrans {
  bool p;
  bool u;
  bool n;
  bool w;
  bool l;
  u8 rn;
  u8 crd;
  u8 cp_sharp;
  u8 offset;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0e000000) == 0xc000000;
  }

  ARM_INSTRUCTION_EXTRACT(instruction, CoprocDataTrans) {
    return {.p = BIT_TO_BOOL(instruction, 24),
            .u = BIT_TO_BOOL(instruction, 23),
            .n = BIT_TO_BOOL(instruction, 22),
            .w = BIT_TO_BOOL(instruction, 21),
            .l = BIT_TO_BOOL(instruction, 20),
            .rn = EXTRACT_BIT_MASK(instruction, u8, 16, 0xf),
            .crd = EXTRACT_BIT_MASK(instruction, u8, 12, 0xf),
            .cp_sharp = EXTRACT_BIT_MASK(instruction, u8, 8, 0xf),
            .offset = EXTRACT_BIT_MASK(instruction, u8, 0, 0xff)};
  }

  ARM_INSTRUCTION_TOASM {
    return "Not implemented yet";
  }
};

struct CoprocDataOperation {
  u8 cp_opc;
  u8 crn;
  u8 crd;
  u8 cp_sharp;
  u8 cp;
  u8 crm;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0f000010) == 0xe000000;
  }

  ARM_INSTRUCTION_EXTRACT(instruction, CoprocDataOperation) {
    return {.cp_opc = EXTRACT_BIT_MASK(instruction, u8, 20, 0xf),
            .crn = EXTRACT_BIT_MASK(instruction, u8, 16, 0xf),
            .crd = EXTRACT_BIT_MASK(instruction, u8, 12, 0xf),
            .cp_sharp = EXTRACT_BIT_MASK(instruction, u8, 8, 0xf),
            .cp = EXTRACT_BIT_MASK(instruction, u8, 5, 0x7),
            .crm = EXTRACT_BIT_MASK(instruction, u8, 0, 0xf)};
  }

  ARM_INSTRUCTION_TOASM {
    return "Not implemented yet";
  }
};

struct CoprocRegisterTrans {
  u8 cp_opc;
  bool l;
  u8 crn;
  u8 crd;
  u8 cp_sharp;
  u8 cp;
  u8 crm;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0f000010) == 0xe000010;
  }

  ARM_INSTRUCTION_EXTRACT(instruction, CoprocRegisterTrans) {
    return {.cp_opc = EXTRACT_BIT_MASK(instruction, u8, 21, 0x7),
            .l = BIT_TO_BOOL(instruction, 20),
            .crn = EXTRACT_BIT_MASK(instruction, u8, 16, 0xf),
            .crd = EXTRACT_BIT_MASK(instruction, u8, 12, 0xf),
            .cp_sharp = EXTRACT_BIT_MASK(instruction, u8, 8, 0xf),
            .cp = EXTRACT_BIT_MASK(instruction, u8, 5, 0x7),
            .crm = EXTRACT_BIT_MASK(instruction, u8, 0, 0xf)};
  }

  ARM_INSTRUCTION_TOASM {
    return "Not implemented yet";
  }
};

struct SoftwareInterrupt {
  u32 swi;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0f000000) == 0xf000000;
  }

  ARM_INSTRUCTION_EXTRACT(instruction, SoftwareInterrupt) {
    return {.swi = EXTRACT_BIT_MASK(instruction, u32, 0, 0xffffff)};
  }

  ARM_INSTRUCTION_TOASM {
    return "Not implemented yet";
  }
};

}; // namespace ArmInstruction

class CPU {
  Registers registers;
  std::shared_ptr<MemoryBus> bus;
  u32 currentInstruction;

public:
  CPU() : bus(nullptr) {};

  [[nodiscard]] inline bool isMemoryBusDefined() const {
    return bus != nullptr;
  }
  inline void useMemoryBus(std::shared_ptr<MemoryBus> bus) {
    this->bus = bus;
  }

  u32 fetch();
  void execute();
  void step();
};

} // namespace neogba::arm7tdmi
