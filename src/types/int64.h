#ifndef TRAITOROUS_TYPES_INT64
#define TRAITOROUS_TYPES_INT64 1

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
class ZeroVal<int64_t> : public DefaultZeroVal<int64_t> {};

template <>
class Semigroup<int64_t> : public DefaultSemigroup<int64_t> {};

template <>
class Monoid<int64_t> : public DefaultMonoid<int64_t> {};

template <>
class Subtractable<int64_t> : public DefaultSubtract<int64_t> {};

template <>
class Multipliable<int64_t> : public DefaultMultipliable<int64_t> {};

template <>
class Dividable<int64_t> : public DefaultDividable<int64_t> {};

template <>
class Modulus<int64_t> : public DefaultModulus<int64_t> {};

template <>
class Negation<int64_t> : public DefaultNegation<int64_t> {};

template <>
class Bounded<int64_t> : public DefaultBounded<int64_t> {};

template <>
class Eq<int64_t> : public DefaultEq<int64_t> {};

constexpr inline bool Equals(int64_t lhs, int64_t rhs) noexcept {
  return Eq<int64_t>::Equals(lhs, rhs);
}

inline Predicate<int64_t> Equals(int64_t lhs) noexcept {
  return [=](int64_t rhs) {
    return Eq<int64_t>::Equals(lhs, rhs);
  };
}

template <>
class Ord<int64_t> : public DefaultOrd<int64_t> {};

template <>
class BitAnd<int64_t> : public DefaultAnd<int64_t> {};

template <>
class BitOr<int64_t> : public DefaultOr<int64_t> {};

template <>
class BitXor<int64_t> : public DefaultXor<int64_t> {};

template<>
class Hashable<int64_t> : public DefaultHashable<int64_t> {};

template <>
class OneVal<int64_t> {
public:

  static constexpr bool exists = true;

  static constexpr int64_t One() noexcept { return 1; }

};

template <>
class Shows<int64_t> {
public:

  static constexpr bool exists = true;

  static const std::string Show(int64_t n) noexcept { return std::to_string(n); }

};

}

#endif
