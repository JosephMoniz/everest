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
class ZeroVal<int16_t> final : public DefaultZeroVal<int16_t> {};

template <>
class Semigroup<int16_t> final : public DefaultSemigroup<int16_t> {};

template <>
class Monoid<int16_t> final : public DefaultMonoid<int16_t> {};

template <>
class Subtractable<int16_t> final : public DefaultSubtract<int16_t> {};

template <>
class Multipliable<int16_t> final : public DefaultMultipliable<int16_t> {};

template <>
class Dividable<int16_t> final : public DefaultDividable<int16_t> {};

template <>
class Modulus<int16_t> final : public DefaultModulus<int16_t> {};

template <>
class Negation<int16_t> final : public DefaultNegation<int16_t> {};

template <>
class Bounded<int16_t> final : public DefaultBounded<int16_t> {};

template <>
class Eq<int16_t> final : public DefaultEq<int16_t> {};

template <>
class SquareRoot<int16_t> final : public DefaultSquareRoot<int16_t> {};

bool Equals(int16_t lhs, int16_t rhs) noexcept {
  return Eq<int16_t>::Equals(lhs, rhs);
}

Predicate<int16_t> Equals(int16_t lhs) noexcept {
  return [=](int16_t rhs) {
    return Eq<int16_t>::Equals(lhs, rhs);
  };
}

template <>
class Ord<int16_t> final : public DefaultOrd<int16_t> {};

template <>
class BitAnd<int16_t> final : public DefaultAnd<int16_t> {};

template <>
class BitOr<int16_t> final : public DefaultOr<int16_t> {};

template <>
class BitXor<int16_t> final : public DefaultXor<int16_t> {};

template<>
class Hashable<int16_t> final : public DefaultHashable<int16_t> {};


template <>
class OneVal<int16_t> final {
public:

  static constexpr bool exists = true;

  static constexpr int16_t One() noexcept { return 1; }

};

template<>
class Fundamental<int16_t> final {
public:
  static constexpr bool exists = true;
};

template<>
class Copyable<int16_t> final {
public:

  static constexpr bool exists = true;

  static int16_t Copy(int16_t n) noexcept {
    return n;
  }

};

template <>
class Shows<int16_t> final {
public:

  static constexpr bool exists = true;

  static size_t NumDigits(int16_t number) noexcept {
    if (number < -10000) return 6;
    if (number < -1000) return 5;
    if (number < -100) return 4;
    if (number < -10) return 3;
    if (number < 0) return 2;
    if (number < 10) return 1;
    if (number < 100) return 2;
    if (number < 1000) return 3;
    if (number < 10000) return 4;
    return 5;
  }

  static String Show(int16_t number) noexcept {
    auto signSpace = number < 0 ? 1 : 0;
    auto size      = NumDigits(number);
    auto offset    = size;
    auto capacity  = size + 1;
    auto memory    = MutableMemory<char>(capacity);
    auto pointer   = MutablePointer(memory);
    auto mask      = number >> 15;
    auto unsignedN = (mask ^ number) - mask;
    for (size_t i = size; i - signSpace; i--) {
      pointer[--offset] = (char) (unsignedN % 10) + '0';
      unsignedN /= 10;
    };
    if (signSpace) {
      pointer[0] = '-';
    }
    pointer[size] = '\0';
    return String(std::move(memory), size, capacity);
  }

};

template<>
class Hexable<int16_t> final {
public:

  static constexpr bool exists = true;

  static String ToHex(int16_t value) noexcept {
    return ToHexFromLittleEndianBytePointer((unsigned char*) &value, sizeof(int16_t));
  }

};

}

