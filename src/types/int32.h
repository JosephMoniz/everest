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
class ZeroVal<int32_t> : public DefaultZeroVal<int32_t> {};

template <>
class Semigroup<int32_t> : public DefaultSemigroup<int32_t> {};

template <>
class Monoid<int32_t> : public DefaultMonoid<int32_t> {};

template <>
class Subtractable<int32_t> : public DefaultSubtract<int32_t> {};

template <>
class Multipliable<int32_t> : public DefaultMultipliable<int32_t> {};

template <>
class Dividable<int32_t> : public DefaultDividable<int32_t> {};

template <>
class Modulus<int32_t> : public DefaultModulus<int32_t> {};

template <>
class Negation<int32_t> : public DefaultNegation<int32_t> {};

template <>
class Bounded<int32_t> : public DefaultBounded<int32_t> {};

template <>
class Eq<int32_t> : public DefaultEq<int32_t> {};

constexpr inline bool Equals(int32_t lhs, int32_t rhs) noexcept {
  return Eq<int32_t>::Equals(lhs, rhs);
}

inline std::function<bool(int32_t)> Equals(int32_t lhs) noexcept {
  return [&](int32_t rhs) {
    return Eq<int32_t>::Equals(lhs, rhs);
  };
}

template <>
class Ord<int32_t> : public DefaultOrd<int32_t> {};

template <>
class BitAnd<int32_t> : public DefaultAnd<int32_t> {};

template <>
class BitOr<int32_t> : public DefaultOr<int32_t> {};

template <>
class BitXor<int32_t> : public DefaultXor<int32_t> {};

template <>
class OneVal<int32_t> {
public:

  static constexpr bool exists = true;

  static constexpr int32_t One() noexcept { return 1; }

};

template <>
class Shows<int32_t> {
public:

  static constexpr bool exists = true;

  static const std::string Show(int32_t n) noexcept { return std::to_string(n); }

};

}

#endif
