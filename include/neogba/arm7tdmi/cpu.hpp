#pragma once
#include "neogba/arm7tdmi/memory.hpp"
#include "neogba/types.hpp"
#include <memory>

namespace neogba::arm7tdmi {

class CPU {
private:
  std::shared_ptr<MemoryBus> bus;

public:
  CPU() : bus(nullptr) {};

  inline bool isMemoryBusDefined() const {
    return bus != nullptr;
  }
  inline void useMemoryBus(std::shared_ptr<MemoryBus> bus) {
    this->bus = bus;
  }

  u32 fetchArm();
  u16 fetchThumb();
  void execute();
  void step();
};

} // namespace neogba::arm7tdmi
