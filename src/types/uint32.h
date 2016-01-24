#ifndef TRAITOROUS_TYPES_UINT32
#define TRAITOROUS_TYPES_UINT32 1

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
struct zero_val<uint32_t> : public default_zero_val<uint32_t> {};

template <>
struct semigroup<uint32_t> : public default_semigroup<uint32_t> {};

template <>
struct monoid<uint32_t> : public default_monoid<uint32_t> {};

template <>
struct subtractable<uint32_t> : public default_subtract<uint32_t> {};

template <>
struct multipliable<uint32_t> : public default_multipliable<uint32_t> {};

template <>
struct dividable<uint32_t> : public default_dividable<uint32_t> {};

template <>
struct modulus<uint32_t> : public default_modulus<uint32_t> {};

template <>
struct negation<uint32_t> : public default_negation<uint32_t> {};

template <>
struct bounded<uint32_t> : public default_bounded<uint32_t> {};

template <>
struct eq<uint32_t> : public default_eq<uint32_t> {};

constexpr inline bool equals(uint32_t lhs, uint32_t rhs) noexcept {
  return eq<uint32_t>::equals(lhs, rhs);
}

inline std::function<bool(uint32_t)> equals(uint32_t lhs) noexcept {
  return [&](uint32_t rhs) {
    return eq<uint32_t>::equals(lhs, rhs);
  };
}

template <>
struct ord<uint32_t> : public default_ord<uint32_t> {};

template <>
struct bit_and<uint32_t> : public default_and<uint32_t> {};

template <>
struct bit_or<uint32_t> : public default_or<uint32_t> {};

template <>
struct bit_xor<uint32_t> : public default_xor<uint32_t> {};

template <>
struct one_val<uint32_t> {
  static constexpr uint32_t one() noexcept { return 1; }
  static constexpr bool exists = true;
};

template <>
struct shows<uint32_t> {
  static const std::string show(uint32_t n) noexcept { return std::to_string(n); }
  static constexpr bool exists = true;
};

}

#endif
