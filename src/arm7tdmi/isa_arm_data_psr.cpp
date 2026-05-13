#include "neogba/arm7tdmi/isa_arm.hpp"

using namespace neogba;
using namespace neogba::arm7;
using namespace neogba::arm7::arm_mode;

ARM_INSTRUCTION_EXECUTE(Branch::, cpu) {
  cpu

      Branch info = Branch::extract(cpu.instruction);

  if (info.l)
    registers.write(14, registers.read(Registers::pc) - 4);

  registers.write(Registers::pc, (info.offset << 2) + registers.read(Registers::pc));
  return;
}
