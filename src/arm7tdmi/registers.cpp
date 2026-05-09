#include "neogba/arm7tdmi/registers.hpp"
#include "neogba/utils.hpp"
#include <algorithm>

using namespace neogba;
using namespace neogba::arm7;

void Registers::setOperationMode(OperationMode mode) {
  if (mode != sys) {
    switch (mode) {
    case user:
      map_current_ = MAP_USER;
      break;
    case fiq:
      map_current_ = MAP_FIQ;
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

[[nodiscard]] Registers::OperationMode Registers::getOperationMode() const {
  return static_cast<OperationMode>(regs_[cpsr] & MASK_MODE);
}

[[nodiscard]] bool Registers::isFlag(FlagMask flag) const {
  return isSetMask(flag, read(cpsr));
}

void Registers::setFlag(FlagMask flag) {
  setBitMask(regs_[cpsr], flag);
}

void Registers::clearFlag(FlagMask flag) {
  clearBitMask(regs_[cpsr], flag);
}

bool Registers::equals(Registers const& other) const {
  return std::equal(regs_, regs_ + TOTAL_REGISTERS, other.regs_);
}
