#ifndef TRAITOROUS_TYPES_UINT64
#define TRAITOROUS_TYPES_UINT64 1

#include <cstdint>

#include "traits/unlawful/eq.h"
#include "traits/unlawful/ord.h"
#include "traits/unlawful/bounded.h"
#include "traits/unlawful/one.h"
#include "traits/lawful/monoid.h"
#include "traits/unlawful/subtract.h"
#include "traits/unlawful/multiply.h"
#include "traits/unlawful/divide.h"
#include "traits/unlawful/remainder.h"
#include "traits/unlawful/negate.h"
#include "traits/unlawful/bit_and.h"
#include "traits/unlawful/bit_or.h"
#include "traits/unlawful/bit_xor.h"
#include "traits/unlawful/shift_left.h"
#include "traits/unlawful/shift_right.h"
#include "traits/unlawful/show.h"

namespace traitorous {

template <>
struct zero_val<uint64_t> : public default_zero_val<uint64_t> {};

template <>
struct semigroup<uint64_t> : public default_semigroup<uint64_t> {};

template <>
struct monoid<uint64_t> : public default_monoid<uint64_t> {};

template <>
struct subtractable<uint64_t> : public default_subtract<uint64_t> {};

template <>
struct multipliable<uint64_t> : public default_multipliable<uint64_t> {};

template <>
struct dividable<uint64_t> : public default_dividable<uint64_t> {};

template <>
struct modulus<uint64_t> : public default_modulus<uint64_t> {};

template <>
struct negation<uint64_t> : public default_negation<uint64_t> {};

template <>
struct bounded<uint64_t> : public default_bounded<uint64_t> {};

template <>
struct eq<uint64_t> : public default_eq<uint64_t> {};

constexpr inline bool equals(uint64_t lhs, uint64_t rhs) noexcept {
  return eq<uint64_t>::equals(lhs, rhs);
}

inline std::function<bool(uint64_t)> equals(uint64_t lhs) noexcept {
  return [&](uint64_t rhs) {
    return eq<uint64_t>::equals(lhs, rhs);
  };
}

template <>
struct ord<uint64_t> : public default_ord<uint64_t> {};

template <>
struct bit_and<uint64_t> : public default_and<uint64_t> {};

template <>
struct bit_or<uint64_t> : public default_or<uint64_t> {};

template <>
struct bit_xor<uint64_t> : public default_xor<uint64_t> {};

template <>
struct one_val<uint64_t> {
  static constexpr uint64_t one() noexcept { return 1; }
  static constexpr bool exists = true;
};

template <>
struct shows<uint64_t> {
  static const std::string show(uint64_t n) noexcept { return std::to_string(n); }
  static constexpr bool exists = true;
};

}

#endif
