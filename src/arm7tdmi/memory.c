#include "neogba/arm7tdmi/memory.h"
#include "neogba/constants.h"
#include "neogba/types.h"
#include "neogba/utils.h"
#include <stdlib.h>

void neogba_MemoryBusProperties_init(struct neogba_MemoryBusProperties* self, u32 n_bits_offset) {
  self->n_bits_offset = n_bits_offset;
  self->n_bits_index = NEOGBA_K_BLOCK_BIT_SIZE - n_bits_offset;

  self->mask_offset = NEOGBA_UTILS_CREATE_RIGHT_MASK(n_bits_offset);
  self->mask_index = NEOGBA_UTILS_CREATE_RIGHT_MASK(NEOGBA_K_BLOCK_BIT_SIZE) - self->mask_offset;

  self->n_max_offset = self->mask_offset;
  self->n_max_index = (self->mask_index >> n_bits_offset);
}

void neogba_IMemory_init(struct neogba_IMemory* self, u32 n_bytes) {
  neogba_MemoryBusProperties_init(&self->bus_properties, 0);

  self->memory_bytes = (n_bytes == 0) ? nullptr : calloc(n_bytes, sizeof(u8));
  self->n_bytes = n_bytes;
  self->is_read_only = true;
  self->name = nullptr;

  self->attached = nullptr;
  self->detached = nullptr;
  self->read = nullptr;
  self->write = nullptr;
  self->destroy = nullptr;
}

bool neogba_IMemory_std_read(struct neogba_IMemory* self, u32 addr, u32* dst,
                             enum neogba_BlockLength len) {
  if (self == nullptr)
    return false;

  auto offset = neogba_MemoryBusProperties_get_addr_offset(&self->bus_properties, addr);

  if (offset + len / BYTE > self->n_bytes)
    return false;

  /*
    addr         = 0x FF 12 23 43
    nBytes       = 0x 01 00 00 00
    nBytes - 1   = 0x 00 FF FF FF
    addr & mask  = 0x 00 12 23 43
  */

  auto m = self->memory_bytes;

  switch (len) {
  case BYTE: {
    if (dst != nullptr)
      *dst = m[offset];
    break;
  }

  case HALFWORD: {
    offset = offset & ~0b01;
    if (dst != nullptr)
      *dst = (m[offset + 1] << BYTE) | m[offset];
    break;
  }

  case WORD: {
    offset = offset & ~0b11;
    if (dst != nullptr)
      *dst = (m[offset + 3] << (HALFWORD + BYTE) | (m[offset + 2] << HALFWORD) |
              (m[offset + 1] << BYTE) | m[offset]);
    break;
  }

  default:
    return false;
  }

  return true;
}

bool neogba_IMemory_std_write(struct neogba_IMemory* self, u32 addr, u32 val,
                              enum neogba_BlockLength len) {
  if (self == nullptr)
    return false;

  auto offset = neogba_MemoryBusProperties_get_addr_offset(&self->bus_properties, addr);

  if (offset + len / BYTE > self->n_bytes)
    return false;

  auto m = self->memory_bytes;

  switch (len) {
  case BYTE:
    m[offset] = val;
    break;

  case HALFWORD:
    offset = offset & ~0b01;
    m[offset] = val;
    m[offset + 1] = val >> BYTE;
    break;

  case WORD:
    offset = offset & ~0b11;
    m[offset] = val;
    m[offset + 1] = val >> BYTE;
    m[offset + 2] = val >> HALFWORD;
    m[offset + 3] = val >> (BYTE + HALFWORD);
    break;

  default:
    return false;
  }

  return true;
}

void neogba_IMemory_std_destroy(struct neogba_IMemory* self) {
  if (self == nullptr)
    return;

  if (self->destroy != nullptr)
    self->destroy(self);

  free(self->memory_bytes);

  self->n_bytes = 0;
  self->name = nullptr;
  self->attached = nullptr;
  self->detached = nullptr;
  self->read = nullptr;
  self->write = nullptr;
  self->destroy = nullptr;
};

void neogba_MemoryBus_init(struct neogba_MemoryBus* self, u32 offset_bit_size) {
  neogba_MemoryBusProperties_init(&self->properties, offset_bit_size);
  *self->memory_map = malloc(self->properties.n_max_index * sizeof(struct neogba_IMemory*));
}

bool neogba_MemoryBus_attach(struct neogba_MemoryBus* self, u32 addr,
                             struct neogba_IMemory* memory) {
  auto index = neogba_MemoryBusProperties_get_addr_index(&self->properties, addr);

  if (!neogba_MemoryBus_is_free_index(self, index))
    return false;

  auto m = self->memory_map;

  m[index] = memory;
  m[index]->bus_properties = self->properties;

  if (m[index]->attached != nullptr && !m[index]->attached(m[index], addr)) {
    m = nullptr;
    return false;
  }

  return true;
}

bool neogba_MemoryBus_detach(struct neogba_MemoryBus* self, u32 addr) {
  auto index = neogba_MemoryBusProperties_get_addr_index(&self->properties, addr);

  if (neogba_MemoryBus_is_free_index(self, index))
    return false;

  auto m = self->memory_map;

  if (m[index]->detached(m[index])) {
    m[index] = nullptr;
    return true;
  }

  return false;
}

bool neogba_MemoryBus_read(struct neogba_MemoryBus* self, u32 addr, u32* dst,
                           enum neogba_BlockLength len) {
  auto index = neogba_MemoryBusProperties_get_addr_index(&self->properties, addr);
  if (neogba_MemoryBus_is_free_index(self, index))
    return false;

  auto m = self->memory_map;
  return m[index]->read(m[index], addr, dst, len);
}

bool neogba_MemoryBus_write(struct neogba_MemoryBus* self, u32 addr, u32 val,
                            enum neogba_BlockLength len) {
  auto index = neogba_MemoryBusProperties_get_addr_index(&self->properties, addr);

  if (neogba_MemoryBus_is_free_index(self, index))
    return false;

  auto m = self->memory_map;
  return (m[index]->is_read_only) ? false : m[index]->write(m[index], addr, val, len);
}
