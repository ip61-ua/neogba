#include "neogba/arm7tdmi/cpu.hpp"
#include <cstring>
#include <gtest/gtest.h>
#include <memory>

using namespace neogba;

namespace {
class cpu_test : public ::testing::Test {
protected:
  std::unique_ptr<arm7tdmi> cpu;

  cpu_test() {}

  virtual ~cpu_test() {}

  void SetUp() override {
    cpu = std::make_unique<arm7tdmi>();
    cpu->empty_registers();
  }

  void TearDown() override {}

  void equals_registers(u32 expected[], bool optimized = true, bool verbose = true) {
    if (optimized) {
      ASSERT_EQ(0, std::memcmp(expected, cpu->registers, arm7tdmi::N_REGISTERS * sizeof(u32)));
    } else {
      for (auto i = 0; i < arm7tdmi::N_REGISTERS; i++) {
        if (verbose)
          std::cout << i << " " << expected[i] << " " << cpu->registers[i] << "\n";

        ASSERT_EQ(expected[i], cpu->registers[i]);
      }
    }
  }
};

} // namespace

TEST_F(cpu_test, set_mode_should_update_cpsr_and_report_correct_mode) {
  for (auto mode : {arm7tdmi::MODE_USR, arm7tdmi::MODE_FIQ, arm7tdmi::MODE_IRQ, arm7tdmi::MODE_SVC,
                    arm7tdmi::MODE_ABT, arm7tdmi::MODE_UND, arm7tdmi::MODE_SYS}) {

    cpu->set_mode(mode, true);
    ASSERT_TRUE(cpu->is_mode(mode));
  }
}

TEST_F(cpu_test, banked_registers_should_be_isolated_between_modes) {
  cpu->set_mode(arm7tdmi::MODE_SYS, false);
  cpu->write_active_register(r8, 100);
  cpu->write_active_register(r13, 200);

  cpu->set_mode(arm7tdmi::MODE_FIQ, false);
  cpu->write_active_register(r8, 888);
  cpu->write_active_register(r13, 999);

  ASSERT_EQ(888, cpu->read_active_register(r8));
  ASSERT_EQ(888, cpu->registers[r8_fiq]);

  cpu->set_mode(arm7tdmi::MODE_SYS, false);
  ASSERT_EQ(100, cpu->read_active_register(r8));
  ASSERT_EQ(200, cpu->read_active_register(r13));
}

TEST_F(cpu_test, spsr_should_be_isolated_between_privileged_modes) {
  cpu->set_mode(arm7tdmi::MODE_FIQ, false);
  cpu->write_spsr(0xAAAA);

  cpu->set_mode(arm7tdmi::MODE_SVC, false);
  cpu->write_spsr(0xBBBB);

  ASSERT_EQ(0xBBBB, cpu->read_spsr());
  ASSERT_EQ(0xBBBB, cpu->registers[spsr_svc]);

  cpu->set_mode(arm7tdmi::MODE_FIQ, false);
  ASSERT_EQ(0xAAAA, cpu->read_spsr());
  ASSERT_EQ(0xAAAA, cpu->registers[spsr_fiq]);
}

TEST_F(cpu_test, cpsr_read_write_should_modify_correct_physical_register) {
  cpu->set_mode(arm7tdmi::MODE_SVC, true);
  cpu->write_cpsr(777);
  ASSERT_EQ(777, cpu->read_active_register(cpsr));
  ASSERT_EQ(777, cpu->registers[cpsr]);

  cpu->write_active_register(cpsr, 42);
  ASSERT_EQ(42, cpu->read_cpsr());
  ASSERT_EQ(42, cpu->registers[cpsr]);
}

TEST_F(cpu_test, checks_if_the_entire_chunk_of_registers_are_equal) {
  u32 expected[arm7tdmi::N_REGISTERS] = {};

  expected[neogba::r0] = 103;
  expected[neogba::r1] = 104;
  expected[neogba::r2] = 105;
  expected[neogba::r3] = 106;
  expected[neogba::r4] = 107;
  expected[neogba::r5] = 108;
  expected[neogba::r6] = 109;
  expected[neogba::r7] = 110;
  expected[neogba::r8] = 111;
  expected[neogba::r9] = 112;
  expected[neogba::r10] = 113;
  expected[neogba::r11] = 114;
  expected[neogba::r12] = 115;
  expected[neogba::r13] = 116;
  expected[neogba::r14] = 117;
  expected[neogba::pc] = 118;
  expected[neogba::cpsr] = 119;
  expected[neogba::spsr] = 0;

  expected[neogba::r8_fiq] = 26;
  expected[neogba::r9_fiq] = 27;
  expected[neogba::r10_fiq] = 28;
  expected[neogba::r11_fiq] = 29;
  expected[neogba::r12_fiq] = 30;
  expected[neogba::r13_fiq] = 31;
  expected[neogba::r14_fiq] = 32;
  expected[neogba::spsr_fiq] = static_cast<u32>(-34);

  expected[neogba::r13_irq] = 48;
  expected[neogba::r14_irq] = 49;
  expected[neogba::spsr_irq] = static_cast<u32>(-51);

  expected[neogba::r13_svc] = 65;
  expected[neogba::r14_svc] = 66;
  expected[neogba::spsr_svc] = static_cast<u32>(-68);

  expected[neogba::r13_abt] = 82;
  expected[neogba::r14_abt] = 83;
  expected[neogba::spsr_abt] = static_cast<u32>(-85);

  expected[neogba::r13_und] = 99;
  expected[neogba::r14_und] = 100;
  expected[neogba::spsr_und] = static_cast<u32>(-102);

  u32 j = 0;
  for (auto mode : {arm7tdmi::MODE_USR, arm7tdmi::MODE_FIQ, arm7tdmi::MODE_IRQ, arm7tdmi::MODE_SVC,
                    arm7tdmi::MODE_ABT, arm7tdmi::MODE_UND, arm7tdmi::MODE_SYS}) {

    cpu->set_mode(mode, false);

    for (auto b : {ARM7TDMI_REGISTERS_ACCESSIBLE}) {
      cpu->write_active_register(b, ++j);
    }

    if (mode == arm7tdmi::MODE_USR || mode == arm7tdmi::MODE_SYS)
      continue;

    cpu->write_spsr(-j);

    auto activ = cpu->REGISTERS_PRESET[cpu->get_idx_registers_preset_by_mode(mode)];
    ASSERT_EQ(expected[activ[spsr]], cpu->read_spsr());
  }
  equals_registers(expected);
}
