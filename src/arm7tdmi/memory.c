#include "neogba/arm7tdmi/memory.h"
#include "neogba/constants.h"
#include "neogba/utils.h"

void neogba_MemoryBusProperties_init(struct neogba_MemoryBusProperties* self, u32 n_bits_offset) {
  self->n_bits_offset = n_bits_offset;
  self->n_bits_index = NEOGBA_K_BLOCK_BIT_SIZE - n_bits_offset;

  self->mask_offset = NEOGBA_UTILS_CREATE_RIGHT_MASK(n_bits_offset);
  self->mask_index = NEOGBA_UTILS_CREATE_RIGHT_MASK(NEOGBA_K_BLOCK_BIT_SIZE) - self->mask_offset;

  self->n_max_offset = self->mask_offset;
  self->n_max_index = (self->mask_index >> n_bits_offset);
}

void neogba_IMemory_init_default(struct neogba_IMemory* self) {
  struct neogba_MemoryBusProperties* properties;
  neogba_MemoryBusProperties_init(properties, 0);

  self->n_bytes = 0;
  self->is_read_only = true;
  self->bus_properties = *properties;
  self->memory_bytes = nullptr;
  self->name = nullptr;
}

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
