#pragma once
#include "neogba/types.hpp"

namespace neogba::arm7tdmi {

class CPU {
private:
public:
  CPU(const CPU&) = default;
  CPU(CPU&&) = default;
  CPU& operator=(const CPU&) = default;
  CPU& operator=(CPU&&) = default;

  u32 fetchArm();
  u16 fetchThumb();
  void execute();
  void step();
};

} // namespace neogba::arm7tdmi
