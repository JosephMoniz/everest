#ifndef TRAITOROUS_TYPES_UINT8
#define TRAITOROUS_TYPES_UINT8 1

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
struct zero_val<uint8_t> : public default_zero_val<uint8_t> {};

template <>
struct semigroup<uint8_t> : public default_semigroup<uint8_t> {};

template <>
struct monoid<uint8_t> : public default_monoid<uint8_t> {};

template <>
struct subtractable<uint8_t> : public default_subtract<uint8_t> {};

template <>
struct multipliable<uint8_t> : public default_multipliable<uint8_t> {};

template <>
struct dividable<uint8_t> : public default_dividable<uint8_t> {};

template <>
struct modulus<uint8_t> : public default_modulus<uint8_t> {};

template <>
struct bounded<uint8_t> : public default_bounded<uint8_t> {};

template <>
struct eq<uint8_t> : public default_eq<uint8_t> {};

constexpr inline bool equals(uint8_t lhs, uint8_t rhs) noexcept {
  return eq<uint8_t>::equals(lhs, rhs);
}

inline std::function<bool(uint8_t)> equals(uint8_t lhs) noexcept {
  return [&](uint8_t rhs) {
    return eq<uint8_t>::equals(lhs, rhs);
  };
}

template <>
struct ord<uint8_t> : public default_ord<uint8_t> {};

template <>
struct bit_and<uint8_t> : public default_and<uint8_t> {};

template <>
struct bit_or<uint8_t> : public default_or<uint8_t> {};

template <>
struct bit_xor<uint8_t> : public default_xor<uint8_t> {};

template <>
struct one_val<uint8_t> {
  static constexpr uint8_t one() noexcept { return 1; }
  static constexpr bool exists = true;
};

template <>
struct shows<uint8_t> {
  static const std::string show(uint8_t n) noexcept { return std::to_string(n); }
  static constexpr bool exists = true;
};

}

#endif
