#ifndef TRAITOROUS_TYPES_UINT16
#define TRAITOROUS_TYPES_UINT16 1

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
struct zero_val<uint16_t> : public default_zero_val<uint16_t> {};

template <>
struct semigroup<uint16_t> : public default_semigroup<uint16_t> {};

template <>
struct monoid<uint16_t> : public default_monoid<uint16_t> {};

template <>
struct subtractable<uint16_t> : public default_subtract<uint16_t> {};

template <>
struct multipliable<uint16_t> : public default_multipliable<uint16_t> {};

template <>
struct dividable<uint16_t> : public default_dividable<uint16_t> {};

template <>
struct modulus<uint16_t> : public default_modulus<uint16_t> {};

template <>
struct negation<uint16_t> : public default_negation<uint16_t> {};

template <>
struct bounded<uint16_t> : public default_bounded<uint16_t> {};

template <>
struct eq<uint16_t> : public default_eq<uint16_t> {};

constexpr inline bool equals(uint16_t lhs, uint16_t rhs) noexcept {
  return eq<uint16_t>::equals(lhs, rhs);
}

inline std::function<bool(uint16_t)> equals(uint16_t lhs) noexcept {
  return [&](uint16_t rhs) {
    return eq<uint16_t>::equals(lhs, rhs);
  };
}

template <>
struct ord<uint16_t> : public default_ord<uint16_t> {};

template <>
struct bit_and<uint16_t> : public default_and<uint16_t> {};

template <>
struct bit_or<uint16_t> : public default_or<uint16_t> {};

template <>
struct bit_xor<uint16_t> : public default_xor<uint16_t> {};

template <>
struct one_val<uint16_t> {
  static constexpr uint16_t one() noexcept { return 1; }
  static constexpr bool exists = true;
};

template <>
struct shows<uint16_t> {
  static const std::string show(uint16_t n) noexcept { return std::to_string(n); }
  static constexpr bool exists = true;
};

}

#endif
