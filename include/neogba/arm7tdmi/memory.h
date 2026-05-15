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
  u8* memory_bytes;
  void* device;
  u32 n_bytes;
  bool is_read_only;
  const char* name;

  bool (*attached)(struct neogba_IMemory* self, u32 base_addr);
  bool (*detached)(struct neogba_IMemory* self);
  bool (*read)(struct neogba_IMemory* self, u32 addr, u32* dst, enum neogba_BlockLength len);
  bool (*write)(struct neogba_IMemory* self, u32 addr, u32 val, enum neogba_BlockLength len);
};

void neogba_IMemory_init(struct neogba_IMemory* self);
bool neogba_IMemory_std_read(struct neogba_IMemory* self, u32 addr, u32* dst,
                             enum neogba_BlockLength len);
bool neogba_IMemory_std_write(struct neogba_IMemory* self, u32 addr, u32 val,
                              enum neogba_BlockLength len);

struct neogba_MemoryBus {
  struct neogba_MemoryBusProperties properties;
  struct neogba_IMemory** memory_map;
};

void neogba_MemoryBus_init(struct neogba_MemoryBus* self, u32 offset_bit_size);
inline bool neogba_MemoryBus_is_free_index(struct neogba_MemoryBus* self, u32 index) {
  return index < self->properties.n_max_index && self->memory_map[index] == nullptr;
}
bool neogba_MemoryBus_attach(struct neogba_MemoryBus* self, u32 addr,
                             struct neogba_IMemory* memory);
bool neogba_MemoryBus_detach(struct neogba_MemoryBus* self, u32 addr);
bool neogba_MemoryBus_read(struct neogba_MemoryBus* self, u32 addr, u32* dst,
                           enum neogba_BlockLength len);
bool neogba_MemoryBus_write(struct neogba_MemoryBus* self, u32 addr, u32 val,
                            enum neogba_BlockLength len);
