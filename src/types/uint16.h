#ifndef TRAITOROUS_TYPES_UINT16
#define TRAITOROUS_TYPES_UINT16 1

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
class ZeroVal<uint16_t> : public DefaultZeroVal<uint16_t> {};

template <>
class Semigroup<uint16_t> : public DefaultSemigroup<uint16_t> {};

template <>
class Monoid<uint16_t> : public DefaultMonoid<uint16_t> {};

template <>
class Subtractable<uint16_t> : public DefaultSubtract<uint16_t> {};

template <>
class Multipliable<uint16_t> : public DefaultMultipliable<uint16_t> {};

template <>
class Dividable<uint16_t> : public DefaultDividable<uint16_t> {};

template <>
class Modulus<uint16_t> : public DefaultModulus<uint16_t> {};

template <>
class Negation<uint16_t> : public DefaultNegation<uint16_t> {};

template <>
class Bounded<uint16_t> : public DefaultBounded<uint16_t> {};

template <>
class Eq<uint16_t> : public DefaultEq<uint16_t> {};

constexpr inline bool Equals(uint16_t lhs, uint16_t rhs) noexcept {
  return Eq<uint16_t>::Equals(lhs, rhs);
}

inline Predicate<uint16_t> Equals(uint16_t lhs) noexcept {
  return [=](uint16_t rhs) {
    return Eq<uint16_t>::Equals(lhs, rhs);
  };
}

template <>
class Ord<uint16_t> : public DefaultOrd<uint16_t> {};

template <>
class BitAnd<uint16_t> : public DefaultAnd<uint16_t> {};

template <>
class BitOr<uint16_t> : public DefaultOr<uint16_t> {};

template <>
class BitXor<uint16_t> : public DefaultXor<uint16_t> {};

template<>
class Hashable<uint16_t> : public DefaultHashable<uint16_t> {};

template <>
class OneVal<uint16_t> {
public:

  static constexpr bool exists = true;

  static constexpr uint16_t One() noexcept { return 1; }

};

template <>
class Shows<uint16_t> {
public:

  static constexpr bool exists = true;

  static const std::string Show(uint16_t n) noexcept { return std::to_string(n); }

};

}

#endif
