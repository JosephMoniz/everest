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
class ZeroVal<uint8_t> final : public DefaultZeroVal<uint8_t> {};

template <>
class Semigroup<uint8_t> final : public DefaultSemigroup<uint8_t> {};

template <>
class Monoid<uint8_t> final : public DefaultMonoid<uint8_t> {};

template <>
class Subtractable<uint8_t> final : public DefaultSubtract<uint8_t> {};

template <>
class Multipliable<uint8_t> final : public DefaultMultipliable<uint8_t> {};

template <>
class Dividable<uint8_t> final : public DefaultDividable<uint8_t> {};

template <>
class Modulus<uint8_t> final : public DefaultModulus<uint8_t> {};

template <>
class Negation<uint8_t> final : public DefaultNegation<uint8_t> {};

template <>
class Bounded<uint8_t> final : public DefaultBounded<uint8_t> {};

template <>
class Eq<uint8_t> final : public DefaultEq<uint8_t> {};

template <>
class SquareRoot<uint8_t> final : public DefaultSquareRoot<uint8_t> {};

constexpr inline bool Equals(uint8_t lhs, uint8_t rhs) noexcept {
  return Eq<uint8_t>::Equals(lhs, rhs);
}

inline Predicate<uint8_t> Equals(uint8_t lhs) noexcept {
  return [=](uint8_t rhs) {
    return Eq<uint8_t>::Equals(lhs, rhs);
  };
}

template <>
class Ord<uint8_t> final : public DefaultOrd<uint8_t> {};

template <>
class BitAnd<uint8_t> final : public DefaultAnd<uint8_t> {};

template <>
class BitOr<uint8_t> final : public DefaultOr<uint8_t> {};

template <>
class BitXor<uint8_t> final : public DefaultXor<uint8_t> {};

template<>
class Hashable<uint8_t> final : public DefaultHashable<uint8_t> {};

template <>
class OneVal<uint8_t> final {
public:

  static constexpr bool exists = true;

  static constexpr uint8_t One() noexcept { return 1; }

};

template<>
class Fundamental<uint8_t> final {
public:
  static constexpr bool exists = true;
};

template<>
class Copyable<uint8_t> final {
public:

  static constexpr bool exists = true;

  static uint8_t Copy(uint8_t n) noexcept {
    return n;
  }

};

template <>
class Shows<uint8_t> final {
public:

  static constexpr bool exists = true;

  static size_t NumDigits(uint8_t number) noexcept {
    if (number < 10u) return 1;
    if (number < 100u) return 2;
    return 3;
  }

  static String Show(uint8_t number) noexcept {
    auto size    = NumDigits(number);
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
class Hexable<uint8_t> final {
public:

  static constexpr bool exists = true;

  static String ToHex(uint8_t value) noexcept {
    return ToHexFromLittleEndianBytePointer((unsigned char*) &value, sizeof(uint8_t));
  }

};

}

