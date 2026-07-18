#pragma once
#include "neogba/arm7tdmi/cpu.hpp"
#include "neogba/arm7tdmi/isa.hpp"
#include "neogba/structs/lut.hpp"
#include "neogba/types.hpp"
#include <utility>

namespace neogba {

struct arm_operand2_result {
  u32 result;
  u8 carry_out; // 1 or 0
  u8 carry_in;  // 1 or 0
};

template <bool i, bool rotate_zero = false, bool bit4 = false, bool shift_zero = false,
          arm_shift_type shift_type = arm_shift_type::LSL>
arm_operand2_result arm_operand2_generator(arm7tdmi& cpu, u32 inst) {
  auto carry_out{static_cast<u8>((cpu.read_cpsr() & arm7tdmi::C) >> arm7tdmi::C_SHIFT)};
  auto carry_in{carry_out};

  u32 result;

  if constexpr (i) {
    auto imm{ISA_ARM_FSR_OPERAND2_IMM::get(inst)};

    if constexpr (rotate_zero) {
      auto rotate{2u * ISA_ARM_FSR_OPERAND2_ROTATE::get(inst)};
      carry_out = (imm >> (rotate - 1)) & 1;
      result = (imm >> rotate) | (imm << (32 - rotate));
    } else {
      result = imm;
    }
  } else {

    auto rm_idx{ISA_ARM_FSR_OPERAND2_RM::get(inst)};
    auto rm{cpu.read_active_register(rm_idx)};
    // auto shift_type{ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(inst)};
    // auto four{ISA_ARM_FSR_OPERAND2_4::get(inst)};

    constexpr bool is_special_case{!bit4 && shift_zero};

    if constexpr (is_special_case) {
      if constexpr (shift_type == arm_shift_type::LSL) {
        result = rm;

      } else if constexpr (shift_type == arm_shift_type::LSR) {
        // shift_amount = 32; // LSR #0 = LSR #32
        result = 0;
        carry_out = (rm >> 31) & 1;

      } else if constexpr (shift_type == arm_shift_type::ASR) {
        // shift_amount = 32; //  ASR #0
        result = static_cast<u32>(static_cast<i32>(rm) >> 31);
        carry_out = (rm >> 31) & 1;

      } else if constexpr (shift_type == arm_shift_type::ROR) {
        // RRX: Rotate 1 bit and include Cin.
        result = ((cpu.read_cpsr() & arm7tdmi::C) << (31 - arm7tdmi::C_SHIFT)) | (rm >> 1);
        carry_out = rm & 1;
      }
    } else {

      // esto no importa al caso especial complemente, por lo que lo podemos atrasar hasta aquí.
      u32 shift_amount;
      if constexpr (bit4) {
        shift_amount = cpu.read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst)) & 0xff;
      } else {
        shift_amount = ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst);
      }

      // Esto posiblemente dé para otra lut y utilizar karnaugh para simplificar saltos ifs, pero de
      // momento hay que tener algo funcando, pero me ha jodido el carry. Creo que es una idea muy
      // certera.
      if constexpr (shift_type == arm_shift_type::LSL) {
        if (shift_amount == 0) {
          result = rm;
        } else if (shift_amount < 32) {
          carry_out = (rm >> (32 - shift_amount)) & 1;
          result = rm << shift_amount;
        } else if (shift_amount == 32) {
          carry_out = rm & 1;
          result = 0;
        } else {
          carry_out = 0;
          result = 0;
        }

      } else if constexpr (shift_type == arm_shift_type::LSR) {
        if (shift_amount == 0) {
          result = rm;
        } else if (shift_amount < 32) {
          result = rm >> shift_amount;
          carry_out = (rm >> (shift_amount - 1)) & 1;
        } else if (shift_amount == 32) {
          result = 0;
          carry_out = (rm >> 31) & 1;
        } else {
          result = 0;
          carry_out = 0;
        }

      } else if constexpr (shift_type == arm_shift_type::ASR) {
        if (shift_amount == 0) {
          result = rm;
        } else if (shift_amount < 32) {
          result = static_cast<u32>(static_cast<i32>(rm) >> shift_amount);
          carry_out = (rm >> (shift_amount - 1)) & 1;
        } else { // shift_amount >= 32
          result = static_cast<u32>(static_cast<i32>(rm) >> 31);
          carry_out = (rm >> 31) & 1;
        }

      } else if constexpr (shift_type == arm_shift_type::ROR) {
        if (shift_amount == 0) {
          result = rm;
        } else {
          auto masked_shift{shift_amount & 0x1f};
          if (masked_shift == 0) {
            result = rm;
            carry_out = (rm >> 31) & 1;
          } else {
            result = (rm >> masked_shift) | (rm << (32 - masked_shift));
            carry_out = (rm >> (masked_shift - 1)) & 1;
          }
        }
      }
    }
  }

  return {result, carry_out, carry_in};
}

inline constexpr auto arm_operand2_lut = []() consteval {
  lut<arm_operand2_result (*)(arm7tdmi&, u32), 14, arm_operand2_result,
      +[](std::size_t idx) -> std::size_t {
        auto i{static_cast<bool>(ISA_ARM_FSR_I::get_raw(idx))};
        auto b4{static_cast<bool>(ISA_ARM_FSR_OPERAND2_4::get_raw(idx))};
        auto t1{static_cast<bool>(ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(idx) & 0x1)};
        auto t0{static_cast<bool>((ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(idx) & 0x2) >> 1)};
        auto s_not_0{(ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(idx)) != 0};
        auto r_not_0{(ISA_ARM_FSR_OPERAND2_ROTATE::get(idx)) != 0};

        auto n3{static_cast<u8>(i | b4)};
        auto n2{static_cast<u8>(i | (!b4 & s_not_0))};
        auto n1{static_cast<u8>(!i & t1)};
        auto n0{static_cast<u8>(((r_not_0) & (i)) | (t0 & !i))};

        return (n3 << 3) | (n2 << 2) | (n1 << 1) | n0;
      }>
      table;

  table.put_raw(0b0000, arm_operand2_generator<false, false, false, true, arm_shift_type::LSL>);
  table.put_raw(0b0001, arm_operand2_generator<false, false, false, true, arm_shift_type::LSR>);
  table.put_raw(0b0010, arm_operand2_generator<false, false, false, true, arm_shift_type::ASR>);
  table.put_raw(0b0011, arm_operand2_generator<false, false, false, true, arm_shift_type::ROR>);
  table.put_raw(0b0100, arm_operand2_generator<false, false, false, false, arm_shift_type::LSL>);
  table.put_raw(0b0101, arm_operand2_generator<false, false, false, false, arm_shift_type::LSR>);
  table.put_raw(0b0110, arm_operand2_generator<false, false, false, false, arm_shift_type::ASR>);
  table.put_raw(0b0111, arm_operand2_generator<false, false, false, false, arm_shift_type::ROR>);
  table.put_raw(0b1000, arm_operand2_generator<false, false, true, false, arm_shift_type::LSL>);
  table.put_raw(0b1001, arm_operand2_generator<false, false, true, false, arm_shift_type::LSR>);
  table.put_raw(0b1010, arm_operand2_generator<false, false, true, false, arm_shift_type::ASR>);
  table.put_raw(0b1011, arm_operand2_generator<false, false, true, false, arm_shift_type::ROR>);
  table.put_raw(0b1100, arm_operand2_generator<true, true>);
  table.put_raw(0b1101, arm_operand2_generator<true, false>);

  return table;
}();

/**
 * @brief Plantilla generadora de operaciones de procesamiento de datos y transferencia FSR para el
 * modo ARM del procesador ARM7TDMI.
 *
 * El diseño de esta plantilla reside en que sea lo más precomputable en tiempo de compilación para
 * evitar el riesgo de emisiones en ordenadores modernos y predicción de saltos condicionales. De
 * forma que será necesario crear variantes de la misma función activando y desactivando parámetros.
 *
 * Esto es a propósito para poder facilitar la implementación y organización dentro de una tabla
 * lut u otras estructuras afines.
 *
 * @param opcode Enumerado de operación de procesamiento a realizar.
 * @param s Bit que indica si activar efectos de escritura sobre el registro de banderas.
 * @param rd_pc Boleano que indica si el destino es PC.
 * @param cpu Objeto por referencia de contexto de la CPU.
 * @param inst Instrucción máquina a ejecutar por valor.
 */
template <arm_fsr_opcode opcode, bool s = false, bool rd_pc = false>
void arm_fsr_generator(arm7tdmi& cpu, u32 inst) {

  // Meta template variables
  constexpr auto is_logical{opcode == arm_fsr_opcode::AND || opcode == arm_fsr_opcode::EOR ||
                            opcode == arm_fsr_opcode::TST || opcode == arm_fsr_opcode::TEQ ||
                            opcode == arm_fsr_opcode::ORR || opcode == arm_fsr_opcode::MOV ||
                            opcode == arm_fsr_opcode::BIC || opcode == arm_fsr_opcode::MVN};
  constexpr auto can_write_rd{!(opcode == arm_fsr_opcode::TST || opcode == arm_fsr_opcode::TEQ ||
                                opcode == arm_fsr_opcode::CMP || opcode == arm_fsr_opcode::CMN)};
  constexpr auto is_inverted_sub{opcode == arm_fsr_opcode::RSB || opcode == arm_fsr_opcode::RSC};

  // Nota!!! read(r15) ->  PC + 8

  // Retrieve values
  u8 rd_idx;
  u32 op1;
  u64 res;
  auto rn_idx{ISA_ARM_FSR_RN::get(inst)};

  if constexpr (rd_pc)
    rd_idx = 0xfu;
  else
    rd_idx = ISA_ARM_FSR_RD::get(inst);

  if constexpr (opcode != arm_fsr_opcode::MOV && opcode != arm_fsr_opcode::MVN)
    op1 = cpu.read_active_register(rn_idx);

  auto op2{arm_operand2_lut.run(inst, cpu, inst)};

  if constexpr (is_inverted_sub)
    std::swap(op1, op2.result);

  // Perform operation
  if constexpr (opcode == arm_fsr_opcode::AND || opcode == arm_fsr_opcode::TST)
    res = op1 & op2.result;
  else if constexpr (opcode == arm_fsr_opcode::EOR || opcode == arm_fsr_opcode::TEQ)
    res = op1 ^ op2.result;
  else if constexpr (opcode == arm_fsr_opcode::SUB || opcode == arm_fsr_opcode::CMP ||
                     opcode == arm_fsr_opcode::RSB)
    res = static_cast<u64>(op1) - op2.result;
  else if constexpr (opcode == arm_fsr_opcode::ADD || opcode == arm_fsr_opcode::CMN)
    res = static_cast<u64>(op1) + op2.result;
  else if constexpr (opcode == arm_fsr_opcode::ADC)
    res = static_cast<u64>(op1) + op2.result + op2.carry_in;
  else if constexpr (opcode == arm_fsr_opcode::SBC || opcode == arm_fsr_opcode::RSC)
    res = static_cast<u64>(op1) - op2.result + op2.carry_in - 1;
  else if constexpr (opcode == arm_fsr_opcode::ORR)
    res = op1 | op2.result;
  else if constexpr (opcode == arm_fsr_opcode::MOV)
    res = op2.result;
  else if constexpr (opcode == arm_fsr_opcode::BIC)
    res = op1 & ~op2.result;
  else if constexpr (opcode == arm_fsr_opcode::MVN)
    res = ~op2.result;

  // write back the result
  auto res32{static_cast<u32>(res)};
  if constexpr (can_write_rd)
    cpu.write_active_register(rd_idx, res32);

  // Side effects
  if constexpr (s) {
    if constexpr (rd_pc) {
      cpu.write_cpsr(cpu.read_spsr());

    } else {

      // common
      auto z{static_cast<u32>(res32 == 0) << arm7tdmi::Z_SHIFT}; // (res32 == 0) -> true -> 0x0...01
      u32 n{res32 & 0x80000000}; // N ya está en el bit 31 -> 0 movimientos

      if constexpr (is_logical) {
        auto c{static_cast<u32>(op2.carry_out << arm7tdmi::C_SHIFT)}; // op2.carry_out es 0 o 1.

        // meter V aquí = !necesario -> no está afectado.
        // set_cpsr(mask, values) sobrescribe solo estos `mask`
        cpu.set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C, z | n | c);
      } else {

        // another meta template info
        constexpr auto is_sum{opcode == arm_fsr_opcode::ADD || opcode == arm_fsr_opcode::ADC ||
                              opcode == arm_fsr_opcode::CMN};

        // (res >> 32) & 1 es 1 o 0.
        auto c{static_cast<u32>(res >> 32)};
        auto v{~(op1 ^ op2.result)};

        if constexpr (not is_sum) {
          c = !c;
          v = ~v;
        }

        // Mover lo necesario!
        c = (c & 1) << arm7tdmi::C_SHIFT;
        // movemos lo justo el bit 31 resultante a la posición de V.
        v = (v & (op1 ^ res32) & 0x80000000) >> (31 - arm7tdmi::V_SHIFT);

        cpu.set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C | arm7tdmi::V, z | n | c | v);
      }
    }
  }
}

inline constexpr auto arm_EOR{arm_fsr_generator<arm_fsr_opcode::EOR>};
inline constexpr auto arm_AND{arm_fsr_generator<arm_fsr_opcode::AND>};
inline constexpr auto arm_SUB{arm_fsr_generator<arm_fsr_opcode::SUB>};
inline constexpr auto arm_RSB{arm_fsr_generator<arm_fsr_opcode::RSB>};
inline constexpr auto arm_ADD{arm_fsr_generator<arm_fsr_opcode::ADD>};
inline constexpr auto arm_ADC{arm_fsr_generator<arm_fsr_opcode::ADC>};
inline constexpr auto arm_SBC{arm_fsr_generator<arm_fsr_opcode::SBC>};
inline constexpr auto arm_RSC{arm_fsr_generator<arm_fsr_opcode::RSC>};
inline constexpr auto arm_TST{arm_fsr_generator<arm_fsr_opcode::TST>};
inline constexpr auto arm_TEQ{arm_fsr_generator<arm_fsr_opcode::TEQ>};
inline constexpr auto arm_CMP{arm_fsr_generator<arm_fsr_opcode::CMP>};
inline constexpr auto arm_CMN{arm_fsr_generator<arm_fsr_opcode::CMN>};
inline constexpr auto arm_ORR{arm_fsr_generator<arm_fsr_opcode::ORR>};
inline constexpr auto arm_MOV{arm_fsr_generator<arm_fsr_opcode::MOV>};
inline constexpr auto arm_BIC{arm_fsr_generator<arm_fsr_opcode::BIC>};
inline constexpr auto arm_MVN{arm_fsr_generator<arm_fsr_opcode::MVN>};

} // namespace neogba
