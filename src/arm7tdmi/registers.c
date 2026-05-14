#include "neogba/arm7tdmi/registers.h"
#include "neogba/constants.h"
#include "neogba/utils.h"

void neogba_Registers_init(struct neogba_Registers* self) {
  for (u8 i = 0; i < NEOGBA_K_TOTAL_REGISTERS; ++i)
    self->regs[i] = 0;

  neogba_Registers_set_mode(self, user);
}

void neogba_Registers_set_mode(struct neogba_Registers* self, enum neogba_RegisterOperation mode) {
  if (mode != sys) {
    switch (mode) {
    case user:
      self->map_current = neogba_g_map_user;
      break;
    case fiq:
      self->map_current = neogba_g_map_fiq;
      break;
    case irq:
      self->map_current = neogba_g_map_irq;
      break;
    case svc:
      self->map_current = neogba_g_map_svc;
      break;
    case abt:
      self->map_current = neogba_g_map_abt;
      break;
    case und:
      self->map_current = neogba_g_map_und;
      break;
    default:
      break;
    }
  }

  NEOGBA_UTILS_CLEAR_BIT_MASK(self->regs[cpsr], NEOGBA_K_MASK_MODE);
  NEOGBA_UTILS_SET_BIT_MASK(self->regs[cpsr], mode);
}

enum neogba_RegisterOperation neogba_Registers_get_mode(struct neogba_Registers* self) {
  return (self->regs[cpsr] & NEOGBA_K_MASK_MODE);
}

bool neogba_Registers_is_flag(struct neogba_Registers* self, enum neogba_RegisterFlagMask flag);
void neogba_Registers_set_flag(struct neogba_Registers* self, enum neogba_RegisterFlagMask flag);
void neogba_Registers_clear_flag(struct neogba_Registers* self, enum neogba_RegisterFlagMask flag);

bool neogba_Registers_equals(struct neogba_Registers* self, struct neogba_Registers* other);

/* [[nodiscard]] Registers::OperationMode Registers::getOperationMode() const {} */

/* [[nodiscard]] bool Registers::isFlag(FlagMask flag) const { */
/*   return isSetMask(flag, read(cpsr)); */
/* } */

/* void Registers::setFlag(FlagMask flag) { */
/*   setBitMask(regs_[cpsr], flag); */
/* } */

/* void Registers::clearFlag(FlagMask flag) { */
/*   clearBitMask(regs_[cpsr], flag); */
/* } */

/* bool Registers::equals(Registers const& other) const { */
/*   return std::equal(regs_, regs_ + TOTAL_REGISTERS, other.regs_); */
/* } */
