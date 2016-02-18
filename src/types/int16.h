#ifndef TRAITOROUS_TYPES_INT16
#define TRAITOROUS_TYPES_INT16 1

#include <cstdint>
#include <functional>

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
#include "traits/unlawful/hashable.h"
#include "functions/types.h"

namespace traitorous {

template <>
class ZeroVal<int16_t> : public DefaultZeroVal<int16_t> {};

template <>
class Semigroup<int16_t> : public DefaultSemigroup<int16_t> {};

template <>
class Monoid<int16_t> : public DefaultMonoid<int16_t> {};

template <>
class Subtractable<int16_t> : public DefaultSubtract<int16_t> {};

template <>
class Multipliable<int16_t> : public DefaultMultipliable<int16_t> {};

template <>
class Dividable<int16_t> : public DefaultDividable<int16_t> {};

template <>
class Modulus<int16_t> : public DefaultModulus<int16_t> {};

template <>
class Negation<int16_t> : public DefaultNegation<int16_t> {};

template <>
class Bounded<int16_t> : public DefaultBounded<int16_t> {};

template <>
class Eq<int16_t> : public DefaultEq<int16_t> {};

constexpr inline bool Equals(int16_t lhs, int16_t rhs) noexcept {
  return Eq<int16_t>::Equals(lhs, rhs);
}

inline Predicate<int16_t> Equals(int16_t lhs) noexcept {
  return [=](int16_t rhs) {
    return Eq<int16_t>::Equals(lhs, rhs);
  };
}

template <>
class Ord<int16_t> : public DefaultOrd<int16_t> {};

template <>
class BitAnd<int16_t> : public DefaultAnd<int16_t> {};

template <>
class BitOr<int16_t> : public DefaultOr<int16_t> {};

template <>
class BitXor<int16_t> : public DefaultXor<int16_t> {};

template<>
class Hashable<int16_t> : public DefaultHashable<int16_t> {};


template <>
class OneVal<int16_t> {
public:

  static constexpr bool exists = true;

  static constexpr int16_t One() noexcept { return 1; }

};

template <>
class Shows<int16_t> {
public:

  static constexpr bool exists = true;

  static const std::string Show(int16_t n) noexcept { return std::to_string(n); }

};

}

#endif
