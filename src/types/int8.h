#ifndef TRAITOROUS_TYPES_INT8
#define TRAITOROUS_TYPES_INT8 1

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
struct zero_val<int8_t> : public default_zero_val<int8_t> {};

template <>
struct semigroup<int8_t> : public default_semigroup<int8_t> {};

template <>
struct monoid<int8_t> : public default_monoid<int8_t> {};

template <>
struct subtractable<int8_t> : public default_subtract<int8_t> {};

template <>
struct multipliable<int8_t> : public default_multipliable<int8_t> {};

template <>
struct dividable<int8_t> : public default_dividable<int8_t> {};

template <>
struct modulus<int8_t> : public default_modulus<int8_t> {};

template <>
struct negation<int8_t> : public default_negation<int8_t> {};

template <>
struct bounded<int8_t> : public default_bounded<int8_t> {};

template <>
struct eq<int8_t> : public default_eq<int8_t> {};

constexpr inline bool equals(int8_t lhs, int8_t rhs) noexcept {
  return eq<int8_t>::equals(lhs, rhs);
}

inline std::function<bool(int8_t)> equals(int8_t lhs) noexcept {
  return [&](int8_t rhs) {
    return eq<int8_t>::equals(lhs, rhs);
  };
}

template <>
struct ord<int8_t> : public default_ord<int8_t> {};

template <>
struct bit_and<int8_t> : public default_and<int8_t> {};

template <>
struct bit_or<int8_t> : public default_or<int8_t> {};

template <>
struct bit_xor<int8_t> : public default_xor<int8_t> {};

template <>
struct one_val<int8_t> {
  static constexpr int8_t one() noexcept { return 1; }
  static constexpr bool exists = true;
};

template <>
struct shows<int8_t> {
  static const std::string show(int8_t n) noexcept { return std::to_string(n); }
  static constexpr bool exists = true;
};

}

#endif
