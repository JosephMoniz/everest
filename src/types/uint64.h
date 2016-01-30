#ifndef TRAITOROUS_TYPES_UINT64
#define TRAITOROUS_TYPES_UINT64 1

#include <cstdint>
#include <string>

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
class ZeroVal<uint64_t> : public DefaultZeroVal<uint64_t> {};

template <>
class Semigroup<uint64_t> : public DefaultSemigroup<uint64_t> {};

template <>
class Monoid<uint64_t> : public DefaultMonoid<uint64_t> {};

template <>
class Subtractable<uint64_t> : public DefaultSubtract<uint64_t> {};

template <>
class Multipliable<uint64_t> : public DefaultMultipliable<uint64_t> {};

template <>
class Dividable<uint64_t> : public DefaultDividable<uint64_t> {};

template <>
class Modulus<uint64_t> : public DefaultModulus<uint64_t> {};

template <>
class Negation<uint64_t> : public DefaultNegation<uint64_t> {};

template <>
class Bounded<uint64_t> : public DefaultBounded<uint64_t> {};

template <>
class Eq<uint64_t> : public DefaultEq<uint64_t> {};

constexpr inline bool Equals(uint64_t lhs, uint64_t rhs) noexcept {
  return Eq<uint64_t>::Equals(lhs, rhs);
}

inline std::function<bool(uint64_t)> Equals(uint64_t lhs) noexcept {
  return [&](uint64_t rhs) {
    return Eq<uint64_t>::Equals(lhs, rhs);
  };
}

template <>
class Ord<uint64_t> : public DefaultOrd<uint64_t> {};

template <>
class BitAnd<uint64_t> : public DefaultAnd<uint64_t> {};

template <>
class BitOr<uint64_t> : public DefaultOr<uint64_t> {};

template <>
class BitXor<uint64_t> : public DefaultXor<uint64_t> {};

template <>
class OneVal<uint64_t> {
public:

  static constexpr bool exists = true;

  static constexpr uint64_t One() noexcept { return 1; }

};

template <>
class Shows<uint64_t> {
public:

  static constexpr bool exists = true;

  static const std::string Show(uint64_t n) noexcept { return std::to_string(n); }

};

}

#endif
