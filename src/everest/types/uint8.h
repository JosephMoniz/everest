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
#include <everest/traits/unlawful/hexable.h>
#include <everest/memory/mutable_memory.h>

namespace everest {

template <>
class ZeroVal<uint8_t> : public DefaultZeroVal<uint8_t> {};

template <>
class Semigroup<uint8_t> : public DefaultSemigroup<uint8_t> {};

template <>
class Monoid<uint8_t> : public DefaultMonoid<uint8_t> {};

template <>
class Subtractable<uint8_t> : public DefaultSubtract<uint8_t> {};

template <>
class Multipliable<uint8_t> : public DefaultMultipliable<uint8_t> {};

template <>
class Dividable<uint8_t> : public DefaultDividable<uint8_t> {};

template <>
class Modulus<uint8_t> : public DefaultModulus<uint8_t> {};

template <>
class Negation<uint8_t> : public DefaultNegation<uint8_t> {};

template <>
class Bounded<uint8_t> : public DefaultBounded<uint8_t> {};

template <>
class Eq<uint8_t> : public DefaultEq<uint8_t> {};

constexpr inline bool Equals(uint8_t lhs, uint8_t rhs) noexcept {
  return Eq<uint8_t>::Equals(lhs, rhs);
}

inline Predicate<uint8_t> Equals(uint8_t lhs) noexcept {
  return [=](uint8_t rhs) {
    return Eq<uint8_t>::Equals(lhs, rhs);
  };
}

template <>
class Ord<uint8_t> : public DefaultOrd<uint8_t> {};

template <>
class BitAnd<uint8_t> : public DefaultAnd<uint8_t> {};

template <>
class BitOr<uint8_t> : public DefaultOr<uint8_t> {};

template <>
class BitXor<uint8_t> : public DefaultXor<uint8_t> {};

template<>
class Hashable<uint8_t> : public DefaultHashable<uint8_t> {};

template <>
class OneVal<uint8_t> {
public:

  static constexpr bool exists = true;

  static constexpr uint8_t One() noexcept { return 1; }

};

template <>
class Shows<uint8_t> {
public:

  static constexpr bool exists = true;

  static size_t NumDigits(uint8_t number) noexcept {
    if (number < 10u) return 1;
    if (number < 100u) return 2;
    return 3;
  }

  static const String Show(uint8_t number) noexcept {
    auto size    = NumDigits(number);
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

template<>
class Hexable<uint8_t> {
public:

  static constexpr bool exists = true;

  static String ToHex(uint8_t value) noexcept {
    return ToHexFromLittleEndianBytePointer((unsigned char*) &value, sizeof(uint8_t));
  }

};

}

