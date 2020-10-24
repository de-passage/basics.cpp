#include <cstddef>
#include <type_traits>
#include <utility>

constexpr std::size_t operator"" _z(unsigned long long n) { return n; }

constexpr static inline auto sorted =
    [](auto &&sll) -> std::remove_reference_t<decltype(sll)> && {
  sll.sort();
  return std::forward<std::remove_reference_t<decltype(sll)>>(sll);
};