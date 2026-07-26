#pragma once
#include "neogba/memory/interfaces.hpp"

namespace neogba {

class memory_bus {
  lut<imemory*, 1 << 8, [](std::size_t addr) -> auto { return addr >> 24; }> ms;

public:
  inline u32 read(u8 size, u32 addr) const { return ms.get(addr)->read(size, addr); }
  inline bool write(u8 size, u32 addr, u32 contents) {
    return ms.get(addr)->write(size, addr, contents);
  }
  inline bool is_null(u32 addr) const { return ms.get(addr) == 0; }
  inline void attach(u32 addr, imemory* new_memory) { ms.fill(addr, new_memory); }
  inline void deattach(u32 addr) {
    ms.get(addr)->deattach();
    ms.
  }
};

} // namespace neogba
