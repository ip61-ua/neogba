#pragma once
#include "neogba/arm7tdmi/memory.hpp"
#include "neogba/arm7tdmi/registers.hpp"
#include "neogba/types.hpp"
#include <memory>

namespace neogba::arm7 {

class ARM7TDMI {
private:
  Registers registers;
  std::shared_ptr<MemoryBus> bus;
  u32 fetchedInstruction;

  friend struct IArmInstruction;

public:
  ARM7TDMI(Registers inyectableRegisters = {}) : registers{inyectableRegisters}, bus{nullptr} {};

  [[nodiscard]] inline bool isMemoryBusDefined() const {
    return bus != nullptr;
  }
  inline void useMemoryBus(std::shared_ptr<MemoryBus> bus) {
    this->bus = bus;
  }

  const Registers getRegisters() const {
    return registers;
  };
  u32 fetch();
  void executeArm(u32 instruction);
  void executeThumb(u32 instruction);
  void execute();
  void step();
};
} // namespace neogba::arm7
