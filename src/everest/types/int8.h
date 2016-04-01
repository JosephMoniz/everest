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

inline Predicate<int8_t> Equals(int8_t lhs) noexcept {
  return [=](int8_t rhs) {
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

template<>
class Hashable<int8_t> : public DefaultHashable<int8_t> {};

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

  static size_t NumDigits(int8_t number) noexcept {
    if (number < -100) return 4;
    if (number < -10) return 3;
    if (number < 0) return 2;
    if (number < 10) return 1;
    if (number < 100) return 2;
    return 3;
  }

  static const String Show(int8_t number) noexcept {
    auto signSpace = number < 0 ? 1 : 0;
    auto size      = NumDigits(number);
    auto offset    = size;
    auto capacity  = size + 1;
    auto memory    = Memory<char>(capacity);
    auto pointer   = memory.MutablePointer();
    auto unsignedN = number & 0x7FFFFFFF;
    for (size_t i = size; i - signSpace; i--) {
      pointer[--offset] = (char) (unsignedN % 10) + '0';
      unsignedN /= 10;
    };
    if (signSpace) {
      pointer[0] = '-';
    }
    pointer[capacity - 1] = '\0';
    return String(std::move(memory), size);
  }

};

}

