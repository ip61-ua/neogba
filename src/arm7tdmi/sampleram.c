#include "neogba/arm7tdmi/sampleram.h"
#include <stdlib.h>

void neogba_SampleRAM_init(struct neogba_IMemory* self, u32 n_bytes) {
  neogba_IMemory_init(self, n_bytes);

  self->is_read_only = false;
  self->memory_bytes = calloc(n_bytes, sizeof(u8));
  self->name = "Sample RAM";

  self->detached = neogba_SampleRAM_detached;
  self->attached = neogba_SampleRAM_attached;
  self->write = neogba_SampleRAM_write;
  self->read = neogba_SampleRAM_read;

  self->device = malloc(sizeof(struct neogba_SampleRAM));
  auto device = (struct neogba_SampleRAM*)self->device;

  device->base2 = device->base1 = 0;
  device->used2 = device->used1 = false;
}

bool neogba_SampleRAM_attached(struct neogba_IMemory* self, u32 base_addr) {
  auto device = (struct neogba_SampleRAM*)self->device;

  if (!device->used1) {
    device->base1 = base_addr;
    return device->used1 = true;
  }

  if (!device->used2) {
    device->base2 = base_addr;
    return device->used2 = true;
  }

  return false;
}

bool neogba_SampleRAM_detached(struct neogba_IMemory* self) {
  auto device = (struct neogba_SampleRAM*)self->device;

  device->used1 = device->used2 = false;
  device->base1 = device->base2 = 0;
  return true;
}

bool neogba_SampleRAM_read(struct neogba_IMemory* self, u32 addr, u32* dst,
                           enum neogba_BlockLength len) {
  return neogba_IMemory_std_read(self, addr, dst, len);
}

bool neogba_SampleRAM_write(struct neogba_IMemory* self, u32 addr, u32 val,
                            enum neogba_BlockLength len) {
  return neogba_IMemory_std_write(self, addr, val, len);
}

void neogba_SampleRAM_destroy(struct neogba_IMemory* self) {
  free(self->device);
}
