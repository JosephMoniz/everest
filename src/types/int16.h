#ifndef TRAITOROUS_TYPES_INT16
#define TRAITOROUS_TYPES_INT16 1

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
struct zero_val<int16_t> : public default_zero_val<int16_t> {};

template <>
struct semigroup<int16_t> : public default_semigroup<int16_t> {};

template <>
struct monoid<int16_t> : public default_monoid<int16_t> {};

template <>
struct subtractable<int16_t> : public default_subtract<int16_t> {};

template <>
struct multipliable<int16_t> : public default_multipliable<int16_t> {};

template <>
struct dividable<int16_t> : public default_dividable<int16_t> {};

template <>
struct modulus<int16_t> : public default_modulus<int16_t> {};

template <>
struct negation<int16_t> : public default_negation<int16_t> {};

template <>
struct bounded<int16_t> : public default_bounded<int16_t> {};

template <>
struct eq<int16_t> : public default_eq<int16_t> {};

constexpr inline bool equals(int16_t lhs, int16_t rhs) noexcept {
  return eq<int16_t>::equals(lhs, rhs);
}

inline std::function<bool(int16_t)> equals(int16_t lhs) noexcept {
  return [&](int16_t rhs) {
    return eq<int16_t>::equals(lhs, rhs);
  };
}

template <>
struct ord<int16_t> : public default_ord<int16_t> {};

template <>
struct bit_and<int16_t> : public default_and<int16_t> {};

template <>
struct bit_or<int16_t> : public default_or<int16_t> {};

template <>
struct bit_xor<int16_t> : public default_xor<int16_t> {};

template <>
struct one_val<int16_t> {
  static constexpr int16_t one() noexcept { return 1; }
  static constexpr bool exists = true;
};

template <>
struct shows<int16_t> {
  static const std::string show(int16_t n) noexcept { return std::to_string(n); }
  static constexpr bool exists = true;
};

}

#endif
