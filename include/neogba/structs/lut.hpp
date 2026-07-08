#include "neogba/types.hpp"
#include <array>
#include <cstddef>

namespace neogba {

template <std::size_t max_length, typename store_t = void*, typename idx_t = u8,
          typename return_t = void>
class lut {
private:
  std::array<store_t, max_length> storage{};
  constexpr void put(std::size_t raw_idx, store_t what) { storage[raw_idx] = what; }
  constexpr std::size_t fill_recursive(std::size_t base, std::size_t mask, store_t what, bool high,
                                       std::size_t bit = 0) {
    // caso base
    std::size_t shifted{mask >> bit};
    if (shifted == 0)
      return 0;

    // caso recursivo no fork
    bool is_mask_one{(shifted & 0x1u) == 1};
    if (!is_mask_one)
      return fill_recursive(base, mask, what, high, ++bit);

    // caso recursivo branch
    std::size_t bit_mask{1u << bit};
    bool bit_set{(base & bit_mask) != 0};
    u8 count{static_cast<u8>(high != bit_set)};
    base ^= (static_cast<std::size_t>(count) << bit);

    ++bit;

    return count + fill_recursive(base, mask, what, true, bit) +
           fill_recursive(base, mask, what, false, bit);
  }

public:
  constexpr virtual std::size_t norm_idx(idx_t idx) const { return static_cast<std::size_t>(idx); }

  constexpr std::array<store_t, max_length> get_wrapper() const { return storage; }
  constexpr store_t get(idx_t idx) const { return storage[norm_idx(idx)]; }
  constexpr return_t run(idx_t idx, auto... params) const { return get(idx)(params...); }

  constexpr void fill(idx_t idx, store_t what) { storage[norm_idx(idx)] = what; }
  constexpr std::size_t fill(idx_t idx_base, store_t what, idx_t mask) {
    std::size_t b{norm_idx(idx_base)}, m{norm_idx(mask)};
    put(b, what);
    return 1 + fill_recursive(b, m, what, true) + fill_recursive(b, m, what, false);
  }

  constexpr std::size_t length() const { return max_length; };
  constexpr std::size_t count_stored(store_t what) const {
    std::size_t n{};
    for (auto elem : storage)
      if (elem == what)
        n++;
    return n;
  }
};

} // namespace neogba
