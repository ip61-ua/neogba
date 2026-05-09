#include "neogba/arm7tdmi/registers.hpp"
#include "neogba/utils.hpp"

using namespace neogba;
using namespace neogba::arm7;

Registers::Registers() {
  for (u8 i = 0; i < TOTAL_REGISTERS; ++i)
    regs_[i] = 0;
}

Registers::Registers(Registers const& registers) {
  for (u8 i = 0; i < TOTAL_REGISTERS; ++i)
    regs_[i] = registers.regs_[i];
}

void Registers::setOperationMode(OperationMode mode) {
  if (mode != sys) {
    switch (mode) {
    case user:
      map_current_ = MAP_USER;
      break;
    case fiq:
      map_current_ = MAP_IRQ;
      break;
    case irq:
      map_current_ = MAP_IRQ;
      break;
    case svc:
      map_current_ = MAP_SVC;
      break;
    case abt:
      map_current_ = MAP_ABT;
      break;
    case und:
      map_current_ = MAP_UND;
      break;
    default:
      break;
    }
  }

  clearBitMask(regs_[cpsr], MASK_MODE);
  setBitMask(regs_[cpsr], mode);
}

[[nodiscard]] inline Registers::OperationMode Registers::getOperationMode() const {
  return static_cast<OperationMode>(regs_[cpsr] & MASK_MODE);
}

[[nodiscard]] inline bool Registers::isFlag(FlagMask flag) const {
  return isSetMask(flag, read(cpsr));
}

inline void Registers::setFlag(FlagMask flag) {
  setBitMask(regs_[cpsr], flag);
}

inline void Registers::clearFlag(FlagMask flag) {
  clearBitMask(regs_[cpsr], flag);
}

bool Registers::equals(Registers const& other) const {
  for (u8 i = 0; i < TOTAL_REGISTERS; ++i)
    if (other.regs_[i] != regs_[i])
      return false;

  return true;
}
