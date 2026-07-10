#include "neogba/types.hpp"
#include <array>
#include <cstddef>
#include <cstdio>

namespace neogba {

template <typename store_t, std::size_t max_length, typename return_t = void,
          std::size_t (*normalizer)(std::size_t idx) =
              +[](std::size_t idx) -> std::size_t { return idx; }>
class lut {
protected:
  const std::size_t MAX_MASK{max_length - 1};
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
    std::size_t a_bit_mask{1u << bit++};
    if (!is_mask_one)
      return fill_recursive(base, mask, what, high, bit);

    // caso recursivo branch
    bool is_base_zero{((base) & (a_bit_mask)) == 0};
    u8 count{0};

    if (!(high ^ is_base_zero)) {
      count = 1;
      base ^= a_bit_mask;
      put(base, what);
    }

    return count + fill_recursive(base, mask, what, true, bit) +
           fill_recursive(base, mask, what, false, bit);
  }

public:
  constexpr std::size_t norm_idx(std::size_t idx) const { return normalizer(idx) & MAX_MASK; }

  constexpr std::array<store_t, max_length> get_wrapper() const { return storage; }
  constexpr store_t get(std::size_t idx) const { return storage[norm_idx(idx)]; }
  constexpr return_t run(std::size_t idx, auto&&... params) const { return get(idx)(params...); }

  constexpr void fill(store_t what) { storage.fill(what); }
  constexpr void fill(std::size_t idx, store_t what) { storage[norm_idx(idx)] = what; }
  constexpr std::size_t fill(std::size_t idx_base, std::size_t mask, store_t what) {
    std::size_t b{norm_idx(idx_base)}, m{norm_idx(mask)};
    put(b, what);
    return 1 + fill_recursive(b, m, what, true) + fill_recursive(b, m, what, false);
  }
  constexpr std::size_t fill_except(std::size_t idx_base, std::size_t mask, store_t what) {
    std::size_t b{norm_idx(idx_base)}, m{norm_idx(mask)};
    return fill_recursive(b, m, what, true) + fill_recursive(b, m, what, false);
  }
  constexpr std::size_t fill_range(std::size_t from, std::size_t to, store_t what) {
    std::size_t f{norm_idx(from)}, t{norm_idx(to)}, n{};

    for (auto i{f}; i < t; ++i) {
      put(i, what);
      n++;
    }

    return n;
  }

  constexpr std::size_t length() const { return max_length; };
  constexpr std::size_t count_stored(store_t what) const {
    std::size_t n{};
    for (const auto& elem : storage)
      if (elem == what)
        n++;
    return n;
  }
};

} // namespace neogba
