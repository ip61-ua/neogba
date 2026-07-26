#pragma once
#include "neogba/memory/interfaces.hpp"

namespace neogba {

inline constexpr std::size_t gba_bus_normalizer(std::size_t addr) { return addr >> 24; }

class memory_bus {
  using lut_type = lut<imemory*, 1 << 8, gba_bus_normalizer>;
  lut_type ms;

public:
  lut_type& data() { return ms; }

  inline bool is_null(u32 addr) const { return ms.get(addr) == 0; }

  inline u32 read(u8 size, u32 addr) const {
    return is_null(addr) ? 0 : ms.get(addr)->read(size, addr);
  }

  inline bool write(u8 size, u32 addr, u32 contents) {
    return !is_null(addr) && ms.get(addr)->write(size, addr, contents);
  }

  inline void reset(u32 addr) {
    if (is_null(addr))
      return;

    ms.get(addr)->reset();
  }

  inline void attach(u32 addr, imemory* new_memory) {
    if (!new_memory)
      return;

    if (!is_null(addr))
      deattach(addr);

    ms.fill(addr, new_memory);
    new_memory->attach(this);
  }

  inline void deattach(u32 addr) {
    auto mem{ms.get(addr)};
    if (!mem)
      return;

    mem->deattach();
    std::ranges::replace(ms, mem, nullptr);
  }
};

} // namespace neogba
