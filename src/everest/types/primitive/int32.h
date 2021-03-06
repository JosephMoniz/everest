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
class ZeroVal<int32_t> final : public DefaultZeroVal<int32_t> {};

template <>
class Semigroup<int32_t> final : public DefaultSemigroup<int32_t> {};

template <>
class Monoid<int32_t> final : public DefaultMonoid<int32_t> {};

template <>
class Subtractable<int32_t> final : public DefaultSubtract<int32_t> {};

template <>
class Multipliable<int32_t> final : public DefaultMultipliable<int32_t> {};

template <>
class Dividable<int32_t> final : public DefaultDividable<int32_t> {};

template <>
class Modulus<int32_t> final : public DefaultModulus<int32_t> {};

template <>
class Negation<int32_t> final : public DefaultNegation<int32_t> {};

template <>
class Bounded<int32_t> final : public DefaultBounded<int32_t> {};

template <>
class Eq<int32_t> final : public DefaultEq<int32_t> {};

template <>
class SquareRoot<int32_t> final : public DefaultSquareRoot<int32_t> {};

bool Equals(int32_t lhs, int32_t rhs) noexcept {
  return Eq<int32_t>::Equals(lhs, rhs);
}

Predicate<int32_t> Equals(int32_t lhs) noexcept {
  return [=](int32_t rhs) {
    return Eq<int32_t>::Equals(lhs, rhs);
  };
}

template <>
class Ord<int32_t> final : public DefaultOrd<int32_t> {};

template <>
class BitAnd<int32_t> final : public DefaultAnd<int32_t> {};

template <>
class BitOr<int32_t> final : public DefaultOr<int32_t> {};

template <>
class BitXor<int32_t> final : public DefaultXor<int32_t> {};

template<>
class Hashable<int32_t> final : public DefaultHashable<int32_t> {};

template <>
class OneVal<int32_t> final {
public:

  static constexpr bool exists = true;

  static constexpr int32_t One() noexcept { return 1; }

};

template<>
class Fundamental<int32_t> final {
public:
  static constexpr bool exists = true;
};

template<>
class Copyable<int32_t> final {
public:

  static constexpr bool exists = true;

  static int32_t Copy(int32_t n) noexcept {
    return n;
  }

};

template <>
class Shows<int32_t> final {
public:

  static constexpr bool exists = true;

  static size_t NumDigits(int32_t number) noexcept {
    if (number < -1000000000) return 11;
    if (number < -100000000) return 10;
    if (number < -10000000) return 9;
    if (number < -1000000) return 8;
    if (number < -100000) return 7;
    if (number < -10000) return 6;
    if (number < -1000) return 5;
    if (number < -100) return 4;
    if (number < -10) return 3;
    if (number < 0) return 2;
    if (number < 10) return 1;
    if (number < 100) return 2;
    if (number < 1000) return 3;
    if (number < 10000) return 4;
    if (number < 100000) return 5;
    if (number < 1000000) return 6;
    if (number < 10000000) return 7;
    if (number < 100000000) return 8;
    if (number < 1000000000) return 9;
    return 10;
  }

  static String Show(int32_t number) noexcept {
    auto signSpace = number < 0 ? 1 : 0;
    auto size      = NumDigits(number);
    auto offset    = size;
    auto capacity  = size + 1;
    auto memory    = MutableMemory<char>(capacity);
    auto pointer   = memory.MutablePointer();
    auto mask      = number >> 31;
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
class Hexable<int32_t> final {
public:

  static constexpr bool exists = true;

  static String ToHex(int32_t value) noexcept {
    return ToHexFromLittleEndianBytePointer((unsigned char*) &value, sizeof(int32_t));
  }

};

}

