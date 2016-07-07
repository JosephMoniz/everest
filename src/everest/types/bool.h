#pragma once

#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/hashable.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>
#include <everest/traits/unlawful/copyable.h>
#include <everest/traits/unlawful/fundamental.h>

namespace everest {

using Bool = bool;

template<>
class Eq<bool> final : public DefaultEq<bool> {};

constexpr inline bool Equals(bool lhs, bool rhs) noexcept {
  return Eq<bool>::Equals(lhs, rhs);
}

inline Function<bool, bool> Equals(bool lhs) noexcept {
  return [&](bool rhs) {
    return Eq<bool>::Equals(lhs, rhs);
  };
}

template<>
class ZeroVal<bool> final {
public:

  static constexpr bool exists = true;

  static constexpr bool Zero() noexcept {
    return false;
  }

};

template<>
class Ord<bool> final : public DefaultOrd<bool> {};

template<>
class Hashable<bool> final : public DefaultHashable<bool> {};

template<>
class Shows<bool> final {
public:

  static constexpr bool exists = true;

  static String Show(bool n) noexcept {
    return n ? String("true") : String("false");
  }

};

template<>
class Fundamental<bool> final {
public:
  static constexpr bool exists = true;
};

template<>
class Copyable<bool> final {
public:

  static constexpr bool exists = true;

  static bool Copy(bool n) noexcept {
    return n;
  }

};

template<>
class Hexable<bool> final {
public:

  static constexpr bool exists = true;

  static String ToHex(bool value) noexcept {
    return value
      ? String("0")
      : String("1");
  }

};

}

