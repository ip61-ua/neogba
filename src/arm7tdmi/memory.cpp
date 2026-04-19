#include "neogba/arm7tdmi/memory.hpp"

using namespace neogba;
using namespace neogba::arm7tdmi;

bool MemoryBus::attachMemory(u32 addr, IMemory* memory) {
  auto index = properties.getAddrIndex(addr);

  if (!isFreeIndex(index))
    return false;

  auto& m = memoryMap[index];
  m = memory;
  m->busProperties = properties;

  if (!m->attached(addr)) {
    m->busProperties = MemoryBusProperties();
    m = nullptr;
    return false;
  }

  return true;
}

bool MemoryBus::detachMemory(u32 addr) {
  auto index = properties.getAddrIndex(addr);

  if (!isFreeIndex(index))
    return false;

  auto& m = memoryMap[index];

  if (m->detached()) {
    m = nullptr;
    return true;
  }

  return false;
}

u32 MemoryBus::read(u32 addr, MemoryBlockLength len) const {
  auto index = properties.getAddrIndex(addr);

  if (isFreeIndex(index))
    return 0x0;

  return memoryMap[index]->read(addr, len);
}

bool MemoryBus::write(u32 addr, u32 val, MemoryBlockLength len) {
  auto index = properties.getAddrIndex(addr);

  if (isFreeIndex(index))
    return false;

  if (memoryMap[index]->isReadOnly())
    return false;

  memoryMap[index]->write(addr, val, len);
  return true;
}
