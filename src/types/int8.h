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
class ZeroVal<int8_t> : public DefaultZeroVal<int8_t> {};

template <>
class Semigroup<int8_t> : public DefaultSemigroup<int8_t> {};

template <>
class Monoid<int8_t> : public DefaultMonoid<int8_t> {};

template <>
class Subtractable<int8_t> : public DefaultSubtract<int8_t> {};

template <>
class Multipliable<int8_t> : public DefaultMultipliable<int8_t> {};

template <>
class Dividable<int8_t> : public DefaultDividable<int8_t> {};

template <>
class Modulus<int8_t> : public DefaultModulus<int8_t> {};

template <>
class Negation<int8_t> : public DefaultNegation<int8_t> {};

template <>
class Bounded<int8_t> : public DefaultBounded<int8_t> {};

template <>
class Eq<int8_t> : public DefaultEq<int8_t> {};

constexpr inline bool Equals(int8_t lhs, int8_t rhs) noexcept {
  return Eq<int8_t>::Equals(lhs, rhs);
}

inline std::function<bool(int8_t)> Equals(int8_t lhs) noexcept {
  return [&](int8_t rhs) {
    return Eq<int8_t>::Equals(lhs, rhs);
  };
}

template <>
class Ord<int8_t> : public DefaultOrd<int8_t> {};

template <>
class BitAnd<int8_t> : public DefaultAnd<int8_t> {};

template <>
class BitOr<int8_t> : public DefaultOr<int8_t> {};

template <>
class BitXor<int8_t> : public DefaultXor<int8_t> {};

template <>
class OneVal<int8_t> {
public:

  static constexpr bool exists = true;

  static constexpr int8_t One() noexcept { return 1; }

};

template <>
class Shows<int8_t> {
public:

  static constexpr bool exists = true;

  static const std::string Show(int8_t n) noexcept { return std::to_string(n); }

};

}

#endif
