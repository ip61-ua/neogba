#pragma once
#include "neogba/arm7tdmi/memory.h"

struct neogba_SampleRAM {
  u32 base1, base2;
  bool used1, used2;
};

void neogba_SampleRAM_init(struct neogba_IMemory* self, u32 n_bytes);
bool neogba_SampleRAM_attached(struct neogba_IMemory* self, u32 base_addr);
bool neogba_SampleRAM_detached(struct neogba_IMemory* self);
bool neogba_SampleRAM_read(struct neogba_IMemory* self, u32 addr, u32* dst,
                           enum neogba_BlockLength len);
bool neogba_SampleRAM_write(struct neogba_IMemory* self, u32 addr, u32 val,
                            enum neogba_BlockLength len);
void neogba_SampleRAM_destroy(struct neogba_IMemory* self);
