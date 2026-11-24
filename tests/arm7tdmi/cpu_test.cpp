#include "neogba/arm7tdmi/cpu.hpp"
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
};

} // namespace

TEST_F(cpu_test, get_idx_registers_preset_by_mode_should_say_right_when_providing_modes) {

  ASSERT_EQ(arm7tdmi::REGISTERS_PRESET_USR,
            arm7tdmi::get_idx_registers_preset_by_mode(arm7tdmi::MODE_USR));

  ASSERT_EQ(arm7tdmi::REGISTERS_PRESET_FIQ,
            arm7tdmi::get_idx_registers_preset_by_mode(arm7tdmi::MODE_FIQ));

  ASSERT_EQ(arm7tdmi::REGISTERS_PRESET_IRQ,
            arm7tdmi::get_idx_registers_preset_by_mode(arm7tdmi::MODE_IRQ));

  ASSERT_EQ(arm7tdmi::REGISTERS_PRESET_SVC,
            arm7tdmi::get_idx_registers_preset_by_mode(arm7tdmi::MODE_SVC));

  ASSERT_EQ(arm7tdmi::REGISTERS_PRESET_ABT,
            arm7tdmi::get_idx_registers_preset_by_mode(arm7tdmi::MODE_ABT));

  ASSERT_EQ(arm7tdmi::REGISTERS_PRESET_UND,
            arm7tdmi::get_idx_registers_preset_by_mode(arm7tdmi::MODE_UND));

  ASSERT_EQ(arm7tdmi::REGISTERS_PRESET_SYS,
            arm7tdmi::get_idx_registers_preset_by_mode(arm7tdmi::MODE_SYS));
}

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
