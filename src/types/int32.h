#ifndef TRAITOROUS_TYPES_INT32
#define TRAITOROUS_TYPES_INT32 1

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
struct zero_val<int32_t> : public default_zero_val<int32_t> {};

template <>
struct semigroup<int32_t> : public default_semigroup<int32_t> {};

template <>
struct monoid<int32_t> : public default_monoid<int32_t> {};

template <>
struct subtractable<int32_t> : public default_subtract<int32_t> {};

template <>
struct multipliable<int32_t> : public default_multipliable<int32_t> {};

template <>
struct dividable<int32_t> : public default_dividable<int32_t> {};

template <>
struct modulus<int32_t> : public default_modulus<int32_t> {};

template <>
struct negation<int32_t> : public default_negation<int32_t> {};

template <>
struct bounded<int32_t> : public default_bounded<int32_t> {};

template <>
struct eq<int32_t> : public default_eq<int32_t> {};

constexpr inline bool equals(int32_t lhs, int32_t rhs) noexcept {
  return eq<int32_t>::equals(lhs, rhs);
}

inline std::function<bool(int32_t)> equals(int32_t lhs) noexcept {
  return [&](int32_t rhs) {
    return eq<int32_t>::equals(lhs, rhs);
  };
}

template <>
struct ord<int32_t> : public default_ord<int32_t> {};

template <>
struct bit_and<int32_t> : public default_and<int32_t> {};

template <>
struct bit_or<int32_t> : public default_or<int32_t> {};

template <>
struct bit_xor<int32_t> : public default_xor<int32_t> {};

template <>
struct one_val<int32_t> {
  static constexpr int32_t one() noexcept { return 1; }
  static constexpr bool exists = true;
};

template <>
struct shows<int32_t> {
  static const std::string show(int32_t n) noexcept { return std::to_string(n); }
  static constexpr bool exists = true;
};

}

#endif
