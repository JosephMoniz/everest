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
class ZeroVal<uint8_t> : public DefaultZeroVal<uint8_t> {};

template <>
class Semigroup<uint8_t> : public DefaultSemigroup<uint8_t> {};

template <>
class Monoid<uint8_t> : public DefaultMonoid<uint8_t> {};

template <>
class Subtractable<uint8_t> : public DefaultSubtract<uint8_t> {};

template <>
class Multipliable<uint8_t> : public DefaultMultipliable<uint8_t> {};

template <>
class Dividable<uint8_t> : public DefaultDividable<uint8_t> {};

template <>
class Modulus<uint8_t> : public DefaultModulus<uint8_t> {};

template <>
class Negation<uint8_t> : public DefaultNegation<uint8_t> {};

template <>
class Bounded<uint8_t> : public DefaultBounded<uint8_t> {};

template <>
class Eq<uint8_t> : public DefaultEq<uint8_t> {};

constexpr inline bool Equals(uint8_t lhs, uint8_t rhs) noexcept {
  return Eq<uint8_t>::Equals(lhs, rhs);
}

inline std::function<bool(uint8_t)> Equals(uint8_t lhs) noexcept {
  return [&](uint8_t rhs) {
    return Eq<uint8_t>::Equals(lhs, rhs);
  };
}

template <>
class Ord<uint8_t> : public DefaultOrd<uint8_t> {};

template <>
class BitAnd<uint8_t> : public DefaultAnd<uint8_t> {};

template <>
class BitOr<uint8_t> : public DefaultOr<uint8_t> {};

template <>
class BitXor<uint8_t> : public DefaultXor<uint8_t> {};

template <>
class OneVal<uint8_t> {
public:

  static constexpr bool exists = true;

  static constexpr uint8_t One() noexcept { return 1; }

};

template <>
class Shows<uint8_t> {
public:

  static constexpr bool exists = true;

  static const std::string Show(uint8_t n) noexcept { return std::to_string(n); }

};

}

#endif
