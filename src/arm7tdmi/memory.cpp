#include "neogba/arm7tdmi/memory.hpp"

using namespace neogba;
using namespace neogba::arm7;

bool MemoryBus::attachMemory(u32 addr, std::shared_ptr<IMemory> memory) {
  auto index = properties_.getAddrIndex(addr);

  if (!isFreeIndex(index))
    return false;

  auto& m = memory_map_[index];
  m = memory;
  m->bus_properties_ = properties_;

  if (!m->attached(addr)) {
    m->bus_properties_ = MemoryBusProperties();
    m = nullptr;
    return false;
  }

  return true;
}

bool MemoryBus::detachMemory(u32 addr) {
  auto index = properties_.getAddrIndex(addr);

  if (isFreeIndex(index))
    return false;

  auto& m = memory_map_[index];

  if (m->detached()) {
    m = nullptr;
    return true;
  }

  return false;
}

u32 MemoryBus::read(u32 addr, BlockLength len) const {
  auto index = properties_.getAddrIndex(addr);

  if (isFreeIndex(index))
    return 0x0;

  return memory_map_[index]->read(addr, len);
}

bool MemoryBus::write(u32 addr, u32 val, BlockLength len) {
  auto index = properties_.getAddrIndex(addr);

  if (isFreeIndex(index))
    return false;

  if (memory_map_[index]->isReadOnly())
    return false;

  memory_map_[index]->write(addr, val, len);
  return true;
}
