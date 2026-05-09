#pragma once
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/registers.hpp"
#include "neogba/types.hpp"
#include "neogba/utils.hpp"
#include <format>
#include <memory>
#include <string>

#define ARM_INSTRUCTION_IS(alias) [[nodiscard]] constexpr static bool is(u32 alias)
#define ARM_INSTRUCTION_EXTRACT(alias)                                                             \
  [[nodiscard]] static std::unique_ptr<IArmInstruction> extract(u32 alias)
#define ARM_INSTRUCTION_TOASM std::string toAsm() const
#define ARM_INSTRUCTION_EXECUTE(alias) void execute(ARM7TDMI& alias)

namespace neogba::arm7::arm_mode {

struct IArmInstruction {
  virtual ~IArmInstruction() = default;
  virtual ARM_INSTRUCTION_TOASM = 0;
  virtual ARM_INSTRUCTION_EXECUTE(cpu) = 0;
};

struct Condition {
  enum ConditionType : u8 {
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

  [[nodiscard]] static constexpr ConditionType getCode(u32 instruction) {
    return static_cast<ConditionType>((instruction & 0xf0000000) >> (4 * 7));
  }

  [[nodiscard]] constexpr bool checkCode(Registers const& registers, ConditionType code) {
    switch (code) {
    case EQ:
      return registers.isFlag(Registers::Z);
    case NE:
      return !registers.isFlag(Registers::Z);
    case HS:
      return registers.isFlag(Registers::C);
    case LO:
      return !registers.isFlag(Registers::C);
    case MI:
      return registers.isFlag(Registers::N);
    case PL:
      return !registers.isFlag(Registers::N);
    case VS:
      return registers.isFlag(Registers::V);
    case VC:
      return !registers.isFlag(Registers::V);
    case HI:
      return registers.isFlag(Registers::C) && !registers.isFlag(Registers::Z);
    case LS:
      return !registers.isFlag(Registers::C) || registers.isFlag(Registers::Z);
    case GE:
      return registers.isFlag(Registers::N) == registers.isFlag(Registers::V);
    case LT:
      return registers.isFlag(Registers::N) != registers.isFlag(Registers::V);
    case GT:
      return !registers.isFlag(Registers::Z) &&
             (registers.isFlag(Registers::N) == registers.isFlag(Registers::V));
    case LE:
      return registers.isFlag(Registers::Z) ||
             (registers.isFlag(Registers::N) != registers.isFlag(Registers::V));
    case AL:
      return true;
    case NV:
      return true;
    }
  }
};

enum ShifterOperand : u16 {

};

struct MultiplyAccumulate : public IArmInstruction {
  bool a;
  bool s;
  u8 rd;
  u8 rn;
  u8 rs;
  u8 rm;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0fc00090) == 0x90;
  }

  ARM_INSTRUCTION_EXTRACT(instruction) {
    auto out{std::make_unique<MultiplyAccumulate>()};
    out->a = bitToBool(instruction, 21);
    out->s = bitToBool(instruction, 20);
    out->rd = extractLShiftMask<u8>(instruction, 16, 0xf);
    out->rn = extractLShiftMask<u8>(instruction, 12, 0xf);
    out->rs = extractLShiftMask<u8>(instruction, 8, 0xf);
    out->rm = extractLShiftMask<u8>(instruction, 0, 0xf);
    return out;
  };

  ARM_INSTRUCTION_TOASM override {
    return "Not Implemented Yet";
  };

  ARM_INSTRUCTION_EXECUTE(cpu) override;
};

struct MultiplyAccumulateLong : public IArmInstruction {
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

  ARM_INSTRUCTION_EXTRACT(instruction) {
    auto out{std::make_unique<MultiplyAccumulateLong>()};
    out->u = bitToBool(instruction, 22);
    out->a = bitToBool(instruction, 21);
    out->s = bitToBool(instruction, 20);
    out->rd_msw = extractLShiftMask<u8>(instruction, 16, 0xf);
    out->rd_lsw = extractLShiftMask<u8>(instruction, 12, 0xf);
    out->rn = extractLShiftMask<u8>(instruction, 8, 0xf);
    out->rm = extractLShiftMask<u8>(instruction, 0, 0xf);

    return out;
  };

  ARM_INSTRUCTION_TOASM override {
    return "Not Implemented Yet";
  }

  ARM_INSTRUCTION_EXECUTE(cpu) override;
};

struct BranchAndExchange : public IArmInstruction {
  u8 rn;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0ffffff0) == 0x012fff10;
  }

  ARM_INSTRUCTION_EXTRACT(instruction) {
    auto out = std::make_unique<BranchAndExchange>();
    out->rn = extractLShiftMask<u8>(instruction, 0, 0xf);
    return out;
  }

  ARM_INSTRUCTION_TOASM override {
    return "Not implemented yet";
  }
  ARM_INSTRUCTION_EXECUTE(cpu) override;
};

struct SingleDataSwap : public IArmInstruction {
  bool b;
  u8 rn;
  u8 rd;
  u8 rm;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0fb00ff0) == 0x1000090;
  }

  ARM_INSTRUCTION_EXTRACT(instruction) {
    auto out = std::make_unique<SingleDataSwap>();
    out->b = bitToBool(instruction, 22);
    out->rn = extractLShiftMask<u8>(instruction, 16, 0xf);
    out->rd = extractLShiftMask<u8>(instruction, 12, 0xf);
    out->rm = extractLShiftMask<u8>(instruction, 0, 0xf);
    return out;
  }

  ARM_INSTRUCTION_TOASM override {
    return "Not implemented yet";
  }
  ARM_INSTRUCTION_EXECUTE(cpu) override;
};

struct HalfwordDataTransRegisterOffset : public IArmInstruction {
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

  ARM_INSTRUCTION_EXTRACT(instruction) {
    auto out = std::make_unique<HalfwordDataTransRegisterOffset>();
    out->p = bitToBool(instruction, 24);
    out->u = bitToBool(instruction, 23);
    out->w = bitToBool(instruction, 21);
    out->l = bitToBool(instruction, 20);
    out->rn = extractLShiftMask<u8>(instruction, 16, 0xf);
    out->rd = extractLShiftMask<u8>(instruction, 12, 0xf);
    out->rm = extractLShiftMask<u8>(instruction, 0, 0xf);
    return out;
  }

  ARM_INSTRUCTION_TOASM override {
    return "Not implemented yet";
  }
  ARM_INSTRUCTION_EXECUTE(cpu) override;
};

struct HalfwordDataTransImmediateOffset : public IArmInstruction {
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

  ARM_INSTRUCTION_EXTRACT(instruction) {
    auto out = std::make_unique<HalfwordDataTransImmediateOffset>();
    out->p = bitToBool(instruction, 24);
    out->u = bitToBool(instruction, 23);
    out->w = bitToBool(instruction, 21);
    out->l = bitToBool(instruction, 20);
    out->rn = extractLShiftMask<u8>(instruction, 16, 0xf);
    out->rd = extractLShiftMask<u8>(instruction, 12, 0xf);
    out->offset = static_cast<u8>((extractLShiftMask<u8>(instruction, 8, 0xf) << 4) |
                                  extractLShiftMask<u8>(instruction, 0, 0xf));
    return out;
  }

  ARM_INSTRUCTION_TOASM override {
    return "Not implemented yet";
  }

  ARM_INSTRUCTION_EXECUTE(cpu) override;
};

struct SignedDataTrans : public IArmInstruction {
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

  ARM_INSTRUCTION_EXTRACT(instruction) {
    auto out = std::make_unique<SignedDataTrans>();
    out->p = bitToBool(instruction, 24);
    out->u = bitToBool(instruction, 23);
    out->b = bitToBool(instruction, 22);
    out->w = bitToBool(instruction, 21);
    out->l = bitToBool(instruction, 20);
    out->rn = extractLShiftMask<u8>(instruction, 16, 0xf);
    out->rd = extractLShiftMask<u8>(instruction, 12, 0xf);
    out->addr_mode = static_cast<u8>((extractLShiftMask<u8>(instruction, 8, 0xf) << 4) |
                                     extractLShiftMask<u8>(instruction, 0, 0xf));
    out->h = bitToBool(instruction, 5);
    return out;
  }

  ARM_INSTRUCTION_TOASM override {
    return "Not implemented yet";
  }

  ARM_INSTRUCTION_EXECUTE(cpu) override;
};

struct DataProcessingPSRTrans : public IArmInstruction {
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

  ARM_INSTRUCTION_EXTRACT(instruction) {
    auto out = std::make_unique<DataProcessingPSRTrans>();
    out->opcode = extractLShiftMask<opcodeT>(instruction, 21, 0xf);
    out->s = bitToBool(instruction, 20);
    out->rn = extractLShiftMask<u8>(instruction, 16, 0xf);
    out->rd = extractLShiftMask<u8>(instruction, 12, 0xf);
    out->operand2 = extractLShiftMask<u16>(instruction, 0, 0xfff);
    return out;
  }

  ARM_INSTRUCTION_TOASM override {
    return "Not implemented yet";
  }

  ARM_INSTRUCTION_EXECUTE(cpu) override;
};

struct LoadStoreRegisterUnsigned : public IArmInstruction {
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

  ARM_INSTRUCTION_EXTRACT(instruction) {
    auto out = std::make_unique<LoadStoreRegisterUnsigned>();
    out->i = bitToBool(instruction, 25);
    out->p = bitToBool(instruction, 24);
    out->u = bitToBool(instruction, 23);
    out->b = bitToBool(instruction, 22);
    out->w = bitToBool(instruction, 21);
    out->l = bitToBool(instruction, 20);
    out->rn = extractLShiftMask<u8>(instruction, 16, 0xf);
    out->rd = extractLShiftMask<u8>(instruction, 12, 0xf);
    out->addr_mode = extractLShiftMask<u16>(instruction, 0, 0xfff);
    return out;
  }

  ARM_INSTRUCTION_TOASM override {
    return "Not implemented yet";
  }

  ARM_INSTRUCTION_EXECUTE(cpu) override;
};

struct Undefined : public IArmInstruction {
  std::string reason;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0e000010) == 0x6000010;
  }

  ARM_INSTRUCTION_EXTRACT(instruction) {
    auto out = std::make_unique<Undefined>();
    out->reason = std::format("Undefined Instruction {}", instruction);
    return out;
  }

  ARM_INSTRUCTION_TOASM override {
    return "Undefined";
  }

  ARM_INSTRUCTION_EXECUTE(cpu) override;
};

struct BlockDataTrans : public IArmInstruction {
  bool p;
  bool u;
  bool w;
  bool l;
  u8 rn;
  u16 register_list;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0e400000) == 0x8000000;
  }

  ARM_INSTRUCTION_EXTRACT(instruction) {
    auto out = std::make_unique<BlockDataTrans>();
    out->p = bitToBool(instruction, 24);
    out->u = bitToBool(instruction, 23);
    out->w = bitToBool(instruction, 21);
    out->l = bitToBool(instruction, 20);
    out->rn = extractLShiftMask<u8>(instruction, 16, 0xf);
    out->register_list = extractLShiftMask<u16>(instruction, 0, 0xffff);
    return out;
  }

  ARM_INSTRUCTION_TOASM override {
    return "Not implemented yet";
  }

  ARM_INSTRUCTION_EXECUTE(cpu) override;
};

struct Branch : public IArmInstruction {
  bool l;
  u32 offset;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0e000000) == 0xa000000;
  }

  ARM_INSTRUCTION_EXTRACT(instruction) {
    auto out = std::make_unique<Branch>();
    out->l = bitToBool(instruction, 24);
    out->offset = extractLShiftMask<u32>(instruction, 0, 0xffffff);
    return out;
  }

  ARM_INSTRUCTION_TOASM override {
    return "Not implemented yet";
  }

  ARM_INSTRUCTION_EXECUTE(cpu) override;
};

struct CoprocDataTrans : public IArmInstruction {
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

  ARM_INSTRUCTION_EXTRACT(instruction) {
    auto out = std::make_unique<CoprocDataTrans>();
    out->p = bitToBool(instruction, 24);
    out->u = bitToBool(instruction, 23);
    out->n = bitToBool(instruction, 22);
    out->w = bitToBool(instruction, 21);
    out->l = bitToBool(instruction, 20);
    out->rn = extractLShiftMask<u8>(instruction, 16, 0xf);
    out->crd = extractLShiftMask<u8>(instruction, 12, 0xf);
    out->cp_sharp = extractLShiftMask<u8>(instruction, 8, 0xf);
    out->offset = extractLShiftMask<u8>(instruction, 0, 0xff);
    return out;
  }

  ARM_INSTRUCTION_TOASM override {
    return "Not implemented yet";
  }

  ARM_INSTRUCTION_EXECUTE(cpu) override;
};

struct CoprocDataOperation : public IArmInstruction {
  u8 cp_opc;
  u8 crn;
  u8 crd;
  u8 cp_sharp;
  u8 cp;
  u8 crm;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0f000010) == 0xe000000;
  }

  ARM_INSTRUCTION_EXTRACT(instruction) {
    auto out = std::make_unique<CoprocDataOperation>();
    out->cp_opc = extractLShiftMask<u8>(instruction, 20, 0xf);
    out->crn = extractLShiftMask<u8>(instruction, 16, 0xf);
    out->crd = extractLShiftMask<u8>(instruction, 12, 0xf);
    out->cp_sharp = extractLShiftMask<u8>(instruction, 8, 0xf);
    out->cp = extractLShiftMask<u8>(instruction, 5, 0x7);
    out->crm = extractLShiftMask<u8>(instruction, 0, 0xf);
    return out;
  }

  ARM_INSTRUCTION_TOASM override {
    return "Not implemented yet";
  }

  ARM_INSTRUCTION_EXECUTE(cpu) override;
};

struct CoprocRegisterTrans : public IArmInstruction {
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

  ARM_INSTRUCTION_EXTRACT(instruction) {
    auto out = std::make_unique<CoprocRegisterTrans>();
    out->cp_opc = extractLShiftMask<u8>(instruction, 21, 0x7);
    out->l = bitToBool(instruction, 20);
    out->crn = extractLShiftMask<u8>(instruction, 16, 0xf);
    out->crd = extractLShiftMask<u8>(instruction, 12, 0xf);
    out->cp_sharp = extractLShiftMask<u8>(instruction, 8, 0xf);
    out->cp = extractLShiftMask<u8>(instruction, 5, 0x7);
    out->crm = extractLShiftMask<u8>(instruction, 0, 0xf);
    return out;
  }

  ARM_INSTRUCTION_TOASM override {
    return "Not implemented yet";
  }

  ARM_INSTRUCTION_EXECUTE(cpu) override;
};

struct SoftwareInterrupt : public IArmInstruction {
  u32 swi;

  ARM_INSTRUCTION_IS(instruction) {
    return (instruction & 0x0f000000) == 0xf000000;
  }

  ARM_INSTRUCTION_EXTRACT(instruction) {
    auto out = std::make_unique<SoftwareInterrupt>();
    out->swi = extractLShiftMask<u32>(instruction, 0, 0xffffff);
    return out;
  }

  ARM_INSTRUCTION_TOASM override {
    return "Not implemented yet";
  }

  ARM_INSTRUCTION_EXECUTE(cpu) override;
};

}; // namespace neogba::arm7::arm_mode
