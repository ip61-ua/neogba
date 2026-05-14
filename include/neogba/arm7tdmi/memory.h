#pragma once
#include "neogba/types.h"

struct neogba_MemoryBusProperties {
  u32 n_bits_offset, n_bits_index;
  u32 mask_offset, mask_index;
  u32 n_max_offset, n_max_index;
};

void neogba_MemoryBusProperties_init(struct neogba_MemoryBusProperties* self, u32 n_bits_offset);

inline u32 neogba_MemoryBusProperties_get_addr_offset(struct neogba_MemoryBusProperties* self,
                                                      u32 addr) {
  return addr & self->mask_offset;
}

inline u32 neogba_MemoryBusProperties_get_addr_index(struct neogba_MemoryBusProperties* self,
                                                     u32 addr) {
  return addr >> self->n_bits_offset;
}

inline bool neogba_MemoryBusProperties_equals(struct neogba_MemoryBusProperties* self,
                                              struct neogba_MemoryBusProperties* other) {
  return self->mask_index == other->mask_index && self->n_bits_offset == other->n_bits_offset &&
         self->mask_offset == other->mask_offset && self->n_bits_index == other->n_bits_index &&
         self->n_max_offset == other->n_max_offset && self->n_max_index == other->n_max_index;
}

struct neogba_IMemory {
  struct neogba_MemoryBusProperties bus_properties;
  u32 n_bytes;
  bool is_read_only;
  u8* memory_bytes;
  const char* name;
};

void neogba_IMemory_init_default(struct neogba_IMemory* self);

class IMemory {

  virtual u32 read(u32 addr, BlockLength len = word) const = 0;
  virtual void write(u32 addr, u32 val, BlockLength len = word) = 0;

protected:
  virtual bool attached(u32 base_addr) = 0;
  virtual bool detached() {
    return true;
  }

  friend class MemoryBus;
};

class MemoryBus {
protected:
  MemoryBusProperties properties_;
  std::vector<std::shared_ptr<IMemory>> memory_map_;

public:
  MemoryBus(u32 offsetBitSize = K_BLOCK_INDEX_MASK)
      : properties_(offsetBitSize), memory_map_(properties_.n_max_index_) {}

  inline bool isFreeIndex(u32 index) const {
    return index < properties_.n_max_index_ && memory_map_[index] == nullptr;
  }

  inline MemoryBusProperties getProperties() const {
    return properties_;
  }

  bool attachMemory(u32 addr, std::shared_ptr<IMemory> memory);
  bool detachMemory(u32 addr);
  u32 read(u32 addr, BlockLength len = word) const;
  bool write(u32 addr, u32 val, BlockLength len = word);
};

} // namespace neogba::arm7
