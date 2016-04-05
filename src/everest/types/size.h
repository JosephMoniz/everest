#pragma once

#include <stddef.h>
#include <everest/types/string.h>
#include <everest/memory/mutable_memory.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>
#include <everest/traits/unlawful/hashable.h>
#include <everest/traits/unlawful/bit_xor.h>
#include <everest/traits/unlawful/bit_or.h>
#include <everest/traits/unlawful/bit_and.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/bounded.h>
#include <everest/traits/unlawful/negate.h>
#include <everest/traits/unlawful/remainder.h>
#include <everest/traits/unlawful/divide.h>
#include <everest/traits/unlawful/multiply.h>
#include <everest/traits/unlawful/subtract.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

template <>
class ZeroVal<size_t> : public DefaultZeroVal<size_t> {};

template <>
class Semigroup<size_t> : public DefaultSemigroup<size_t> {};

template <>
class Monoid<size_t> : public DefaultMonoid<size_t> {};

template <>
class Subtractable<size_t> : public DefaultSubtract<size_t> {};

template <>
class Multipliable<size_t> : public DefaultMultipliable<size_t> {};

template <>
class Dividable<size_t> : public DefaultDividable<size_t> {};

template <>
class Modulus<size_t> : public DefaultModulus<size_t> {};

template <>
class Negation<size_t> : public DefaultNegation<size_t> {};

template <>
class Bounded<size_t> : public DefaultBounded<size_t> {};

template <>
class Eq<size_t> : public DefaultEq<size_t> {};

constexpr inline bool Equals(size_t lhs, size_t rhs) noexcept {
  return Eq<size_t>::Equals(lhs, rhs);
}

inline Predicate<size_t> Equals(size_t lhs) noexcept {
  return [=](size_t rhs) {
    return Eq<size_t>::Equals(lhs, rhs);
  };
}

template <>
class Ord<size_t> : public DefaultOrd<size_t> {};

template <>
class BitAnd<size_t> : public DefaultAnd<size_t> {};

template <>
class BitOr<size_t> : public DefaultOr<size_t> {};

template <>
class BitXor<size_t> : public DefaultXor<size_t> {};

template<>
class Hashable<size_t> : public DefaultHashable<size_t> {};

template <>
class OneVal<size_t> {
public:

  static constexpr bool exists = true;

  static constexpr size_t One() noexcept { return 1; }

};

// TODO: this seems pretty sketch, should ensure it aligns
//       with the correct size of the systems size_t
template <>
class Shows<size_t> {
public:

  static constexpr bool exists = true;

  static size_t NumDigits(size_t number) noexcept {
    if (number < 10u)         return 1;
    if (number < 100u)        return 2;
    if (number < 1000u)       return 3;
    if (number < 10000u)      return 4;
    if (number < 100000u)     return 5;
    if (number < 1000000u)    return 6;
    if (number < 10000000u)   return 7;
    if (number < 100000000u)  return 8;
    if (number < 1000000000u) return 9;
    return 10;
  }

  static const String Show(size_t number) noexcept {
    auto size     = NumDigits(number);
    auto offset   = size;
    auto capacity = size + 1;
    auto memory   = MutableMemory<char>(capacity);
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
