#ifndef TRAITOROUS_TYPES_UINT64
#define TRAITOROUS_TYPES_UINT64 1

#include <cstdint>
#include <string>
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

inline Predicate<uint64_t> Equals(uint64_t lhs) noexcept {
  return [=](uint64_t rhs) {
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

template<>
class Hashable<uint64_t> : public DefaultHashable<uint64_t> {};

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

  static size_t NumDigits(uint64_t number) noexcept {
    if (number < 10)                   return 1;
    if (number < 100)                  return 2;
    if (number < 1000)                 return 3;
    if (number < 10000)                return 4;
    if (number < 100000)               return 5;
    if (number < 1000000)              return 6;
    if (number < 10000000)             return 7;
    if (number < 100000000)            return 8;
    if (number < 1000000000)           return 9;
    if (number < 10000000000)          return 10;
    if (number < 100000000000)         return 11;
    if (number < 1000000000000)        return 12;
    if (number < 10000000000000)       return 13;
    if (number < 100000000000000)      return 14;
    if (number < 1000000000000000)     return 15;
    if (number < 10000000000000000)    return 16;
    if (number < 100000000000000000)   return 17;
    if (number < 1000000000000000000)  return 18;
    if (number < 10000000000000000000) return 19;
    return 20;
  }

  static const LocalString Show(uint64_t number) noexcept {
    auto size     = NumDigits(number);
    auto offset   = size;
    auto capacity = size + 1;
    auto memory   = LocalMemory<char>(capacity);
    auto pointer  = memory.MutablePointer();
    for (auto i = size; i; i--) {
      pointer[--offset] = (char) (number % 10) + '0';
      number /= 10;
    };
    pointer[capacity - 1] = '\0';
    return LocalString(std::move(memory), size);
  }

};

}

#endif
