#include "neogba/arm7tdmi/cpu.hpp"
#include <cstring>
#include <gtest/gtest.h>
#include <memory>

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

  void equals_registers(u32 expected[]) {
    ASSERT_EQ(0, std::memcmp(expected, cpu->registers,
                             ARM7TDMI_CPU_REGISTERS_TOTAL * sizeof(u32)));

    // for (auto i = 0; i < ARM7TDMI_CPU_REGISTERS_TOTAL; i++) {
    //   std::cout << i << " " << expected[i] << " " << cpu->registers[i]
    //   <<"\n";
    //
    //    ASSERT_EQ(expected[i], cpu->registers[i]);
    // }
  }
};

} // namespace

#define NEOGBA_CPU_REGISTERS_TEST_CASE(name, mode, ...)                        \
  TEST_F(cpu_test, name) {                                                     \
    cpu->set_mode(mode);                                                       \
    ASSERT_EQ(mode, cpu->read_cpsr());                                         \
                                                                               \
    u32 expected[ARM7TDMI_CPU_REGISTERS_TOTAL_REAL];                           \
    std::memset(expected, 0, sizeof(expected));                                \
                                                                               \
    auto activ = cpu->REGISTERS_LUT[cpu->get_idx_registers_lut_by_mode(mode)]; \
                                                                               \
    for (auto a : (u32[]){__VA_ARGS__}) {                                      \
      expected[activ[a]] = a;                                                  \
      cpu->write_active_register(a, a);                                        \
                                                                               \
      ASSERT_EQ(a, cpu->read_active_register(a));                              \
    }                                                                          \
                                                                               \
    equals_registers(expected);                                                \
  }

NEOGBA_CPU_REGISTERS_TEST_CASE(
    write_read_get_idx_registers_lut_by_mode_should_be_fine_when_usr,
    ARM7TDMI_CPU_MODE_USR, r0, r2, r3, r7, r8, r9, r10, r13, r14, pc, cpsr);

NEOGBA_CPU_REGISTERS_TEST_CASE(
    write_read_get_idx_registers_lut_by_mode_should_be_fine_the_same_when_sys,
    ARM7TDMI_CPU_MODE_USR, r0, r2, r3, r7, r8, r9, r10, r13, r14, pc, cpsr);

NEOGBA_CPU_REGISTERS_TEST_CASE(
    write_read_get_idx_registers_lut_by_mode_should_be_fine_even_with_extra_when_fiq,
    ARM7TDMI_CPU_MODE_USR, r2, r3, r7, r8, r9, r12, r13, r14, pc, cpsr,
    cpsr + 1);

// crear aquí uno tal que escriba en modo 1, cambie a modo 2, escriba, y
// compare.
