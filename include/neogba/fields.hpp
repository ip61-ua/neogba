#pragma once
#include "neogba/types.hpp"
#include <type_traits>
#include <utility>

namespace neogba {

/**
 * @brief Describes a contiguous bit field within an instruction encoding.
 *
 * Provides compile-time utilities to extract and insert a bit or bits field using a mask and shift
 * value.
 *
 * @tparam instruction_t Instruction type. `u32` for ARM. `u16` for Thumb.
 * @tparam return_t Type returned by the extracted field.
 * @tparam n_shift Least significant bit position of the field.
 * @tparam bit_mask Bit mask identifying the field.
 */
template <typename instruction_t, typename return_t, u8 n_shift, instruction_t bit_mask = 0xfu,
          typename alternative_return_t = return_t>
struct field {
  using ins_t = instruction_t;
  using ret_t = return_t;
  using alt_ret_t = alternative_return_t;
  static constexpr u8 shift{n_shift};
  static constexpr ins_t mask{bit_mask};

  /**
   * @brief Extracts the field value from an instruction.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @return Retrieved value from instruction.
   */
  [[nodiscard]] static inline constexpr ret_t get(ins_t instruction) {
    return static_cast<ret_t>(((instruction) & (mask)) >> shift);
  }

  /**
   * @brief Replaces the field value within an instruction.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @param value Raw value to set in the field.
   * @return Copy of the instruction and replaced field.
   */
  [[nodiscard]] static inline constexpr ins_t set(ins_t instruction, ret_t value) {
    return ((instruction) & (~mask)) | ((value << shift) & mask);
  }

  [[nodiscard]] static inline constexpr ins_t set(ins_t instruction, alt_ret_t value)
    requires(not std::same_as<alt_ret_t, ret_t>)
  {
    if constexpr (std::is_enum_v<alt_ret_t>) {
      return set(instruction, std::to_underlying(value));
    } else {
      return set(instruction, static_cast<ret_t>(value));
    }
  }

  /**
   * @brief Adds binary ones the field value within an instruction.
   *
   * @param value Raw value to set of the field.
   * @return That original value shifted and masked.
   */
  [[nodiscard]] static inline constexpr ins_t set_high(ret_t value) {
    return (value << shift) & mask;
  }

  [[nodiscard]] static inline constexpr ins_t set_high(alt_ret_t value)
    requires(not std::same_as<alt_ret_t, ret_t>)
  {
    if constexpr (std::is_enum_v<alt_ret_t>) {
      return set_high(std::to_underlying(value));
    } else {
      return set_high(static_cast<ret_t>(value));
    }
  }

  // operator overloading

  // get
  [[nodiscard]] static inline constexpr ret_t operator()(ins_t instruction)
    requires(not std::same_as<ins_t, ret_t> and not std::same_as<ins_t, alt_ret_t>)
  {
    return get(instruction);
  }

  // set
  [[nodiscard]] static inline constexpr ins_t operator()(ins_t instruction, ret_t value) {
    return set(instruction, value);
  }

  [[nodiscard]] static inline constexpr ins_t operator()(ins_t instruction, alt_ret_t value)
    requires(not std::same_as<alt_ret_t, ret_t>)
  {
    return set(instruction, value);
  }

  // set_high
  [[nodiscard]] static inline constexpr ins_t operator()(ret_t value) { return set_high(value); }

  [[nodiscard]] static inline constexpr ins_t operator()(alt_ret_t value)
    requires(not std::same_as<alt_ret_t, ret_t>)
  {
    return set_high(value);
  }

  // only mask
  [[nodiscard]] static inline constexpr ins_t operator()() { return mask; }
};

/**
 * @brief Convenient wrapper for fields defined by an unshifted mask.
 *
 * The supplied mask is automatically shifted by `n_shift` before creating the underlying
 * `field`.
 *
 * @tparam instruction_t Instruction type.
 * @tparam return_t Extracted value type.
 * @tparam n_shift Least significant bit position of the field.
 * @tparam base_mask Unshifted field mask.
 * @tparam alternative_return_t Alternative type to avoid writing static_cast.
 *
 * @see field
 */
template <typename instruction_t, typename return_t, u8 n_shift, instruction_t base_mask = 0xfu,
          typename alternative_return_t = return_t>
struct field_delayed
    : field<instruction_t, return_t, n_shift, (base_mask << n_shift), alternative_return_t> {};

/**
 * @brief Specialization for single-bit instruction fields.
 *
 * Provides boolean accessors and convenience operations for manipulating individual bits.
 *
 * @tparam instruction_t Instruction type.
 * @tparam n_shift Bit position.
 *
 * @see field
 */
template <typename instruction_t, u8 n_shift>
struct field_bool : field<instruction_t, bool, n_shift, (1u << n_shift)> {
  using ins_t = instruction_t;

  /**
   * @brief Returns the bit as a boolean value.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @return Retrieved boolean from instruction.
   */
  [[nodiscard]] static constexpr bool get(ins_t instruction) {
    return ((instruction)&field_bool::mask) != 0;
  }

  /**
   * @brief Returns the bit as a 8 bit unsigned value.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @return Retrieved bit as 8 bit unsigned from instruction, but masked and shifted.
   */
  [[nodiscard]] static constexpr u8 get_raw(ins_t instruction) {
    return ((instruction)&field_bool::mask) >> n_shift;
  }

  /**
   * @brief Sets or clears the bit given an instruction.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @param value Sets if `true`, clears if `false`.
   * @return Copy of the instruction with the bit changed.
   */
  [[nodiscard]] static constexpr ins_t set(ins_t instruction, bool value) {
    return ((instruction) & (~field_bool::mask)) | (value ? field_bool::mask : 0);
  }

  /**
   * @brief Clears the bit given an instruction.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @return Copy of the instruction with bit cleared.
   */
  [[nodiscard]] static constexpr ins_t set0(ins_t instruction) {
    return instruction & ~field_bool::mask;
  }

  /**
   * @brief Sets the bit given an instruction.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @return Copy of the instruction with bit set.
   */
  [[nodiscard]] static constexpr ins_t set1(ins_t instruction) {
    return instruction | field_bool::mask;
  }

  /**
   * @brief Toggles the bit given an instruction.
   *
   * toggle `true` becomes `false` and viceversa.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @return Copy of the instruction with bit toggled.
   */
  [[nodiscard]] static constexpr ins_t toggle(ins_t instruction) {
    return instruction ^ field_bool::mask;
  }

  /**
   * @brief Adds binary one in the field value within an instruction.
   *
   * @return That bit shifted and masked.
   */
  [[nodiscard]] static inline constexpr ins_t set_high() { return field_bool::mask; }

  [[nodiscard]]
  static inline constexpr ins_t operator()() {
    return set_high();
  }

  [[nodiscard]]
  static inline constexpr bool operator()(ins_t instruction) {
    return get(instruction);
  }

  [[nodiscard]]
  static inline constexpr ins_t operator()(ins_t instruction, bool value) {
    return set(instruction, value);
  }
};

/**
 * @brief Describes an instruction field split across two bit ranges.
 *
 * Some instruction encodings store a logical value in two non-contiguous bit fields. This helper
 * represents them as a single contiguous value.
 *
 * Supose that A = a2,x,a0.
 *
 * @tparam instruction_t Instruction type.
 * @tparam return_t Extracted value type.
 * @tparam n_shift Unused by this specialization's extraction logic but kept for compatibility
 * with `field`. This value represents the least significant bit position of the field a0 in out
 * example.
 * @tparam bit_mask Upper bit range.
 * @tparam bit_mask2 Lower bit range.
 * @tparam join_shift Number of bits separating both ranges.
 */
template <typename instruction_t, typename return_t, u8 n_shift, instruction_t bit_mask,
          instruction_t bit_mask2, u8 join_shift = 4>
struct field_split : field<instruction_t, return_t, n_shift, bit_mask> {
  using ret_t = return_t;
  using ins_t = instruction_t;

  static constexpr u8 join{join_shift};
  static constexpr instruction_t mask2{bit_mask2};

  /**
   * @brief Extracts the combined field value.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @return Retrieved combined value from instruction.
   */
  [[nodiscard]] static inline constexpr ret_t get(ins_t instruction) {
    return static_cast<ret_t>(((instruction & field_split::mask) >> join) | (instruction & mask2));
  }

  /**
   * @brief Stores a combined value into both bit ranges.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @param value Combined raw value to set in split fields.
   * @return Copy of the instruction and replaced field.
   */
  [[nodiscard]] static inline constexpr ins_t set(ins_t instruction, ret_t value) {
    auto val = static_cast<ins_t>(value);
    return (instruction & ~(field_split::mask | mask2)) | ((val) & (mask2)) |
           ((val << join) & field_split::mask);
  }

  /**
   * @brief Adds binary ones the field value within an instruction.
   *
   * @param value Raw value to set of the field.
   * @return That original value shifted and masked.
   */
  [[nodiscard]] static inline constexpr ins_t set_high(ret_t value) {
    return ((value) & (mask2)) | ((value << join) & field_split::mask);
  }

  // get
  [[nodiscard]] static inline constexpr ret_t operator()(ins_t instruction)
    requires(not std::same_as<ins_t, ret_t>)
  {
    return get(instruction);
  }

  // set
  [[nodiscard]] static inline constexpr ins_t operator()(ins_t instruction, ret_t value) {
    return set(instruction, value);
  }
  // set_high
  [[nodiscard]] static inline constexpr ins_t operator()(ret_t value) { return set_high(value); }

  // only mask
  [[nodiscard]] static inline constexpr ins_t operator()() { return mask2 | field_split::mask; }
};
} // namespace neogba
