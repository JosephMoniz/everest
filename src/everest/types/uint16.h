#pragma once

#include <cstdint>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/unlawful/one.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/traits/unlawful/subtract.h>
#include <everest/traits/unlawful/multiply.h>
#include <everest/traits/unlawful/divide.h>
#include <everest/traits/unlawful/remainder.h>
#include <everest/traits/unlawful/negate.h>
#include <everest/traits/unlawful/bounded.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/bit_and.h>
#include <everest/traits/unlawful/bit_or.h>
#include <everest/traits/unlawful/bit_xor.h>
#include <everest/traits/unlawful/hashable.h>
#include <everest/traits/unlawful/show.h>
#include <everest/containers/memory.h>

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

  static size_t NumDigits(uint16_t number) noexcept {
    if (number < 10u)         return 1;
    if (number < 100u)        return 2;
    if (number < 1000u)       return 3;
    if (number < 10000u)      return 4;
    return 5;
  }

  static const String Show(uint16_t number) noexcept {
    auto size     = NumDigits(number);
    auto offset   = size;
    auto capacity = size + 1;
    auto memory   = Memory<char>(capacity);
    auto pointer  = memory.MutablePointer();
    for (auto i = size; i; i--) {
      pointer[--offset] = (char) (number % 10) + '0';
      number /= 10;
    };
    pointer[capacity - 1] = '\0';
    return String(std::move(memory), size);
  }

};

}

