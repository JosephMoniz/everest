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
#include <everest/traits/unlawful/square_root.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/bit_and.h>
#include <everest/traits/unlawful/bit_or.h>
#include <everest/traits/unlawful/bit_xor.h>
#include <everest/traits/unlawful/hashable.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>
#include <everest/memory/mutable_memory.h>
#include <everest/traits/unlawful/copyable.h>
#include <everest/traits/unlawful/fundamental.h>

namespace everest {

template <>
class ZeroVal<uint16_t> final : public DefaultZeroVal<uint16_t> {};

template <>
class Semigroup<uint16_t> final : public DefaultSemigroup<uint16_t> {};

template <>
class Monoid<uint16_t> final : public DefaultMonoid<uint16_t> {};

template <>
class Subtractable<uint16_t> final : public DefaultSubtract<uint16_t> {};

template <>
class Multipliable<uint16_t> final : public DefaultMultipliable<uint16_t> {};

template <>
class Dividable<uint16_t> final : public DefaultDividable<uint16_t> {};

template <>
class Modulus<uint16_t> final : public DefaultModulus<uint16_t> {};

template <>
class Negation<uint16_t> final : public DefaultNegation<uint16_t> {};

template <>
class Bounded<uint16_t> final : public DefaultBounded<uint16_t> {};

template <>
class Eq<uint16_t> final : public DefaultEq<uint16_t> {};

template <>
class SquareRoot<uint16_t> final : public DefaultSquareRoot<uint16_t> {};

bool Equals(uint16_t lhs, uint16_t rhs) noexcept {
  return Eq<uint16_t>::Equals(lhs, rhs);
}

Predicate<uint16_t> Equals(uint16_t lhs) noexcept {
  return [=](uint16_t rhs) {
    return Eq<uint16_t>::Equals(lhs, rhs);
  };
}

template <>
class Ord<uint16_t> final : public DefaultOrd<uint16_t> {};

template <>
class BitAnd<uint16_t> final : public DefaultAnd<uint16_t> {};

template <>
class BitOr<uint16_t> final : public DefaultOr<uint16_t> {};

template <>
class BitXor<uint16_t> final : public DefaultXor<uint16_t> {};

template<>
class Hashable<uint16_t> final : public DefaultHashable<uint16_t> {};

template <>
class OneVal<uint16_t> final {
public:

  static constexpr bool exists = true;

  static constexpr uint16_t One() noexcept { return 1; }

};

template<>
class Fundamental<uint16_t> final {
public:
  static constexpr bool exists = true;
};

template<>
class Copyable<uint16_t> final {
public:

  static constexpr bool exists = true;

  static uint16_t Copy(uint16_t n) noexcept {
    return n;
  }

};

template <>
class Shows<uint16_t> final {
public:

  static constexpr bool exists = true;

  static size_t NumDigits(uint16_t number) noexcept {
    if (number < 10u) return 1;
    if (number < 100u) return 2;
    if (number < 1000u) return 3;
    if (number < 10000u) return 4;
    return 5;
  }

  static String Show(uint16_t number) noexcept {
    auto size     = NumDigits(number);
    auto offset   = size;
    auto capacity = size + 1;
    auto memory   = MutableMemory<char>(capacity);
    auto pointer  = MutablePointer(memory);
    for (auto i = size; i; i--) {
      pointer[--offset] = (char) (number % 10) + '0';
      number /= 10;
    };
    pointer[size] = '\0';
    return String(std::move(memory), size, capacity);
  }

};

template<>
class Hexable<uint16_t> final {
public:

  static constexpr bool exists = true;

  static String ToHex(uint16_t value) noexcept {
    return ToHexFromLittleEndianBytePointer((unsigned char*) &value, sizeof(uint16_t));
  }

};

}

