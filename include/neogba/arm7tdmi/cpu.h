#pragma once
#include "neogba/arm7tdmi/memory.h"
#include "neogba/arm7tdmi/registers.h"

struct neogba_ARM7TDMI {
  struct neogba_Registers* registers;
  struct neogba_MemoryBus* bus;
  u32 fetched_instruction;
  u32 decoded_instruction;
  u32 executed_instruction;
};

void neogba_ARM7TDMI_init(struct neogba_ARM7TDMI* self);
void neogba_ARM7TDMI_destroy(struct neogba_ARM7TDMI* self);

void neogba_ARM7TDMI_fetch(struct neogba_ARM7TDMI* self);
void neogba_ARM7TDMI_decode(struct neogba_ARM7TDMI* self);
void neogba_ARM7TDMI_execute(struct neogba_ARM7TDMI* self);

void neogba_ARM7TDMI_execute_arm(struct neogba_ARM7TDMI* self, u32 instruction);
void neogba_ARM7TDMI_execute_thumb(struct neogba_ARM7TDMI* self, u32 instruction);

void neogba_ARM7TDMI_step(struct neogba_ARM7TDMI* self);

struct neogba_IARMV4TInstruction {
  bool (*is)(int a);
  void* specific;
};
