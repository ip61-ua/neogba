#include "neogba/arm7tdmi/cpu.hpp"
#include <cstring>
#include <gtest/gtest.h>
#include <memory>

using namespace neogba;

namespace {
class cpu_test : public ::testing::Test {
protected:
  std::unique_ptr<ARM7TDMI_CPU> cpu;

  cpu_test() {}

  virtual ~cpu_test() {}

  void SetUp() override {
    cpu = std::make_unique<ARM7TDMI_CPU>();
    cpu->empty_registers();
  }

  void TearDown() override {}

  void equals_registers(u32 expected[], bool optimized = true,
                        bool verbose = true) {
    if (optimized) {
      ASSERT_EQ(0, std::memcmp(expected, cpu->registers,
                               ARM7TDMI_CPU_REGISTERS_TOTAL * sizeof(u32)));
    } else {
      for (auto i = 0; i < ARM7TDMI_CPU_REGISTERS_TOTAL; i++) {
        if (verbose)
          std::cout << i << " " << expected[i] << " " << cpu->registers[i]
                    << "\n";

        ASSERT_EQ(expected[i], cpu->registers[i]);
      }
    }
  }
};

} // namespace

TEST_F(cpu_test, set_mode_should_update_cpsr_and_report_correct_mode) {
  for (auto mode :
       {ARM7TDMI_CPU_MODE_USR, ARM7TDMI_CPU_MODE_FIQ, ARM7TDMI_CPU_MODE_IRQ,
        ARM7TDMI_CPU_MODE_SVC, ARM7TDMI_CPU_MODE_ABT, ARM7TDMI_CPU_MODE_UND,
        ARM7TDMI_CPU_MODE_SYS}) {

    cpu->set_mode(mode, true);
    ASSERT_TRUE(cpu->is_mode(mode));
  }
}

TEST_F(cpu_test, banked_registers_should_be_isolated_between_modes) {
  cpu->set_mode(ARM7TDMI_CPU_MODE_SYS, false);
  cpu->write_active_register(r8, 100);
  cpu->write_active_register(r13, 200);

  cpu->set_mode(ARM7TDMI_CPU_MODE_FIQ, false);
  cpu->write_active_register(r8, 888);
  cpu->write_active_register(r13, 999);

  ASSERT_EQ(888, cpu->read_active_register(r8));
  ASSERT_EQ(888, cpu->registers[r8_fiq]);

  cpu->set_mode(ARM7TDMI_CPU_MODE_SYS, false);
  ASSERT_EQ(100, cpu->read_active_register(r8));
  ASSERT_EQ(200, cpu->read_active_register(r13));
}

TEST_F(cpu_test, spsr_should_be_isolated_between_privileged_modes) {
  cpu->set_mode(ARM7TDMI_CPU_MODE_FIQ, false);
  cpu->write_spsr(0xAAAA);

  cpu->set_mode(ARM7TDMI_CPU_MODE_SVC, false);
  cpu->write_spsr(0xBBBB);

  ASSERT_EQ(0xBBBB, cpu->read_spsr());
  ASSERT_EQ(0xBBBB, cpu->registers[spsr_svc]);

  cpu->set_mode(ARM7TDMI_CPU_MODE_FIQ, false);
  ASSERT_EQ(0xAAAA, cpu->read_spsr());
  ASSERT_EQ(0xAAAA, cpu->registers[spsr_fiq]);
}

TEST_F(cpu_test, cpsr_read_write_should_modify_correct_physical_register) {
  cpu->set_mode(ARM7TDMI_CPU_MODE_SVC, true);
  cpu->write_cpsr(777);
  ASSERT_EQ(777, cpu->read_active_register(cpsr));
  ASSERT_EQ(777, cpu->registers[cpsr]);

  cpu->write_active_register(cpsr, 42);
  ASSERT_EQ(42, cpu->read_cpsr());
  ASSERT_EQ(42, cpu->registers[cpsr]);
}

TEST_F(cpu_test, checks_if_the_entire_chunk_of_registers_are_equal) {
  u32 expected[ARM7TDMI_CPU_REGISTERS_TOTAL_REAL + 1];
  // std::memset(expected, 0, sizeof(expected));

  ARM7TDMI_CPU_REGISTERS_CREATE_STUB(
      expected, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115,
      116, 117, 118, 119, 26, 27, 28, 29, 30, 31, 32, (u32)-34, 65, 66,
      (u32)-68, 82, 83, (u32)-85, 48, 49, (u32)-51, 99, 100, (u32)-102,
      (u32)-119);

  u32 j = 0;
  for (auto mode : (u32[]){ARM7TDMI_CPU_MODE_USR, ARM7TDMI_CPU_MODE_FIQ,
                           ARM7TDMI_CPU_MODE_IRQ, ARM7TDMI_CPU_MODE_SVC,
                           ARM7TDMI_CPU_MODE_ABT, ARM7TDMI_CPU_MODE_UND,
                           ARM7TDMI_CPU_MODE_SYS}) {

    cpu->set_mode(mode, false);

    for (auto b : (u32[]){ARM7TDMI_CPU_REGISTERS_USR}) {
      cpu->write_active_register(b, ++j);
    }

    if (mode == ARM7TDMI_CPU_MODE_USR || mode == ARM7TDMI_CPU_MODE_SYS)
      continue;

    cpu->write_spsr(-j);

    auto activ = cpu->REGISTERS_LUT[cpu->get_idx_registers_lut_by_mode(mode)];
    ASSERT_EQ(expected[activ[SPSR]], cpu->read_spsr());
  }
  equals_registers(expected);
}
